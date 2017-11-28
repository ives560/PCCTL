// Calendar.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "Calendar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
#define COL_WIDTH    30//32
#define ROW_HEIGHT   20
#define TITLE_HEIGHT 20
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// CCalendar dialog

CCalendar::CCalendar(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	/*--------------------------------------------*/
	SYSTEMTIME systime;
	::GetSystemTime(&systime);
	
	m_iYear  = systime.wYear;//获得当天日期并初始化
	m_iMonth = systime.wMonth;
	m_iDay   = systime.wDay;
	/*---------------------------------------------*/
	m_dwBackColor      = RGB(255,255,255);//未选中时的文字背景颜色
	m_dwForeColor      = RGB(0,0,0);//每日的文字颜色
	m_dwSelColor       = RGB(150,150,230);//选中时的背景颜色
	m_dwSelForeColor   = RGB(255,255,255);//选中时的文字颜色
	m_dwTitleBkColor     = RGB(190,70,70);
	m_dwTitleColor = RGB(255,255,0);
}


void CCalendar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalendar, CDialog)
	//{{AFX_MSG_MAP(CCalendar)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendar message handlers
//创建日历窗口
BOOL CCalendar::Create(RECT &rect, CWnd *pParentWnd, UINT nID)
{
    CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|
		CS_HREDRAW|CS_VREDRAW,
		0, (HBRUSH)CBrush(RGB(255,255,255)), 0);

	//rect.left = rect.CenterPoint().x - 64;
	rect.top  += 2; 
	rect.right = rect.left + COL_WIDTH*7 +4;
    rect.bottom = rect.top + TITLE_HEIGHT+ROW_HEIGHT*6 +10 ;

	if(!CWnd::CreateEx(WS_EX_CLIENTEDGE, szClassName, _T(""),
		WS_CHILD|WS_VISIBLE|WS_TABSTOP, rect, 
		pParentWnd, nID, NULL)) 
		
		return FALSE;
	
    UpdateWindow();
	
	return TRUE;
}

void CCalendar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.SetMapMode(0);
	PaintTitle(dc);//显示星期标题
	PaintMonth(dc);//画日历一个月的每一日
	// Do not call CDialog::OnPaint() for painting messages
}
//显示星期标题
void CCalendar::PaintTitle(CPaintDC &dc)
{
	   CRect rect ;
	   GetClientRect(&rect);
	   
	   rect.left ++;   rect.top ++;
	   rect.right --;  rect.bottom = rect.top + TITLE_HEIGHT;
	   dc.FillRect(&rect, &CBrush(m_dwTitleBkColor));
	   
	   dc.SetBkColor(m_dwTitleBkColor); 
	   dc.SetTextColor(m_dwTitleColor); 
	   
	   int startx = rect.left +8;
	   CString sztext[]={"日","一","二","三","四","五","六"};
	   for(int i=0; i <7; i++)
	   {
		   dc.TextOut(startx, rect.top +2, sztext[i]);
		   startx += COL_WIDTH;
		}
}
//画日历一个月的每一日
void CCalendar::PaintMonth(CPaintDC &dc)
{
	   CDC imgdc;
	   imgdc.CreateCompatibleDC(&dc);
	   
	   RECT rect;
	   GetClientRect(&rect);
	   rect.top  +=TITLE_HEIGHT+6;
	   
	   dc.SetBkColor(m_dwBackColor);
	   dc.SetTextColor(m_dwForeColor);
	   
	   WORD day =1;
	   bool Situation;
	   WORD weekday=WeekDay(m_iYear, m_iMonth, 1);
	   WORD monthDay=MonthDays(m_iYear, m_iMonth);
	   for(int i=0; i<6; i++, rect.top += ROW_HEIGHT)
	   {
		   long startx = rect.left +2;
		   for(int j=0; j<7; j++,startx += COL_WIDTH)
		   {
			   if(j < weekday && i==0)
				   continue;
			   
			   if(day >monthDay)
				   break;

			   Situation=GetDataSituation(day);
			   PaintOneDay(dc, imgdc, day,startx, rect.top,Situation);//画日历一日
			   day++;
		   }
	   }
}

WORD CCalendar::WeekDay(WORD iYear, WORD iMonth, WORD iDay)
{
	//数组元素monthday[i]表示第i个月以前的总天数除以7的余数
	WORD monthday[]={0,3,3,6,1,4,6,2,5,0,3,5};
	WORD iDays = (iYear-1)%7 + (iYear-1)/4 - (iYear-1)/100 +(iYear-1)/400;
	iDays += (monthday[iMonth-1] +iDay) ;
	//如果iYear是闰年
    if(IsLeapYear(iYear) && iMonth>2)
		iDays++;
	//返回:0,1,2,3,4,5,6表日、一、二、三、四、五、六
	return iDays%7;
}

WORD CCalendar::MonthDays(WORD iYear, WORD iMonth)
{
	switch(iMonth)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:case 12:
		return 31;
		break;
	case 4:case 6:case 9:case 11:
		return 30;
		break;
	case 2:
		//如果是闰年
		if(IsLeapYear(iYear))
			return 29;
		else
			return 28;
		break;
	}
	return 0;
}
//画日历一日
void CCalendar:: PaintOneDay(CPaintDC &dc, CDC &imgdc, WORD &iDay,  
							 LONG startx, LONG starty,bool DataSituat)
{
	char text[3];
	sprintf(text, "%2d", iDay);
	
	if(iDay== m_iDay)
	{
		dc.FillRect(&CRect(startx-1, starty, 
			startx +COL_WIDTH-3, starty + ROW_HEIGHT), 
			&CBrush(m_dwSelColor));//填充选中矩形颜色
		dc.SetTextColor(m_dwSelForeColor);
		dc.SetBkColor(m_dwSelColor);
		dc.TextOut(startx+4, starty +2, text);
		dc.SetBkColor(m_dwBackColor);
		dc.SetTextColor(m_dwForeColor); 
		dc.BitBlt(startx+17, starty +2, 8,16,&imgdc,0,0,MERGEPAINT);  		
	}
	else
	{
		dc.FillRect(&CRect(startx-1, starty, 
			startx +COL_WIDTH-3, starty + ROW_HEIGHT), 
			&CBrush(m_dwBackColor));//填充选中矩形颜色
		if(DataSituat==TRUE)//有数据
			dc.SetTextColor(RGB(0,0,255));
		else
			dc.SetTextColor(m_dwForeColor);
		dc.TextOut(startx+4, starty+2, text);	
		dc.BitBlt(startx+17, starty +2, 8,16,&imgdc,0,0,SRCCOPY);  
	}

}

void CCalendar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	WORD day = CalcSelectDay(&point);
	if(day !=0 && day != m_iDay)
	{
		m_iDay = day;
		SeleDay.Format("%.2d%.2d%.2d",m_iYear,m_iMonth,m_iDay);
		Invalidate(FALSE);
    }
	SetFocus();
	CDialog::OnLButtonDown(nFlags, point);
}

WORD CCalendar::CalcSelectDay(POINT *pt)
{
	RECT rect;
    GetClientRect(&rect);
	WORD iRow = (pt->y - rect.top -26)/ROW_HEIGHT;
	WORD iCol = (pt->x - rect.left )/COL_WIDTH;
	
	WORD startcol ,endrow, endcol;
	startcol = WeekDay(m_iYear, m_iMonth, 1);
	endcol   = WeekDay(m_iYear, m_iMonth, MonthDays(m_iYear,m_iMonth));
	
	endrow   = (MonthDays(m_iYear, m_iMonth) + startcol -1)/7 ;
    if(iRow == 0 && iCol < startcol || iRow == endrow && iCol > endcol ||  iRow > endrow)
		return 0;
	return iRow *7 + iCol + 1 - startcol ;
}

void CCalendar::GetDate(WORD &iYear, WORD &iMonth, WORD &iDay)
{
	iYear  = m_iYear;
	iMonth = m_iMonth;
	iDay   = m_iDay;
}

bool CCalendar::SetDate(WORD iYear, WORD iMonth, WORD iDay)
{
	if(iYear < START_YEAR || iYear > END_YEAR || iMonth <1 || iMonth >12)
		return FALSE;
	
	if(iDay <1 || iDay > MonthDays(iYear, iMonth))
		return FALSE;
	
	m_iYear   = iYear;
	m_iMonth  = iMonth;
	m_iDay    = iDay;
  SeleDay.Format("%.2d%.2d%.2d",m_iYear,m_iMonth,m_iDay);	
  return TRUE;
}

bool CCalendar::GetDataSituation(WORD day)
{
	CString str;
	str.Format("%.2d%.2d%.2d",m_iYear,m_iMonth,day);
	POSITION	pos;
	pos=DayList->Find(str);
	if(pos!=NULL)
		return true;
	else
		return false;
}
