// MyChart.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "MyChart.h"
#include "CommSet.h"
#include "CalendarShow.h"
#include "OldChart.h"
#include "MyCalendarDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool ChangeTable;
extern CCommSet m_comm;
extern int m_para_tot_num;
extern PARAINI_INFO m_para_info[MAX_PARA_INI_NUM];
/////////////////////////////////////////////////////////////////////////////
// CMyChart

IMPLEMENT_DYNCREATE(CMyChart, CFormView)

CMyChart::CMyChart()
	: CFormView(CMyChart::IDD)
{
	//{{AFX_DATA_INIT(CMyChart)
	//}}AFX_DATA_INIT
	m_initOver=false;
}

CMyChart::~CMyChart()
{
}

void CMyChart::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyChart)
	DDX_Control(pDX, IDC_COMBO_PARA, m_para);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyChart, CFormView)
	//{{AFX_MSG_MAP(CMyChart)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_PARA, OnSelchangeComboPara)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_OLDCHART_BUTTON, OnOldchartButton)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyChart diagnostics

#ifdef _DEBUG
void CMyChart::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyChart::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyChart message handlers
/////////////////////////////////////////////////////////////////////////////
// CMyChartDoc

IMPLEMENT_DYNCREATE(CMyChartDoc, CDocument)

CMyChartDoc::CMyChartDoc()
{

}

BOOL CMyChartDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	SetTitle("Chart");
	return TRUE;
}

CMyChartDoc::~CMyChartDoc()
{
}


BEGIN_MESSAGE_MAP(CMyChartDoc, CDocument)
	//{{AFX_MSG_MAP(CMyChartDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyChartDoc diagnostics

#ifdef _DEBUG
void CMyChartDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyChartDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyChartDoc serialization

void CMyChartDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyChartDoc commands
//文档初始化
void CMyChart::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_BasePath.Format("%s\\test.mdb",m_ado.GetAppPath());
	bool basefalg=m_ado.SearchBaseData(m_BasePath);
	if(basefalg==false)
		m_ado.CreateBaseData(m_BasePath);
	m_ado.OnInitADOConn(m_BasePath);//连接数据库
	if(basefalg==false)
		m_ado.NewNameTable("表名");
	/*----------获得当天表名-----------------------*/
	m_tablename=GetTableName();
	if(m_ado.NewDataTable(m_tablename)==false)//表已经存在
		m_ado.ReadTable(m_tablename,&m_chart);
	else//名字保存到“表名”表中
		m_ado.AddRowNameTable(m_tablename);
	/*---------------------------------------------*/
	m_Day=CTime::GetCurrentTime();
	/*----------------------------------------------*/
	m_pMainFram = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	for(int i=0;i<=m_para_tot_num;i++)
	{
		m_para.InsertString(i,m_para_info[i].itemName);
	}
	m_chart.m_pinfo=&m_para_info[0];
	m_para.SetCurSel(0);
	m_Selet=0;
	OnSelchangeComboPara();//y轴单位和数值
	SetTimer(1,10000,NULL);
	/*----------------------------------------------------*/
	CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
												0, (HBRUSH)CBrush(RGB(255,255,255)), 0);
	CRect rect;
	GetClientRect(rect);
	rect.top=100;
	m_chart.CreateEx(WS_EX_CLIENTEDGE, szClassName, _T(""),
		WS_CHILD|WS_VISIBLE|WS_TABSTOP, rect, 
		this, ID_CHART_DIALOG, NULL);

	m_initOver=true;
}
///定时器
void CMyChart::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1:
		{
			CTime time=CTime::GetCurrentTime();
			EnterNextDay(time);
			double var=m_chart.m_pinfo->curval;//通过比例设置后的值
			var=10;
			m_chart.GetPoints(time,var);
			m_chart.Invalidate();
		}
	}

	CFormView::OnTimer(nIDEvent);
}
//通过下拉菜单挑选参数
void CMyChart::OnSelchangeComboPara() 
{
	// TODO: Add your control notification handler code here
	int i=m_para.GetCurSel();
	if(i>=0)
	{
		if(m_chart.m_pinfo!=(&m_para_info[i]))
		{
			if((m_para_info[i].RdContinue!=1)||(m_para_info[i].max==0))
			{
				MessageBox("请先设置变量的参数!");
				m_para.SetCurSel(m_Selet);
				return;
			}
			m_chart.m_pinfo=&m_para_info[i];
			m_chart.Tlist.RemoveAll();
			m_chart.Dlist.RemoveAll();
			m_chart.Invalidate();
			m_Selet=i;
		}
	}
}
//窗口关闭
void CMyChart::OnDestroy() 
{
	CFormView::OnDestroy();
	m_ado.SaveTable(m_tablename,&m_chart);//保存表
	m_ado.CloseConn();//断开数据库连接
	// TODO: Add your message handler code here
	
}

CString CMyChart::GetTableName()
{
	CTime time=CTime::GetCurrentTime();
	CString str;
	str.Format("%.2d%.2d%.2d",time.GetYear(),time.GetMonth(),time.GetDay());
	return str;
}
//判断是否进入下一天
void CMyChart::EnterNextDay(CTime curDay)
{
	int old=m_Day.GetDay()+m_Day.GetMonth()+m_Day.GetYear();
	int cur=curDay.GetDay()+curDay.GetMonth()+curDay.GetYear();
	if(cur>old)//到下一天
	{
		m_Day=curDay;
		m_ado.SaveTable(m_tablename,&m_chart);
		m_tablename=GetTableName();
		m_ado.NewDataTable(m_tablename);
		m_ado.AddRowNameTable(m_tablename);
		m_chart.Tlist.RemoveAll();
		m_chart.Dlist.RemoveAll();
	}
}

void CMyChart::OnOldchartButton() 
{
	// TODO: Add your control notification handler code here
	CMyCalendarDlg dlg;
	if(Snamelist.GetCount()==0)
		ReadNameTable();
	dlg.pSlist=&Snamelist;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.m_Calendar.SeleDay!=m_tablename)//当天表
		{
			COldChart OldChart;
			m_ado.ReadTable(dlg.m_Calendar.SeleDay,&OldChart.m_chart);
			OldChart.DoModal();
		}
	}
}

void CMyChart::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_initOver==true)
	{
		CRect rect;
		GetClientRect(rect);
		rect.top=100;
		m_chart.MoveWindow(rect);
	}

}

void CMyChart::ReadNameTable()
{
	m_ado.OpenRecordset("表名");
	while(!m_ado.m_pRecordset->adoEOF)
	{
		CString str=(char*)(_bstr_t)m_ado.m_pRecordset->GetCollect("名字");
		Snamelist.AddTail(str);
		m_ado.m_pRecordset->MoveNext();//将记录集指针移动到下一条记录

	}
	m_ado.CloseRecordset();
}
