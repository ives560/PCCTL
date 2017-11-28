#if !defined(AFX_SATCONBITSHOWVIEW_H__4AD49163_DD82_43F8_AD5F_5D2235442BF0__INCLUDED_)
#define AFX_SATCONBITSHOWVIEW_H__4AD49163_DD82_43F8_AD5F_5D2235442BF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SatConBitShowView.h : header file
//
#include "SatConBitShowDoc.h"
#include "SubBitDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CSatConBitShowView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSatConBitShowView : public CFormView
{
protected:
	CSatConBitShowView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSatConBitShowView)

// Form Data
public:
	//{{AFX_DATA(CSatConBitShowView)
	enum { IDD = IDD_SATCON_BITSHOW_FORM };
	CTabCtrl	m_BitShowTab;
	//}}AFX_DATA

// Attributes
public:
	CMenu m_popupMenu;
	CPoint m_MenuPoint;
	
	CRect m_formrect;
	int m_curSelPage;
	CSatConBitShowDoc* m_pBitDoc;
	SubBitDlg *m_BitDlg[TAB_MAX_NUM][ITEM_MAX_NUM];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSatConBitShowView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	int ShowTabComb(int page,int isShow);
private:
	bool m_initOver;
// Implementation
protected:
	int UpdateItemRect(int i,int j);
	int CreateItem(int i,int j);
	virtual ~CSatConBitShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSatConBitShowView)
	afx_msg void OnSelchangeBitshowTab(NMHDR* pNMHDR, LRESULT* pResult);
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

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SATCONBITSHOWVIEW_H__4AD49163_DD82_43F8_AD5F_5D2235442BF0__INCLUDED_)
