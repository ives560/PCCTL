#if !defined(AFX_SATCONWRITEDOC_H__F7CBC5F3_6EA6_4197_B6BC_FFC6276EAC3B__INCLUDED_)
#define AFX_SATCONWRITEDOC_H__F7CBC5F3_6EA6_4197_B6BC_FFC6276EAC3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SatConWriteDoc.h : header file
//读写变量窗口文档类
#include "BaseData.h"
#include "MainFrm.h"
/////////////////////////////////////////////////////////////////////////////
// SatConWriteDoc document

class SatConWriteDoc : public CDocument
{
protected:
	SatConWriteDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(SatConWriteDoc)

// Attributes
public:

	int m_lastPage;

	int m_form_top;
	int m_form_left;
	int m_form_height;
	int m_form_width;
//	int m_itemNum[TAB_MAX_NUM];				//page中item的个数

	CMainFrame *m_pMainFram;	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SatConWriteDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void DeleteWritePage(int pageId);
	void DeleteWriteItem(int pageId, int itemId);
	virtual ~SatConWriteDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	void filterStr(char *str);
	void processWriteIni();
	void WritebackWriteIni();
	//{{AFX_MSG(SatConWriteDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SATCONWRITEDOC_H__F7CBC5F3_6EA6_4197_B6BC_FFC6276EAC3B__INCLUDED_)
