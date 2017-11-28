// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__EBE66B99_BD26_4D8B_9317_037E8EB75CC8__INCLUDED_)
#define AFX_MAINFRM_H__EBE66B99_BD26_4D8B_9317_037E8EB75CC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseData.h"
#include "BitShowBar.h"
#include "ButtonBar.h"
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	int m_form_top;
	int m_form_left;
	int m_form_height;
	int m_form_width;
	
private:
	bool connectflg;
	void filterStr(char *str);
public:
//	int m_para_tot_num;
//	PARAINI_INFO m_para_info[MAX_PARA_INI_NUM];
//	int m_ValNum;
//	ParaValInfo m_ValInfo[MAX_VAL_NUM];
//	MainInfo m_maininfo;
protected:  // control bar embedded members

	CToolBar    m_wndToolBar;
public:
	ParaValInfo* GetValBitInfo(char *name);
	int process_para_ini();
	int writeback_para_ini();
	int process_program_int();
	PARAINI_INFO* GetVariableInfo(char *name);
	CStatusBar  m_wndStatusBar;
	BitShowBar m_bitshowBar;
	ButtonBar m_ButtonBar;
// Generated message map functions
protected:
	void SortParaStr();
	void WriteBackMainIni();
	void WritebackProgramini();
	void WritebackParaBitIni();
	int ParaBitCheckBit(char *lineBuff);
	void ProcessParaBitIni();
	int PargramCheckSum(char *pchar,char *Buff);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMenuSetParameters();
	afx_msg void OnMenuOprCnnset();
	afx_msg void OnMenuOprCntpcs();
	afx_msg void OnMenuOprDiscntpcs();
	afx_msg void OnMenuOprUserlevel();
	afx_msg void OnMenuOprSyslevel();
	afx_msg void OnMenuOprSercerlevel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnInitMenu(CMenu* pMenu);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__EBE66B99_BD26_4D8B_9317_037E8EB75CC8__INCLUDED_)
