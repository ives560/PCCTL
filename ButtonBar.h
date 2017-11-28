#if !defined(AFX_BUTTONBAR_H__A6AA6B35_2429_4430_B373_5C78134D9DA8__INCLUDED_)
#define AFX_BUTTONBAR_H__A6AA6B35_2429_4430_B373_5C78134D9DA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonBar.h : header file
//左侧命令按钮工具条
#include "BaseData.h"
/////////////////////////////////////////////////////////////////////////////
// ButtonBar dialog

class ButtonBar : public CDialogBar
{
// Construction
public:
	int ReadUserIni();
	ButtonBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ButtonBar)
	enum { IDD = IDD_BUTTON_DIALOGBAR };
	CButton	m_start;
	CButton	m_shutdown;
	CButton	m_reset;
	CButton	m_stop;
	//}}AFX_DATA

private:
	CToolTipCtrl m_TipCtrl;
	CMD_BUTTON Reset;
	CMD_BUTTON Start;
	CMD_BUTTON Stop;
	CMD_BUTTON Shutdown;

	CMD_BUTTON cmdbutton[10];
	CButton m_button[10];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ButtonBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void WriteCommData(CMD_BUTTON cmd);
	void AddVarAddress();
	void filterStr(char *str);
	
	// Generated message map functions
	//{{AFX_MSG(ButtonBar)
	afx_msg LONG OnInitDialog(UINT, LONG);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler);
	afx_msg void OnStopButton();
	afx_msg void OnShutdownButton();
	afx_msg void OnResetButton();
	afx_msg void OnStartButton();
	//}}AFX_MSG
	afx_msg void OnCMDButton(UINT id);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONBAR_H__A6AA6B35_2429_4430_B373_5C78134D9DA8__INCLUDED_)
