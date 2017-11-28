// OldChart.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "OldChart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COldChart dialog


COldChart::COldChart(CWnd* pParent /*=NULL*/)
	: CDialog(COldChart::IDD, pParent)
{
	//{{AFX_DATA_INIT(COldChart)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COldChart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COldChart)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COldChart, CDialog)
	//{{AFX_MSG_MAP(COldChart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COldChart message handlers

BOOL COldChart::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
		0, (HBRUSH)CBrush(RGB(255,255,255)), 0);
	CRect rect;
	GetClientRect(rect);
	m_chart.CreateEx(WS_EX_CLIENTEDGE, szClassName, _T(""),
		WS_CHILD|WS_VISIBLE|WS_TABSTOP, rect, 
		this, ID_OCHART_DIALOG, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
