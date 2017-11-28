#if !defined(AFX_SATCONWRITEVIEW_H__EAF9DB3B_6BA6_4C51_9E41_B913C78C4ABB__INCLUDED_)
#define AFX_SATCONWRITEVIEW_H__EAF9DB3B_6BA6_4C51_9E41_B913C78C4ABB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SatConWriteView.h : header file
//读写变量窗口视图类

/////////////////////////////////////////////////////////////////////////////
// SatConWriteView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "SatConWriteDoc.h"
#include "SubWriteDlg.h"
#include "CommSet.h"
class SatConWriteView : public CFormView
{
protected:
	SatConWriteView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(SatConWriteView)

// Form Data
public:
	//{{AFX_DATA(SatConWriteView)
	enum { IDD = IDD_SATCON_WRITE_FORM };
	CButton	m_saveall;
	CButton	m_loadFpc;
	CButton	m_loadFdsp;
	CButton	m_clear;
	CTabCtrl	m_WriteTab;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:	
	CMenu m_popupMenu;
	CPoint m_MenuPoint;
	CRect m_formrect;
	int m_curSelPage;
	SatConWriteDoc* m_pWriteDoc;
	SubWriteDlg *m_WriteDlg[TAB_MAX_NUM][ITEM_MAX_NUM];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SatConWriteView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	int ShowTabComb(int page,int isShow);
protected:
	bool m_initOver;
	int CreateItem(int i,int j);
	int UpdateItemRect(int i,int j);
	virtual ~SatConWriteView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(SatConWriteView)
		afx_msg void OnSelchangeWriteTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClearButton();
	afx_msg void OnLoadfdspButton();
	afx_msg void OnLoadfpcButton();
	afx_msg void OnSaveallButton();
	//}}AFX_MSG
	afx_msg void OnPopmenuDeleteItem(WPARAM wParam,LPARAM lParam);
	afx_msg void OnPopmenuNewItem();
	afx_msg void OnPopmenuNewPage();
	afx_msg void OnPopmenuDeletePage();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SATCONWRITEVIEW_H__EAF9DB3B_6BA6_4C51_9E41_B913C78C4ABB__INCLUDED_)
