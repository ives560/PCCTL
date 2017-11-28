// SubDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "SubDlg.h"
#include "VarNameSetDlg.h"
#include "SatConReadView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int  OpLevel;
/////////////////////////////////////////////////////////////////////////////
// CSubDlg dialog


CSubDlg::CSubDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlg)
	m_unit = _T("");
	m_val = 0.0f;
	//}}AFX_DATA_INIT
}


void CSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlg)
	DDX_Control(pDX, IDC_READ_BASE_GROUP, m_readitem);
	DDX_Text(pDX, IDC_READ_UNIT_EDIT, m_unit);
	DDX_Text(pDX, IDC_READ_VAL_EDIT, m_val);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlg, CDialog)
	//{{AFX_MSG_MAP(CSubDlg)
	ON_EN_CHANGE(IDC_READ_VAL_EDIT, OnChangeReadBaseEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_POPMENU_DELETE_ITEM, OnPopmenuDeleteItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlg message handlers
BOOL CSubDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	EnableToolTips(TRUE);
	m_TipCtrl.Create(this,TTS_ALWAYSTIP);
	m_TipCtrl.Activate(TRUE);
	m_TipCtrl.SetDelayTime(500);

	CRect rect;
	GetClientRect(rect);
	rect.bottom=rect.bottom/4;
	m_TipCtrl.AddTool(this,m_tipstr,&rect,ID_SUBDLG_TOOLTIP);

	UpdateReadItem();		//更新显示数据
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSubDlg::Create( UINT nID,CWnd* pParentWnd,int i,int j,ItemInfo *iteminfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	pageNumber=i;
	itemNumber=j;
	m_iteminfo=iteminfo;
	return CDialog::Create(IDD, pParentWnd);
}

void CSubDlg::OnChangeReadBaseEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

}

void CSubDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
if(OpLevel!=0)
{
	CRect rect;
	GetWindowRect(rect);
	if(point.y<(rect.Height()/4))	//限制响应范围
	{
		CSatConReadView *pParent = (CSatConReadView*)GetParent();
	//	CSatConReadView *pParent = (CSatConReadView*)GetDlgItem(IDD_SATCON_READ_FORM);
		VarNameSetDlg Vardlg(pParent->m_pReadDoc->m_ReadTabInfo[pParent->m_curSelPage].tabName,rect,m_iteminfo);
		if(Vardlg.DoModal()==IDOK)
		{
			char*pStr =(LPSTR)(LPCTSTR)Vardlg.m_setabnam;
			strcpy(pParent->m_pReadDoc->m_ReadTabInfo[pParent->m_curSelPage].tabName,pStr);//设置page名
			pParent->m_ReaderTab.DeleteItem(pParent->m_curSelPage);
			pParent->m_ReaderTab.InsertItem(pParent->m_curSelPage,Vardlg.m_setabnam);
			pParent->ShowTabComb(pParent->m_curSelPage,0);
			pParent->ShowTabComb(pParent->m_curSelPage,1);
			UpdateReadItem();		//更新数据
		}
	}
}
	CDialog::OnLButtonDown(nFlags, point);
}

void CSubDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(OpLevel!=0)
	{
		CMenu popupMenu;
		popupMenu.CreatePopupMenu();

		popupMenu.AppendMenu(MF_STRING|MF_GRAYED, ID_POPMENU_NEW_PAGE, "New a page"); //无效
		popupMenu.AppendMenu(MF_STRING|MF_GRAYED, ID_POPMENU_NEW_ITEM, "New a item"); //无效
		popupMenu.AppendMenu(MF_STRING|MF_GRAYED, ID_POPMENU_DELETE_PAGE, "Delete current page"); //无效
		popupMenu.AppendMenu(MF_STRING, ID_POPMENU_DELETE_ITEM, "Delete current item");
		
		CPoint poin;
		GetCursorPos(&poin);
		popupMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,poin.x,poin.y,this);
	}
	CDialog::OnRButtonDown(nFlags, point);
}
void CSubDlg::OnPopmenuDeleteItem()
{
	CSatConReadView *m_parent=(CSatConReadView*)GetParent();
	m_parent->PostMessage(ID_POPMENU_DELETE_ITEM,pageNumber,itemNumber);

}

BOOL CSubDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	//if(pMsg->message== WM_MOUSEMOVE)
		m_TipCtrl.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CSubDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSubDlg::UpdateReadItem()
{
	m_readitem.SetWindowText(m_iteminfo->ValName);//显示变量名
	if(m_iteminfo->ValInfo!=0)		//有变量数据信息
	{
		//m_val=m_iteminfo->ValInfo->curval;
		m_unit=m_iteminfo->ValInfo->unit;
		m_tipstr=m_iteminfo->ValInfo->comt;			//设置说明信息
		m_TipCtrl.UpdateTipText(m_tipstr,this,ID_SUBDLG_TOOLTIP);
	}
	else						//无变量数据信息
	{
		m_unit="";
		m_tipstr="";
		m_TipCtrl.UpdateTipText(m_tipstr,this,ID_SUBDLG_TOOLTIP);
	}
	UpdateData(FALSE);
}

void CSubDlg::UpValData()
{
	if(m_iteminfo->ValInfo!=0)
		m_val=m_iteminfo->ValInfo->curval;

	UpdateData(FALSE);
}
void CSubDlg::OnOK()
{

}
void CSubDlg::OnCancel()
{

}