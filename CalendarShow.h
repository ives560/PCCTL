#if !defined(AFX_CALENDARSHOW_H__2F1EA4B9_D2E6_45BD_ADBE_3B3CDAD054B8__INCLUDED_)
#define AFX_CALENDARSHOW_H__2F1EA4B9_D2E6_45BD_ADBE_3B3CDAD054B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarShow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalendarShow dialog

class CCalendarShow : public CDialog
{
// Construction
public:
	CCalendarShow(CWnd* pParent = NULL);   // standard constructor
	CList<CString,CString&>*pSlist;
	CString SeleTableName;
// Dialog Data
	//{{AFX_DATA(CCalendarShow)
	enum { IDD = IDD_CALENDAR_SHOW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarShow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalendarShow)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARSHOW_H__2F1EA4B9_D2E6_45BD_ADBE_3B3CDAD054B8__INCLUDED_)
