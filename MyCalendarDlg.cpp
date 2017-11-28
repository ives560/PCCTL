// MyCalendarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "MyCalendarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const WORD START_YEAR =1901;//年范围
const WORD END_YEAR   =2050;
/////////////////////////////////////////////////////////////////////////////
// CMyCalendarDlg dialog

CMyCalendarDlg::CMyCalendarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyCalendarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyCalendarDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyCalendarDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyCalendarDlg, CDialog)
	//{{AFX_MSG_MAP(CMyCalendarDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_MONTHSELECT, OnMonthChange)
	ON_EN_CHANGE(IDC_YEAREDIT, OnYearChange)
	ON_BN_CLICKED(IDC_BUTTODAY, OnTodayClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCalendarDlg message handlers

BOOL CMyCalendarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(pSlist->GetCount()>0)
	{
		m_Calendar.DayList=pSlist;
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyCalendarDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyCalendarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CMyCalendarDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CRect rect;
	GetClientRect(&rect);

    if(!m_Calendar.Create(rect, this, IDD_CALENDAR_DIALOG))
		return -1;
/*---------------------------------------------------------------*/
#define LEFT_X   2
#define TOP_Y    160
#define WIDTH    60
#define HEIGHT   22
	//create select year spingbutton and buddy
	rect.SetRect(LEFT_X, TOP_Y, LEFT_X+WIDTH, TOP_Y+HEIGHT);
	if(!m_YearEdit.CreateEx(WS_EX_CLIENTEDGE, _T("EDIT"), NULL, 
		                   WS_CHILD|WS_VISIBLE, rect, this, IDC_YEAREDIT))
		return -1;   
    m_YearEdit.SetLimitText(4);  
/*----------------------------------------------------------------------*/	
    if(!m_YearSelect.Create(UDS_NOTHOUSANDS|WS_CHILD|WS_TABSTOP|
		WS_VISIBLE|UDS_SETBUDDYINT|UDS_ALIGNRIGHT, 
							 rect, this, IDC_YEARSELECT))
							 return -1;
    m_YearSelect.SetBuddy(&m_YearEdit); 
    m_YearSelect.SetRange(START_YEAR, END_YEAR);
	m_YearSelect.SetPos(m_Calendar.GetYear());
/*---------------------------------------------------------------------*/    
	//create select month combobox	
	rect.SetRect(LEFT_X+WIDTH*2, TOP_Y, LEFT_X + WIDTH*3, TOP_Y+HEIGHT*5); 
	if(!m_MonthSelect.Create(WS_VSCROLL|CBS_DROPDOWNLIST|WS_CHILD|
		WS_VISIBLE|WS_TABSTOP, 
		rect, this, IDC_MONTHSELECT))
		return -1;
/*-----------------------------------------------------------------------*/
	//create today button
	rect.SetRect(LEFT_X+WIDTH*4, TOP_Y, LEFT_X+WIDTH*5, TOP_Y+HEIGHT);
	if(!m_butToday.Create("今天", WS_CHILD|WS_VISIBLE|WS_TABSTOP, rect, this, IDC_BUTTODAY))
		return -1; 
	
	CString text;
	for(int i=0; i<12; i++)
	{  
		text.Format("%d",i+1);
		m_MonthSelect.AddString(text);
	}
	m_MonthSelect.SetCurSel(m_Calendar.GetMonth()-1); 
#undef LEFT_X
#undef TOP_Y	
#undef WIDTH 
#undef HEIGHT
	return 0;
}

void CMyCalendarDlg::OnYearChange()
{
	CString text;
	m_YearEdit.GetWindowText(text); 
	if(text.GetLength()<4)
		return;
	
	WORD iYear, iMonth, iDay;
	m_Calendar.GetDate(iYear, iMonth, iDay);
	iYear = m_YearSelect.GetPos();
	
	if(iYear != m_Calendar.GetYear())
	{
		if(iDay > m_Calendar.MonthDays(iYear, iMonth))
			iDay = m_Calendar.MonthDays(iYear, iMonth); 
		m_Calendar.SetDate(iYear, iMonth, iDay); 
		text.Format("%4d", iYear);
		m_YearEdit.SetWindowText(text);
		Invalidate(); 
	}
}
void CMyCalendarDlg::OnMonthChange()
{
	WORD iYear, iDay, iMonth;
	m_Calendar.GetDate(iYear, iMonth, iDay); 
	iMonth = m_MonthSelect.GetCurSel()+1;
	
	if(iMonth != m_Calendar.GetMonth())
	{
		if(iDay > m_Calendar.MonthDays(iYear, iMonth))
			iDay = m_Calendar.MonthDays(iYear, iMonth); 
		m_Calendar.SetDate(iYear, iMonth, iDay); 
		Invalidate(); 
	}
	
}
void CMyCalendarDlg::OnTodayClick()
{
	WORD iYear, iMonth, iDay;
    SYSTEMTIME systime;
	::GetSystemTime(&systime);
	
	iYear  = systime.wYear;
	iMonth = systime.wMonth;
	iDay   = systime.wDay;
    if(iYear != m_Calendar.GetYear() || iMonth != m_Calendar.GetMonth()
		|| iDay  !=  m_Calendar.GetDay())
	{
		m_Calendar.SetDate(iYear, iMonth, iDay);
		m_YearSelect.SetPos(iYear);
		m_MonthSelect.SetCurSel(iMonth -1); 
		Invalidate(); 
	}
}

void CMyCalendarDlg::OnOK() 
{
	// TODO: Add extra validation here
	POSITION pos;
	pos=m_Calendar.DayList->Find(m_Calendar.SeleDay);
	if(pos==NULL)//检查选中日期
	{
		MessageBox("所选日期无数据!");
		return;
	}
	CDialog::OnOK();
}
