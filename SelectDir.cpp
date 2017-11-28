// SelectDir.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "SelectDir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int OpLevel;
extern CString path;
extern CString project_dir[11];
extern int projectsum;
/////////////////////////////////////////////////////////////////////////////
// CSelectDir dialog


CSelectDir::CSelectDir(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDir::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectDir)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	projectsum=0;
}


void CSelectDir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectDir)
	DDX_Control(pDX, IDC_DIRECTORY_COMBO, m_Directory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectDir, CDialog)
	//{{AFX_MSG_MAP(CSelectDir)
	ON_BN_CLICKED(IDC_BROWSE_BUTTON, OnBrowseButton)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDir message handlers

BOOL CSelectDir::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ReadMainIni();
	for(int i=0;i<projectsum;i++)
		m_Directory.InsertString(i,project_dir[i]);
	m_Directory.SetCurSel(0);
//////////////////////////////////////////////////////���ñ���
	CWnd *pEdit = GetDlgItem(IDC_TITLE_STATIC);   
	CFont *pfont = pEdit->GetFont();   
	LOGFONT logfont;   
	pfont->GetLogFont(&logfont);   
	logfont.lfHeight = -35;   
	m_font.CreateFontIndirect(&logfont);   
	pEdit->SetFont(&m_font);   

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CSelectDir::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_ERROR_STATIC)
	{
		pDC->SetTextColor(RGB(255,0,0));
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSelectDir::OnOK() 
{
	// TODO: Add extra validation here
    FILE *pf=NULL; CString str,exchange;
	m_Directory.GetWindowText(str);
    pf = fopen((str+"\\files\\para.ini"), "r");
    if (!pf)		//·���Ƿ���Ч
    {
		GetDlgItem(IDC_ERROR_STATIC)->SetWindowText("This project does not exist! Please select again.");
		return;
    }
	path=str;		//���ù���·��
	if(project_dir[0]==str) //·��ΪĬ��·��
	{
		CDialog::OnOK();
		return;
	}
	int i,j=projectsum;

	for(i=0;i<projectsum;i++)	//·����ΪĬ��·������ΪĬ��·��
	{
		if(project_dir[i]==str)
			j=i;
	}
	for(;j>0;j--)  //·���б�����
		project_dir[j]=project_dir[j-1];
	project_dir[0]=str;
	CDialog::OnOK();
}

void CSelectDir::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

int CALLBACK BrowseCallBackFun(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)  
{  
    switch(uMsg)  
    {  
    case BFFM_INITIALIZED:  //ѡ���ļ��жԻ����ʼ�� 
		{
        //����Ĭ��·��ΪlpData   
        ::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		TCHAR pszPath[MAX_PATH];
		//��ȡ��ǰѡ��·��   
		SHGetPathFromIDList((LPCITEMIDLIST)lParam, pszPath);  
		//��STATUSTEXT������ʾ��ǰ·��   
        ::SendMessage(hwnd, BFFM_SETSTATUSTEXT, TRUE, (LPARAM)pszPath);
        //��STATUSTEXT������ʾ��ǰ·��   
        //::SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, lpData);  
        //����ѡ���ļ��жԻ���ı���   
        //::SetWindowText(hwnd, TEXT("�������ø�����Ŀ¼"));   
        }break;  
    case BFFM_SELCHANGED:   //ѡ���ļ��б��ʱ   
        {  
            TCHAR pszPath[MAX_PATH];  
            //��ȡ��ǰѡ��·��   
            SHGetPathFromIDList((LPCITEMIDLIST)lParam, pszPath);  
            //��STATUSTEXT������ʾ��ǰ·��   
            ::SendMessage(hwnd, BFFM_SETSTATUSTEXT, TRUE, (LPARAM)pszPath);  
        }break;  
    }  
    return 0;  
}

void CSelectDir::OnBrowseButton() 
{
	// TODO: Add your control notification handler code here
	char str[100];
	strcpy(str,(LPSTR)(LPCTSTR)project_dir[0]);
	TCHAR pszPath[MAX_PATH];  
    BROWSEINFO bi;   
    bi.hwndOwner      = this->GetSafeHwnd();  
    bi.pidlRoot       = NULL;  
    bi.pszDisplayName = NULL;   
    bi.lpszTitle      = TEXT("Select A Directory");   
    bi.ulFlags        = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;  
    bi.lpfn           = BrowseCallBackFun;     //�ص�����   
    bi.lParam         = (LPARAM)TEXT(str);  //�����ص������Ĳ���,����Ĭ��·��  
    bi.iImage         = 0;   
	
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);  
    if (pidl == NULL)  
    {  
        return;  
    }  
	
    if (SHGetPathFromIDList(pidl, pszPath))  
    {  
        //AfxMessageBox(pszPath); 
		GetDlgItem(IDC_DIRECTORY_COMBO)->SetWindowText(pszPath);
    } 
}
//�����ִ���ȥ����Ч�ַ�
void CSelectDir::filterStr(char *str)
{
    int i, j, len;
    len = strlen(str);
    
    for (i = 0, j = 0; i < len; i++)
    {
        if (str[i] == 0x0D || str[i] == 0x0A)
        {
            //str[j++] = 0;
            break;
        }
        //else if (str[i] == 0x20)
        //{
        //}
        else
        {
            str[j++] = str[i];
        }
    }
    str[j++] = 0;
    return;
}
#define PARA_CHECK_STR(a)	((pTmp = strstr(lineBuff, a)) != NULL)	
#define PARA_GET_INT(a,b)	(a = atoi(pTmp + strlen(b)))
#define PARA_GET_STR(a,b)	(a = (pTmp + strlen(b)))
void CSelectDir::ReadMainIni()
{
	char lineBuff[256]; char charstr[20];
    char *pTmp; int curItem;
    FILE *pf=NULL;
	projectsum=1;
    pf = fopen("main.ini", "r");
    if (!pf)
    {
        //create and init.
        pf = fopen("main.ini", "w");
        fclose(pf);
        return ;
    }
	while(!feof(pf))
    {
		memset(lineBuff, 0, 256*sizeof(char));
        fgets(lineBuff, 256, pf);
        filterStr(lineBuff);
        if (strlen(lineBuff) == 0)
        {
            continue;
        }
        
        // read item...
		if(PARA_CHECK_STR("OpLevel="))
		{
			PARA_GET_INT(OpLevel,"OpLevel=");
		}
        else if (PARA_CHECK_STR("project_dir"))
        {
			if(PARA_CHECK_STR("project_dir="))
			{
				PARA_GET_STR(project_dir[0],"project_dir=");
			}
			else if (PARA_CHECK_STR("="))
			{
				pTmp++;
				project_dir[projectsum]=pTmp;
				projectsum++;
			}
            //PARA_GET_INT(address, "address=");
        }
	}
fclose(pf);
}

void CSelectDir::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here	
}
