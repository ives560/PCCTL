// SatConReadView.cpp : implementation of the CSatConReadView class
//

#include "stdafx.h"
#include "SatCon.h"
#include "BaseData.h"
#include "SatConReadDoc.h"
#include "SatConReadView.h"
#include "SubDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CCommSet m_comm;
extern bool UpDataRead;
extern int 	OpLevel;
extern bool ChangeTable;
/////////////////////////////////////////////////////////////////////////////
// CSatConReadView

IMPLEMENT_DYNCREATE(CSatConReadView, CFormView)

BEGIN_MESSAGE_MAP(CSatConReadView, CFormView)
	//{{AFX_MSG_MAP(CSatConReadView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_READER_TAB, OnSelchangeReaderTab)
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
// CSatConReadView construction/destruction

CSatConReadView::CSatConReadView()
	: CFormView(CSatConReadView::IDD)
{
	//{{AFX_DATA_INIT(CSatConReadView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	m_initOver=FALSE;

	for(int i=0;i<TAB_MAX_NUM;i++)
		for(int j=0;j<ITEM_MAX_NUM;j++)
			m_ReadDlg[i][j]=NULL;
}

CSatConReadView::~CSatConReadView()
{
}

void CSatConReadView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSatConReadView)
	DDX_Control(pDX, IDC_READER_TAB, m_ReaderTab);
	//}}AFX_DATA_MAP
}

BOOL CSatConReadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSatConReadView diagnostics

#ifdef _DEBUG
void CSatConReadView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSatConReadView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSatConReadDoc* CSatConReadView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSatConReadDoc)));
	return (CSatConReadDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSatConReadView message handlers
void CSatConReadView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();
	m_pReadDoc = (CSatConReadDoc*)GetDocument();
//	MoveWindow(m_pReadDoc->m_form_left,m_pReadDoc->m_form_top,
//				m_pReadDoc->m_form_width,m_pReadDoc->m_form_height);
	m_curSelPage=m_pReadDoc->m_lastPage;
	int i,j; bool tabflg=FALSE,itemflg=FALSE;
	// TODO: Add your specialized code here and/or call the base class
	//动态创建TAB
	for(i=0;i<m_pReadDoc->m_TabNum;i++)
	{
		tabflg=true;
		m_ReaderTab.InsertItem(i,m_pReadDoc->m_ReadTabInfo[i].tabName);
	}
	//创建item
	for(i=0;i<m_pReadDoc->m_TabNum;i++)
	{
		int &num=m_pReadDoc->m_ReadTabInfo[i].itemNum;	//引用
		if(num<10) num=10;		//item个数不够10个设置为10个
		for(j=0;j<num;j++)
		{
			itemflg=true;
			CreateItem(i, j);
		}
	}
	if(tabflg)
		m_ReaderTab.SetCurSel(m_curSelPage);
	//改变tab大小
	if(itemflg)
	{
		/*CRect rect;
		j=m_pReadDoc->m_ReadTabInfo[m_curSelPage].itemNum-1;
		m_ReadDlg[m_curSelPage][j]->GetWindowRect(rect);
		m_ReaderTab.GetClientRect(m_formrect);
		m_formrect.bottom=rect.bottom;
		m_ReaderTab.MoveWindow(m_formrect,TRUE);*/
		m_initOver=true;
		OnSize(0,0,0);
	}
	m_comm.pReadView=this;
//	SetTimer(1,300,NULL);//更新数据
}

void CSatConReadView::OnSelchangeReaderTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

 	int curSel = m_ReaderTab.GetCurSel();
	m_pReadDoc->m_lastPage=curSel;
	ShowTabComb(m_curSelPage,0);
	m_curSelPage=curSel;
	OnSize(0,0,0);
	ShowTabComb(m_curSelPage,1);
	ChangeTable=TRUE;
	*pResult = 0;
}

int CSatConReadView::CreateItem(int i, int j)	//创建item并计算显示位置
{
	CRect frmrect,dlgrect,rect; char* comtstr=NULL;
		GetClientRect(frmrect);
		frmrect.top += 30;
		frmrect.left += 20;
	m_ReadDlg[i][j]= new CSubDlg;
	m_ReadDlg[i][j]->Create(IDD_SUB_DIALOG,this,i,j,&(m_pReadDoc->m_ReadTabInfo[i].iteminfo[j]));
	m_ReadDlg[i][j]->GetWindowRect(dlgrect);
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

	m_ReadDlg[i][j]->MoveWindow(rect,TRUE);
	//m_ReadDlg[i][j]->SetWindowPos(this,rect.left,rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
	if (i == m_curSelPage) //显示窗口
	{
		m_ReadDlg[i][j]->ShowWindow(SW_SHOW);
		if(m_ReadDlg[i][j]->m_iteminfo->ValInfo)
			m_ReadDlg[i][j]->m_iteminfo->ValInfo->commable=TRUE;
	}
	return 1;
}
int CSatConReadView::UpdateItemRect(int i, int j)//更新item位置
{
	CRect frmrect,dlgrect,rect;
	GetClientRect(frmrect);
	frmrect.top += 30;
	frmrect.left += 20;
	m_ReadDlg[i][j]->GetWindowRect(dlgrect);
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
	
	m_ReadDlg[i][j]->MoveWindow(rect,TRUE);
	return 1;
}
void CSatConReadView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
//	ShowScrollBar(SB_BOTH,FALSE);
	ShowScrollBar(SB_HORZ,FALSE);//隐藏水平滚动条
	SetScrollPos(SB_VERT,0);
	if (m_initOver == FALSE)	//还没初始化好，直接返回。
		return;
	CRect tabrect,dlgrect;
	GetClientRect(m_formrect);
	m_ReaderTab.GetClientRect(tabrect);
	tabrect.right=m_formrect.right;
	m_ReaderTab.MoveWindow(tabrect);//右边对齐

	int itemnum=m_pReadDoc->m_ReadTabInfo[m_curSelPage].itemNum;
	if(itemnum<=0)	//page中无item
		return;
	int j = 0;
	for(j=0;j<itemnum;j++)		//重新排列item
		UpdateItemRect(m_curSelPage,j);

	j=m_pReadDoc->m_ReadTabInfo[m_curSelPage].itemNum-1;//最后一个item标号
	m_ReadDlg[m_curSelPage][j]->GetWindowRect(dlgrect);
	ScreenToClient(dlgrect);
	tabrect.bottom=dlgrect.bottom+30;		//底部对齐
	m_ReaderTab.MoveWindow(tabrect,TRUE);
		SetScrollRange(SB_VERT,0,tabrect.bottom);
	// TODO: Add your message handler code here
	
}

void CSatConReadView::OnRButtonDown(UINT nFlags, CPoint point) 
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
void CSatConReadView::OnPopmenuDeleteItem(WPARAM wParam,LPARAM lParam)//删除item
{
	int lastnum=m_pReadDoc->m_ReadTabInfo[wParam].itemNum-1;
	m_ReadDlg[wParam][lastnum]->DestroyWindow();
	delete	m_ReadDlg[wParam][lastnum];

	m_pReadDoc->DeleteReadItem(wParam,lParam);

	for(int i=lParam;i<m_pReadDoc->m_ReadTabInfo[wParam].itemNum;i++)
	{
		m_ReadDlg[wParam][i]->UpdateReadItem();
	}
	
}
void CSatConReadView::OnPopmenuNewItem()		//新建item
{
	int j=m_pReadDoc->m_ReadTabInfo[m_curSelPage].itemNum;
	CreateItem(m_curSelPage, j);
	m_pReadDoc->m_ReadTabInfo[m_curSelPage].itemNum++;
	m_initOver=true;
	OnSize(0,0,0);
}
void CSatConReadView::OnPopmenuNewPage()
{
	int tabnum=m_pReadDoc->m_TabNum;
	m_ReaderTab.InsertItem(tabnum,"New Page");	//在最后插入新页
	m_ReaderTab.SetCurSel(tabnum);
	if(tabnum>1)
		ShowTabComb(m_curSelPage,0);
	m_curSelPage=tabnum;	
	strcpy(m_pReadDoc->m_ReadTabInfo[m_curSelPage].tabName,"New Page");
	m_pReadDoc->m_ReadTabInfo[m_curSelPage].itemNum=10;		//新建page默认新建item个数10
	for(int i=0;i<m_pReadDoc->m_ReadTabInfo[m_curSelPage].itemNum;i++)
		CreateItem(tabnum,i);
	m_pReadDoc->m_TabNum++;
}
void CSatConReadView::OnPopmenuDeletePage()		//删除页
{
	int i,j;
	int curitemNum=m_pReadDoc->m_ReadTabInfo[m_curSelPage].itemNum;//item个数
	int tabnum=m_pReadDoc->m_TabNum;
	if(tabnum==0)//无page页
		return;

	if (AfxMessageBox("Delete page?", MB_YESNO|MB_ICONQUESTION, 0)!= IDYES)
		return;

	for(i=0;i<curitemNum;i++)
	{
		m_ReadDlg[m_curSelPage][i]->DestroyWindow();
		delete	m_ReadDlg[m_curSelPage][i];
	}

	for(i=m_curSelPage;i<(tabnum-1);i++)//page前移
	{

		m_ReaderTab.DeleteItem(i);
		m_ReaderTab.InsertItem(i, m_pReadDoc->m_ReadTabInfo[i+1].tabName);

		for(j=0;j<m_pReadDoc->m_ReadTabInfo[i+1].itemNum;j++)
		{
			m_ReadDlg[i][j]=m_ReadDlg[i+1][j];
			m_ReadDlg[i][j]->pageNumber=i;
		}

	}
	m_ReaderTab.DeleteItem(tabnum-1);		//删除tab最后一页
	if((m_curSelPage==(tabnum-1))&&(m_curSelPage!=0))	//当删除的是最后一页
	{
		m_curSelPage--;
		m_ReaderTab.SetCurSel(m_curSelPage);
		ShowTabComb(m_curSelPage, 1);
	}
	else if(tabnum!=1)
		ShowTabComb(m_curSelPage, 1);
	m_pReadDoc->DeleteReadPage(m_curSelPage);	//删除page数据
	OnSize(0,0,0);
}
int CSatConReadView::ShowTabComb(int page, int isShow)
{
	if(isShow)
	{
		for(int i=0;i<m_pReadDoc->m_ReadTabInfo[page].itemNum;i++)
		{
			m_ReadDlg[page][i]->ShowWindow(SW_SHOW);
			if(m_ReadDlg[page][i]->m_iteminfo->ValInfo)
				m_ReadDlg[page][i]->m_iteminfo->ValInfo->commable=TRUE;
		}
	}
	else
	{
		for(int i=0;i<m_pReadDoc->m_ReadTabInfo[page].itemNum;i++)
		{
			m_ReadDlg[page][i]->ShowWindow(SW_HIDE);
			if(m_ReadDlg[page][i]->m_iteminfo->ValInfo)
				m_ReadDlg[page][i]->m_iteminfo->ValInfo->commable=FALSE;
		}
	}

	return 1;
}

void CSatConReadView::OnDestroy() 
{
	CFormView::OnDestroy();
	m_comm.pReadView=0;
//	KillTimer(1);
	for(int i=0;i<m_pReadDoc->m_TabNum;i++)
	{
		int &num=m_pReadDoc->m_ReadTabInfo[i].itemNum;	//引用
		for(int j=0;j<num;j++)
		{
			m_ReadDlg[i][j]->DestroyWindow();
			delete m_ReadDlg[i][j];
		}
	}
	// TODO: Add your message handler code here
	
}

void CSatConReadView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	KillTimer(1);
	if(UpDataRead)//如果变量数据被用户修改更新所有数据
	{
		for(int i=0;i<m_pReadDoc->m_TabNum;i++)
			for(int j=0;j<m_pReadDoc->m_ReadTabInfo[i].itemNum;j++)
				m_ReadDlg[i][j]->UpdateReadItem();
		UpDataRead=FALSE;
	}
	else
	{
		for(int j=0;j<m_pReadDoc->m_ReadTabInfo[m_curSelPage].itemNum;j++)
			m_ReadDlg[m_curSelPage][j]->UpValData();//更新读取数据
	}
//	SetTimer(1,300,NULL);
	CFormView::OnTimer(nIDEvent);
}
