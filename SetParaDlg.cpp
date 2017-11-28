// SetParaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "SetParaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int OpLevel;
/////////////////////////////////////////////////////////////////////////////
// SetParaDlg dialog


SetParaDlg::SetParaDlg(PARAINI_INFO *paraini,int* totnum,CWnd* pParent /*=NULL*/)
	: CDialog(SetParaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetParaDlg)
	m_adderss = _T("");
	m_binary = _T("");
	m_comment = _T("");
	m_decadal = _T("");
	m_format = _T("");
	m_max = _T("");
	m_min = _T("");
	m_step = _T("");
	m_unit = _T("");
	m_value = _T("");
	m_readable = FALSE;
	m_writeable = FALSE;
	m_readcont = FALSE;
	//}}AFX_DATA_INIT
	m_paratotnum=totnum;
	m_pparaini=paraini;
	m_CurrSel=-1;
}


void SetParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetParaDlg)
	DDX_Control(pDX, IDC_NAME_COMBO, m_namebox);
	DDX_Text(pDX, IDC_ADDERSS_EDIT, m_adderss);
	DDX_Text(pDX, IDC_BINARY_EDIT, m_binary);
	DDX_Text(pDX, IDC_COMMENT_EDIT, m_comment);
	DDX_Text(pDX, IDC_DECADAL_EDIT, m_decadal);
	DDX_Text(pDX, IDC_FORMAT_EDIT, m_format);
	DDX_Text(pDX, IDC_MAX_EDIT, m_max);
	DDX_Text(pDX, IDC_MIN_EDIT, m_min);
	DDX_Text(pDX, IDC_STEP_EDIT, m_step);
	DDX_Text(pDX, IDC_UNIT_EDIT, m_unit);
	DDX_Text(pDX, IDC_VALUE_EDIT, m_value);
	DDX_Check(pDX, IDC_RABLE_CHECK, m_readable);
	DDX_Check(pDX, IDC_WABLE_CHECK, m_writeable);
	DDX_Check(pDX, IDC_RCONT_CHECK, m_readcont);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetParaDlg, CDialog)
	//{{AFX_MSG_MAP(SetParaDlg)
	ON_CBN_SELCHANGE(IDC_NAME_COMBO, OnSelchangeNameCombo)
	ON_CBN_EDITCHANGE(IDC_NAME_COMBO, OnEditchangeNameCombo)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, OnSaveButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetParaDlg message handlers
BOOL SetParaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str=" ";
	for(int i=0;i<=*m_paratotnum;i++)
	{
		str=m_pparaini[i].itemName;
		m_namebox.InsertString(i,str);
	}
	if(OpLevel!=2)
		GetDlgItem(IDC_SAVE_BUTTON)->EnableWindow(FALSE); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void SetParaDlg::OnSaveButton() //Save
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char *pStr=NULL;
	bool updataflg=false;
	CString str;
	int i=m_CurrSel;
	m_namebox.GetWindowText(str); //当前变量名
	if(i==-1)
	{
		updataflg=true;
		if(str.GetLength()<=0)	//无变量名
			return;
		for(int j=0;j<=(*m_paratotnum);j++) //变量名重复
		{
			if(strcmp(m_pparaini[j].itemName,str)==0)
			{
				i=j;
				break;
			}			
		}
		if(i==-1)		//变量名未重复
		{
			(*m_paratotnum)++;
			i=*m_paratotnum;
			strcpy(m_pparaini[i].itemName,(LPSTR)(LPCTSTR)str);
			m_namebox.InsertString(i,str);
		}
		//m_namebox.SetWindowText("");
	}
	memset(&m_pparaini[i],0,sizeof(PARAINI_INFO));//数据清零
	strcpy(m_pparaini[i].itemName,(LPSTR)(LPCTSTR)str);//重写变量名
	if(m_unit.GetLength())
	{
		m_pparaini[i].itemBmFlag |=SIGN_UNIT;
		strcpy(m_pparaini[i].unit,(LPSTR)(LPCTSTR)m_unit);//unit
		//m_unit="";
	}
	if(m_comment.GetLength())
	{
		m_pparaini[i].itemBmFlag |=SIGN_COMT;
		strcpy(m_pparaini[i].comt,(LPSTR)(LPCTSTR)m_comment);//comment
		//m_comment="";
	}
	if(m_format.GetLength())
	{
		m_pparaini[i].itemBmFlag |=SIGN_VFORMAT;
		strcpy(m_pparaini[i].vformat,(LPSTR)(LPCTSTR)m_format);//format
		//m_format="";
	}
	if(m_adderss.GetLength())
	{
		m_pparaini[i].itemBmFlag |=SIGN_ADDR;  //地址 未修改
		m_pparaini[i].address=atoi(m_adderss);
		//m_adderss="";
	}
	if(m_value.GetLength())
	{
		m_pparaini[i].itemBmFlag |=SIGN_VALUE;
		//m_pparaini[i].value=atof(m_value);		//value		float
		strcpy(m_pparaini[i].cvalue,(LPSTR)(LPCTSTR)m_value);
		//m_value="";
	}
	if(m_binary.GetLength())
	{
		m_pparaini[i].itemBmFlag |=SIGN_BINSCALE;
		m_pparaini[i].binscale=atof(m_binary);	//binary	float
		strcpy(m_pparaini[i].cbinscale,(LPSTR)(LPCTSTR)m_binary);
		//m_binary="";
	}
	if(m_decadal.GetLength())
	{
		m_pparaini[i].itemBmFlag |=SIGN_DESCALE;
		m_pparaini[i].decscale=atof(m_decadal);	//decadal	float
		strcpy(m_pparaini[i].cdecscale,(LPSTR)(LPCTSTR)m_decadal);		
		//m_decadal="";
	}
	if(m_max.GetLength())
	{
		m_pparaini[i].itemBmFlag |=SIGN_MAX;
		m_pparaini[i].max=atof(m_max);			//max	float
		strcpy(m_pparaini[i].cmax,(LPSTR)(LPCTSTR)m_max);
		//m_max="";
	}
	if(m_min.GetLength())
	{
		m_pparaini[i].itemBmFlag |=SIGN_MIN;
		m_pparaini[i].min=atof(m_min);			//min	float
		strcpy(m_pparaini[i].cmin,(LPSTR)(LPCTSTR)m_min);
		//m_min="";
	}
	if(m_step.GetLength())
	{
		m_pparaini[i].itemBmFlag |=SIGN_STEP;
		m_pparaini[i].step=atof(m_step);			//step	float
		strcpy(m_pparaini[i].cstep,(LPSTR)(LPCTSTR)m_step);
		//m_step="";
	}
	m_pparaini[i].itemBmFlag |=SIGN_READABLE;
	m_pparaini[i].readable=m_readable;
	//m_readable=FALSE;
	m_pparaini[i].itemBmFlag |=SIGN_WRITEABLE;
	m_pparaini[i].writeable=m_writeable;
	//m_writeable=FALSE;
	m_pparaini[i].itemBmFlag |=SIGN_READCTN;
	m_pparaini[i].RdContinue=m_readcont;
	//m_readcont=FALSE;
	if(updataflg)
		UpdateData(FALSE);
}

void SetParaDlg::OnOK()
{
	// TODO: Add extra validation here

//	CDialog::OnOK();
}

void SetParaDlg::OnSelchangeNameCombo() 
{
	// TODO: Add your control notification handler code here
	m_CurrSel=m_namebox.GetCurSel();
	int i=m_CurrSel;
	m_value=m_pparaini[i].cvalue;
	m_unit = m_pparaini[i].unit;
	m_comment = m_pparaini[i].comt;
	m_format =m_pparaini[i].vformat;
	m_adderss.Format("%d",m_pparaini[i].address);  //地址未修改
	m_binary=m_pparaini[i].cbinscale;
	m_decadal=m_pparaini[i].cdecscale;
	m_max=m_pparaini[i].cmax;
	m_min=m_pparaini[i].cmin;
	m_step=m_pparaini[i].cstep;
	m_readable=m_pparaini[i].readable;
	m_writeable=m_pparaini[i].writeable;
	m_readcont=m_pparaini[i].RdContinue;
	UpdateData(FALSE);
}

void SetParaDlg::OnEditchangeNameCombo() 
{
	// TODO: Add your control notification handler code here
	CString name;
	m_namebox.GetWindowText(name);
	if(m_namebox.GetCurSel()!=CB_ERR)//有选择清除选择
	{
		m_CurrSel=-1;
		m_namebox.SetCurSel(-1);
		m_unit="";
		m_comment="";
		m_format="";
		m_adderss="";
		m_value="";
		m_binary="";
		m_decadal="";
		m_max="";
		m_min="";
		m_step="";
		m_readable=FALSE;
		m_writeable=FALSE;
		m_readcont=FALSE;
		UpdateData(FALSE);
	}
	m_namebox.ShowDropDown(TRUE);
	::SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW)));
	m_namebox.SetWindowText(name);
	int len=name.GetLength();
	m_namebox.SetEditSel(len,-1);
/*	if(m_namebox.SelectString(-1,name)==CB_ERR)
		m_namebox.SetWindowText(name);
	int len=name.GetLength();
	m_namebox.SetEditSel(len,-1);*/


	return;
}

BOOL SetParaDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_KEYDOWN)		
	{
		UINT nKey = (int) pMsg->wParam;
			  
		if( VK_RETURN == nKey || VK_ESCAPE == nKey )
		{
			CString name;
			m_namebox.GetWindowText(name);
			m_namebox.ShowDropDown(FALSE);
			m_namebox.SetWindowText(name);
			int len=name.GetLength();
			m_namebox.SetEditSel(len,-1);
			int i=m_namebox.FindStringExact(-1,name);
			if(i!=CB_ERR)
			{
				m_CurrSel=i;
				m_namebox.SetCurSel(i);
				OnSelchangeNameCombo();
			}
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
