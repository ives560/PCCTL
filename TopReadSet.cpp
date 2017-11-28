// TopReadSet.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "TopReadSet.h"
#include "BaseData.h"
#include "DlaglogBarRW.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "MainFrm.h"
extern int m_para_tot_num;
extern PARAINI_INFO m_para_info[MAX_PARA_INI_NUM];
extern MainInfo m_maininfo;
/////////////////////////////////////////////////////////////////////////////
// TopReadSet dialog


TopReadSet::TopReadSet(CWnd* pParent /*=NULL*/)
	: CDialog(TopReadSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(TopReadSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Color=RGB(0,0,0);
}


void TopReadSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TopReadSet)
	DDX_Control(pDX, IDC_NAME_COMBO, m_namecomb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TopReadSet, CDialog)
	//{{AFX_MSG_MAP(TopReadSet)
	ON_BN_CLICKED(IDC_COLOR_STATIC, OnColorStatic)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_NAME_COMBO, OnSelchangeNameCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TopReadSet message handlers

BOOL TopReadSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	CMainFrame	*m_pMainFram = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	for(int i=0;i<=m_para_tot_num;i++)
	{
		m_namecomb.InsertString(i,m_para_info[i].itemName);//插入变量名
		if(strcmp(m_para_info[i].itemName,m_maininfo.mainval[m_num].Dply_Name)==0)
		{
			m_namecomb.SetCurSel(i);
			CString str=m_maininfo.mainval[m_num].Dply_Color;//颜色
			m_Color=atol(str);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL TopReadSet::Create(int num,CWnd* pParentWnd, UINT nID) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_num=num;
	return CDialog::Create(IDD, pParentWnd);
}

void TopReadSet::OnColorStatic() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg(m_Color);
	if(dlg.DoModal()==IDOK)
	{
		m_Color=dlg.GetColor();
		Invalidate();
	}
}

HBRUSH TopReadSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_COLOR_STATIC)
		pDC->SetTextColor(m_Color);
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void TopReadSet::OnSelchangeNameCombo() 
{
	// TODO: Add your control notification handler code here
	
}

void TopReadSet::OnOK() 
{
	// TODO: Add extra validation here
	int i=m_namecomb.GetCurSel();
	CString str;
	if(i>=0)
	{

		m_namecomb.GetWindowText(str);	
		strcpy(m_maininfo.mainval[m_num].Dply_Name,(LPSTR)(LPCTSTR)str);

		str.Format("%d",m_Color);
		strcpy(m_maininfo.mainval[m_num].Dply_Color,(LPSTR)(LPCTSTR)str);
		m_maininfo.mainval[m_num].ValInfo=&m_para_info[i];
	}
	CDialog::DestroyWindow();
//	CDialog::OnOK();
}
