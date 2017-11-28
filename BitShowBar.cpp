// BitShowBar.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "BitShowBar.h"
#include "UniButton.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CUniButton m_commLed;

/////////////////////////////////////////////////////////////////////////////
// BitShowBar dialog


BitShowBar::BitShowBar(CWnd* pParent /*=NULL*/)

{
	//{{AFX_DATA_INIT(BitShowBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void BitShowBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BitShowBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BitShowBar, CDialogBar)
	//{{AFX_MSG_MAP(BitShowBar)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BitShowBar message handlers
LONG BitShowBar::OnInitDialog(UINT wParam, LONG lParam)
{
	BOOL bRet = HandleInitDialog(wParam, lParam);
	CPoint point;
	point.x=10;
	point.y=10;
	CRect rect;
	HRGN rgn = CreateEllipticRgn(0, 0, 20, 20);
	m_commLed.Create("", WS_VISIBLE, point, rgn, this,IDC_LED_BUTTON);
	m_commLed.m_nColor=RGB(255,0,0);
	m_commLed.Invalidate();
	for(int i=0;i<12;i++)
	{
		CreateItem(0, i);
		if(i<7)
		CreateItem(1, i);
	}

	return bRet;
}

HBRUSH BitShowBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void BitShowBar::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialogBar::OnTimer(nIDEvent);
}

int BitShowBar::CreateItem(int i, int j)
{
	CRect frmrect,dlgrect,rect;
	GetClientRect(frmrect);
	frmrect.top += 5;
	frmrect.left += 50;
	if(i==0)
	{
		dlgbarBit[j].Create(IDD_DIALOGBAR_BIT,this,j);
		dlgbarBit[j].GetWindowRect(dlgrect);

	}
	else if(i==1)
	{
		dlgbarRW[j].Create(IDD_DIALOGBAR_RW,this,j);
		dlgbarRW[j].GetWindowRect(dlgrect);
	}
	int width=dlgrect.Width()+3;
	int height=dlgrect.Height()+5;
	int lineNum=frmrect.Width()/width;
	if(lineNum<1)lineNum=1;
	int line = i;
	int row = j % lineNum;
	rect.left = frmrect.left+row*width;
	rect.top  =frmrect.top+line*height;
	rect.right=rect.left+dlgrect.Width();
	rect.bottom=rect.top+dlgrect.Height();
	if(i==0)
		dlgbarBit[j].MoveWindow(rect,TRUE);
	else if(i==1)
		dlgbarRW[j].MoveWindow(rect,TRUE);
	return 1;
}
