#if !defined(AFX_SUBWRITEDLG_H__C665A9D7_BF3C_4C41_B275_143C6727304B__INCLUDED_)
#define AFX_SUBWRITEDLG_H__C665A9D7_BF3C_4C41_B275_143C6727304B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubWriteDlg.h : header file
//tab控件页面中读写变量对话框
#include "BaseData.h"
/////////////////////////////////////////////////////////////////////////////
// SubWriteDlg dialog

class SubWriteDlg : public CDialog
{
// Construction
public:
	SubWriteDlg(CWnd* pParent = NULL);   // standard constructor
public:
	int editcolor;		//编辑框颜色
	int pageNumber;
	int itemNumber;
	CString m_tipstr;
	ItemInfo *m_iteminfo;
	CToolTipCtrl m_TipCtrl;
// Dialog Data
	//{{AFX_DATA(SubWriteDlg)
	enum { IDD = IDD_SUB_DIALOG_WRITE };
	CButton	m_writeitem;
	float	m_val;
	CString	m_unit;
	float	m_step;
	float	m_currval;
	//}}AFX_DATA

public:
	void UpValData();
	void ChangeColor(int color);
	void UpdateWriteItem();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SubWriteDlg)
	public:
	virtual BOOL Create(UINT nID,CWnd* pParentWnd,int i,int j,ItemInfo *iteminfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void PCvalToDSPval(PARAINI_INFO *parainfo,float data);

	// Generated message map functions
	//{{AFX_MSG(SubWriteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnChangeWriteCurrvalEdit();
	afx_msg void OnAddButton();
	afx_msg void OnDecButton();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSaveButton();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg void OnPopmenuDeleteItem();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBWRITEDLG_H__C665A9D7_BF3C_4C41_B275_143C6727304B__INCLUDED_)
