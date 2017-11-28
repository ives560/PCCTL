#if !defined(AFX_SUBDLG_H__A3EE4BF6_CCFA_4345_AD83_74D6847642A9__INCLUDED_)
#define AFX_SUBDLG_H__A3EE4BF6_CCFA_4345_AD83_74D6847642A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlg.h : header file
//只读变量对话框
#include "BaseData.h"

/////////////////////////////////////////////////////////////////////////////
// CSubDlg dialog

class CSubDlg : public CDialog
{
// Construction
public:
	CSubDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubDlg)
	enum { IDD = IDD_SUB_DIALOG };
	CButton	m_readitem;
	CString	m_unit;
	float	m_val;
	//}}AFX_DATA
public:
	void UpValData();
	void UpdateReadItem();
	int pageNumber;
	int itemNumber;
	CString m_tipstr;
	ItemInfo *m_iteminfo;
private:

	CToolTipCtrl m_TipCtrl;
private:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL Create(UINT nID,CWnd* pParentWnd,int i,int j,ItemInfo *iteminfo);
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlg)
	afx_msg void OnChangeReadBaseEdit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	afx_msg void OnPopmenuDeleteItem();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLG_H__A3EE4BF6_CCFA_4345_AD83_74D6847642A9__INCLUDED_)
