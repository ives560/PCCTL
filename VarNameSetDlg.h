#if !defined(AFX_VARNAMESETDLG_H__834A3370_36FA_46E5_AE15_CCD1C51FF003__INCLUDED_)
#define AFX_VARNAMESETDLG_H__834A3370_36FA_46E5_AE15_CCD1C51FF003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VarNameSetDlg.h : header file
//tab控件页中要选择变量名显示的对话框
#include "MainFrm.h"
#include "BaseData.h"
/////////////////////////////////////////////////////////////////////////////
// VarNameSetDlg dialog

class VarNameSetDlg : public CDialog
{
// Construction
public:
	VarNameSetDlg(CString tabname,RECT rect,ItemInfo *iteminfo,CWnd* pParent = NULL);   // standard constructor
protected:
	RECT m_FramRect;
	ItemInfo *m_pSetiteminfo;
	CMainFrame *m_pMainFram;

public:
	PARAINI_INFO m_paraset;
// Dialog Data
	//{{AFX_DATA(VarNameSetDlg)
	enum { IDD = IDD_VARNAME_SET_DIALOG };
	CComboBox	m_namebox;
	CString	m_setabnam;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VarNameSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VarNameSetDlg)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VARNAMESETDLG_H__834A3370_36FA_46E5_AE15_CCD1C51FF003__INCLUDED_)
