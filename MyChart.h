#if !defined(AFX_MYCHART_H__A743DDDF_9B7F_4383_9C97_6429773AE254__INCLUDED_)
#define AFX_MYCHART_H__A743DDDF_9B7F_4383_9C97_6429773AE254__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyChart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyChart form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "MainFrm.h"
#include "ADO.h"
#include "ChartControl.h"
class CMyChart : public CFormView
{
protected:
	CMyChart();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyChart)

// Form Data
public:
	//{{AFX_DATA(CMyChart)
	enum { IDD = IDD_MYCHART_FORM };
	CComboBox	m_para;
	//}}AFX_DATA
public:
	CChartControl m_chart;
// Attributes
public:
	CDC m_dc;
	CMainFrame *m_pMainFram;
	ADO m_ado;
	CString m_BasePath;
	CString m_tablename;
	CTime m_Day;
	bool m_initOver;
	CList<CString,CString&>Snamelist;
	int m_Selet;
// Operations
public:
	void ReadNameTable();
	void EnterNextDay(CTime curDay);
	CString GetTableName();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyChart)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyChart();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMyChart)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeComboPara();
	afx_msg void OnDestroy();
	afx_msg void OnOldchartButton();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMyChartDoc document

class CMyChartDoc : public CDocument
{
protected:
	CMyChartDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyChartDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyChartDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyChartDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyChartDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCHART_H__A743DDDF_9B7F_4383_9C97_6429773AE254__INCLUDED_)
