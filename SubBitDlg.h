#if !defined(AFX_SUBBITDLG_H__5BC1C3DF_15FD_4397_80F5_477CF4E97C8A__INCLUDED_)
#define AFX_SUBBITDLG_H__5BC1C3DF_15FD_4397_80F5_477CF4E97C8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubBitDlg.h : header file
//tab控件页面中位变量对话框

/////////////////////////////////////////////////////////////////////////////
// SubBitDlg dialog
#include "UniButton.h"
#include "BaseData.h"
class SubBitDlg : public CDialog
{
// Construction
public:
	SubBitDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SubBitDlg)
	enum { IDD = IDD_SUB_DIALOG_BIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
public:
	void UpValData();
	void UpdateBitItem();
	CUniButton m_led;
	int pageNumber;
	int itemNumber;
	CString m_tipstr;
	ItemInfo *m_iteminfo;
	CToolTipCtrl m_TipCtrl;
	COLORREF m_oldcl;
	CString m_oldDispl;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SubBitDlg)
	public:
	virtual BOOL Create(UINT nID,CWnd* pParentWnd,int i,int j,ItemInfo *iteminfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:
	COLORREF StrToRgb(CString str);

	// Generated message map functions
	//{{AFX_MSG(SubBitDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void OnLedButtonClicked();
	afx_msg void OnPopmenuDeleteItem();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBBITDLG_H__5BC1C3DF_15FD_4397_80F5_477CF4E97C8A__INCLUDED_)
