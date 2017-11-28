#if !defined(AFX_DIALOGBARBIT_H__91A3676A_EB27_4C95_8C85_E082D13B7CEB__INCLUDED_)
#define AFX_DIALOGBARBIT_H__91A3676A_EB27_4C95_8C85_E082D13B7CEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogBarBit.h : header file
//在顶部bit工具条中显示bit变量的对话框

/////////////////////////////////////////////////////////////////////////////
// DialogBarBit dialog
#include "TopBitSet.h"
class DialogBarBit : public CDialog
{
// Construction
public:
	DialogBarBit(CWnd* pParent = NULL);   // standard constructor
	TopBitSet BitSetDlg;
// Dialog Data
	//{{AFX_DATA(DialogBarBit)
	enum { IDD = IDD_DIALOGBAR_BIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
public:
	void UpdateItemRect();
	int num;//
	COLORREF m_Color;
	COLORREF m_oldCol;
	CString m_oldDispl;
	HBRUSH m_brush;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DialogBarBit)
	public:
	virtual BOOL Create(UINT nID,CWnd* pParentWnd,int number);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DialogBarBit)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBitStatic();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGBARBIT_H__91A3676A_EB27_4C95_8C85_E082D13B7CEB__INCLUDED_)
