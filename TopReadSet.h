#if !defined(AFX_TOPREADSET_H__D76E116C_09BF_482A_8EEF_E5E16D87A330__INCLUDED_)
#define AFX_TOPREADSET_H__D76E116C_09BF_482A_8EEF_E5E16D87A330__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TopReadSet.h : header file
//顶层工具条中只读变量对话框
/////////////////////////////////////////////////////////////////////////////
// TopReadSet dialog

class TopReadSet : public CDialog
{
// Construction
public:
	TopReadSet(CWnd* pParent = NULL);   // standard constructor

private:
	COLORREF m_Color;
	int m_num;
// Dialog Data
	//{{AFX_DATA(TopReadSet)
	enum { IDD = IDD_TOPREADSET_DIALOG };
	CComboBox	m_namecomb;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TopReadSet)
	public:
	virtual BOOL Create(int num,CWnd* pParentWnd, UINT nID);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TopReadSet)
	afx_msg void OnColorStatic();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeNameCombo();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPREADSET_H__D76E116C_09BF_482A_8EEF_E5E16D87A330__INCLUDED_)
