// DialogBarBit.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "DialogBarBit.h"
#include "BaseData.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern MainInfo m_maininfo;
/////////////////////////////////////////////////////////////////////////////
// DialogBarBit dialog


DialogBarBit::DialogBarBit(CWnd* pParent /*=NULL*/)
	: CDialog(DialogBarBit::IDD, pParent)
{
	//{{AFX_DATA_INIT(DialogBarBit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DialogBarBit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DialogBarBit)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DialogBarBit, CDialog)
	//{{AFX_MSG_MAP(DialogBarBit)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BIT_STATIC, OnBitStatic)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DialogBarBit message handlers

HBRUSH DialogBarBit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_BIT_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr=m_brush;

	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL DialogBarBit::Create(UINT nID,CWnd* pParentWnd,int number) 
{
	// TODO: Add your specialized code here and/or call the base class
	num=number;

	return CDialog::Create(IDD, pParentWnd);
}

BOOL DialogBarBit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_oldCol=0;
	m_oldDispl=" ";
	m_brush=CreateSolidBrush(m_Color);
	UpdateItemRect();
	SetTimer(1,300,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void DialogBarBit::OnBitStatic() 
{
	// TODO: Add your control notification handler code here
//	if(BitDlgflg)
//		BitSetDlg.DestroyWindow();
	BitSetDlg.Create(num,this,IDD_TOPBITSET_DIALOG);
	CRect Prect;
	GetWindowRect(Prect);

	RECT rect;
	BitSetDlg.GetClientRect(&rect);
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
	BitSetDlg.MoveWindow(&rect,TRUE);		//显示位置
}

void DialogBarBit::UpdateItemRect()
{
	if(m_maininfo.mainbit[num].pvalbitinfo!=0)//有变量值
	{
		int val;
		int i=m_maininfo.mainbit[num].Bit_No;
		if(m_maininfo.mainbit[num].ValInfo!=0)
		{
			val=m_maininfo.mainbit[num].ValInfo->curval;
			val=(val>>i)&0x01;
		}
		else
			val=0;
		CString str=m_maininfo.mainbit[num].pvalbitinfo->bitinfo[i].Displ[val];
		if(m_oldDispl!=str)
			GetDlgItem(IDC_BIT_STATIC)->SetWindowText(str);
		m_oldDispl=str;
		str=m_maininfo.mainbit[num].pvalbitinfo->bitinfo[i].Color[val];//颜色
		m_Color=atol(str);
		if(m_Color==0)m_Color=RGB(255,255,255);

		if(m_oldCol!=m_Color)
		{
			DeleteObject(m_brush);
			m_brush=CreateSolidBrush(m_Color);
			GetDlgItem(IDC_BIT_STATIC)->Invalidate();
		}
		m_oldCol=m_Color;
	}
	else
	{
		GetDlgItem(IDC_BIT_STATIC)->SetWindowText("");
		m_Color=RGB(255,255,255);
		DeleteObject(m_brush);
		m_brush=CreateSolidBrush(m_Color);
		GetDlgItem(IDC_BIT_STATIC)->Invalidate();
	}

}

void DialogBarBit::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateItemRect();
	CDialog::OnTimer(nIDEvent);
}
