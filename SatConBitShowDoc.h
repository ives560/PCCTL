#if !defined(AFX_SATCONBITSHOWDOC_H__8A864BC0_5ED0_471B_8BFB_2988926BDEA8__INCLUDED_)
#define AFX_SATCONBITSHOWDOC_H__8A864BC0_5ED0_471B_8BFB_2988926BDEA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SatConBitShowDoc.h : header file
//
#include "BaseData.h"
#include "MainFrm.h"
/////////////////////////////////////////////////////////////////////////////
// CSatConBitShowDoc document

class CSatConBitShowDoc : public CDocument
{
protected:
	CSatConBitShowDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSatConBitShowDoc)

// Attributes
public:
	int m_TabNum;
	int m_lastPage;
	
	int m_form_top;
	int m_form_left;
	int m_form_height;
	int m_form_width;
	TabInfo m_BitTabInfo[TAB_MAX_NUM];		//read´°¿ÚtabÐÅÏ¢

	CMainFrame *m_pMainFram;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSatConBitShowDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSatConBitShowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
public:
	void DeleteBitItem(int pageId, int itemId);
	void DeleteBitPage(int pageId);

protected:
	void WritebackFrmBitIni();
	void BitShowFilterStr(char *str);
	void ProcessFrmBitIni();
	//{{AFX_MSG(CSatConBitShowDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SATCONBITSHOWDOC_H__8A864BC0_5ED0_471B_8BFB_2988926BDEA8__INCLUDED_)
