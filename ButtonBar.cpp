// ButtonBar.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "ButtonBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "CommSet.h"
extern CCommSet m_comm;
extern CString path;
extern int m_para_tot_num;
extern PARAINI_INFO m_para_info[MAX_PARA_INI_NUM];
extern CMD_BUTTON save_cmd;
extern CMD_BUTTON OPSEQ;
extern CString OpseqStr[30];
/////////////////////////////////////////////////////////////////////////////
// ButtonBar dialog


ButtonBar::ButtonBar(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(ButtonBar)
	//}}AFX_DATA_INIT
	Reset.Button=""; Reset.Comment=""; Reset.Vname=""; Reset.Value=0; Reset.pinfo=NULL;
	Start.Button=""; Start.Comment=""; Start.Vname=""; Start.Value=0; Start.pinfo=NULL;
	Stop.Button=""; Stop.Comment=""; Stop.Vname=""; Stop.Value=0; Stop.pinfo=NULL;
	Shutdown.Button=""; Shutdown.Comment=""; Shutdown.Vname=""; Shutdown.Value=0; Shutdown.pinfo=NULL;
	for(int i=0;i<10;i++)
	{
		cmdbutton[i].Button="";
		cmdbutton[i].Comment="";
		cmdbutton[i].Vname="";
		cmdbutton[i].Value=0;
		cmdbutton[i].pinfo=NULL;
	}
}


void ButtonBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ButtonBar)
	DDX_Control(pDX, IDC_START_BUTTON, m_start);
	DDX_Control(pDX, IDC_SHUTDOWN_BUTTON, m_shutdown);
	DDX_Control(pDX, IDC_RESET_BUTTON, m_reset);
	DDX_Control(pDX, IDC_STOP_BUTTON, m_stop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ButtonBar, CDialogBar)
	//{{AFX_MSG_MAP(ButtonBar)
	ON_BN_CLICKED(IDC_STOP_BUTTON, OnStopButton)
	ON_BN_CLICKED(IDC_SHUTDOWN_BUTTON, OnShutdownButton)
	ON_BN_CLICKED(IDC_RESET_BUTTON, OnResetButton)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_BN_CLICKED(IDC_START_BUTTON, OnStartButton)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED,IDC_BASE_BUTTON,IDC_BASE_BUTTON+10, OnCMDButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ButtonBar message handlers

 LONG ButtonBar::OnInitDialog(UINT wParam, LONG lParam)
{
	BOOL bRet = HandleInitDialog(wParam, lParam);
	if(!UpdateData(FALSE))			//更新位图
		TRACE0("Warning, Unalbe to init update./n");
	ReadUserIni();		//读取按键信息
	AddVarAddress();
	// Add Code here
	//按钮添加位图
	HBITMAP	hshutBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_SHUTDOWN_BITMAP));
	m_shutdown.SetBitmap(hshutBmp); 
	HBITMAP	hrestBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_RESET_BITMAP));
	m_reset.SetBitmap(hrestBmp); 
	HBITMAP	hstartBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_START_BITMAP));
	m_start.SetBitmap(hstartBmp); 
	HBITMAP	hstopBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_STOP_BITMAP));
	m_stop.SetBitmap(hstopBmp);
	//按钮添加提示
	EnableToolTips(TRUE);
	m_TipCtrl.Create(this,TTS_ALWAYSTIP);
	m_TipCtrl.Activate(TRUE);
	CWnd* pwnd;
	pwnd=GetDlgItem(IDC_SHUTDOWN_BUTTON);
	m_TipCtrl.AddTool(pwnd,"Shutdown");
	
	pwnd=GetDlgItem(IDC_RESET_BUTTON);
	m_TipCtrl.AddTool(pwnd,"Reset");

	pwnd=GetDlgItem(IDC_START_BUTTON);
	m_TipCtrl.AddTool(pwnd,"Start Inverter");

	pwnd=GetDlgItem(IDC_STOP_BUTTON);
	m_TipCtrl.AddTool(pwnd,"Stop");
	RECT rect;
	rect.left=0;
	rect.right=rect.left+40;
	rect.top=125;
	rect.bottom=rect.top+20;
	for(int i=0;i<10;i++)
	{
		rect.top +=25;
		rect.bottom=rect.top+20;
		if(cmdbutton[i].Button!="")
		{
			m_button[i].Create(cmdbutton[i].Button,WS_CHILD|WS_VISIBLE,rect,this,IDC_BASE_BUTTON+i);
			pwnd=GetDlgItem(IDC_BASE_BUTTON+i);
			m_TipCtrl.AddTool(pwnd,cmdbutton[i].Comment);
		}
	}
	return bRet;
}
void ButtonBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler)//按钮可用
{
	bDisableIfNoHandler = FALSE;
    CDialogBar::OnUpdateCmdUI(pTarget, FALSE);
}

void ButtonBar::OnShutdownButton() 
{
	// TODO: Add your control notification handler code here
	WriteCommData(Shutdown);
}

void ButtonBar::OnResetButton() 
{
	// TODO: Add your control notification handler code here
	WriteCommData(Reset);
}

void ButtonBar::OnStartButton() 
{
	// TODO: Add your control notification handler code here
	WriteCommData(Start);
}

void ButtonBar::OnStopButton() 
{
	// TODO: Add your control notification handler code here
	WriteCommData(Stop);
}
void ButtonBar::OnCMDButton(UINT id)
{
	WriteCommData(cmdbutton[id-IDC_BASE_BUTTON]);
}
BOOL ButtonBar::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_TipCtrl.RelayEvent(pMsg);
	return CDialogBar::PreTranslateMessage(pMsg);
}
#define USER_CHECK_STR(a)	((pTmp = strstr(lineBuff, a)) != NULL)	
#define USER_GET_INT(a,b)	(a = atoi(pTmp + strlen(b)))
#define USER_GET_FLOAT(a,b)	(a = atof(pTmp + strlen(b)))
#define USER_GET_STR(a,b)	(a=pTmp + strlen(b))
int ButtonBar::ReadUserIni()
{
	char lineBuff[256];
	char *pTmp; 
	FILE *pf;
	CString cmdstr;int cmdint=0;
	int OPSEQ_int=0;
	pf = fopen(path+"\\files\\user.ini", "r");
	if (!pf)
	{
		//create and init.
		pf = fopen(path+"\\files\\user.ini", "w");
		fclose(pf);
		return 1;
	}
		
	while(!feof(pf))
	{
		memset(lineBuff, 0, 256*sizeof(char));
		fgets(lineBuff, 256, pf);
		filterStr(lineBuff);
		if (strlen(lineBuff) == 0)
			continue;

		if (USER_CHECK_STR("ResetVname="))
			USER_GET_STR(Reset.Vname, "ResetVname=");		
		else if(USER_CHECK_STR("ResetValue="))
			USER_GET_INT(Reset.Value, "ResetValue=");		
		else if(USER_CHECK_STR("StartVname="))
			USER_GET_STR(Start.Vname, "StartVname=");
		else if(USER_CHECK_STR("StartValue="))
			USER_GET_INT(Start.Value, "StartValue=");
		else if(USER_CHECK_STR("StopVname="))
			USER_GET_STR(Stop.Vname, "StopVname=");
		else if(USER_CHECK_STR("StopValue="))
			USER_GET_INT(Stop.Value, "StopValue=");
		else if(USER_CHECK_STR("ShutdownVname="))
			USER_GET_STR(Shutdown.Vname, "ShutdownVname=");
		else if(USER_CHECK_STR("ShutdownValue="))
			USER_GET_INT(Shutdown.Value, "ShutdownValue=");
		else if(USER_CHECK_STR("SaveVname="))
			USER_GET_STR(save_cmd.Vname, "SaveVname=");
		else if(USER_CHECK_STR("SaveValue="))
			USER_GET_INT(save_cmd.Value, "SaveValue=");
		else if(USER_CHECK_STR("OPSEQ_vname="))
			USER_GET_STR(OPSEQ.Vname,"OPSEQ_vname=");
		else if(USER_CHECK_STR("OPSEQ"))
		{
			OpseqStr[OPSEQ_int]=pTmp;
			OPSEQ_int++;
		}
		else if(USER_CHECK_STR("CMD"))
		{
			char *ptop=pTmp+3;
			if(USER_CHECK_STR("Button="))
			{
				*pTmp=0;
				cmdint=atoi(ptop);
				*pTmp='B';
				if(cmdint<10)
					USER_GET_STR(cmdbutton[cmdint].Button,"Button=");
			}
			else if(USER_CHECK_STR("Comment="))
			{
				*pTmp=0;
				cmdint=atoi(ptop);
				*pTmp='C';
				if(cmdint<10)
					USER_GET_STR(cmdbutton[cmdint].Comment,"Comment=");
			}
			else if(USER_CHECK_STR("Vname="))
			{
				*pTmp=0;
				cmdint=atoi(ptop);
				*pTmp='V';
				if(cmdint<10)
					USER_GET_STR(cmdbutton[cmdint].Vname,"Vname=");
			}
			else if(USER_CHECK_STR("Value="))
			{
				*pTmp=0;
				cmdint=atoi(ptop);
				*pTmp='V';
				if(cmdint<10)
					USER_GET_INT(cmdbutton[cmdint].Value,"Value=");
			}

		}
	}//end while(!feof(pf))
    fclose(pf);
return 1;
}

void ButtonBar::filterStr(char *str)
{
	int i, j, len;
    len = strlen(str);
    
    for (i = 0, j = 0; i < len; i++)
    {
        if (str[i] == 0x0D || str[i] == 0x0A)
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

void ButtonBar::AddVarAddress()
{
	CString str;
	for(int i=0;i<=m_para_tot_num;i++)
	{
		str=m_para_info[i].itemName;
		if(str==Reset.Vname)
			Reset.pinfo=&m_para_info[i];
		if(str==Start.Vname)
			Start.pinfo=&m_para_info[i];
		if(str==Stop.Vname)
			Stop.pinfo=&m_para_info[i];
		if(str==Shutdown.Vname)
			Shutdown.pinfo=&m_para_info[i];
		if(str==save_cmd.Vname)
			save_cmd.pinfo=&m_para_info[i];
		if(str==OPSEQ.Vname)
			OPSEQ.pinfo=&m_para_info[i];

		for(int j=0;j<10;j++)
		{
			if(str==cmdbutton[j].Vname)
			{
				cmdbutton[j].pinfo=&m_para_info[i];
				break;
			}
		}
	}
}

void ButtonBar::WriteCommData(CMD_BUTTON cmd)
{
	if(!m_comm.m_ComOpened)//串口 打开
		return;
	if(cmd.Value!=0)//有变量数据
	{
		if(cmd.pinfo!=NULL)
		{
			if(cmd.pinfo->writeable)//写使能
			{
				memset(&m_comm.TxBuffer[m_comm.TxIndex],0,sizeof(BUFFER_STRUCT));//数据清零
				
				m_comm.TxBuffer[m_comm.TxIndex].TxAddss=cmd.pinfo->address;
				
				m_comm.TxBuffer[m_comm.TxIndex].TxData[0]=(cmd.Value>>8)&0xff;
				m_comm.TxBuffer[m_comm.TxIndex].TxData[1]=cmd.Value&0xff;
				
				m_comm.TxIndex++;		//有发送数据
			}
		}
		
	}
}
