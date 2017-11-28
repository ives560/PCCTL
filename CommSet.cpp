// CommSet.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "CommSet.h"
#include "SatConReadView.h"
#include "SatConWriteView.h"
#include "SatConBitShowView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "UniButton.h"
extern CUniButton m_commLed;
extern int m_para_tot_num;
extern PARAINI_INFO m_para_info[MAX_PARA_INI_NUM];
extern int TableNum;
extern PARAINI_INFO *ComReadTable[MAX_READCOM_NUM];
extern bool ChangeTable;
/////////////////////////////////////////////////////////////////////////////
// CCommSet dialog


CCommSet::CCommSet(CWnd* pParent /*=NULL*/)
	: CDialog(CCommSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommSet)
	m_baud = _T("");
	m_data = _T("");
	m_port = _T("");
	m_stop = _T("");
	//}}AFX_DATA_INIT
	memset(TxBuffer,0,255*sizeof(BUFFER_STRUCT));
	RxIndex=0;
	TxIndex=0;
	sendval=0;
	sendsum=0;
	m_ComOpened=false;
	RxRWflag=FALSE;
	TxRWflag=FALSE;
	CommState=0;
	TimeOut=0;
	Rxcase=0;
	pReadView=0;
	pWriteView=0;
	pBitView=0;

	refreshcount=0;
	timesum=0;
}


void CCommSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommSet)
	DDX_Control(pDX, IDC_PARITY_COMBO, m_parity);
	DDX_CBString(pDX, IDC_BAUD_COMBO, m_baud);
	DDX_CBString(pDX, IDC_DATA_COMBO, m_data);
	DDX_CBString(pDX, IDC_PORT_COMBO, m_port);
	DDX_CBString(pDX, IDC_STOP_COMBO, m_stop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommSet, CDialog)
	//{{AFX_MSG_MAP(CCommSet)
	ON_WM_TIMER()
	ON_MESSAGE(WM_COMM_RXCHAR, OnComm)
	ON_CBN_SELCHANGE(IDC_PARITY_COMBO, OnSelchangeParityCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommSet message handlers

BOOL CCommSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_pMainFram = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	// TODO: Add extra initialization here
//	m_port="1";
//	m_baud="19200";
	int i=0;
	switch(parity)
	{
		case 'N': i=0; break;
		case 'O': i=1; break;
		case 'E': i=2; break;
	}
	m_parity.SetCurSel(i);
//	parity='N';
//	m_data="8";
//	m_stop="1";
	UpdateData(FALSE);
	InitComm();
//	SetTimer(4,1000,NULL);//刷新次数定时器
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
bool CCommSet::InitComm(void)
{
	UpdateData(TRUE);
	int port=atoi(m_port); int baud=atoi(m_baud);
	int data=atoi(m_data); int stop=atoi(m_stop);
	
	if (m_SerialPort.InitPort(this,port,baud,parity,data,stop,EV_RXFLAG | EV_RXCHAR,512))
	{
		m_SerialPort.StartMonitoring();   //启动串口监视线程
		m_ComOpened=true;     //COM1打开
		SetTimer(1,1,NULL);  //启动定时器，1mm后发送数据
		return true;
	}
	else  //初始化不成功，则显示提示信息
	{
		CString strTemp;
		strTemp.Format("COM%d 没有发现，或被其它设备占用",port);
		AfxMessageBox(strTemp);
		return false;
	}
}
void CCommSet::CloseComm()
{
	m_ComOpened=false;
	KillTimer(1);
	KillTimer(2);
	m_SerialPort.ClosePort();
	CommState=0x00;
	RxIndex=0;
	Rxcase=0;
	m_commLed.m_nColor=RGB(255,0,0);//状态灯红色
	m_commLed.Invalidate();
}
void CCommSet::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
		case 1:		//发送接收定时器
		{
			KillTimer(1);
			if(m_ComOpened)//串口打开
			{
				if(!(CommState&0x01))		//串口状态灯0x01发送状态
				{
					m_commLed.m_nColor=RGB(255,255,0);
					m_commLed.Invalidate();
					CommState=0x01;
					TimeOut=0;		//超时次数
				}
				if(0==sendval)		
				{
					if(TRUE==ChangeTable)		//当前页是否改变
					{
						CSatConApp *app=(CSatConApp *)AfxGetApp();
						app->SelectReadableVal();
						app->BasisAddressSortTable();
						ChangeTable=FALSE;
					}
				}
				if(TxIndex>0)		//首先判断写缓存区中是否有数据
				{
					TxRWflag=true;
					WriteDataTimer();
				}
				else		//读
				{
					TxRWflag=false;
					ReadDataTimer();
				}
				SetTimer(2,300,NULL);		//启动超时定时器
			}
		}break;
		case 2:		//超时定时器
		{
			TimeOut++;
			if(TimeOut>5)
				CommState=0x00; //改变状态灯
			KillTimer(3);
			SetTimer(1,1,NULL);
		}break;
		case 3:
		{
			KillTimer(3);
			RxIndex=0;
			SetTimer(1,1,NULL);
		}
		break;
		case 4:	//刷新次数测试
		{
			timesum=refreshcount;
			refreshcount=0;
		}
		break;
		
	}
	CDialog::OnTimer(nIDEvent);
}
void CCommSet::ReadDataTimer()
{
	sendsum=1;

    while(1)	
	{
		if((sendval+sendsum)<TableNum)
		{
			if(ComReadTable[sendval+sendsum]->address==(ComReadTable[sendval+sendsum-1]->address+1))
				sendsum++;
			else
				break;
		}
		else
			break;
	}
	RxIndex=0; //接收字符数清零
	SendReadOrder(0x01,0x03,ComReadTable[sendval]->address,sendsum);//读保存寄存器
}
void CCommSet::WriteDataTimer()
{
	TxIndex--;
	SendWriteOrder(TxBuffer[TxIndex].TxAddss,TxBuffer[TxIndex].TxData);

}
LONG CCommSet::OnComm(WPARAM ch, LPARAM port)
{
	KillTimer(3);//字节超时定时器
	RxBuffer[RxIndex]=ch;
	RxIndex++;
	switch(Rxcase)
	{
		case 0:
			{
				if(ch==0x01)
					Rxcase=1;
				else
					RxIndex=0;

			}break;
		case 1:
			{
				if(ch==0x03||ch==0x04)
					Rxcase=2;
				else if(ch==0x10)
					Rxcase=3;
				else
				{
					RxIndex=0;
					Rxcase=0;
				}
			}break;
		case 2://接收读命令数据
			{
				if((RxIndex==(5+RxBuffer[2]))&&(TxRWflag==FALSE))//读命令接收到返回值
				{
					KillTimer(2);
					if(!(CommState&0x02)) //接收状态0x02
					{
						m_commLed.m_nColor=RGB(0,255,0);
						m_commLed.Invalidate();
						CommState |=0x02;
					}
					ReadDataComm();
					RxIndex=0;
					Rxcase=0;
					return 0;
				}

			}break;
		case 3://接收写命令数据
			{
				if((TxRWflag==TRUE)&&RxIndex==8)//写命令接收到返回值
				{
					KillTimer(2);
					WriteDataComm();
					RxIndex=0;
					Rxcase=0;
					return 0;
				}

			}break;
	}
	SetTimer(3,50,NULL);//字节超时定时器
	return 0;
}
void CCommSet::ReadDataComm()
{
	unsigned int chk=RxBuffer[RxIndex-2]+(RxBuffer[RxIndex-1]<<8);
	if(chk==crcchk(RxBuffer,(RxIndex-2)))		//CRC校验
	{
		for(int i=0;i<RxBuffer[2];)		//赋值
		{
			short int commdata=(RxBuffer[3+i]<<8)+RxBuffer[4+i];//读16位整数（正负）
 			ComReadTable[sendval]->curval=commdata;//高位在前
			DSPvalToPCval(ComReadTable[sendval]);//dsp值比例转换
			i+=2;
			sendval++;
		}
	}
	RxIndex=0;
	if(sendval<TableNum)//变量值未接收完
		SetTimer(1,1,NULL);//PostMessage(WM_TIMER,1);
	else	//变量值接收完	
	{
		sendval=0;
		UpDataView();
		SetTimer(1,10,NULL);
		//refreshcount++;
	}
}
void CCommSet::WriteDataComm()
{
	unsigned int chk=RxBuffer[RxIndex-2]+(RxBuffer[RxIndex-1]<<8);
	if(chk==crcchk(RxBuffer,(RxIndex-2)))		//CRC校验
	{
		TxRWflag=FALSE;	//确认写入完成，转为读状态
	}
	else		//重写
	{
		TxIndex++;
	}
	RxIndex=0;
	SetTimer(1,1,NULL);//PostMessage(WM_TIMER,1);//OnTimer(1)
}
//读命令
void CCommSet::SendReadOrder(int Address,int FunCode,int StartAddress,int Length)
{
	BYTE  Buf[8]={'\0'};
	Buf[0]=(BYTE)Address;		
	Buf[1]=(BYTE)FunCode;		//功能码
//	int addr=CharToInt(StartAddress);
	Buf[2]=(BYTE)((StartAddress & 0xFF00)>>8);	//起始地址
	Buf[3]=(BYTE)(StartAddress & 0xFF);
	Buf[4]=(BYTE)((Length & 0xFF00)>>8);	//寄存器数量
	Buf[5]=(BYTE)(Length & 0xFF);
	unsigned int CRC=crcchk(Buf,6);
	Buf[6]=(BYTE)(CRC & 0xFF);
	Buf[7]=(BYTE)((CRC & 0xFF00)>>8);		//CRC校验

	m_SerialPort.WriteToPort(Buf,8);
/*	for(int i=0;i<8;i++)		//串口发送
	{
		m_SerialPort.WriteToPort(&Buf[i],1);
		//MSleep(500,TRUE);
		Sleep(1);
	}*/
}
void CCommSet::SendWriteOrder(int StartAddress,char* dataval)
{
	BYTE  Buf[11]={'\0'};
	Buf[0]=0x01;
	Buf[1]=0x10;
//	int addr=CharToInt(StartAddress);
	Buf[2]=(BYTE)((StartAddress & 0xFF00)>>8);	//起始地址
	Buf[3]=(BYTE)(StartAddress & 0xFF);
	Buf[4]=0x00;
	Buf[5]=0x01;
	Buf[6]=0x02;
	Buf[7]=(BYTE)dataval[0];
	Buf[8]=(BYTE)dataval[1];
	unsigned int CRC=crcchk(Buf,9);
	Buf[9]=(BYTE)(CRC & 0xFF);
	Buf[10]=(BYTE)((CRC & 0xFF00)>>8);

	m_SerialPort.WriteToPort(Buf,11);
/*	for(int i=0;i<11;i++)
	{
		m_SerialPort.WriteToPort(&Buf[i],1);
		Sleep(1);
	}*/
}
//字符转数字
char CCommSet::HexChar(char c)
{
	if((c>='0')&&(c<='9'))
		return c-0x30;
	else if((c>='A')&&(c<='F'))
		return c-'A'+10;
	else if((c>='a')&&(c<='f'))
		return c-'a'+10;
	else 
		return 0x10;
}

//字符串数字转换为int
int CCommSet::CharToInt(char* data)
{
	int t,t1;
	int intdata=0;
	int rlen=0,len=strlen(data);
	//data.SetSize(len/2);
	for(int i=len-1;i>=0;)//高字节在前
	{
		char l=data[i],h;
		if(l==' ')
		{
			i--;
			continue;
		}
		i--;
		if(i>=0)
			h=data[i];
		else
			h='0';
		t=HexChar(h);
		t1=HexChar(l);
		if((t==16)||(t1==16))
			break;
		else 
			t=t*16+t1;
		i--;
		intdata+=t*pow(0x100,rlen); //int
		//data[rlen]=(char)t;
		rlen++;
	}
	return intdata;
}
//////////////////////////////////////////////////////////
					/*CRC校验*/
//////////////////////////////////////////////////////////
unsigned int CCommSet::crcchk(unsigned char *data_ad,unsigned int length)
{
	int i,j; unsigned int crcsum; 
	crcsum=0xFFFF;
	for(i=0;i<length;i++)
	{
		crcsum^=*data_ad++;
		for(j=0;j<8;j++)
		{
			if((crcsum&1)==1)
				crcsum=(crcsum>>1) ^ 0xA001;
			else 
				crcsum=(crcsum>>1);
		}
	}
	return crcsum;
}
void CCommSet::OnOK() 
{
	// TODO: Add extra validation here
	m_SerialPort.ClosePort();
	if(InitComm()==true)
		CDialog::OnOK();
}
void CCommSet::OnSelchangeParityCombo() 
{
	// TODO: Add your control notification handler code here
	int i=m_parity.GetCurSel();
	switch(i)
	{
	case 0:
		parity='N';
		break;
	case 1:
		parity='O';
		break;
	case 2:
		parity='E';
		break;
	}

}

void CCommSet::UpDataView()
{
	if(pReadView!=0)
		pReadView->PostMessage(WM_TIMER);
	if(pWriteView!=0)
		pWriteView->PostMessage(WM_TIMER);
	if(pBitView!=0)
		pBitView->PostMessage(WM_TIMER);
}

void CCommSet::DSPvalToPCval(PARAINI_INFO *parainfo)
{
	if((parainfo->binscale!=0)&&(parainfo->decscale!=0))
		parainfo->curval=(parainfo->curval*parainfo->decscale)/parainfo->binscale;

	long data;
	CString str=parainfo->vformat;
	CString val;
	if(parainfo->min>=0)
	{
		if(parainfo->curval<0)
			parainfo->curval=(unsigned short)parainfo->curval;
	}
	if(str=="0.0")
	{
		data=parainfo->curval*10;
		parainfo->curval = (float)data/10;
		val.Format("%.1f",parainfo->curval);
	}
	else if(str=="0.00")
	{
		data=parainfo->curval*100;
		parainfo->curval = (float)data/100;
		val.Format("%.2f",parainfo->curval);
	}
	else if(str=="0.000")
	{
		data=parainfo->curval*1000;
		parainfo->curval = (float)data/1000;
		val.Format("%.3f",parainfo->curval);
	}
	else
	{
		val.Format("%.0f",parainfo->curval);
	}
	strcpy(parainfo->cfval,(LPSTR)(LPCTSTR)val);
}
// lTime----休眠时间（微秒）      
// bProcessMsg----休眠时是否处理系统消息 
void CCommSet::MSleep( long lTime, bool bProcessMsg)
{           
	LARGE_INTEGER litmp;           
	LONGLONG QPart1,QPart2;           
	double dfMinus, dfFreq, dfTim, dfSpec;            
	QueryPerformanceFrequency(&litmp);           
	dfFreq = (double)litmp.QuadPart;           
	QueryPerformanceCounter(&litmp);           
	QPart1 = litmp.QuadPart;           
	dfSpec = 0.000001*lTime;             
	do          
	{                
		if ( bProcessMsg == true )                
		{                     
			MSG msg;                     
			PeekMessage(&msg,NULL,0,0,PM_REMOVE);                     
			TranslateMessage(&msg);                      
			DispatchMessage(&msg);                
		}                 
		QueryPerformanceCounter(&litmp);                
		QPart2 = litmp.QuadPart;              
		dfMinus = (double)(QPart2-QPart1);                
		dfTim = dfMinus / dfFreq;           
	}while(dfTim<dfSpec);      
}