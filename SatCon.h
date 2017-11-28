// SatCon.h : main header file for the SATCON application
//

#if !defined(AFX_SATCON_H__4FB9929D_6C2A_49EF_9465_F79E5A08469A__INCLUDED_)
#define AFX_SATCON_H__4FB9929D_6C2A_49EF_9465_F79E5A08469A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSatConApp:
// See SatCon.cpp for the implementation of this class
//

class CSatConApp : public CWinApp
{
public:
	CSatConApp();

public:
	void BasisAddressSortTable();
	void SelectReadableVal();
	//Fred...
	CMultiDocTemplate* pDocWrite;
	CMultiDocTemplate* pDocRead;
	CMultiDocTemplate* pDocBitshow;
	CMultiDocTemplate* pMyChart;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSatConApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSatConApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnMenuReader();
	afx_msg void OnMenuWriter();
	afx_msg void OnMenuBitshow();
	afx_msg void OnMenuUploadDspPc();
	afx_msg void OnMenuDownloadPcDsp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void CopyToFrmwrite(CString newpart);
	int CopyParaToOther(CString newpath);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SATCON_H__4FB9929D_6C2A_49EF_9465_F79E5A08469A__INCLUDED_)
