#if !defined(AFX_UNIBUTTON_H__EBEB2EA0_A067_11D2_9E44_0020182F735A__INCLUDED_)
#define AFX_UNIBUTTON_H__EBEB2EA0_A067_11D2_9E44_0020182F735A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CUniButton window
//Ô²ÐÎ°´Å¥
// AUTHOR: Pavel A .Simakov
// DATE: 981226
// E-MAIL: psimakov@outplay.com
// ORGANIZATION: Outplay Consulting
// HTTP: www.outplay.com
// TERM OF USE: unlimited, must cite AUTHOR
// COPYRIHT: 1998 Outplay Consulting
//
/////////////////////////////////////////////////////////////////////////////

class CUniButton : public CButton
{
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUniButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CUniButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	UINT m_nBorder;														// width of the border in pixels for 3D highlight
	LONG m_lfEscapement;												// orientation of the caption (in tenth of the degree as in LOGFONT)
	COLORREF m_nColor;					// background colors for button states: normal, selected, hover, disabled
	CBitmap * m_pNormal;												// bitmaps to hold button images	
	CPoint m_CenterPoint;												// button caption will be centered around this point
	HRGN m_hRgn;														// region in screen coordinates
	BOOL m_bNeedBitmaps;												// flag idicates that state bitmaps must be rebuild
	void DrawButton(CDC * pDC, CRect * pRect, UINT state);				// draws button to the screen
	void PrepareStateBitmaps(CDC * pDC, CRect * pRect);					// prepares bitmaps for button states
protected:
	void PrepareNormalState(CDC * pDC, CDC * pMemDC, CRect * pRect);	// prepare normal state button bitmap
	void PrepareSelectedState(CDC * pDC, CDC * pMemDC, CRect * pRect);	// prepare selectedstate button bitmap
	void DrawButtonCaption(HDC hDC, CRect * pRect, BOOL bEnabled, BOOL bSunken);	// draws button caption 
	void PaintRgn(CDC * pDC, CDC * pMemDC, CBitmap * pBitmap, COLORREF color, CRect * pRect, BOOL bEnabled, BOOL bSunken);	// paint button 
public:
	CUniButton();				// constructor
	virtual ~CUniButton();	// destructor
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const CPoint point, const HRGN hRgn, CWnd* pParentWnd, UINT nID);
							// constructor with default colors and border
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNIBUTTON_H__EBEB2EA0_A067_11D2_9E44_0020182F735A__INCLUDED_)
