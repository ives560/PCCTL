// SatConBitShowView.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "SatConBitShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "SubBitDlg.h"
#include "CommSet.h"
extern CCommSet m_comm;
extern bool UpDataBit;
extern int 	OpLevel;
extern bool ChangeTable;
/////////////////////////////////////////////////////////////////////////////
// CSatConBitShowView

IMPLEMENT_DYNCREATE(CSatConBitShowView, CFormView)

CSatConBitShowView::CSatConBitShowView()
	: CFormView(CSatConBitShowView::IDD)
{
	//{{AFX_DATA_INIT(CSatConBitShowView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_initOver=FALSE;
}

CSatConBitShowView::~CSatConBitShowView()
{
}

void CSatConBitShowView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSatConBitShowView)
	DDX_Control(pDX, IDC_BITSHOW_TAB, m_BitShowTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSatConBitShowView, CFormView)
	//{{AFX_MSG_MAP(CSatConBitShowView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_BITSHOW_TAB, OnSelchangeBitshowTab)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	//ON_MESSAGE(ID_POPMENU_DELETE_ITEM, OnPopmenuDeleteItem)
	ON_COMMAND(ID_POPMENU_NEW_ITEM, OnPopmenuNewItem)
	ON_COMMAND(ID_POPMENU_NEW_PAGE, OnPopmenuNewPage)
	ON_COMMAND(ID_POPMENU_DELETE_PAGE, OnPopmenuDeletePage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSatConBitShowView diagnostics

#ifdef _DEBUG
void CSatConBitShowView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSatConBitShowView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSatConBitShowView message handlers
void CSatConBitShowView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();
	// TODO: Add your specialized code here and/or call the base class
	m_pBitDoc = (CSatConBitShowDoc*)GetDocument();

	m_curSelPage=m_pBitDoc->m_lastPage;
	int i,j; bool tabflg=FALSE,itemflg=FALSE;
	// TODO: Add your specialized code here and/or call the base class
	//动态创建TAB
	for(i=0;i<m_pBitDoc->m_TabNum;i++)
	{
		tabflg=true;
		m_BitShowTab.InsertItem(i,m_pBitDoc->m_BitTabInfo[i].tabName);
	}
	//创建item
	for(i=0;i<m_pBitDoc->m_TabNum;i++)
	{
		int &num=m_pBitDoc->m_BitTabInfo[i].itemNum;	//引用
		if(num<16) num=16;		//item个数不够16个设置为16个
		for(j=0;j<num;j++)
		{
			itemflg=true;
			CreateItem(i, j);
		}
	}
	if(tabflg)
		m_BitShowTab.SetCurSel(m_curSelPage);
	//改变tab大小
	if(itemflg)
	{
		/*CRect rect;
		j=m_pBitDoc->m_BitTabInfo[m_curSelPage].itemNum-1;
		m_BitDlg[m_curSelPage][j]->GetWindowRect(rect);
		m_BitShowTab.GetClientRect(m_formrect);
		m_formrect.bottom=rect.bottom;
		m_BitShowTab.MoveWindow(m_formrect,TRUE);*/
		m_initOver=true;
		OnSize(0,0,0);
	}
	m_comm.pBitView=this;
//	SetTimer(1,300,NULL);//数据更新
}

int CSatConBitShowView::CreateItem(int i, int j)
{
	CRect frmrect,dlgrect,rect; char* comtstr=NULL;
	GetClientRect(frmrect);
	frmrect.top += 30;
	frmrect.left += 20;
	m_BitDlg[i][j]= new SubBitDlg;
	m_BitDlg[i][j]->Create(IDD_SUB_DIALOG,this,i,j,&(m_pBitDoc->m_BitTabInfo[i].iteminfo[j]));
	m_BitDlg[i][j]->GetWindowRect(dlgrect);
	int width=dlgrect.Width()+ITEM_OUTER_WIDTH;
	int height=dlgrect.Height()+ITEM_OUTER_HEIGHT;
	int lineNum=frmrect.Width()/width;
	if(lineNum<1)lineNum=1;
	int line = j / lineNum;
	int row = j % lineNum;
	rect.left = frmrect.left+row*width;
	rect.top  =frmrect.top+line*height;
	rect.right=rect.left+dlgrect.Width();
	rect.bottom=rect.top+dlgrect.Height();
	
	m_BitDlg[i][j]->MoveWindow(rect,TRUE);
	//m_ReadDlg[i][j]->SetWindowPos(this,rect.left,rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
	if (i == m_curSelPage) //显示窗口
	{
		m_BitDlg[i][j]->ShowWindow(SW_SHOW);
		if(m_BitDlg[i][j]->m_iteminfo->ValInfo)
			m_BitDlg[i][j]->m_iteminfo->ValInfo->commable=TRUE;
	}
	return 1;
}

void CSatConBitShowView::OnSelchangeBitshowTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int curSel = m_BitShowTab.GetCurSel();
	ShowTabComb(m_curSelPage,0);
	m_curSelPage=curSel;
	OnSize(0,0,0);
	ShowTabComb(m_curSelPage,1);
	ChangeTable=TRUE;
	*pResult = 0;
}
void CSatConBitShowView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(OpLevel==0)
		return;
	CMenu popupMenu;
	popupMenu.CreatePopupMenu();
	popupMenu.AppendMenu(MF_STRING, ID_POPMENU_NEW_PAGE, "New a page");
	popupMenu.AppendMenu(MF_STRING, ID_POPMENU_NEW_ITEM, "New a item");
	//	popupMenu.AppendMenu(MF_STRING, ID_POPMENU_MODIFY_PAGE, "Modify current page");
	popupMenu.AppendMenu(MF_STRING, ID_POPMENU_DELETE_PAGE, "Delete current page");
	popupMenu.AppendMenu(MF_STRING|MF_GRAYED, ID_POPMENU_DELETE_ITEM, "Delete current item"); //无效
	CPoint	MenuPoint;
	GetCursorPos(&MenuPoint);
	popupMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, MenuPoint.x, MenuPoint.y, this);

	CFormView::OnRButtonDown(nFlags, point);
}
void CSatConBitShowView::OnPopmenuDeleteItem(WPARAM wParam,LPARAM lParam)//删除item
{
	int lastnum=m_pBitDoc->m_BitTabInfo[wParam].itemNum-1;
	m_BitDlg[wParam][lastnum]->DestroyWindow();
	delete	m_BitDlg[wParam][lastnum];
	
	m_pBitDoc->DeleteBitItem(wParam,lParam);
	
	for(int i=lParam;i<m_pBitDoc->m_BitTabInfo[wParam].itemNum;i++)
	{
		m_BitDlg[wParam][i]->UpdateBitItem();
	}
	
}
void CSatConBitShowView::OnPopmenuNewItem()		//新建item
{
	int j=m_pBitDoc->m_BitTabInfo[m_curSelPage].itemNum;
	CreateItem(m_curSelPage, j);
	m_pBitDoc->m_BitTabInfo[m_curSelPage].itemNum++;
	m_initOver=true;
	OnSize(0,0,0);
}
void CSatConBitShowView::OnPopmenuNewPage()
{
	int tabnum=m_pBitDoc->m_TabNum;
	m_BitShowTab.InsertItem(tabnum,"New Page");	//在最后插入新页
	m_BitShowTab.SetCurSel(tabnum);
	if(tabnum>1)
		ShowTabComb(m_curSelPage,0);
	m_curSelPage=tabnum;	
	strcpy(m_pBitDoc->m_BitTabInfo[m_curSelPage].tabName,"New Page");
	m_pBitDoc->m_BitTabInfo[m_curSelPage].itemNum=16;		//新建page默认新建item个数16
	for(int i=0;i<m_pBitDoc->m_BitTabInfo[m_curSelPage].itemNum;i++)
		CreateItem(tabnum,i);
	m_pBitDoc->m_TabNum++;
}
void CSatConBitShowView::OnPopmenuDeletePage()		//删除页
{
	int i,j;
	int curitemNum=m_pBitDoc->m_BitTabInfo[m_curSelPage].itemNum;//item个数
	int tabnum=m_pBitDoc->m_TabNum;
	if(tabnum==0)//无page页
		return;
	
	if (AfxMessageBox("Delete page?", MB_YESNO|MB_ICONQUESTION, 0)!= IDYES)
		return;
	
	for(i=0;i<curitemNum;i++)
	{
		m_BitDlg[m_curSelPage][i]->DestroyWindow();
		delete	m_BitDlg[m_curSelPage][i];
	}
	
	for(i=m_curSelPage;i<(tabnum-1);i++)//page前移
	{
		
		m_BitShowTab.DeleteItem(i);
		m_BitShowTab.InsertItem(i, m_pBitDoc->m_BitTabInfo[i+1].tabName);
		
		for(j=0;j<m_pBitDoc->m_BitTabInfo[i+1].itemNum;j++)
		{
			m_BitDlg[i][j]=m_BitDlg[i+1][j];
			m_BitDlg[i][j]->pageNumber=i;
		}
		
	}
	m_BitShowTab.DeleteItem(tabnum-1);		//删除tab最后一页
	if((m_curSelPage==(tabnum-1))&&(m_curSelPage!=0))	//当删除的是最后一页
	{
		m_curSelPage--;
		m_BitShowTab.SetCurSel(m_curSelPage);
		ShowTabComb(m_curSelPage, 1);
	}
	else if(tabnum!=1)
		ShowTabComb(m_curSelPage, 1);
	m_pBitDoc->DeleteBitPage(m_curSelPage);	//删除page数据
	//	m_ReaderTab.SetCurSel(curSel);
		OnSize(0,0,0);
}
int CSatConBitShowView::ShowTabComb(int page, int isShow)
{
	if(isShow)
	{
		for(int i=0;i<m_pBitDoc->m_BitTabInfo[page].itemNum;i++)
		{
			m_BitDlg[page][i]->ShowWindow(SW_SHOW);
			if(m_BitDlg[page][i]->m_iteminfo->ValInfo)
				m_BitDlg[page][i]->m_iteminfo->ValInfo->commable=TRUE;
		}
	}
	else
	{
		for(int i=0;i<m_pBitDoc->m_BitTabInfo[page].itemNum;i++)
		{
			m_BitDlg[page][i]->ShowWindow(SW_HIDE);
			if(m_BitDlg[page][i]->m_iteminfo->ValInfo)
				m_BitDlg[page][i]->m_iteminfo->ValInfo->commable=FALSE;
		}
	}
	
	return 1;
}
int CSatConBitShowView::UpdateItemRect(int i, int j)
{
	CRect frmrect,dlgrect,rect;
	GetClientRect(frmrect);
	frmrect.top += 30;
	frmrect.left += 20;
	m_BitDlg[i][j]->GetWindowRect(dlgrect);
	int width=dlgrect.Width()+ITEM_OUTER_WIDTH;
	int height=dlgrect.Height()+ITEM_OUTER_HEIGHT;
	int lineNum=frmrect.Width()/width;
	if(lineNum<1)lineNum=1;
	int line = j / lineNum;
	int row = j % lineNum;
	rect.left = frmrect.left+row*width;
	rect.top  =frmrect.top+line*height;
	rect.right=rect.left+dlgrect.Width();
	rect.bottom=rect.top+dlgrect.Height();
	
	m_BitDlg[i][j]->MoveWindow(rect,TRUE);
	return 1;
}
void CSatConBitShowView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetScrollPos(SB_VERT,0);
	ShowScrollBar(SB_HORZ,FALSE);//隐藏水平滚动条
	if (m_initOver == FALSE)	//还没初始化好，直接返回。
		return;
	CRect tabrect,dlgrect;
	GetClientRect(m_formrect);
	m_BitShowTab.GetClientRect(tabrect);
	tabrect.right=m_formrect.right;
	m_BitShowTab.MoveWindow(tabrect);//右边对齐
	
	int itemnum=m_pBitDoc->m_BitTabInfo[m_curSelPage].itemNum;
	if(itemnum<=0)	//page中无item
		return;
	int j = 0;
	for(j=0;j<itemnum;j++)		//重新排列item
		UpdateItemRect(m_curSelPage,j);
	
	j=m_pBitDoc->m_BitTabInfo[m_curSelPage].itemNum-1;//最后一个item标号
	m_BitDlg[m_curSelPage][j]->GetWindowRect(dlgrect);
	ScreenToClient(dlgrect);
	tabrect.bottom=dlgrect.bottom+30;		//底部对齐
	m_BitShowTab.MoveWindow(tabrect,TRUE);
	SetScrollRange(SB_VERT,0,tabrect.bottom);//滚动条范围
}

void CSatConBitShowView::OnDestroy() 
{
	CFormView::OnDestroy();
	m_comm.pBitView=0;
//	KillTimer(1);
	for(int i=0;i<m_pBitDoc->m_TabNum;i++)
	{
		int &num=m_pBitDoc->m_BitTabInfo[i].itemNum;	//引用
		for(int j=0;j<num;j++)
		{
			m_BitDlg[i][j]->DestroyWindow();
			delete m_BitDlg[i][j];
		}
	}

	// TODO: Add your message handler code here
	
}

void CSatConBitShowView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	KillTimer(1);
	if(UpDataBit)//如果变量数据被用户修改更新所有数据
	{
		for(int i=0;i<m_pBitDoc->m_TabNum;i++)
			for(int j=0;j<m_pBitDoc->m_BitTabInfo[i].itemNum;j++)
				m_BitDlg[i][j]->UpdateBitItem();
		UpDataBit=FALSE;
	}
	else
	{
		for(int j=0;j<m_pBitDoc->m_BitTabInfo[m_curSelPage].itemNum;j++)
			m_BitDlg[m_curSelPage][j]->UpdateBitItem();//更新读取数据
	}
//	SetTimer(1,300,NULL);
	CFormView::OnTimer(nIDEvent);
}
