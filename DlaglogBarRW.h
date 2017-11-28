#if !defined(AFX_DLAGLOGBARRW_H__8B5368CA_20AB_4B4A_8077_FBA19EA6C20A__INCLUDED_)
#define AFX_DLAGLOGBARRW_H__8B5368CA_20AB_4B4A_8077_FBA19EA6C20A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlaglogBarRW.h : header file
//在顶部读写工具条中显示读写变量的对话框
#include "TopReadSet.h"
/////////////////////////////////////////////////////////////////////////////
// DlaglogBarRW dialog

class DlaglogBarRW : public CDialog
{
// Construction
public:
	void UpdateItemRect();
	DlaglogBarRW(CWnd* pParent = NULL);   // standard constructor
	int num;
	COLORREF m_Color;
	COLORREF m_oldCol;
	CString m_oldDply;
private:
	TopReadSet ReadSetDlg;

// Dialog Data
	//{{AFX_DATA(DlaglogBarRW)
	enum { IDD = IDD_DIALOGBAR_RW };
	float	m_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlaglogBarRW)
	public:
	virtual BOOL Create(UINT nID,CWnd* pParentWnd,int number);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlaglogBarRW)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnValbarStatic();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLAGLOGBARRW_H__8B5368CA_20AB_4B4A_8077_FBA19EA6C20A__INCLUDED_)
