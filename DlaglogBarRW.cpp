// DlaglogBarRW.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "DlaglogBarRW.h"
#include "BaseData.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern MainInfo m_maininfo;
/////////////////////////////////////////////////////////////////////////////
// DlaglogBarRW dialog


DlaglogBarRW::DlaglogBarRW(CWnd* pParent /*=NULL*/)
	: CDialog(DlaglogBarRW::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlaglogBarRW)
	m_value = 0.0f;
	//}}AFX_DATA_INIT
}


void DlaglogBarRW::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlaglogBarRW)
	DDX_Text(pDX, IDC_VALBAR_STATIC, m_value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlaglogBarRW, CDialog)
	//{{AFX_MSG_MAP(DlaglogBarRW)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_VALNAMEBAR_STATIC, OnValbarStatic)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlaglogBarRW message handlers

HBRUSH DlaglogBarRW::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_VALNAMEBAR_STATIC)
		pDC->SetTextColor(m_Color);
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL DlaglogBarRW::Create(UINT nID,CWnd* pParentWnd,int number) 
{
	// TODO: Add your specialized code here and/or call the base class
	num=number;
	return CDialog::Create(IDD, pParentWnd);
}

void DlaglogBarRW::OnValbarStatic() 
{
	// TODO: Add your control notification handler code here
	ReadSetDlg.DestroyWindow();
	ReadSetDlg.Create(num,this,IDD_TOPREADSET_DIALOG);
	CRect Prect;
	GetWindowRect(Prect);
	RECT rect;
	ReadSetDlg.GetClientRect(&rect);
	rect.left += Prect.left;
	rect.top += Prect.top;
	rect.right += Prect.left;
	rect.bottom += Prect.top;

	CMainFrame* pFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pFrame->GetWindowRect(Prect);
	int width=GetSystemMetrics( SM_CXSCREEN );// 屏幕宽
	if(rect.right>width)
	{
		rect.left -= (rect.right-width);
		rect.right = width;
	}
	if(rect.right>Prect.right)
	{
		rect.left -= (rect.right-Prect.right);
		rect.right = Prect.right;
	}
	ReadSetDlg.MoveWindow(&rect,TRUE);		//显示位置
}

BOOL DlaglogBarRW::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_oldCol=0;
	m_oldDply=" ";
	UpdateItemRect();
	SetTimer(1,300,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlaglogBarRW::UpdateItemRect()
{
	CString str;
	str=m_maininfo.mainval[num].Dply_Name;
	if(m_oldDply!=str)
		GetDlgItem(IDC_VALNAMEBAR_STATIC)->SetWindowText(str); //变量名
	m_oldDply=str;

	str=m_maininfo.mainval[num].Dply_Color;//颜色
	m_Color=atol(str);
	if(m_oldCol!=m_Color)
		GetDlgItem(IDC_VALNAMEBAR_STATIC)->Invalidate();
	m_oldCol=m_Color;

	if(m_maininfo.mainval[num].ValInfo!=0)//有变量值
	{
		//int val=m_maininfo.mainval[num].ValInfo->curval;
		//str.Format("%d",val);
		//GetDlgItem(IDC_VALBAR_STATIC)->SetWindowText(str);
		m_value=m_maininfo.mainval[num].ValInfo->curval;
		UpdateData(FALSE);
	}
	else
		GetDlgItem(IDC_VALBAR_STATIC)->SetWindowText("");

}

void DlaglogBarRW::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateItemRect();
	CDialog::OnTimer(nIDEvent);
}
