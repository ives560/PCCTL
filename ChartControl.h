#if !defined(AFX_CHARTCONTROL_H__A980C389_5C71_40ED_8B55_E93B5B86E8BF__INCLUDED_)
#define AFX_CHARTCONTROL_H__A980C389_5C71_40ED_8B55_E93B5B86E8BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartControl.h : header file
//
#include "BaseData.h"
/////////////////////////////////////////////////////////////////////////////
// CChartControl window

class CChartControl : public CWnd
{
// Construction
public:
	CChartControl();

// Attributes
public:
	CDC m_dc;
	CBitmap m_BitMap;
	CPoint m_origion;
	CPoint m_Xend;
	CPoint m_Yend;
	CPoint m_section;
	CList<CPoint,CPoint&>Plist;
	CList<CTime,CTime&>Tlist;
	CList<double,double&>Dlist;
	PARAINI_INFO *m_pinfo;

	CString YaxisStr;
	int YMax;
	int Yaxis;
	double m_unitX;
	double m_unitY;

	CString m_BasePath;
	CString m_tablename;
	CTime m_Day;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartControl)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString TimeToStr(CTime time);
	CTime StrToTime(CString timeStr);
	void GetPoints(CTime time,double var);
	void DrawGraph();
	void DrawSection(int sum, bool XorY);
	void DrowCoor();
	void InitCoordinate(CRect rect);
	virtual ~CChartControl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChartControl)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTCONTROL_H__A980C389_5C71_40ED_8B55_E93B5B86E8BF__INCLUDED_)
