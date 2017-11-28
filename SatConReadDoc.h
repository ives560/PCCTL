// SatConReadDoc.h : interface of the CSatConReadDoc class
//只读变量窗口文档类
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SATCONREADDOC_H__A922AD1E_F321_422B_A866_B85D7AF41A0A__INCLUDED_)
#define AFX_SATCONREADDOC_H__A922AD1E_F321_422B_A866_B85D7AF41A0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseData.h"
#include "MainFrm.h"
/////////////////////////////////////////////////////////////////////////////
// CSatConReadDoc document
class CSatConReadDoc : public CDocument
{
protected: // create from serialization only
	CSatConReadDoc();
	DECLARE_DYNCREATE(CSatConReadDoc)

// Attributes
public:
	int m_TabNum;
	int m_lastPage;
	
	int m_form_top;
	int m_form_left;
	int m_form_height;
	int m_form_width;
//	int m_itemNum[TAB_MAX_NUM];				//page中item的个数
	TabInfo m_ReadTabInfo[TAB_MAX_NUM];		//read窗口tab信息
	CMainFrame *m_pMainFram;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSatConReadDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DeleteReadPage(int pageId);
	void DeleteReadItem(int pageId, int itemId);
	virtual ~CSatConReadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void processReadIni();
	void WritebackReadIni();
	void filterStr(char *str);
// Generated message map functions
protected:
	//{{AFX_MSG(CSatConReadDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SATCONREADDOC_H__A922AD1E_F321_422B_A866_B85D7AF41A0A__INCLUDED_)
