// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SatCon.h"
#include "SetParaDlg.h"
#include "MainFrm.h"
#include "CommSet.h"
#include "PassWord.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCommSet m_comm;
extern int m_para_tot_num;
extern PARAINI_INFO m_para_info[MAX_PARA_INI_NUM];
extern int m_ValNum;
extern ParaValInfo m_ValInfo[MAX_VAL_NUM];
extern MainInfo m_maininfo;
extern CString path;
extern CMD_BUTTON OPSEQ;
extern CString OpseqStr[30];
extern int  OpLevel;
extern CString project_dir[11];
extern int projectsum;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_MENU_SET_PARAMETERS, OnMenuSetParameters)
	ON_COMMAND(ID_MENU_OPR_CNNSET, OnMenuOprCnnset)
	ON_COMMAND(ID_MENU_OPR_CNTPCS, OnMenuOprCntpcs)
	ON_COMMAND(ID_MENU_OPR_DISCNTPCS, OnMenuOprDiscntpcs)
	ON_COMMAND(ID_MENU_OPR_USERLEVEL, OnMenuOprUserlevel)
	ON_COMMAND(ID_MENU_OPR_SYSLEVEL, OnMenuOprSyslevel)
	ON_COMMAND(ID_MENU_OPR_SERCERLEVEL, OnMenuOprSercerlevel)
	ON_WM_TIMER()
	ON_WM_INITMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
//	ID_SEPARATOR,           // status line indicator
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
	ID_STATE_INFO,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	connectflg=false;//连接标记位
	m_para_tot_num=0;
	memset(m_para_info, 0, MAX_PARA_INI_NUM*sizeof(PARAINI_INFO));
	memset(m_ValInfo, 0, TAB_MAX_NUM*sizeof(ParaValInfo));
	memset(&m_maininfo,0,sizeof(MainInfo));
	process_para_ini();		//read para.ini,init base data.
	SortParaStr();
	ProcessParaBitIni();	//read parabit.ini
	process_program_int();	//read program.ini

	connectflg=true;   //串口打开标记
}

CMainFrame::~CMainFrame()
{
	writeback_para_ini();	//write back para.ini
	WritebackParaBitIni();
	WritebackProgramini();
	WriteBackMainIni();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
/*	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}*/

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if(!m_bitshowBar.Create(this,IDD_BITSHOW_DIALOGBAR,WS_CHILD|
		WS_VISIBLE|CBRS_TOP,IDD_BITSHOW_DIALOGBAR))//bitshow工具条
	{
		TRACE0("Failed to create bit show bar\n");
		return -1;      // fail to create
	}
	if(!m_ButtonBar.Create(this,IDD_BUTTON_DIALOGBAR,WS_CHILD|
		WS_VISIBLE|CBRS_LEFT,IDD_BUTTON_DIALOGBAR))//Button工具条
	{
		TRACE0("Failed to create bit show bar\n");
		return -1;      // fail to create
	}
	SetTitle("PC Controller");//设置主窗口标题
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
/*	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/

/*	m_bitshowBar.EnableDocking(CBRS_ALIGN_ANY);//使bitshow工具条活动
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_bitshowBar);*/
	m_wndStatusBar.SetPaneInfo(0,ID_STATE_INFO,SBPS_NOBORDERS,300);//设置状态栏
//////////////////////////////////////////////////
	SetTimer(1,100,NULL);//更新状态栏信息
	return 0;
}
//定时器事件
void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(OPSEQ.pinfo)
	{
		CString str; int j=0;
		int data=OPSEQ.pinfo->curval;
		str.Format("OPSEQ%d=",data);
		for(int i=0;i<30;i++)
		{
			j=OpseqStr[i].Find(str,0);
			if(j>=0)
			{
				j =OpseqStr[i].GetLength()-str.GetLength();
				str=OpseqStr[i].Right(j);
				int inex=m_wndStatusBar.CommandToIndex(ID_STATE_INFO);//状态栏显示信息
				m_wndStatusBar.SetPaneText(inex,str);
				break;
			}
		}
	}
	CMDIFrameWnd::OnTimer(nIDEvent);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}
//过滤字串，去除无效字符
void CMainFrame::filterStr(char *str)
{
    int i, j, len;
    len = strlen(str);
    
    for (i = 0, j = 0; i < len; i++)
    {
        if (str[i] == 0x0D || str[i] == 0x0A || str[i] == ']')  //遇到']'时截断
        {
            //str[j++] = 0;
            break;
        }
        //else if (str[i] == 0x20)
        //{
        //}
        else
        {
            str[j++] = str[i];
        }
    }
    str[j++] = 0;
    return;
}

#define PARA_CHECK_STR(a)	((pTmp = strstr(lineBuff, a)) != NULL)	
#define PARA_GET_INT(a,b)	(m_para_info[curItem].a = atoi(pTmp + strlen(b)))
#define PARA_GET_FLOAT(a,b)	(m_para_info[curItem].a = atof(pTmp + strlen(b)))
#define PARA_GET_STR(a,b)	strcpy(m_para_info[curItem].a, pTmp + strlen(b))
#define PARA_ADD_FLAG(a)    (m_para_info[curItem].itemBmFlag |= (a))
//读取para配置文件
int CMainFrame::process_para_ini()
{
    char lineBuff[256];
    char *pTmp;
    FILE *pf=NULL;
    int curItem = -1, test;
    
    pf = fopen(path+"\\files\\para.ini", "r");
    if (!pf)
    {
        //create and init.
        pf = fopen(path+"\\files\\para.ini", "w");
        fclose(pf);
        return 1;
    }
    
    while(!feof(pf))
    {
        fgets(lineBuff, 256, pf);
        filterStr(lineBuff);
        if (strlen(lineBuff) == 0)
        {
            continue;
        }
        
        // read item...
        if (PARA_CHECK_STR("["))    //item start
        {
            curItem++;
            PARA_GET_STR(itemName, "[");
			//strcpy(m_para_info[curItem].itemName, pTmp + strlen("["));	//strcpy(m_para_info[curItem].a, pTmp + strlen(b))
			m_para_info[curItem].itemBmFlag = 0;
        }
        else if (PARA_CHECK_STR("address="))
        {
            PARA_GET_INT(address, "address=");
            PARA_ADD_FLAG(SIGN_ADDR);
        }
        else if (PARA_CHECK_STR("writeable="))
        {
            PARA_GET_INT(writeable, "writeable=");
            PARA_ADD_FLAG(SIGN_WRITEABLE);
        }
        else if (PARA_CHECK_STR("writable="))   //NOTE: same as the prev one
        {
            PARA_GET_INT(writeable, "writable=");
            PARA_ADD_FLAG(SIGN_WRITEABLE);
        }
        else if (PARA_CHECK_STR("readable="))
        {
            PARA_GET_INT(readable, "readable=");
            PARA_ADD_FLAG(SIGN_READABLE);
        }
        else if (PARA_CHECK_STR("needrdcontinue="))
        {
            PARA_GET_INT(RdContinue, "needrdcontinue=");
            PARA_ADD_FLAG(SIGN_READCTN);
        }
        else if (PARA_CHECK_STR("value="))
        {
            //PARA_GET_FLOAT(value, "value=");
			PARA_GET_STR(cvalue,"value=");
            PARA_ADD_FLAG(SIGN_VALUE);
        }
        else if (PARA_CHECK_STR("unit="))
        {
            PARA_GET_STR(unit, "unit=");
            PARA_ADD_FLAG(SIGN_UNIT);
        }

        else if (PARA_CHECK_STR("comt="))
        {
            PARA_GET_STR(comt, "comt=");
            PARA_ADD_FLAG(SIGN_COMT);
        }
        else if (PARA_CHECK_STR("vformat="))
        {
            PARA_GET_STR(vformat, "vformat=");
            PARA_ADD_FLAG(SIGN_VFORMAT);
        }
        else if (PARA_CHECK_STR("decscale="))
        {
            PARA_GET_FLOAT(decscale, "decscale=");
			PARA_GET_STR(cdecscale,"decscale=");
            PARA_ADD_FLAG(SIGN_DESCALE);
        }
        else if (PARA_CHECK_STR("binscale="))
        {
            PARA_GET_FLOAT(binscale, "binscale=");
			PARA_GET_STR(cbinscale,"binscale=");
            PARA_ADD_FLAG(SIGN_BINSCALE);
        }
        else if (PARA_CHECK_STR("min="))
        {
            PARA_GET_FLOAT(min, "min=");
			PARA_GET_STR(cmin,"min=");
            PARA_ADD_FLAG(SIGN_MIN);
        }
        else if (PARA_CHECK_STR("max="))
        {
            PARA_GET_FLOAT(max, "max=");
			PARA_GET_STR(cmax,"max=");
            PARA_ADD_FLAG(SIGN_MAX);
        }
        else if (PARA_CHECK_STR("step="))
        {
            PARA_GET_FLOAT(step, "step=");
			PARA_GET_STR(cstep,"step=");
            PARA_ADD_FLAG(SIGN_STEP);
        }
        else if (PARA_CHECK_STR("dh="))
        {
            PARA_GET_STR(dh, "dh=");
            PARA_ADD_FLAG(SIGN_DH);
        }
        else
        {
            test = 0;
        }
    }
    m_para_tot_num = curItem;	//填充最后一条的数量
    
    fclose(pf);
    return 1;
}

void CMainFrame::SortParaStr()
{
	int flag;
	PARAINI_INFO swap;
	memset(&swap, 0,sizeof(PARAINI_INFO));
    for(int i=0;i<m_para_tot_num;i++)
    {
        flag=0;
        for(int j=0;j<m_para_tot_num-i;j++)
        {
            if(stricmp(m_para_info[j+1].itemName,m_para_info[j].itemName)<0)
            {
                swap=m_para_info[j];
                m_para_info[j]=m_para_info[j+1];
                m_para_info[j+1]=swap;
                flag=1;
            }
        }
        if(flag==0) break;
    }
}
//回写到para
int CMainFrame::writeback_para_ini()
{
    FILE *pf;
    int i;
    
    pf = fopen(path+"\\files\\para.ini", "w");
    if (!pf)
    {
        AfxMessageBox("Write para.ini failed!");
        return 1;
    }
    
    // write tab item...
    for (i = 0; i <=m_para_tot_num; i++)
    {
        fprintf(pf, "\n[%s]\n", m_para_info[i].itemName);
        if (m_para_info[i].itemBmFlag & SIGN_ADDR)
            fprintf(pf, "address=%d\n", m_para_info[i].address);
        if (m_para_info[i].itemBmFlag & SIGN_DH)
            fprintf(pf, "dh=%s\n", m_para_info[i].dh);
        if (m_para_info[i].itemBmFlag & SIGN_UNIT)
            fprintf(pf, "unit=%s\n", m_para_info[i].unit);
        if (m_para_info[i].itemBmFlag & SIGN_MIN)
            fprintf(pf, "min=%s\n", m_para_info[i].cmin);
        if (m_para_info[i].itemBmFlag & SIGN_MAX)
            fprintf(pf, "max=%s\n", m_para_info[i].cmax);
        if (m_para_info[i].itemBmFlag & SIGN_COMT)
            fprintf(pf, "comt=%s\n", m_para_info[i].comt);
		
        if (m_para_info[i].itemBmFlag & SIGN_WRITEABLE)
            fprintf(pf, "writeable=%d\n", m_para_info[i].writeable);
        if (m_para_info[i].itemBmFlag & SIGN_READABLE)
            fprintf(pf, "readable=%d\n", m_para_info[i].readable);
        if (m_para_info[i].itemBmFlag & SIGN_READCTN)
            fprintf(pf, "needrdcontinue=%d\n", m_para_info[i].RdContinue);
        if (m_para_info[i].itemBmFlag & SIGN_VALUE)
            fprintf(pf, "value=%s\n", m_para_info[i].cvalue);
        if (m_para_info[i].itemBmFlag & SIGN_DESCALE)
            fprintf(pf, "decscale=%s\n", m_para_info[i].cdecscale);
        if (m_para_info[i].itemBmFlag & SIGN_BINSCALE)
            fprintf(pf, "binscale=%s\n", m_para_info[i].cbinscale);
        if (m_para_info[i].itemBmFlag & SIGN_VFORMAT)
            fprintf(pf, "vformat=%s\n", m_para_info[i].vformat);
        if (m_para_info[i].itemBmFlag & SIGN_STEP)
            fprintf(pf, "step=%s\n", m_para_info[i].cstep);
    }
    
    fclose(pf);
    return 1;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

PARAINI_INFO* CMainFrame::GetVariableInfo(char *name)
{
	int i=0; PARAINI_INFO *info=NULL; 
	if(*name==0)
		return 0;
	for (i = 0; i <=m_para_tot_num; i++)
	{
		if (strcmp(m_para_info[i].itemName, name) == 0)	//匹配到
		{
			break;
		}
	}
	if (i <=m_para_tot_num)
	{
		info=&m_para_info[i];
		return info;
	}
	return 0;
}

void CMainFrame::OnMenuSetParameters() //弹出变量参数设置窗口
{
	// TODO: Add your command handler code here
	SetParaDlg paradlg(m_para_info,&m_para_tot_num);
//	OnMenuOprDiscntpcs();//关闭串口
	if(paradlg.DoModal()==IDOK)
	{
		//UpDataRead=TRUE;
	}
//	OnMenuOprCntpcs();//打开串口
}

void CMainFrame::OnMenuOprCnnset() //弹出串口设置窗口
{
	// TODO: Add your command handler code here
//	OnMenuOprDiscntpcs();//关闭串口
	m_comm.ShowWindow(SW_SHOW);
	int inex=m_wndStatusBar.CommandToIndex(ID_STATE_INFO);//状态栏显示信息
	m_wndStatusBar.SetPaneText(inex,"Communication Setting");
}

void CMainFrame::OnMenuOprCntpcs() //连接串口
{
	// TODO: Add your command handler code here
	if(!connectflg)//connectflg=false;
	{
		if(m_comm.InitComm())
		{
			connectflg=true;
			GetMenu()->GetSubMenu(0)->CheckMenuItem(5,MF_BYPOSITION|MF_CHECKED);//标记
			GetMenu()->GetSubMenu(0)->CheckMenuItem(6,MF_BYPOSITION|MF_UNCHECKED);//不标记
			int inex=m_wndStatusBar.CommandToIndex(ID_STATE_INFO);//状态栏显示信息
			m_wndStatusBar.SetPaneText(inex,"Connect Device");
		}
	}
}

void CMainFrame::OnMenuOprDiscntpcs()//关闭串口
{
	// TODO: Add your command handler code here
	if(connectflg)//connectflg=true;
	{
		connectflg=false;
		m_comm.CloseComm();//关闭串口
		GetMenu()->GetSubMenu(0)->CheckMenuItem(6,MF_BYPOSITION|MF_CHECKED);//标记
		GetMenu()->GetSubMenu(0)->CheckMenuItem(5,MF_BYPOSITION|MF_UNCHECKED);//不标记
		int inex=m_wndStatusBar.CommandToIndex(ID_STATE_INFO);//状态栏显示信息
		m_wndStatusBar.SetPaneText(inex,"Disconnect Device");
	}

}

void CMainFrame::OnMenuOprUserlevel() 
{
	// TODO: Add your command handler code here
	OpLevel=0;
}
//
void CMainFrame::OnMenuOprSercerlevel() 
{
	// TODO: Add your command handler code here	
	if(OpLevel==0)
	{
		CPassWord passwordlg;
		passwordlg.PassWordLevel="Please Input the Password for SERVICE Level";
		passwordlg.RealPassWord="serviceman";
		if(passwordlg.DoModal()==IDOK)
		{
			OpLevel=1;
		}
	}
	else if(OpLevel==2)
	{
		OpLevel=1;
	}
}

void CMainFrame::OnMenuOprSyslevel() 
{
	// TODO: Add your command handler code here
	if(OpLevel!=2)
	{
		CPassWord passwordlg;
		passwordlg.PassWordLevel="Please Input the Password for SYSTEM Level";
		passwordlg.RealPassWord="systemman";
		if(passwordlg.DoModal()==IDOK)
		{
			OpLevel=2;
		}
	}
}
#define PROGRAM_CHECK_STR(a)	((pTmp = strstr(lineBuff, a)) != NULL)	
#define PROGRAM_GET_INT(a,b)	(a = atoi(pTmp + strlen(b)))
#define PROGRAM_GET_FLOAT(a,b)	(a = atof(pTmp + strlen(b)))
#define PROGRAM_GET_STR(a,b)	strcpy(a, pTmp + strlen(b))

int CMainFrame::process_program_int()
{
    char lineBuff[256]; char charstr[20];
    char *pTmp; int curItem;
    FILE *pf;
    pf = fopen(path+"\\files\\program.ini", "r");
    if (!pf)
    {
        //create and init.
        pf = fopen(path+"\\files\\program.ini", "w");
        fclose(pf);
        return 1;
    }    
    while(!feof(pf))
    {
        fgets(lineBuff, 256, pf);
        filterStr(lineBuff);
        if (strlen(lineBuff) == 0)
        {
            continue;
        }

		if (PROGRAM_CHECK_STR("MDIfrmMain.Top="))
		{
			PROGRAM_GET_INT(m_form_top, "MDIfrmMain.Top=");
		}
		else if(PROGRAM_CHECK_STR("MDIfrmMain.Left="))
		{
			PROGRAM_GET_INT(m_form_left, "MDIfrmMain.Left=");
		}
		else if(PROGRAM_CHECK_STR("MDIfrmMain.Height="))
		{
			PROGRAM_GET_INT(m_form_left, "MDIfrmMain.Height=");
		}
		else if(PROGRAM_CHECK_STR("MDIfrmMain.Width="))
		{
			PROGRAM_GET_INT(m_form_width, "MDIfrmMain.Width=");
		}
		else if(PARA_CHECK_STR("FormShow"))
		{
			curItem=PargramCheckSum("FormShow",lineBuff);
			PARA_CHECK_STR("=");
			PROGRAM_GET_STR(m_maininfo.FormShow[curItem],"=");
		}
		else if(PROGRAM_CHECK_STR("CommPort="))
		{
			PROGRAM_GET_STR(charstr, "CommPort=");
			m_comm.m_port=charstr;
		}
		else if(PROGRAM_CHECK_STR("CommBaud="))
		{
			PROGRAM_GET_STR(charstr, "CommBaud=");
			m_comm.m_baud=charstr;
		}
		else if(PROGRAM_CHECK_STR("CommParity="))
		{
			PROGRAM_GET_STR(charstr, "CommParity=");
			m_comm.parity=charstr[0];
		}
 		else if(PROGRAM_CHECK_STR("CommDataBit="))
		{
			PROGRAM_GET_STR(charstr, "CommDataBit=");
			m_comm.m_data=charstr;
		}
		else if(PROGRAM_CHECK_STR("CommStopBit="))
		{
			PROGRAM_GET_STR(charstr, "CommStopBit=");
			m_comm.m_stop=charstr;
		}
		else if(PROGRAM_CHECK_STR("Dply_Name"))
		{
			curItem=PargramCheckSum("Dply_Name",lineBuff);
			PARA_CHECK_STR("=");
			PROGRAM_GET_STR(m_maininfo.mainval[curItem].Dply_Name,"=");
			m_maininfo.mainval[curItem].ValInfo=GetVariableInfo(m_maininfo.mainval[curItem].Dply_Name);
		}
		else if(PROGRAM_CHECK_STR("Dply_Color"))
		{
			curItem=PargramCheckSum("Dply_Color",lineBuff);
			PARA_CHECK_STR("=");
			PROGRAM_GET_STR(m_maininfo.mainval[curItem].Dply_Color,"=");
		}
		else if(PROGRAM_CHECK_STR("Bit_Vname"))
		{
			curItem=PargramCheckSum("Bit_Vname",lineBuff);
			PARA_CHECK_STR("=");
			PROGRAM_GET_STR(m_maininfo.mainbit[curItem].Bit_Vname,"=");
			m_maininfo.mainbit[curItem].ValInfo=GetVariableInfo(m_maininfo.mainbit[curItem].Bit_Vname);
			m_maininfo.mainbit[curItem].pvalbitinfo=GetValBitInfo(m_maininfo.mainbit[curItem].Bit_Vname);
		}
		else if(PROGRAM_CHECK_STR("Bit_No"))
		{
			curItem=PargramCheckSum("Bit_No",lineBuff);
			PARA_CHECK_STR("=");
			PROGRAM_GET_INT(m_maininfo.mainbit[curItem].Bit_No,"=");
		}
	}//end while(!feof(pf))
  fclose(pf);
	return 1;
}
//数据回写到program.ini文件
void CMainFrame::WritebackProgramini()
{
	FILE *pf;
	int i;
	CString str;
	pf = fopen(path+"\\files\\program.ini", "w");
	if (!pf)
	{
		AfxMessageBox("Write program.ini failed!");
		return;
	}
	// write tab item...
	fprintf(pf,"\n[Main_ini]\n");
	fprintf(pf, "MDIfrmMain.Top=%d\n", m_form_top);
	fprintf(pf, "MDIfrmMain.Left=%d\n", m_form_left);
	fprintf(pf, "MDIfrmMain.Height=%d\n", m_form_height);
	fprintf(pf, "MDIfrmMain.Width=%d\n", m_form_width);
	for(i=0;i<MAINITEM_MAX_NUM;i++)
	{
		str=m_maininfo.mainval[i].Dply_Name;
		if(str!="")
		fprintf(pf, "Dply_Name %d=%s\n",i,m_maininfo.mainval[i].Dply_Name);
		str=m_maininfo.mainval[i].Dply_Color;
		if(str!="")
		fprintf(pf, "Dply_Color %d=%s\n",i,m_maininfo.mainval[i].Dply_Color);
		str=m_maininfo.mainbit[i].Bit_Vname;
		if(str!="")
		{
			fprintf(pf, "Bit_Vname %d=%s\n",i,m_maininfo.mainbit[i].Bit_Vname);
			fprintf(pf, "Bit_No %d=%d\n",i,m_maininfo.mainbit[i].Bit_No);
		}
	}
	fprintf(pf,"\n[PCS_ini]\n");
	fprintf(pf,"CommPort=%s\n",(LPSTR)(LPCTSTR)m_comm.m_port);
	fprintf(pf,"CommBaud=%s\n",(LPSTR)(LPCTSTR)m_comm.m_baud);
	fprintf(pf,"CommParity=%c\n",m_comm.parity);
	fprintf(pf,"CommDataBit=%s\n",(LPSTR)(LPCTSTR)m_comm.m_data);
	fprintf(pf,"CommStopBit=%s\n",(LPSTR)(LPCTSTR)m_comm.m_stop);
			
}

int CMainFrame::PargramCheckSum(char *pchar,char *Buff)
{
	char *pTmp; int sum;
	int len=strlen(pchar);
	char ch[2];
	pTmp = strstr(Buff, "=");
	*pTmp = 0;
	strcpy(ch,&Buff[len+1]);
	sum = atoi(ch);
    *pTmp = '=';
	return sum;
}
//读parabit.ini文件数据到结构体m_parabitInfo
#define PARABIT_CHECK_STR(a)	((pTmp = strstr(lineBuff, a)) != NULL)	
#define PARABIT_GET_INT(a,b)	(m_ValInfo[VarNum].a = atoi(pTmp + strlen(b)))
#define PARABIT_GET_STR(a,b)	strcpy(m_ValInfo[VarNum].a, pTmp + strlen(b))
void CMainFrame::ProcessParaBitIni()
{
	char lineBuff[256];
	char *pTmp;
	FILE *pf;
	int VarNum=-1, flag = 0, test = 0,bit;
	CString Checkstr;
	pf = fopen(path+"\\files\\parabit.ini", "r");
	if (!pf)
	{
		//create and init.
		pf = fopen(path+"\\files\\parabit.ini", "w");
		fclose(pf);
		return;
	}
	
	while(!feof(pf))
	{
		fgets(lineBuff, 256, pf);
		filterStr(lineBuff);
		if (strlen(lineBuff) == 0)
		{
			continue;
		}
		if (PARABIT_CHECK_STR("["))    //item start
        {
            VarNum++;
			PARABIT_GET_STR(ValName, "[");
			
        }
        else if ((bit=ParaBitCheckBit(lineBuff))!=-1)
        {
			
			if(PARABIT_CHECK_STR("Dspl0="))
			{
				PARABIT_GET_STR(bitinfo[bit].Displ[0],"Dspl0=");
			}
			else if(PARABIT_CHECK_STR("Dspl1="))
			{
				PARABIT_GET_STR(bitinfo[bit].Displ[1],"Dspl1=");
			}
			else if(PARABIT_CHECK_STR("Color0="))
			{
				PARABIT_GET_STR(bitinfo[bit].Color[0],"Color0=");
			}
			else if(PARABIT_CHECK_STR("Color1="))
			{
				PARABIT_GET_STR(bitinfo[bit].Color[1],"Color1=");
			}
			else if(PARABIT_CHECK_STR("Comment="))
			{
				PARABIT_GET_STR(bitinfo[bit].Comment,"Comment=");
			}
			
        }				
	}
	m_ValNum=VarNum;
}

int CMainFrame::ParaBitCheckBit(char *lineBuff)
{
	CString str; int i;
	for(i=10;i<16;i++)
	{
		str.Format("Bit%d",i);
		if(strstr(lineBuff, str) != NULL)
			return i;
	}
	for(i=0;i<10;i++)
	{
		str.Format("Bit%d",i);
		if(strstr(lineBuff, str) != NULL)
			return i;		
	}
	return -1;
}
//回写到parabit.ini中
void CMainFrame::WritebackParaBitIni()
{
	FILE *pf;
	int i, j;
	CString str;
	pf = fopen(path+"\\files\\parabit.ini", "w");
	if (!pf)
	{
		AfxMessageBox("Write parabit.ini failed!");
		return;
	}
	// write tab item...
    for (i = 0; i <=m_ValNum; i++)
    {
		fprintf(pf, "\n[%s]\n", m_ValInfo[i].ValName);
		for(j=0;j<16;j++)
		{
			str=m_ValInfo[i].bitinfo[j].Displ[0];
			if(str!="")
				fprintf(pf,"Bit%dDspl0=%s\n", j, str);
			str=m_ValInfo[i].bitinfo[j].Displ[1];
			if(str!="")
				fprintf(pf,"Bit%dDspl1=%s\n", j,str);
			str=m_ValInfo[i].bitinfo[j].Color[0];
			if(str!="")
				fprintf(pf,"Bit%dColor0=%s\n", j,str);
			str=m_ValInfo[i].bitinfo[j].Color[1];
			if(str!="")
				fprintf(pf,"Bit%dColor1=%s\n", j,str);
			str=m_ValInfo[i].bitinfo[j].Comment;
			if(str!="")
				fprintf(pf,"Bit%dComment=%s\n", j,str);
		}
	}
}
//根据变量名获得变量指针
ParaValInfo* CMainFrame::GetValBitInfo(char *name)
{
	int i; ParaValInfo *info;
	if(*name==0)
		return 0;
	for (i = 0; i <=m_ValNum; i++)
	{
		if (strcmp(m_ValInfo[i].ValName, name) == 0)	//匹配到
		{
			break;
		}
	}
	if (i <=m_ValNum)
	{
		info=&m_ValInfo[i];
		return info;
	}
	return 0;
}

void CMainFrame::WriteBackMainIni()
{
	FILE *pf;
    int i;
    
    pf = fopen("main.ini", "w");
    if (!pf)
    {
        AfxMessageBox("Write main.ini failed!");
        return;
    }
	fprintf(pf, "[main_ini]\n");
	fprintf(pf, "frmSetFolder.Top=4155\n");
	fprintf(pf, "frmSetFolder.Left=6375\n");
	fprintf(pf, "frmSetFolder.Height=3675\n");
	fprintf(pf, "frmSetFolder.Width=6435\n");
	fprintf(pf, "OpLevel=%d\n",OpLevel);
	fprintf(pf, "\n[project_ini]\n");
	fprintf(pf, "project_dir=%s\n",project_dir[0]);
	for(i=1;i<=10;i++)
	{
		if(project_dir[i]=="")
			break;
		fprintf(pf, "project_dir%d=%s\n",i,project_dir[i]);
	}
    fclose(pf);
}

void CMainFrame::OnInitMenu(CMenu* pMenu) 
{
	CMDIFrameWnd::OnInitMenu(pMenu);
	
	// TODO: Add your message handler code here
	if(	connectflg==true)
	{
		GetMenu()->GetSubMenu(0)->CheckMenuItem(5,MF_BYPOSITION|MF_CHECKED);//标记
		GetMenu()->GetSubMenu(0)->CheckMenuItem(6,MF_BYPOSITION|MF_UNCHECKED);//不标记
	}
	GetMenu()->GetSubMenu(0)->CheckMenuItem(9,MF_BYPOSITION|MF_UNCHECKED);//不标记
	GetMenu()->GetSubMenu(0)->CheckMenuItem(10,MF_BYPOSITION|MF_UNCHECKED);//不标记
	GetMenu()->GetSubMenu(0)->CheckMenuItem(11,MF_BYPOSITION|MF_UNCHECKED);//不标记
	if(OpLevel==0)
		GetMenu()->GetSubMenu(0)->CheckMenuItem(9,MF_BYPOSITION|MF_CHECKED);//标记
	else if(OpLevel==1)
		GetMenu()->GetSubMenu(0)->CheckMenuItem(10,MF_BYPOSITION|MF_CHECKED);//标记
	else if(OpLevel==2)
		GetMenu()->GetSubMenu(0)->CheckMenuItem(11,MF_BYPOSITION|MF_CHECKED);//标记
}
