// SatConWriteView.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "SatConWriteView.h"
#include "SatConWriteDoc.h"
#include "BaseData.h"
#include "SubWriteDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "CommSet.h"
extern CCommSet m_comm;
extern bool UpDataWrite;
extern int 	OpLevel;
extern int m_WriteTabNum;
extern 	TabInfo m_WriteTabInfo[TAB_MAX_NUM];
extern CMD_BUTTON save_cmd;
extern bool ChangeTable;
/////////////////////////////////////////////////////////////////////////////
// SatConWriteView

IMPLEMENT_DYNCREATE(SatConWriteView, CFormView)

BEGIN_MESSAGE_MAP(SatConWriteView, CFormView)
	//{{AFX_MSG_MAP(SatConWriteView)
	ON_NOTIFY(TCN_SELCHANGE,IDC_WRITE_TAB, OnSelchangeWriteTab)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, OnClearButton)
	ON_BN_CLICKED(IDC_LOADFDSP_BUTTON, OnLoadfdspButton)
	ON_BN_CLICKED(IDC_LOADFPC_BUTTON, OnLoadfpcButton)
	ON_BN_CLICKED(IDC_SAVEALL_BUTTON, OnSaveallButton)
	//}}AFX_MSG_MAP
	//ON_MESSAGE(ID_POPMENU_DELETE_ITEM, OnPopmenuDeleteItem)
	ON_COMMAND(ID_POPMENU_NEW_ITEM, OnPopmenuNewItem)
	ON_COMMAND(ID_POPMENU_NEW_PAGE, OnPopmenuNewPage)
	ON_COMMAND(ID_POPMENU_DELETE_PAGE, OnPopmenuDeletePage)
END_MESSAGE_MAP()
SatConWriteView::SatConWriteView()
	: CFormView(SatConWriteView::IDD)
{
	//{{AFX_DATA_INIT(SatConWriteView)
	//}}AFX_DATA_INIT
	m_initOver=FALSE;
	for(int i=0;i<TAB_MAX_NUM;i++)
		for(int j=0;j<ITEM_MAX_NUM;j++)
			m_WriteDlg[i][j]=NULL;
}

SatConWriteView::~SatConWriteView()
{

}

void SatConWriteView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SatConWriteView)
	DDX_Control(pDX, IDC_SAVEALL_BUTTON, m_saveall);
	DDX_Control(pDX, IDC_LOADFPC_BUTTON, m_loadFpc);
	DDX_Control(pDX, IDC_LOADFDSP_BUTTON, m_loadFdsp);
	DDX_Control(pDX, IDC_CLEAR_BUTTON, m_clear);
	DDX_Control(pDX, IDC_WRITE_TAB, m_WriteTab);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SatConWriteView diagnostics

#ifdef _DEBUG
void SatConWriteView::AssertValid() const
{
	CFormView::AssertValid();
}

void SatConWriteView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// SatConWriteView message handlers
void SatConWriteView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();
	m_pWriteDoc = (SatConWriteDoc*)GetDocument();
	m_curSelPage=m_pWriteDoc->m_lastPage;
	int i,j; bool tabflg=FALSE,itemflg=FALSE;
	// TODO: Add your specialized code here and/or call the base class	
	//动态创建TAB
	for(i=0;i<m_WriteTabNum;i++)
	{
		tabflg=true;
		m_WriteTab.InsertItem(i,m_WriteTabInfo[i].tabName);
	}
	//创建item
	for(i=0;i<m_WriteTabNum;i++)
	{
		int &num=m_WriteTabInfo[i].itemNum;	//引用
		if(num<10) num=10;		//item个数不够10个设置为10个
		for(j=0;j<num;j++)
		{
			itemflg=true;
			CreateItem(i, j);
		}
	}
	if(tabflg)
		m_WriteTab.SetCurSel(m_curSelPage);
	//改变tab大小
	if(itemflg)
	{
		/*CRect rect;
		j=m_pWriteDoc->m_WriteTabInfo[m_curSelPage].itemNum-1;
		m_WriteDlg[m_curSelPage][j]->GetWindowRect(rect);
		m_WriteTab.GetClientRect(m_formrect);
		m_formrect.bottom=rect.bottom;
		m_WriteTab.MoveWindow(m_formrect,TRUE);*/
		m_initOver=true;
		OnSize(0,0,0);
	}
	m_comm.pWriteView=this;
//	SetTimer(1,300,NULL);//更新数据
}

void SatConWriteView::OnSelchangeWriteTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int curSel = m_WriteTab.GetCurSel();
	m_pWriteDoc->m_lastPage=curSel;
	ShowTabComb(m_curSelPage,0);
	m_curSelPage=curSel;
	OnSize(0,0,0);
	ShowTabComb(m_curSelPage,1);
	ChangeTable=TRUE;
	*pResult = 0;
}

int SatConWriteView::CreateItem(int i, int j)	//创建item并计算显示位置
{
	CRect frmrect,dlgrect,rect; char* comtstr=NULL;
		GetClientRect(frmrect);
		frmrect.top += 30;
		frmrect.left += 20;
	m_WriteDlg[i][j]= new SubWriteDlg;
	m_WriteDlg[i][j]->Create(IDD_SUB_DIALOG_WRITE,this,i,j,&(m_WriteTabInfo[i].iteminfo[j]));
	m_WriteDlg[i][j]->GetWindowRect(dlgrect);
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

	m_WriteDlg[i][j]->MoveWindow(rect,TRUE);
	//m_ReadDlg[i][j]->SetWindowPos(this,rect.left,rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
	if (i == m_curSelPage) //显示窗口
	{
		m_WriteDlg[i][j]->ShowWindow(SW_SHOW);
		if(m_WriteDlg[i][j]->m_iteminfo->ValInfo)
			m_WriteDlg[i][j]->m_iteminfo->ValInfo->commable=TRUE;
	}
	return 1;
}
int SatConWriteView::UpdateItemRect(int i, int j)//更新item位置
{
	CRect frmrect,dlgrect,rect;
	GetClientRect(frmrect);
	frmrect.top += 30;
	frmrect.left += 20;
	m_WriteDlg[i][j]->GetWindowRect(dlgrect);
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
	
	m_WriteDlg[i][j]->MoveWindow(rect,TRUE);
	return 1;
}
void SatConWriteView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	SetScrollPos(SB_VERT,0);//移动滚动条到0
	if (m_initOver == FALSE)	//还没初始化好，直接返回。
		return;
	CRect tabrect,dlgrect,btnrect;
	GetClientRect(m_formrect);
	m_WriteTab.GetClientRect(tabrect);
	tabrect.right=m_formrect.right;
	m_WriteTab.MoveWindow(tabrect);//右边对齐

	int itemnum=m_WriteTabInfo[m_curSelPage].itemNum;
	if(itemnum<=0)	//page中无item
		return;
	int j = 0;
	for(j=0;j<itemnum;j++)		//重新排列item
		UpdateItemRect(m_curSelPage,j);

	j=m_WriteTabInfo[m_curSelPage].itemNum-1;//最后一个item标号
	m_WriteDlg[m_curSelPage][j]->GetWindowRect(dlgrect);
	ScreenToClient(dlgrect);
	tabrect.bottom=dlgrect.bottom+30;		//底部对齐
	m_WriteTab.MoveWindow(tabrect,TRUE);
	for(int m=IDC_SAVEALL_BUTTON;m<(IDC_SAVEALL_BUTTON+4);m++)
	{
		CWnd *cwnd=GetDlgItem(m);
		cwnd->GetWindowRect(btnrect);
		int width=btnrect.bottom-btnrect.top;
		ScreenToClient(btnrect);
		btnrect.top=tabrect.bottom+10;
		btnrect.bottom =btnrect.top+width;
		cwnd->MoveWindow(btnrect,TRUE);
	}

	SetScrollRange(SB_VERT,0,tabrect.bottom+50);//滚动条范围
	// TODO: Add your message handler code here
	
}

void SatConWriteView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(OpLevel==0)
		return;
	CMenu popupMenu;
	popupMenu.CreatePopupMenu();
	popupMenu.AppendMenu(MF_STRING, ID_POPMENU_NEW_PAGE, "New a page");
	popupMenu.AppendMenu(MF_STRING, ID_POPMENU_NEW_ITEM, "New a item");
	popupMenu.AppendMenu(MF_STRING, ID_POPMENU_DELETE_PAGE, "Delete current page");
	popupMenu.AppendMenu(MF_STRING|MF_GRAYED, ID_POPMENU_DELETE_ITEM, "Delete current item"); //无效
	CPoint	MenuPoint;
	GetCursorPos(&MenuPoint);
	popupMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, MenuPoint.x, MenuPoint.y, this);
	CFormView::OnRButtonDown(nFlags, point);
}
void SatConWriteView::OnPopmenuDeleteItem(WPARAM wParam,LPARAM lParam)//删除item
{
	int lastnum=m_WriteTabInfo[wParam].itemNum-1;
	m_WriteDlg[wParam][lastnum]->DestroyWindow();
	delete	m_WriteDlg[wParam][lastnum];

	m_pWriteDoc->DeleteWriteItem(wParam,lParam);

	for(int i=lParam;i<m_WriteTabInfo[wParam].itemNum;i++)
	{
		m_WriteDlg[wParam][i]->UpdateWriteItem();
	}
	
}
void SatConWriteView::OnPopmenuNewItem()		//新建item
{
	int j=m_WriteTabInfo[m_curSelPage].itemNum;
	CreateItem(m_curSelPage, j);
	m_WriteTabInfo[m_curSelPage].itemNum++;
	m_initOver=true;
	OnSize(0,0,0);
}
void SatConWriteView::OnPopmenuNewPage()
{
	int tabnum=m_WriteTabNum;
	m_WriteTab.InsertItem(tabnum,"New Page");	//在最后插入新页
	m_WriteTab.SetCurSel(tabnum);
	if(tabnum>1)
		ShowTabComb(m_curSelPage,0);
	m_curSelPage=tabnum;	
	strcpy(m_WriteTabInfo[m_curSelPage].tabName,"New Page");
	m_WriteTabInfo[m_curSelPage].itemNum=10;		//新建page默认新建item个数10
	for(int i=0;i<m_WriteTabInfo[m_curSelPage].itemNum;i++)
		CreateItem(tabnum,i);
	m_WriteTabNum++;
}
void SatConWriteView::OnPopmenuDeletePage()		//删除页
{
	int i,j;
	int curitemNum=m_WriteTabInfo[m_curSelPage].itemNum;//item个数
	int tabnum=m_WriteTabNum;
	if(tabnum==0)//无page页
		return;

	if (AfxMessageBox("Delete page?", MB_YESNO|MB_ICONQUESTION, 0)!= IDYES)
		return;

	for(i=0;i<curitemNum;i++)
	{
		m_WriteDlg[m_curSelPage][i]->DestroyWindow();
		delete	m_WriteDlg[m_curSelPage][i];
	}

	for(i=m_curSelPage;i<(tabnum-1);i++)//page前移
	{

		m_WriteTab.DeleteItem(i);
		m_WriteTab.InsertItem(i,m_WriteTabInfo[i+1].tabName);

		for(j=0;j<m_WriteTabInfo[i+1].itemNum;j++)
		{
			m_WriteDlg[i][j]=m_WriteDlg[i+1][j];
			m_WriteDlg[i][j]->pageNumber=i;
		}

	}
	m_WriteTab.DeleteItem(tabnum-1);		//删除tab最后一页
	if((m_curSelPage==(tabnum-1))&&(m_curSelPage!=0))	//当删除的是最后一页
	{
		m_curSelPage--;
		m_WriteTab.SetCurSel(m_curSelPage);
		ShowTabComb(m_curSelPage, 1);
	}
	else if(tabnum!=1)
		ShowTabComb(m_curSelPage, 1);
	m_pWriteDoc->DeleteWritePage(m_curSelPage);	//删除page数据
//	m_ReaderTab.SetCurSel(curSel);
	OnSize(0,0,0);
}
int SatConWriteView::ShowTabComb(int page, int isShow)
{
	if(isShow)
	{
		for(int i=0;i<m_WriteTabInfo[page].itemNum;i++)
		{
			m_WriteDlg[page][i]->ShowWindow(SW_SHOW);
			if(m_WriteDlg[page][i]->m_iteminfo->ValInfo)
				m_WriteDlg[page][i]->m_iteminfo->ValInfo->commable=TRUE;
		}
	}
	else
	{
		for(int i=0;i<m_WriteTabInfo[page].itemNum;i++)
		{
			m_WriteDlg[page][i]->ShowWindow(SW_HIDE);
			if(m_WriteDlg[page][i]->m_iteminfo->ValInfo)
				m_WriteDlg[page][i]->m_iteminfo->ValInfo->commable=FALSE;
		}
	}

	return 1;
}
void SatConWriteView::OnClearButton() 
{
	// TODO: Add your control notification handler code here
	for(int i=0;i<m_WriteTabInfo[m_curSelPage].itemNum;i++)
	{
		m_WriteDlg[m_curSelPage][i]->m_currval=0;
		m_WriteDlg[m_curSelPage][i]->UpdateData(FALSE);
		m_WriteDlg[m_curSelPage][i]->ChangeColor(0);
	}
}

void SatConWriteView::OnLoadfdspButton() 
{
	// TODO: Add your control notification handler code here
	for(int i=0;i<m_WriteTabInfo[m_curSelPage].itemNum;i++)
	{
		m_WriteDlg[m_curSelPage][i]->m_currval=m_WriteDlg[m_curSelPage][i]->m_val;
		m_WriteDlg[m_curSelPage][i]->UpdateData(FALSE);
		m_WriteDlg[m_curSelPage][i]->ChangeColor(2);
	}
}

void SatConWriteView::OnLoadfpcButton() 
{
	// TODO: Add your control notification handler code here
	for(int i=0;i<m_WriteTabInfo[m_curSelPage].itemNum;i++)
	{
		if(m_WriteDlg[m_curSelPage][i]->m_iteminfo->ValInfo)
			m_WriteDlg[m_curSelPage][i]->m_currval=atof(m_WriteDlg[m_curSelPage][i]->m_iteminfo->ValInfo->cvalue);
		else
			m_WriteDlg[m_curSelPage][i]->m_currval=0;
		m_WriteDlg[m_curSelPage][i]->UpdateData(FALSE);
		m_WriteDlg[m_curSelPage][i]->ChangeColor(3);
	}
}

void SatConWriteView::OnSaveallButton() 
{
	// TODO: Add your control notification handler code here
	if(!m_comm.m_ComOpened||OpLevel==0)//串口 打开
		return;
	if(save_cmd.Value!=0)//有变量数据
	{
		if(save_cmd.pinfo->writeable)//写使能
		{
			memset(&m_comm.TxBuffer[m_comm.TxIndex],0,sizeof(BUFFER_STRUCT));//数据清零
			
			m_comm.TxBuffer[m_comm.TxIndex].TxAddss=save_cmd.pinfo->address;
			
			m_comm.TxBuffer[m_comm.TxIndex].TxData[0]=(save_cmd.Value>>8)&0xff;
			m_comm.TxBuffer[m_comm.TxIndex].TxData[1]=save_cmd.Value&0xff;
			
			m_comm.TxIndex++;		//有发送数据
		}
		
	}
/*	for(int i=0;i<m_pWriteDoc->m_WriteTabInfo[m_curSelPage].itemNum;i++)//保存到配置文件
	{
		m_WriteDlg[m_curSelPage][i]->UpdateData(TRUE);
		if(m_WriteDlg[m_curSelPage][i]->m_iteminfo->ValInfo)
		{
			m_WriteDlg[m_curSelPage][i]->m_iteminfo->ValInfo->value=m_WriteDlg[m_curSelPage][i]->m_currval;
			if(!m_comm.m_ComOpened)//串口 打开
				break;
			if(m_WriteDlg[m_curSelPage][i]->m_iteminfo->ValInfo->writeable)//写使能
			{
				memset(&m_comm.TxBuffer[i],0,sizeof(BUFFER_STRUCT));//数据清零		
				m_comm.TxBuffer[i].TxAddss=m_WriteDlg[m_curSelPage][i]->m_iteminfo->ValInfo->address;
				int data=m_WriteDlg[m_curSelPage][i]->m_currval;
				m_comm.TxBuffer[i].TxData[0]=(data>>8)&0xff;
				m_comm.TxBuffer[i].TxData[1]=data&0xff;
			}
		}
		m_WriteDlg[m_curSelPage][i]->ChangeColor(0);
	}
	m_comm.TxIndex=i;*/		//有发送数据
}

void SatConWriteView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	if(UpDataWrite)//如果变量数据被用户修改更新所有数据
	{
		for(int i=0;i<m_WriteTabNum;i++)
			for(int j=0;j<m_WriteTabInfo[i].itemNum;j++)
				m_WriteDlg[i][j]->UpdateWriteItem();
			UpDataWrite=FALSE;
	}
	else
	{
		for(int j=0;j<m_WriteTabInfo[m_curSelPage].itemNum;j++)
			m_WriteDlg[m_curSelPage][j]->UpValData();//更新读取数据
	}
	SetTimer(1,300,NULL);
	CFormView::OnTimer(nIDEvent);
}

void SatConWriteView::OnDestroy() 
{
	CFormView::OnDestroy();	
	// TODO: Add your message handler code here
	m_comm.pWriteView=0;
	for(int i=0;i<m_WriteTabNum;i++)
	{
		int &num=m_WriteTabInfo[i].itemNum;	//引用
		for(int j=0;j<num;j++)
		{
			m_WriteDlg[i][j]->DestroyWindow();
			delete m_WriteDlg[i][j];
		}
	}
}
