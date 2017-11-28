// SubBitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "SubBitDlg.h"
#include "BitSet.h"
#include "SatConBitShowView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int 	OpLevel;
/////////////////////////////////////////////////////////////////////////////
// SubBitDlg dialog

SubBitDlg::SubBitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SubBitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SubBitDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_oldcl=0;
	m_oldDispl=" ";
}

void SubBitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SubBitDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(SubBitDlg, CDialog)
	//{{AFX_MSG_MAP(SubBitDlg)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_POPMENU_DELETE_ITEM, OnPopmenuDeleteItem)
	ON_BN_CLICKED(IDC_LED_BUTTON,OnLedButtonClicked)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// SubBitDlg message handlers
BOOL SubBitDlg::Create(UINT nID,CWnd* pParentWnd,int i,int j,ItemInfo *iteminfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	pageNumber=i;
	itemNumber=j;
	m_iteminfo=iteminfo;
	return CDialog::Create(IDD, pParentWnd);
}

BOOL SubBitDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CPoint point;
	point.x=10;
	point.y=10;
	CRect rect;
	HRGN rgn = CreateEllipticRgn(0, 0, 20, 20);
	m_led.Create("", WS_VISIBLE, point, rgn, this,IDC_LED_BUTTON);
	rect.left=40;	rect.top=13;	rect.right=200;	rect.bottom=33;
	GetDlgItem(IDC_BITNAME_STATIC)->MoveWindow(rect);
///////////////////////////////////////////////////////////////////
	EnableToolTips(TRUE);
	m_TipCtrl.Create(this,TTS_ALWAYSTIP);
	m_TipCtrl.Activate(TRUE);
	m_TipCtrl.SetDelayTime(500);
	m_TipCtrl.AddTool(this,m_tipstr,&rect,ID_SUBWRITEDLG_TOOLTIP);
	UpdateBitItem();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SubBitDlg::UpdateBitItem()
{
	CString str; int val;
	if(m_iteminfo->pvalbitinfo!=0)
	{

		str.Format("%d",itemNumber);
		m_led.SetWindowText(str);		//item数
		if(m_iteminfo->ValInfo!=0)//有变量值
		{
			val=m_iteminfo->ValInfo->curval;
			val=(val>>m_iteminfo->BitNo)&0x01;
		}
		else
			val=0;

		m_tipstr=m_iteminfo->pvalbitinfo->bitinfo[m_iteminfo->BitNo].Comment;	//设置tip说明信息
		m_TipCtrl.UpdateTipText(m_tipstr,this,ID_SUBWRITEDLG_TOOLTIP);

		str=m_iteminfo->pvalbitinfo->bitinfo[m_iteminfo->BitNo].Displ[val];
		if(str!=m_oldDispl)
			GetDlgItem(IDC_BITNAME_STATIC)->SetWindowText(str);//显示
		m_oldDispl=str;

		str=m_iteminfo->pvalbitinfo->bitinfo[m_iteminfo->BitNo].Color[val];//颜色
		m_led.m_nColor=StrToRgb(str);
		if(m_oldcl!=m_led.m_nColor)
			m_led.Invalidate();
		m_oldcl=m_led.m_nColor;
	}
	else
	{
		m_tipstr="";
		m_TipCtrl.UpdateTipText(m_tipstr,this,ID_SUBWRITEDLG_TOOLTIP);
		GetDlgItem(IDC_BITNAME_STATIC)->SetWindowText("");
		m_led.m_nColor=StrToRgb("");
		m_led.Invalidate();
	}
}
void SubBitDlg::OnLedButtonClicked()
{
	if(OpLevel==0)
		return;
	CSatConBitShowView *pParent = (CSatConBitShowView*)GetParent();

//	BitSet dlg(pParent->m_pBitDoc->m_BitTabInfo[pParent->m_curSelPage].tabName,
//				itemNumber,m_iteminfo,pParent);
	BitSet dlg(pParent,itemNumber,m_iteminfo,pParent);

	if(dlg.DoModal()==IDOK)
	{
		char*pStr =(LPSTR)(LPCTSTR)dlg.m_TabName;
		strcpy(pParent->m_pBitDoc->m_BitTabInfo[pParent->m_curSelPage].tabName,pStr);//设置page名
		pParent->m_BitShowTab.DeleteItem(pParent->m_curSelPage);
		pParent->m_BitShowTab.InsertItem(pParent->m_curSelPage,dlg.m_TabName);
		pParent->ShowTabComb(pParent->m_curSelPage,0);
		pParent->ShowTabComb(pParent->m_curSelPage,1);
		UpdateBitItem();
	}
	
}

void SubBitDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(OpLevel==0)
		return;
	CMenu popupMenu;
	popupMenu.CreatePopupMenu();
	
	popupMenu.AppendMenu(MF_STRING|MF_GRAYED, ID_POPMENU_NEW_PAGE, "New a page"); //无效
	popupMenu.AppendMenu(MF_STRING|MF_GRAYED, ID_POPMENU_NEW_ITEM, "New a item"); //无效
	popupMenu.AppendMenu(MF_STRING|MF_GRAYED, ID_POPMENU_DELETE_PAGE, "Delete current page"); //无效
	popupMenu.AppendMenu(MF_STRING, ID_POPMENU_DELETE_ITEM, "Delete current item");
	
	CPoint poin;
	GetCursorPos(&poin);
	popupMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,poin.x,poin.y,this);
	CDialog::OnRButtonDown(nFlags, point);
}
void SubBitDlg::OnPopmenuDeleteItem()
{
	CSatConBitShowView *m_parent=(CSatConBitShowView*)GetParent();
	m_parent->PostMessage(ID_POPMENU_DELETE_ITEM,pageNumber,itemNumber);
	
}

BOOL SubBitDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_TipCtrl.RelayEvent(pMsg);	
	return CDialog::PreTranslateMessage(pMsg);
}

COLORREF SubBitDlg::StrToRgb(CString str)
{
	COLORREF color=atol(str);
	if(color==0)
		color=RGB(180,180,180);
	return color;
}

void SubBitDlg::UpValData()
{

}
void SubBitDlg::OnOK()
{

}
void SubBitDlg::OnCancel()
{
	
}