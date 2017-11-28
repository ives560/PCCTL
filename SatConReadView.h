// SatConReadView.h : interface of the CSatConReadView class
//只读变量窗口视图类
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SATCONREADVIEW_H__670A73B5_15CB_4D29_ADA4_901BB0BA4FAC__INCLUDED_)
#define AFX_SATCONREADVIEW_H__670A73B5_15CB_4D29_ADA4_901BB0BA4FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SatConReadDoc.h"
#include "SubDlg.h"
#include "CommSet.h"
class CSatConReadView : public CFormView
{
protected: // create from serialization only
	CSatConReadView();
	DECLARE_DYNCREATE(CSatConReadView)

public:
	//{{AFX_DATA(CSatConReadView)
	enum { IDD = IDD_SATCON_READ_FORM };
	CTabCtrl	m_ReaderTab;
	//}}AFX_DATA

// Attributes
public:
	CSatConReadDoc* GetDocument();
public:

// Operations
public:
	CMenu m_popupMenu;
	CPoint m_MenuPoint;
	
	CRect m_formrect;
	int m_curSelPage;
	CSatConReadDoc* m_pReadDoc;
	CSubDlg *m_ReadDlg[TAB_MAX_NUM][ITEM_MAX_NUM];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSatConReadView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	int ShowTabComb(int page,int isShow);
protected:
	bool m_initOver;
	int UpdateItemRect(int i,int j);
	int CreateItem(int i,int j);
	virtual ~CSatConReadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSatConReadView)
	afx_msg void OnSelchangeReaderTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg void OnPopmenuDeleteItem(WPARAM wParam,LPARAM lParam);
	afx_msg void OnPopmenuNewItem();
	afx_msg void OnPopmenuNewPage();
	afx_msg void OnPopmenuDeletePage();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SatConReadView.cpp
inline CSatConReadDoc* CSatConReadView::GetDocument()
   { return (CSatConReadDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SATCONREADVIEW_H__670A73B5_15CB_4D29_ADA4_901BB0BA4FAC__INCLUDED_)
