// SatCon.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SatCon.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SatConReadDoc.h"
#include "SatConReadView.h"
#include "SatConWriteView.h"
#include "SatConWriteDoc.h"
#include "SatConBitShowView.h"
#include "SatConBitShowDoc.h"
#include "CommSet.h"
#include "UniButton.h"
#include "SelectDir.h"
#include "PassWord.h"
#include "MyChart.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSatConApp

BEGIN_MESSAGE_MAP(CSatConApp, CWinApp)
	//{{AFX_MSG_MAP(CSatConApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_MENU_READER, OnMenuReader)
	ON_COMMAND(ID_MENU_WRITER, OnMenuWriter)
	ON_COMMAND(ID_MENU_BITSHOW, OnMenuBitshow)
	ON_COMMAND(ID_MENU_UPLOAD_DSP_PC, OnMenuUploadDspPc)
	ON_COMMAND(ID_MENU_DOWNLOAD_PC_DSP, OnMenuDownloadPcDsp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSatConApp construction

CSatConApp::CSatConApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSatConApp object

CSatConApp theApp;
CCommSet m_comm;	//串口窗口全局变量
CUniButton m_commLed;//
CSelectDir SelectDlg;
int  OpLevel;			//操作等级
CString path;	//文件路径
bool UpDataRead=FALSE;
bool UpDataWrite=FALSE;
bool UpDataBit=FALSE;
/////////////////////////////
int m_para_tot_num;
PARAINI_INFO m_para_info[MAX_PARA_INI_NUM];

int TableNum;
PARAINI_INFO *ComReadTable[MAX_READCOM_NUM];//串口读取变量顺序表
bool ChangeTable=FALSE;

int m_ValNum;
ParaValInfo m_ValInfo[MAX_VAL_NUM];
MainInfo m_maininfo;
////////////////////////////////////////////
int m_WriteTabNum;
TabInfo m_WriteTabInfo[TAB_MAX_NUM];		//write窗口tab信息
///////////////////////////
CMD_BUTTON save_cmd;
CMD_BUTTON OPSEQ;
CString OpseqStr[30];
////////////////////////////
CString project_dir[11];
int projectsum;
/////////////////////////////////////////////////////////////////////////////
// CSatConApp initialization

BOOL CSatConApp::InitInstance()
{

	{	// BLOCK: doc template registration
		// Register the document template.  Document templates serve
		// as the connection between documents, frame windows and views.
		// Attach this form to another document or frame window by changing
		// the document or frame class in the constructor below.
		CMultiDocTemplate* pNewDocTemplate = new CMultiDocTemplate(
			IDR_MYCHART_TMPL,
			RUNTIME_CLASS(CMyChartDoc),		// document class
			RUNTIME_CLASS(CMDIChildWnd),		// frame class
			RUNTIME_CLASS(CMyChart));		// view class
		AddDocTemplate(pNewDocTemplate);
	}


	if(SelectDlg.DoModal()==IDOK)//路径选择
	{
		if(OpLevel==2)//sysetm level 密码
		{
			CPassWord passwordlg;
			passwordlg.PassWordLevel="Please Input the Password for SYSTEM Level";
			passwordlg.RealPassWord="systemman";
			//if(passwordlg.DoModal()!=IDOK)
			//	OpLevel=0;
		}
		else if(OpLevel==1)//sercerman level 密码
		{
			CPassWord passwordlg;
			passwordlg.PassWordLevel="Please Input the Password for SERVICE Level";
			passwordlg.RealPassWord="serviceman";
		//	if(passwordlg.DoModal()!=IDOK)
			//	OpLevel=0;
		}
	}
	else
		return FALSE;
/*	{	// BLOCK: doc template registration
		// Register the document template.  Document templates serve
		// as the connection between documents, frame windows and views.
		// Attach this form to another document or frame window by changing
		// the document or frame class in the constructor below.
		CMultiDocTemplate* pNewDocTemplate = new CMultiDocTemplate(
			IDR_SATCONWRITEVIEW_TMPL,
			RUNTIME_CLASS(SatConWriteDoc),		// document class
			RUNTIME_CLASS(CMDIChildWnd),		// frame class
			RUNTIME_CLASS(SatConWriteView));		// view class
		AddDocTemplate(pNewDocTemplate);
	}*/

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	// pDocRead
	pDocRead = new CMultiDocTemplate(
		IDR_SATCONTYPE,
		RUNTIME_CLASS(CSatConReadDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSatConReadView));
	AddDocTemplate(pDocRead);
		//Fred...
	// pDocWrite
	pDocWrite = new CMultiDocTemplate(
		IDR_SATCONTYPE,
		RUNTIME_CLASS(SatConWriteDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(SatConWriteView));
	AddDocTemplate(pDocWrite);
	// pDocBitshow
	pDocBitshow = new CMultiDocTemplate(
		IDR_SATCONTYPE,
		RUNTIME_CLASS(CSatConBitShowDoc),		// document class
		RUNTIME_CLASS(CMDIChildWnd),		// frame class
		RUNTIME_CLASS(CSatConBitShowView));		// view class
	AddDocTemplate(pDocBitshow);
	// pDocBitshow
	pMyChart = new CMultiDocTemplate(
		IDR_SATCONTYPE,
		RUNTIME_CLASS(CMyChartDoc),		// document class
		RUNTIME_CLASS(CMDIChildWnd),		// frame class
		RUNTIME_CLASS(CMyChart));		// view class
	AddDocTemplate(pMyChart);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

void CSatConApp::OnFileNew()
{
	OnMenuBitshow();
	OnMenuReader();
	OnMenuWriter();

	//pMyChart->OpenDocumentFile(NULL);//打开图表窗口

	SelectReadableVal();
	BasisAddressSortTable();

	m_comm.Create(IDD_COMMSET_DIALOG);
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CSatConApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSatConApp message handlers
void CSatConApp::OnMenuReader() 
{
	// TODO: Add your command handler code here
	if(m_comm.pReadView==0)
		pDocRead->OpenDocumentFile(NULL);
}

void CSatConApp::OnMenuWriter() 
{
	// TODO: Add your command handler code here
	if(m_comm.pWriteView==0)
		pDocWrite->OpenDocumentFile(NULL);
}

void CSatConApp::OnMenuBitshow() 
{
	// TODO: Add your command handler code here
	if(m_comm.pBitView==0)
		pDocBitshow->OpenDocumentFile(NULL);
}

void CSatConApp::OnMenuUploadDspPc() 
{
	// TODO: Add your command handler code here
	if(m_comm.pWriteView==NULL)
	{
		AfxMessageBox( "Please Open Write Window First!" );
		return;
	}
	CString str;
	CFileDialog FileDlg(FALSE,".ini",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Ini Files(*.ini)|*.ini||");
	FileDlg.m_ofn.lpstrInitialDir=path;
	if(FileDlg.DoModal()==IDOK)
	{
		pDocWrite->CloseAllDocuments(TRUE);
		str=FileDlg.GetPathName();
		BOOL TempFile = CopyFile(path+"\\files\\frmWrite.ini",str,FALSE);
		if(!TempFile)
		{
			AfxMessageBox( "Copy File Failed!" );
			return;
		}
		Sleep(10);
		pDocWrite->OpenDocumentFile(NULL);
		CopyParaToOther(str);			
 	}
}

void CSatConApp::OnMenuDownloadPcDsp() 
{
	// TODO: Add your command handler code here
	CString str;
	CFileDialog FileDlg(TRUE,".ini",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Ini Files(*.ini)|*.ini||");
	FileDlg.m_ofn.lpstrInitialDir=path;
	if(FileDlg.DoModal()==IDOK)
	{
		CopyFile(path+"\\files\\frmWrite.ini",path+"\\files\\frmWrite.ini.bak",FALSE);
		CopyFile(path+"\\files\\para.ini",path+"\\files\\para.ini.bak",FALSE);
		bool viewflg=false;
		if(m_comm.pWriteView!=NULL)
		{
			pDocWrite->CloseAllDocuments(TRUE);
			viewflg=true;
		}
		Sleep(10);
		str=FileDlg.GetPathName();
		CopyToFrmwrite(str);
		if(viewflg==true)
			pDocWrite->OpenDocumentFile(NULL);
	}
}

int CSatConApp::CopyParaToOther(CString newpath)
{
	FILE *pf;
	pf = fopen(newpath, "a+");
	fprintf(pf, "\n[para.ini]\n");
	for(int i=0;i<m_WriteTabNum;i++)
	{
		for(int j=0;j<m_WriteTabInfo[i].itemNum;j++)
		{
			if(m_WriteTabInfo[i].iteminfo[j].ValInfo!=NULL)
			{
				fprintf(pf, "\n[%s]\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->itemName);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_ADDR)
					fprintf(pf, "address=%d\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->address);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_DH)
					fprintf(pf, "dh=%s\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->dh);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_UNIT)
					fprintf(pf, "unit=%s\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->unit);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_MIN)
					fprintf(pf, "min=%s\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->cmin);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_MAX)
					fprintf(pf, "max=%s\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->cmax);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_COMT)
					fprintf(pf, "comt=%s\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->comt);
				
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_WRITEABLE)
					fprintf(pf, "writeable=%d\n",m_WriteTabInfo[i].iteminfo[j].ValInfo->writeable);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_READABLE)
					fprintf(pf, "readable=%d\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->readable);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_READCTN)
					fprintf(pf, "needrdcontinue=%d\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->RdContinue);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_VALUE)
					fprintf(pf, "value=%s\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->cvalue);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_DESCALE)
					fprintf(pf, "decscale=%s\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->cdecscale);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_BINSCALE)
					fprintf(pf, "binscale=%s\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->cbinscale);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_VFORMAT)
					fprintf(pf, "vformat=%s\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->vformat);
				if (m_WriteTabInfo[i].iteminfo[j].ValInfo->itemBmFlag & SIGN_STEP)
				fprintf(pf, "step=%s\n", m_WriteTabInfo[i].iteminfo[j].ValInfo->cstep);
			}
		}
	}
	fclose(pf);
	return 1;
}

#define GET_STR(a)			strcpy(a, (pTmp +1))
#define PARA_CHECK_STR(a)	((pTmp = strstr(lineBuff, a)) != NULL)	
#define PARA_GET_INT(a,b)	(m_para_info[curItem].a = atoi(pTmp + strlen(b)))
#define PARA_GET_FLOAT(a,b)	(m_para_info[curItem].a = atof(pTmp + strlen(b)))
#define PARA_GET_STR(a,b)	strcpy(m_para_info[curItem].a, pTmp + strlen(b))
#define PARA_ADD_FLAG(a)    (m_para_info[curItem].itemBmFlag |= (a))
void CSatConApp::CopyToFrmwrite(CString newpart)
{
	char lineBuff[256];
	char *pTmp;
	FILE *infile,*outfile;
	int curItem=-1;
	infile = fopen(newpart, "r");
	outfile=fopen(path+"\\files\\frmWrite.ini", "w");
	if ((!infile)||(!outfile))
	{
		return;
	}
	while(!feof(infile))
	{
		fgets(lineBuff, 256, infile);
		if (strlen(lineBuff) == 0)
            continue;
		if(PARA_CHECK_STR("[para.ini]"))
			break;
		fprintf(outfile, lineBuff);
    }
	while(!feof(infile))
	{
		char valname[20];
		fgets(lineBuff, 256, infile);
		if (strlen(lineBuff) == 0)
            continue;
		if(PARA_CHECK_STR("]"))
			*pTmp=0;
		if(PARA_CHECK_STR("["))
		{
			curItem=-1;
			GET_STR(valname);
			for(int i=0;i<=m_para_tot_num;i++)
			{
				if(strstr(m_para_info[i].itemName,valname)!=NULL)
				{
					curItem=i;
					memset(&m_para_info[i], 0, sizeof(PARAINI_INFO));
					break;
				}
			}
			if(curItem==-1)
			{
				m_para_tot_num++;
				curItem=m_para_tot_num;
			}
			strcpy(m_para_info[curItem].itemName,valname);
		}
		else if (PARA_CHECK_STR("address="))
        {
			//m_para_info[curItem].address = atoi(pTmp + strlen("address="));
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
	}
	fclose(infile);
	fclose(outfile);
}
//读使能的参数加入串口数据表
void CSatConApp::SelectReadableVal()
{
	TableNum=0;
	for(int i=0;i<=m_para_tot_num;i++)
	{
		if(TRUE==m_para_info[i].RdContinue||TRUE==m_para_info[i].commable)
		{
			ComReadTable[TableNum]=&m_para_info[i];
			TableNum++;
		}
	}
}
//串口数据表排序
void CSatConApp::BasisAddressSortTable()
{
	int flag;
	PARAINI_INFO *swap=NULL;

    for(int i=0;i<TableNum;i++)
    {
        flag=0;
        for(int j=0;j<(TableNum-1-i);j++)
        {
            if(ComReadTable[j+1]->address<ComReadTable[j]->address)
            {
                swap=ComReadTable[j];
                ComReadTable[j]=ComReadTable[j+1];
                ComReadTable[j+1]=swap;
                flag=1;
            }
        }
        if(flag==0) break;
    }
}
