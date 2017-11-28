#if !defined(AFX_PASSWORD_H__BA94F73D_ADA4_4F85_A771_7E6A9E230B12__INCLUDED_)
#define AFX_PASSWORD_H__BA94F73D_ADA4_4F85_A771_7E6A9E230B12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassWord.h : header file
//√‹¬Î ‰»Î∂‘ª∞øÚ

/////////////////////////////////////////////////////////////////////////////
// CPassWord dialog

class CPassWord : public CDialog
{
// Construction
public:
	CPassWord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPassWord)
	enum { IDD = IDD_PASSWORD_DIALOG };
	CString	m_password;
	//}}AFX_DATA
public:
	CString PassWordLevel;
	CString RealPassWord;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassWord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPassWord)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWORD_H__BA94F73D_ADA4_4F85_A771_7E6A9E230B12__INCLUDED_)
