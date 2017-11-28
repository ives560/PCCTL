#if !defined(AFX_TOPBITSET_H__FA976CCB_D1D8_46CE_A118_C123B58C6DA0__INCLUDED_)
#define AFX_TOPBITSET_H__FA976CCB_D1D8_46CE_A118_C123B58C6DA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TopBitSet.h : header file
//顶层工具条中bit变量对话框
/////////////////////////////////////////////////////////////////////////////
// TopBitSet dialog

class TopBitSet : public CDialog
{
// Construction
public:
	TopBitSet(CWnd* pParent = NULL);   // standard constructor
	int m_num;
	// Dialog Data
	//{{AFX_DATA(TopBitSet)
	enum { IDD = IDD_TOPBITSET_DIALOG };
	CComboBox	m_bitcomb;
	CComboBox	m_namecomb;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TopBitSet)
	public:
	virtual BOOL Create(int num,CWnd* pParentWnd, UINT nID);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TopBitSet)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPBITSET_H__FA976CCB_D1D8_46CE_A118_C123B58C6DA0__INCLUDED_)
