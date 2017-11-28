// TopBitSet.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "TopBitSet.h"

#include "BaseData.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int m_para_tot_num;
extern PARAINI_INFO m_para_info[MAX_PARA_INI_NUM];
extern MainInfo m_maininfo;
/////////////////////////////////////////////////////////////////////////////
// TopBitSet dialog


TopBitSet::TopBitSet(CWnd* pParent /*=NULL*/)
	: CDialog(TopBitSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(TopBitSet)
	//}}AFX_DATA_INIT
}


void TopBitSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TopBitSet)
	DDX_Control(pDX, IDC_BIT_COMBO, m_bitcomb);
	DDX_Control(pDX, IDC_VARIABLE_COMBO, m_namecomb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TopBitSet, CDialog)
	//{{AFX_MSG_MAP(TopBitSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TopBitSet message handlers
BOOL TopBitSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	for(int i=0;i<=m_para_tot_num;i++)
	{
		m_namecomb.InsertString(i,m_para_info[i].itemName);//插入变量名
		if(strcmp(m_para_info[i].itemName,m_maininfo.mainbit[m_num].Bit_Vname)==0)
			m_namecomb.SetCurSel(i);
	}

	m_bitcomb.SetCurSel(m_maininfo.mainbit[m_num].Bit_No);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void TopBitSet::OnOK() 
{
	// TODO: Add extra validation here
	int i=m_namecomb.GetCurSel();
	int j=m_bitcomb.GetCurSel();
	CString str;
	if(i>=0)
	{
		//DialogBarBit *pParent=(DialogBarBit*)GetParent();
		CMainFrame *pMainFram = (CMainFrame *)AfxGetApp()->m_pMainWnd;

		strcpy(m_maininfo.mainbit[m_num].Bit_Vname,m_para_info[i].itemName);
		if(j<0)j=0;
		m_maininfo.mainbit[m_num].Bit_No=j;
		m_maininfo.mainbit[m_num].ValInfo=&m_para_info[i];

		m_maininfo.mainbit[m_num].pvalbitinfo=pMainFram->GetValBitInfo(m_maininfo.mainbit[m_num].Bit_Vname);
	}
	CDialog::DestroyWindow();
	//CDialog::OnOK();
}

BOOL TopBitSet::Create(int num,CWnd* pParentWnd, UINT nID) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_num=num;
	return CDialog::Create(IDD, pParentWnd);
}
