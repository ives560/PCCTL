// PassWord.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "PassWord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPassWord dialog


CPassWord::CPassWord(CWnd* pParent /*=NULL*/)
	: CDialog(CPassWord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPassWord)
	m_password = _T("");
	//}}AFX_DATA_INIT
	PassWordLevel=_T("");
	RealPassWord=_T("");
}


void CPassWord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPassWord)
	DDX_Text(pDX, IDC_PASSWORD_EDIT, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPassWord, CDialog)
	//{{AFX_MSG_MAP(CPassWord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassWord message handlers

void CPassWord::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(m_password!=RealPassWord)
	{
		GetDlgItem(IDC_PROMPT_STATIC)->SetWindowText("The password is wrong.");
		return;
	}
	CDialog::OnOK();
}

BOOL CPassWord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_PASSWORD_STATIC)->SetWindowText(PassWordLevel);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
