// UniButton.cpp : implementation file
//

#include "stdafx.h"
#include "UniButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUniButton

CUniButton::CUniButton()
{
	m_nColor = RGB(180,180,180);//GetSysColor(COLOR_BTNFACE);
	m_nBorder = 1;
	m_lfEscapement = 0;
	m_pNormal = NULL;
	m_hRgn = 0;
	m_bNeedBitmaps = true;
}

CUniButton::~CUniButton()
{
	delete m_pNormal;
	DeleteObject(m_hRgn);
}

BEGIN_MESSAGE_MAP(CUniButton, CButton)
	//{{AFX_MSG_MAP(CUniButton)
	ON_WM_ERASEBKGND()
//	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUniButton message handlers

BOOL CUniButton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const CPoint point, const HRGN hRgn, CWnd* pParentWnd, UINT nID)
{
	// store region in member variable
	DeleteObject(m_hRgn);
	m_hRgn = CreateRectRgn(0, 0, 31, 31);
	CRect box(0, 0, 0, 0);
	if (m_hRgn != 0) 
		CombineRgn(m_hRgn, hRgn, 0, RGN_COPY);

	// make sure that region bounding rect is located in (0, 0)
	GetRgnBox(m_hRgn, &box);
	OffsetRgn(m_hRgn, -box.left, -box.top);
	GetRgnBox(m_hRgn, &box);

	// update position of region center for caption output
	m_CenterPoint = CPoint(box.left + box.Width() /2 , box.top + box.Height() /2);
	box.OffsetRect(point);
	return CButton::Create(lpszCaption, dwStyle, box, pParentWnd, nID);
}

void CUniButton::PreSubclassWindow() 
{
	// change window style to allow owner draw
	ModifyStyle(0, BS_OWNERDRAW | BS_PUSHBUTTON);	
	CButton::PreSubclassWindow();
}

int CUniButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	// assign new region to a window
	m_bNeedBitmaps = true;
	SetWindowRgn(m_hRgn, true);

	return 0;
}

LRESULT CUniButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// I have noticed that default windows buttons can be clicked very quickly.
	// Double or single click both result in a button being pushed down.
	// For owner drawn buttons this is not the case. Double click does
	// not push button down. Here is a solution for the problem:
	// double click message is substituted for single click.

	if (message == WM_LBUTTONDBLCLK)
		message = WM_LBUTTONDOWN;
	
	return CButton::DefWindowProc(message, wParam, lParam);
}

BOOL CUniButton::OnEraseBkgnd(CDC* pDC) 
{
	// do not erase background
	return 1;
}

//////////////////////// DRAWING ROUTINES ////////////////////////////

void CUniButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// prepare DC
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct -> hDC);
	CRect rect;
	GetClientRect(rect);

	// prepare bitmaps they need to be prepared
	//if (m_bNeedBitmaps)
		PrepareStateBitmaps(pDC, &rect);

	// draw button to the screen
	DrawButton(pDC, &rect, lpDrawItemStruct -> itemState);
}

void CUniButton::PrepareStateBitmaps(CDC * pDC, CRect * pRect)
{
	// prepare memory DC
	CDC * pMemDC;
	pMemDC = new CDC;
	pMemDC -> CreateCompatibleDC(pDC);

	// prepare bitmaps for all button states and for the mask
	PrepareNormalState(pDC, pMemDC, pRect);

	// clean up
	delete pMemDC; 
	m_bNeedBitmaps = false;
}


void CUniButton::PrepareNormalState(CDC * pDC, CDC * pMemDC, CRect * pRect)
{
	// prepare MYBS_NORMAL state bitmap
	delete m_pNormal;
	m_pNormal = new CBitmap;
	PaintRgn(pDC, pMemDC, m_pNormal, m_nColor, pRect, true, false);
}

void CUniButton::PaintRgn(CDC * pDC, CDC * pMemDC, CBitmap * pBitmap, COLORREF color, CRect * pRect, BOOL bEnabled, BOOL bSunken)
{
	// create bitmap
	pBitmap -> CreateCompatibleBitmap(pDC, pRect -> Width(), pRect -> Height());
	CBitmap * pOldBitmap = pMemDC -> SelectObject(pBitmap); 

	// prepare region
	HRGN hRgn = CreateRectRgn(0, 0, 0, 0);
	GetWindowRgn(hRgn);

	// fill rect a with transparent color and fill rgn
	HBRUSH hBrush = CreateSolidBrush(color);
	pMemDC -> FillSolidRect(pRect, RGB(0, 0, 0));
	FillRgn(pMemDC -> GetSafeHdc(), hRgn, hBrush);
	DeleteObject(hBrush);

	// draw 3D border and text
	DrawButtonCaption(pMemDC -> GetSafeHdc(), pRect, bEnabled, bSunken);
	//FrameRgn3D(pMemDC -> GetSafeHdc(), hRgn, bSunken);

	// clean up
	DeleteObject(hRgn);
	pMemDC -> SelectObject(pOldBitmap); 
}

void CUniButton::DrawButtonCaption(HDC hDC, CRect * pRect, BOOL bEnabled, BOOL bSunken) 
{
	// select parent font
	int nOldMode = SetBkMode(hDC, TRANSPARENT);
	CString text;
	GetWindowText(text);
	LOGFONT lf;
	GetParent() -> GetFont() -> GetLogFont(&lf);
	HFONT hFont = CreateFontIndirect(&lf);
	HFONT hOldFont = (HFONT) SelectObject(hDC, hFont);

	// determine point where to output text
	TEXTMETRIC tm;
	GetTextMetrics(hDC, &tm);
	CPoint p = CPoint(m_CenterPoint.x, m_CenterPoint.y + tm.tmHeight/ 2); 
	if (bSunken) 
		p.Offset(m_nBorder, m_nBorder); 
		
	// draw button caption depending upon button state
	if (bEnabled) {
		SetTextColor(hDC, GetSysColor(COLOR_BTNTEXT));
		SetTextAlign(hDC, TA_CENTER | TA_BOTTOM);
		TextOut(hDC, p.x, p.y, text, text.GetLength());
	}
	else {
		SetTextColor(hDC, GetSysColor(COLOR_3DHILIGHT));
		TextOut(hDC, p.x + 1, p.y + 1, text, text.GetLength());
		SetTextColor(hDC, GetSysColor(COLOR_3DSHADOW));
		TextOut(hDC, p.x, p.y, text, text.GetLength());
	}

	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);
	SetBkMode(hDC, nOldMode);
}
void CUniButton::DrawButton(CDC * pDC, CRect * pRect, UINT state)
{
	// create memory DC
	CDC * pMemDC = new CDC;
	pMemDC -> CreateCompatibleDC(pDC);
	CBitmap * pOldBitmap;

	// get region
	HRGN hRgn = CreateRectRgn(0, 0, 0, 0);
	GetWindowRgn(hRgn);

	// select bitmap to paint depending upon button state
		pOldBitmap = pMemDC -> SelectObject(m_pNormal);

	// paint using region for clipping
	::SelectClipRgn(pDC -> GetSafeHdc(), hRgn);
	pDC -> BitBlt(0, 0, pRect -> Width(), pRect -> Height(), pMemDC, 0, 0, SRCCOPY);
	::SelectClipRgn(pDC -> GetSafeHdc(), NULL);

	// clean up
	DeleteObject(hRgn);
	pMemDC -> SelectObject(pOldBitmap);
	delete pMemDC;
}
