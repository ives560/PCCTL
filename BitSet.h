#if !defined(AFX_BITSET_H__B6D0380B_3277_4297_ACB0_50B4C16B785A__INCLUDED_)
#define AFX_BITSET_H__B6D0380B_3277_4297_ACB0_50B4C16B785A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitSet.h : header file
//位变量信息设置对话框
//#include "SatConBitShowDoc.h"
#include "MainFrm.h"
#include "BaseData.h"
#include "SatConBitShowView.h"
/////////////////////////////////////////////////////////////////////////////
// BitSet dialog

class BitSet : public CDialog
{
// Construction
public://(tab名，item位，item信息，pParent)
//	BitSet(CString tabname,int j,ItemInfo *iteminfo,CWnd* pParent = NULL);   // standard constructor
BitSet(CSatConBitShowView *pBitView,int j,ItemInfo *iteminfo,CWnd* pParent = NULL); 
private:
	CMainFrame *m_pMainFram;
	CSatConBitShowView *m_pBitView;
	ItemInfo *m_pSetiteminfo;
	ParaValInfo *m_pcurvalinfo;
public:
	COLORREF m_Sel0Color;
	COLORREF m_Sel1Color;
//	CPoint m_frmpoint;
//	int curSel_Set;
//	int item_Set;

// Dialog Data
	//{{AFX_DATA(BitSet)
	enum { IDD = IDD_BIT_SET_DIALOG };
	CComboBox	m_BitNo;
	CComboBox	m_VarName;
	CString	m_BitCom;
	CString	m_Display1;
	CString	m_Display0;
	CString	m_TabName;
	CString	m_itemnum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BitSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateBitSet();
	CString RgbToStr(COLORREF color);
	COLORREF StrToRgb(CString str);

	// Generated message map functions
	//{{AFX_MSG(BitSet)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelcolor0Static();
	afx_msg void OnSelchangeVarnameCombo();
	afx_msg void OnSelcolor1Static();
	afx_msg void OnSelchangeBitnoCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITSET_H__B6D0380B_3277_4297_ACB0_50B4C16B785A__INCLUDED_)
