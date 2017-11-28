#if !defined(AFX_BITSHOWBAR_H__D9B8F9D1_F192_409E_BEDE_A9C3676BF382__INCLUDED_)
#define AFX_BITSHOWBAR_H__D9B8F9D1_F192_409E_BEDE_A9C3676BF382__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitShowBar.h : header file
//顶部位变量显示工具条
#include "DialogBarBit.h"
#include "DlaglogBarRW.h"
/////////////////////////////////////////////////////////////////////////////
// BitShowBar dialog

class BitShowBar : public CDialogBar
{
// Construction
public:
	BitShowBar(CWnd* pParent = NULL);   // standard constructor
private:
	DlaglogBarRW dlgbarRW[7];
	DialogBarBit dlgbarBit[12];
// Dialog Data
	//{{AFX_DATA(BitShowBar)
	enum { IDD = IDD_BITSHOW_DIALOGBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BitShowBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int CreateItem(int i,int j);

	// Generated message map functions
	//{{AFX_MSG(BitShowBar)
	afx_msg LONG OnInitDialog(UINT, LONG);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITSHOWBAR_H__D9B8F9D1_F192_409E_BEDE_A9C3676BF382__INCLUDED_)
