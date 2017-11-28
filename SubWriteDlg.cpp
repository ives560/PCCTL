// SubWriteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "SubWriteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "VarNameSetDlg.h"
#include "SatConWriteView.h"
#include "CommSet.h"
extern CCommSet m_comm;
extern int  OpLevel;
extern 	TabInfo m_WriteTabInfo[TAB_MAX_NUM];
extern  CMD_BUTTON save_cmd;
/////////////////////////////////////////////////////////////////////////////
// SubWriteDlg dialog


SubWriteDlg::SubWriteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SubWriteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SubWriteDlg)
	m_val = 0.0f;
	m_unit = _T("");
	m_step = 0.0f;
	m_currval = 0.0f;
	//}}AFX_DATA_INIT
	editcolor=0;
}


void SubWriteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SubWriteDlg)
	DDX_Control(pDX, IDC_WRITE_GROUP, m_writeitem);
	DDX_Text(pDX, IDC_WRITE_VRL_EDIT, m_val);
	DDX_Text(pDX, IDC_WRITE_UNIT_EDIT, m_unit);
	DDX_Text(pDX, IDC_WRITE_STEP_EDIT, m_step);
	DDX_Text(pDX, IDC_WRITE_CURRVAL_EDIT, m_currval);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SubWriteDlg, CDialog)
	//{{AFX_MSG_MAP(SubWriteDlg)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_WRITE_CURRVAL_EDIT, OnChangeWriteCurrvalEdit)
	ON_BN_CLICKED(IDC_ADD_BUTTON, OnAddButton)
	ON_BN_CLICKED(IDC_DEC_BUTTON, OnDecButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, OnSaveButton)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_POPMENU_DELETE_ITEM, OnPopmenuDeleteItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SubWriteDlg message handlers

BOOL SubWriteDlg::OnInitDialog() 
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
	m_TipCtrl.AddTool(this,m_tipstr,&rect,ID_SUBWRITEDLG_TOOLTIP);
	UpdateWriteItem();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL SubWriteDlg::Create(UINT nID,CWnd* pParentWnd,int i,int j,ItemInfo *iteminfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	pageNumber=i;
	itemNumber=j;
	m_iteminfo=iteminfo;
	return CDialog::Create(IDD, pParentWnd);
}

BOOL SubWriteDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	//if(pMsg->message== WM_MOUSEMOVE)
	m_TipCtrl.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void SubWriteDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	

	if(OpLevel==0)
		return;
	CRect rect;
	GetWindowRect(rect);
	if(point.y<(rect.Height()/5))	//限制响应范围
	{
		SatConWriteView *pParent = (SatConWriteView*)GetParent();
		//	CSatConReadView *pParent = (CSatConReadView*)GetDlgItem(IDD_SATCON_READ_FORM);
		VarNameSetDlg Vardlg(m_WriteTabInfo[pParent->m_curSelPage].tabName,rect,m_iteminfo);
		if(Vardlg.DoModal()==IDOK)
		{
			strcpy(m_WriteTabInfo[pParent->m_curSelPage].tabName,(LPSTR)(LPCTSTR)Vardlg.m_setabnam);//设置page名
			pParent->m_WriteTab.DeleteItem(pParent->m_curSelPage);
			pParent->m_WriteTab.InsertItem(pParent->m_curSelPage,Vardlg.m_setabnam);
			pParent->ShowTabComb(pParent->m_curSelPage,0);
			pParent->ShowTabComb(pParent->m_curSelPage,1);
			UpdateWriteItem();
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void SubWriteDlg::OnRButtonDown(UINT nFlags, CPoint point) 
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
void SubWriteDlg::OnPopmenuDeleteItem()
{
	SatConWriteView *m_parent=(SatConWriteView*)GetParent();
	m_parent->PostMessage(ID_POPMENU_DELETE_ITEM,pageNumber,itemNumber);
	
}
void SubWriteDlg::UpdateWriteItem()
{
	m_writeitem.SetWindowText(m_iteminfo->ValName);//显示变量名
	if(m_iteminfo->ValInfo!=0)		//有变量数据信息
	{
		//m_val=m_iteminfo->ValInfo->curval;
		m_currval=0;
		m_unit=m_iteminfo->ValInfo->unit;
		m_step=m_iteminfo->ValInfo->step;
		m_tipstr=m_iteminfo->ValInfo->comt;			//设置说明信息
		m_TipCtrl.UpdateTipText(m_tipstr,this,ID_SUBWRITEDLG_TOOLTIP);
	}
	else						//无变量数据信息
	{
		m_unit="";
		m_tipstr="";
		m_currval=0;
		m_step=0;
		m_TipCtrl.UpdateTipText(m_tipstr,this,ID_SUBWRITEDLG_TOOLTIP);
	}
	UpdateData(FALSE);
}

void SubWriteDlg::UpValData()
{
	if(m_iteminfo->ValInfo!=0)
	{
		GetDlgItem(IDC_WRITE_VRL_EDIT)->SetWindowText(m_iteminfo->ValInfo->cfval);
	}
}

HBRUSH SubWriteDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_WRITE_GROUP)
		pDC->SetTextColor(RGB(255,0,0));
	else if(pWnd->GetDlgCtrlID()==IDC_WRITE_CURRVAL_EDIT)
	{
		if(editcolor==0)
			pDC->SetTextColor(RGB(0,0,0));
		else if(editcolor==1)
			pDC->SetTextColor(RGB(255,0,0));
		else if(editcolor==2)
			pDC->SetTextColor(RGB(0,128,192));//浅蓝 OnLoadfdspButton
		else if(editcolor==3)
			pDC->SetTextColor(RGB(255,0,255));	//粉红	OnLoadfpcButton
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void SubWriteDlg::OnChangeWriteCurrvalEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	ChangeColor(1);
	// TODO: Add your control notification handler code here
	
}
void SubWriteDlg::OnCancel()
{

}
void SubWriteDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(!m_comm.m_ComOpened||OpLevel==0)//串口 打开
		return;
	UpdateData(TRUE);
	if(m_iteminfo->ValInfo!=0)//有变量数据
	{
		if(m_iteminfo->ValInfo->writeable)//写使能
		{

			short data=(short)m_currval;
			if((m_iteminfo->ValInfo->binscale!=0)&&(m_iteminfo->ValInfo->decscale!=0))//数据 转换
				data=(short)((m_currval*m_iteminfo->ValInfo->binscale)/m_iteminfo->ValInfo->decscale);

			if((m_currval>-32768)&&(m_currval<65536)&&(data>=m_iteminfo->ValInfo->min)&&((data<=m_iteminfo->ValInfo->max)||(m_iteminfo->ValInfo->max==0)))//判断取值范围
			{
				memset(&m_comm.TxBuffer[m_comm.TxIndex],0,sizeof(BUFFER_STRUCT));//数据清零
				
				m_comm.TxBuffer[m_comm.TxIndex].TxAddss=m_iteminfo->ValInfo->address;
				m_comm.TxBuffer[m_comm.TxIndex].TxData[0]=(data>>8)&0xff;
				m_comm.TxBuffer[m_comm.TxIndex].TxData[1]=data&0xff;
				ChangeColor(0);
				m_comm.TxIndex++;		//有发送数据
			}
			else
				MessageBox("Out of range");
		}
		
	}
	//	CDialog::OnOK();
}

void SubWriteDlg::OnAddButton() 
{
	// TODO: Add your control notification handler code here
	if(!m_comm.m_ComOpened||OpLevel==0)//用户等级
		return;
	UpdateData(TRUE);
	if(m_step!=0)
	{
		if(m_iteminfo->ValInfo!=0)//有变量数据
		{
			if(m_iteminfo->ValInfo->writeable)//写使能
			{
				float fdata=m_val+m_step;
				int data;
				if((m_iteminfo->ValInfo->binscale!=0)&&(m_iteminfo->ValInfo->decscale!=0))
					data=(fdata*m_iteminfo->ValInfo->binscale)/m_iteminfo->ValInfo->decscale;
				else
					data=fdata;
				if((data>=m_iteminfo->ValInfo->min)&&(data<=m_iteminfo->ValInfo->max)||(m_iteminfo->ValInfo->max==0))//判断取值范围
				{
					memset(&m_comm.TxBuffer[m_comm.TxIndex],0,sizeof(BUFFER_STRUCT));//数据清零
					
					m_comm.TxBuffer[m_comm.TxIndex].TxAddss=m_iteminfo->ValInfo->address;
					m_comm.TxBuffer[m_comm.TxIndex].TxData[0]=(data>>8)&0xff;
					m_comm.TxBuffer[m_comm.TxIndex].TxData[1]=data&0xff;
					m_comm.TxIndex++;		//有发送数据
					m_currval = fdata;
					ChangeColor(0);
					UpdateData(FALSE);
				}
				else
					MessageBox("Out of range");
			}
			
		}
	}
}

void SubWriteDlg::OnDecButton() 
{
	// TODO: Add your control notification handler code here
	if(!m_comm.m_ComOpened||OpLevel==0)//串口 打开
		return;
	UpdateData(TRUE);
	if(m_step!=0)
	{
		if(m_iteminfo->ValInfo!=0)//有变量数据
		{
			if(m_iteminfo->ValInfo->writeable)//写使能
			{
				float fdata=m_val-m_step;
				int data;
				if((m_iteminfo->ValInfo->binscale!=0)&&(m_iteminfo->ValInfo->decscale!=0))
					data=(fdata*m_iteminfo->ValInfo->binscale)/m_iteminfo->ValInfo->decscale;
				else
					data=fdata;
				if((data>=m_iteminfo->ValInfo->min)&&(data<=m_iteminfo->ValInfo->max)||(m_iteminfo->ValInfo->max==0))//判断取值范围
				{
					memset(&m_comm.TxBuffer[m_comm.TxIndex],0,sizeof(BUFFER_STRUCT));//数据清零
					
					m_comm.TxBuffer[m_comm.TxIndex].TxAddss=m_iteminfo->ValInfo->address;
					m_comm.TxBuffer[m_comm.TxIndex].TxData[0]=(data>>8)&0xff;
					m_comm.TxBuffer[m_comm.TxIndex].TxData[1]=data&0xff;
					m_comm.TxIndex++;		//有发送数据
					m_currval = fdata;
					UpdateData(FALSE);
					ChangeColor(0);
				}
				else
					MessageBox("Out of range");
			}
			
		}
	}
}
void SubWriteDlg::OnSaveButton() 
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
}
void SubWriteDlg::ChangeColor(int color)
{
	editcolor=color;
	GetDlgItem(IDC_WRITE_CURRVAL_EDIT)->Invalidate();
}

void SubWriteDlg::PCvalToDSPval(PARAINI_INFO *parainfo, float data)
{
	if((parainfo->binscale!=0)&&(parainfo->decscale!=0))
		parainfo->curval=(parainfo->curval*parainfo->binscale)/parainfo->decscale;
}

void SubWriteDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnTimer(nIDEvent);
}
