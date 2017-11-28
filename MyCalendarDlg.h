// MyCalendarDlg.h : header file
//

#if !defined(AFX_MYCALENDARDLG_H__FC9AB4E7_C724_4096_BE87_FF77A42EC41D__INCLUDED_)
#define AFX_MYCALENDARDLG_H__FC9AB4E7_C724_4096_BE87_FF77A42EC41D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Calendar.h"
/////////////////////////////////////////////////////////////////////////////
// CMyCalendarDlg dialog

class CMyCalendarDlg : public CDialog
{
// Construction
public:
	CMyCalendarDlg(CWnd* pParent = NULL);	// standard constructor

	CList<CString,CString&>*pSlist;
	CCalendar m_Calendar;
// Dialog Data
	//{{AFX_DATA(CMyCalendarDlg)
	enum { IDD = IDD_MYCALENDAR_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCalendarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CSpinButtonCtrl  m_YearSelect;
	CComboBox        m_MonthSelect;
	CEdit			 m_YearEdit;
	CButton          m_butToday;
	// Generated message map functions
	//{{AFX_MSG(CMyCalendarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnOK();
	//}}AFX_MSG
	afx_msg void OnMonthChange();
	afx_msg void OnYearChange();
	afx_msg void OnTodayClick();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCALENDARDLG_H__FC9AB4E7_C724_4096_BE87_FF77A42EC41D__INCLUDED_)
