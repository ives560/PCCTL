#if !defined(AFX_CALENDAR_H__EFAD9D81_285C_4F6D_84D3_573F65386E3C__INCLUDED_)
#define AFX_CALENDAR_H__EFAD9D81_285C_4F6D_84D3_573F65386E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Calendar.h : header file
//
extern const WORD START_YEAR;
extern const WORD END_YEAR;
/////////////////////////////////////////////////////////////////////////////
// CCalendar dialog

class CCalendar : public CDialog
{
// Construction
public:
	CCalendar(CWnd* pParent = NULL);   // standard constructor
	CList<CString,CString&>*DayList;
	CString SeleDay;
private:
	WORD    m_iYear, m_iMonth, m_iDay;

public:
	COLORREF m_dwBackColor,  m_dwForeColor;
	COLORREF m_dwSelColor,   m_dwSelForeColor;
	COLORREF m_dwTitleBkColor, m_dwTitleColor;
public:
	void PaintMonth(CPaintDC &dc);
	void PaintTitle(CPaintDC &dc);
	void PaintOneDay(CPaintDC &dc, CDC &imgdc, WORD &iDay,  
					 LONG startx, LONG starty,bool DataSituat);
public:
	WORD CalcSelectDay(POINT * pt);
	//返回iYear年iMonth月的天数 1年1月 --- 65535年12月
	WORD MonthDays(WORD iYear, WORD iMonth);
	//计算iYear,iMonth,iDay对应是星期几 1年1月1日 --- 65535年12月31日
	WORD WeekDay(WORD iYear, WORD iMonth, WORD iDay);
	//判断iYear是不是闰年
    static BOOL IsLeapYear(WORD iYear)
	{return !(iYear%4)&&(iYear%100) || !(iYear%400);}
public:
	bool GetDataSituation(WORD day);
	bool SetDate(WORD iYear, WORD iMonth, WORD iDay);
	void GetDate(WORD &iYear, WORD &iMonth, WORD &iDay);
	WORD GetYear(){return m_iYear;}
	WORD GetMonth(){return m_iMonth;}
	WORD GetDay(){return m_iDay;}
/*-----------------------------------------------------------------*/
	// Dialog Data
	//{{AFX_DATA(CCalendar)
	enum { IDD = IDD_CALENDAR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	public:
	virtual BOOL Create(RECT &rect, CWnd * pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalendar)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDAR_H__EFAD9D81_285C_4F6D_84D3_573F65386E3C__INCLUDED_)
