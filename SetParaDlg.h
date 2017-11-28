#if !defined(AFX_SETPARADLG_H__4D9CA895_843C_423B_8F3D_5B12772E3E75__INCLUDED_)
#define AFX_SETPARADLG_H__4D9CA895_843C_423B_8F3D_5B12772E3E75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetParaDlg.h : header file
//菜单选择变量参数设置对话框
#include "BaseData.h"
/////////////////////////////////////////////////////////////////////////////
// SetParaDlg dialog

class SetParaDlg : public CDialog
{
// Construction
public:
	SetParaDlg(PARAINI_INFO *paraini,int *totnum,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SetParaDlg)
	enum { IDD = IDD_SETPARA_DIALOG };
	CComboBox	m_namebox;
	CString	m_adderss;
	CString	m_binary;
	CString	m_comment;
	CString	m_decadal;
	CString	m_format;
	CString	m_max;
	CString	m_min;
	CString	m_step;
	CString	m_unit;
	CString	m_value;
	BOOL	m_readable;
	BOOL	m_writeable;
	BOOL	m_readcont;
	//}}AFX_DATA

private:
	int *m_paratotnum;
	PARAINI_INFO *m_pparaini;
	int m_CurrSel;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetParaDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetParaDlg)
	virtual void OnOK();
	afx_msg void OnSelchangeNameCombo();
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeNameCombo();
	afx_msg void OnSaveButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETPARADLG_H__4D9CA895_843C_423B_8F3D_5B12772E3E75__INCLUDED_)
