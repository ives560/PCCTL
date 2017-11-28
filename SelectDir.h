#if !defined(AFX_SELECTDIR_H__118746C5_809C_42F2_BE66_422177DAC995__INCLUDED_)
#define AFX_SELECTDIR_H__118746C5_809C_42F2_BE66_422177DAC995__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectDir.h : header file
//变量路径选择

/////////////////////////////////////////////////////////////////////////////
// CSelectDir dialog

class CSelectDir : public CDialog
{
// Construction
public:
	CSelectDir(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CSelectDir)
	enum { IDD = IDD_SEL_DIRECTORY_DIALOG };
	CComboBox	m_Directory;
	//}}AFX_DATA
public:
	CFont m_font; 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectDir)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ReadMainIni();
	void filterStr(char *str);
	// Generated message map functions
	//{{AFX_MSG(CSelectDir)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowseButton();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTDIR_H__118746C5_809C_42F2_BE66_422177DAC995__INCLUDED_)
