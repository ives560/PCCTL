// BitSet.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "BitSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int m_para_tot_num;
extern PARAINI_INFO m_para_info[MAX_PARA_INI_NUM];
extern int m_ValNum;
extern ParaValInfo m_ValInfo[MAX_VAL_NUM];
extern bool ChangeTable;
/////////////////////////////////////////////////////////////////////////////
// BitSet dialog


//BitSet::BitSet(CString tabname,int j,ItemInfo *iteminfo,CWnd* pParent /*=NULL*/)
BitSet::BitSet(CSatConBitShowView *pBitView,int j,ItemInfo *iteminfo,CWnd* pParent /*=NULL*/)
: CDialog(BitSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(BitSet)
	m_BitCom = _T("");
	m_Display1 = _T("");
	m_Display0 = _T("");
	m_TabName = _T("");
	m_itemnum = _T("");
	//}}AFX_DATA_INIT
	m_pBitView=pBitView;
	m_itemnum.Format("%d",j);
	m_TabName=m_pBitView->m_pBitDoc->m_BitTabInfo[m_pBitView->m_curSelPage].tabName;
	m_pSetiteminfo=iteminfo;
	m_pcurvalinfo=m_pSetiteminfo->pvalbitinfo;//获得变量信息
}


void BitSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BitSet)
	DDX_Control(pDX, IDC_BITNO_COMBO, m_BitNo);
	DDX_Control(pDX, IDC_VARNAME_COMBO, m_VarName);
	DDX_Text(pDX, IDC_BITCOM_EDIT, m_BitCom);
	DDX_Text(pDX, IDC_DISPLAY1_EDIT, m_Display1);
	DDX_Text(pDX, IDC_DISPLAY0_EDIT, m_Display0);
	DDX_Text(pDX, IDC_TABNAME_EDIT, m_TabName);
	DDX_Text(pDX, IDC_ITEMNUM_STATIC, m_itemnum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BitSet, CDialog)
	//{{AFX_MSG_MAP(BitSet)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SELCOLOR0_STATIC, OnSelcolor0Static)
	ON_CBN_SELCHANGE(IDC_VARNAME_COMBO, OnSelchangeVarnameCombo)
	ON_BN_CLICKED(IDC_SELCOLOR1_STATIC, OnSelcolor1Static)
	ON_CBN_SELCHANGE(IDC_BITNO_COMBO, OnSelchangeBitnoCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BitSet message handlers

BOOL BitSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//////////////////////////////////////////////////////////////////////////
//	GetDlgItem(IDC_SETBIT_STATIC)->SetWindowText(ItemInfo->);

	m_pMainFram = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	for(int i=0;i<=m_para_tot_num;i++)
	{
		m_VarName.InsertString(i,m_para_info[i].itemName);//插入变量名
		if(strcmp(m_para_info[i].itemName,m_pSetiteminfo->ValName)==0)
			m_VarName.SetCurSel(i);
	}
	m_BitNo.SetCurSel(m_pSetiteminfo->BitNo);
/////////////////////////////////////////////////////////////////////////////////////
	UpdateBitSet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH BitSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_SELCOLOR0_STATIC)
	{
		pDC->SetBkColor(m_Sel0Color);
	}
	else if(pWnd->GetDlgCtrlID()==IDC_SELCOLOR1_STATIC)
	{
		pDC->SetBkColor(m_Sel1Color);
	}
	else if(pWnd->GetDlgCtrlID()==IDC_SETBIT_STATIC)
		pDC->SetTextColor(RGB(255,0,0));
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

COLORREF BitSet::StrToRgb(CString str)
{
	COLORREF color=atol(str);
	if(color==0)
		color=RGB(180,180,180);
	return color;
}

CString BitSet::RgbToStr(COLORREF color)
{
	CString str="";
	str.Format("%d",color);
	return str;
}

void BitSet::OnSelcolor0Static() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg(m_Sel0Color);
	if(dlg.DoModal()==IDOK)
	{
		m_Sel0Color=dlg.GetColor();
		Invalidate();
	}
}
void BitSet::OnSelcolor1Static() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg(m_Sel1Color);
	if(dlg.DoModal()==IDOK)
	{
		m_Sel1Color=dlg.GetColor();
		Invalidate();
	}
}

void BitSet::OnSelchangeVarnameCombo() //挑选变量
{
	// TODO: Add your control notification handler code here
	int i=m_VarName.GetCurSel();
	m_pcurvalinfo=m_pMainFram->GetValBitInfo(m_para_info[i].itemName);
	UpdateBitSet();
}

void BitSet::OnSelchangeBitnoCombo() //挑选位
{
	// TODO: Add your control notification handler code here
	UpdateBitSet();
}
void BitSet::OnOK() 
{
	// TODO: Add extra validation here
	CString str;
	int i=m_VarName.GetCurSel();
	if(i<0)
	{
		CDialog::OnOK();
		return;
	}
	UpdateData(TRUE);
	int bit=m_BitNo.GetCurSel();
	if(m_pcurvalinfo==0)	//无对应变量信息，增加新信息
	{
		m_ValNum++;
		m_pcurvalinfo=&m_ValInfo[m_ValNum];
		GetDlgItem(IDC_VARNAME_COMBO)->GetWindowText(str);
		strcpy(m_pcurvalinfo->ValName,(LPSTR)(LPCTSTR)str);
	}

	strcpy(m_pcurvalinfo->bitinfo[bit].Comment,(LPSTR)(LPCTSTR)m_BitCom);//BitCom

	strcpy(m_pcurvalinfo->bitinfo[bit].Displ[0],(LPSTR)(LPCTSTR)m_Display0);//m_Display0

	strcpy(m_pcurvalinfo->bitinfo[bit].Displ[1],(LPSTR)(LPCTSTR)m_Display1);//m_Display1

	str=RgbToStr(m_Sel0Color);
	strcpy(m_pcurvalinfo->bitinfo[bit].Color[0],(LPSTR)(LPCTSTR)str);

	str=RgbToStr(m_Sel1Color);
	strcpy(m_pcurvalinfo->bitinfo[bit].Color[1],(LPSTR)(LPCTSTR)str);
/////////////////////////////////////////////////////////////////////存储item信息
	strcpy(m_pSetiteminfo->ValName,m_para_info[i].itemName);
	m_para_info[i].commable=true;		//串口可读
	ChangeTable=TRUE;
	m_pSetiteminfo->ValInfo=&m_para_info[i];
	m_pSetiteminfo->BitNo=bit;//位数
	m_pSetiteminfo->pvalbitinfo=m_pcurvalinfo;
	CDialog::OnOK();
}

void BitSet::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void BitSet::UpdateBitSet()
{

	if(m_pcurvalinfo!=0)
	{
		CString str;
		int i=m_BitNo.GetCurSel();
		m_BitCom=m_pcurvalinfo->bitinfo[i].Comment;
		m_Display0=m_pcurvalinfo->bitinfo[i].Displ[0];
		m_Display1=m_pcurvalinfo->bitinfo[i].Displ[1];
		m_Sel0Color=StrToRgb(m_pcurvalinfo->bitinfo[i].Color[0]);
		m_Sel1Color=StrToRgb(m_pcurvalinfo->bitinfo[i].Color[1]);
	}
	else
	{
		m_BitCom="";
		m_Display0="";
		m_Display1="";
		m_Sel0Color=RGB(180,180,180);
		m_Sel1Color=RGB(180,180,180);
	}
	Invalidate();
	UpdateData(FALSE);
}
