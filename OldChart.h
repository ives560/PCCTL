#if !defined(AFX_OLDCHART_H__94517125_3DCD_41D0_88AC_7FBCA10A9ABE__INCLUDED_)
#define AFX_OLDCHART_H__94517125_3DCD_41D0_88AC_7FBCA10A9ABE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OldChart.h : header file
//
#include "ChartControl.h"
/////////////////////////////////////////////////////////////////////////////
// COldChart dialog

class COldChart : public CDialog
{
// Construction
public:
	COldChart(CWnd* pParent = NULL);   // standard constructor
	CChartControl m_chart;
// Dialog Data
	//{{AFX_DATA(COldChart)
	enum { IDD = IDD_OLDCHART_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COldChart)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COldChart)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OLDCHART_H__94517125_3DCD_41D0_88AC_7FBCA10A9ABE__INCLUDED_)
