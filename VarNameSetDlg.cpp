// VarNameSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "VarNameSetDlg.h"
#include "SatConReadDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int m_para_tot_num;
extern PARAINI_INFO m_para_info[MAX_PARA_INI_NUM];
extern bool ChangeTable;
/////////////////////////////////////////////////////////////////////////////
// VarNameSetDlg dialog


VarNameSetDlg::VarNameSetDlg(CString tabname,RECT rect,	ItemInfo *iteminfo,CWnd* pParent /*=NULL*/)
	: CDialog(VarNameSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(VarNameSetDlg)
	m_setabnam = _T("");
	//}}AFX_DATA_INIT
	m_setabnam=tabname;
	m_FramRect=rect;
	m_pSetiteminfo=iteminfo;
}


void VarNameSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VarNameSetDlg)
	DDX_Control(pDX, IDC_VARNAME_COMBO, m_namebox);
	DDX_Text(pDX, IDC_TABNAME_EDIT, m_setabnam);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VarNameSetDlg, CDialog)
	//{{AFX_MSG_MAP(VarNameSetDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VarNameSetDlg message handlers
BOOL VarNameSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	RECT rect;
	GetClientRect(&rect);
	rect.left += m_FramRect.left;
	rect.top += m_FramRect.top;
	rect.right += m_FramRect.left;
	rect.bottom += m_FramRect.top;
	MoveWindow(&rect,TRUE);		//显示位置
/////////////////////////////////////////////////////
	m_pMainFram = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	for(int i=0;i<=m_para_tot_num;i++)
	{
		m_namebox.InsertString(i,m_para_info[i].itemName);
		if(strcmp(m_para_info[i].itemName,m_pSetiteminfo->ValName)==0)
			m_namebox.SetCurSel(i);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void VarNameSetDlg::OnOK() 
{
	// TODO: Add extra validation here
	int i=m_namebox.GetCurSel();
	if(i>=0)
	{
		m_pSetiteminfo->ValInfo=&m_para_info[i];		//变量信息指针
		strcpy(m_pSetiteminfo->ValName,m_para_info[i].itemName);//变量名
		m_pSetiteminfo->ValInfo->commable=TRUE;
		ChangeTable=TRUE;
	}
	CDialog::OnOK();
}
