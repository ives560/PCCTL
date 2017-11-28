// CalendarShow.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "CalendarShow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarShow dialog


CCalendarShow::CCalendarShow(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendarShow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarShow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCalendarShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarShow)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalendarShow, CDialog)
	//{{AFX_MSG_MAP(CCalendarShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarShow message handlers

BOOL CCalendarShow::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(pSlist->GetCount()>0)
	{

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCalendarShow::OnOK() 
{
	// TODO: Add extra validation here
	if(SeleTableName=="")//检查选中日期
	{
		MessageBox("所选日期无数据!");
	}
	CDialog::OnOK();
}
