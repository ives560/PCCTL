// SatConReadDoc.cpp : implementation of the CSatConReadDoc class
//

#include "stdafx.h"
#include "SatCon.h"

#include "SatConReadDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CString path;
/////////////////////////////////////////////////////////////////////////////
// CSatConReadDoc

IMPLEMENT_DYNCREATE(CSatConReadDoc, CDocument)

BEGIN_MESSAGE_MAP(CSatConReadDoc, CDocument)
	//{{AFX_MSG_MAP(CSatConReadDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSatConReadDoc construction/destruction

CSatConReadDoc::CSatConReadDoc()
{
	// TODO: add one-time construction code here
	m_TabNum = 0;
	m_lastPage = 0;
	memset(m_ReadTabInfo, 0, TAB_MAX_NUM*sizeof(TabInfo));
	m_pMainFram = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	processReadIni();
}

CSatConReadDoc::~CSatConReadDoc()
{
	WritebackReadIni();
}

BOOL CSatConReadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	SetTitle("Reader");
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSatConReadDoc serialization

void CSatConReadDoc::Serialize(CArchive& ar)
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
// CSatConReadDoc diagnostics

#ifdef _DEBUG
void CSatConReadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSatConReadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSatConReadDoc commands
//过滤字串，去除无效字符
void CSatConReadDoc::filterStr(char *str)
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
#define READ_CHECK_STR(a)	((pTmp = strstr(lineBuff, a)) != NULL)	
#define READ_GET_VALUE(a)	(atoi(pTmp + strlen(a)))
#define READ_GET_STR(a,b)	strcpy(a, pTmp + strlen(b))
//从配置文件frmRead.ini中读取数据并填充结构体m_ReadTabInfo
void CSatConReadDoc::processReadIni()
{
	char lineBuff[256];
	char *pTmp;
	FILE *pf;
	int curTab = -1, curItem=0, flag = 0;
	
	pf = fopen(path+"\\files\\frmRead.ini", "r");
	if (!pf)
	{
		//create and init.
		pf = fopen(path+"\\files\\frmRead.ini", "w");
		fclose(pf);
		return;
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
		// read top/bottom/left/right
		if (READ_CHECK_STR("frmRead.Top="))
		{
			m_form_top = READ_GET_VALUE("frmRead.Top=");
		}
		if (READ_CHECK_STR("frmRead.Left="))
		{
			m_form_left = READ_GET_VALUE("frmRead.Left=");
		}
		if (READ_CHECK_STR("frmRead.Height="))
		{
			m_form_height = READ_GET_VALUE("frmRead.Height=");
		}
		if (READ_CHECK_STR("frmRead.Width="))
		{
			m_form_width = READ_GET_VALUE("frmRead.Width=");
		}
		
		// read last_tab/total_tabs
		else if (READ_CHECK_STR("LastTab="))	//((pTmp = strstr(lineBuff, "LastTab=")) != NULL)
		{
			m_lastPage = READ_GET_VALUE("LastTab=");
		}
		else if(READ_CHECK_STR("TotalTabs="))	//((pTmp = strstr(lineBuff, "TotalTabs=")) != NULL)
		{
			m_TabNum = READ_GET_VALUE("TotalTabs=");	//最小为1
		}
		// read item...
		else if (READ_CHECK_STR("[Tab"))
		{
			if (curTab >= 0)
			{
				m_ReadTabInfo[curTab].itemNum = curItem;
			}
			flag = 1;	//开启flag
			curTab++;
			curItem = 0;
			if (curTab >= TAB_MAX_NUM || curTab >= m_TabNum)
			{
				break;
			}
		}
		else if (READ_CHECK_STR("TabName="))
		{
			//strcpy(m_pageName[curTab], pTmp + strlen("TabName="));
			READ_GET_STR(m_ReadTabInfo[curTab].tabName, "TabName=");
		}
		else if (flag == 1 && READ_CHECK_STR("="))
		{			
			READ_GET_STR(m_ReadTabInfo[curTab].iteminfo[curItem].ValName, "=");	//获得变量名
			if(strlen(m_ReadTabInfo[curTab].iteminfo[curItem].ValName)>0)
			m_ReadTabInfo[curTab].iteminfo[curItem].ValInfo = m_pMainFram->GetVariableInfo(m_ReadTabInfo[curTab].iteminfo[curItem].ValName);//添加item变量信息
			curItem++;
		}

	}
	m_ReadTabInfo[curTab].itemNum = curItem;	//填充最后一条的数量最小为1
	fclose(pf);
	return;
}
//数据写回到配置文件中去
void CSatConReadDoc::WritebackReadIni()
{
	FILE *pf;
	int i, j;
	
	pf = fopen(path+"\\files\\frmRead.ini", "w");
	if (!pf)
	{
		AfxMessageBox("Write frmRead.ini failed!");
		return;
	}
	
	//  write FORM
	fprintf(pf, "[Form]\n");
	fprintf(pf, "frmRead.Top=%d\n", m_form_top);
	fprintf(pf, "frmRead.Left=%d\n", m_form_left);
	fprintf(pf, "frmRead.Height=%d\n", m_form_height);
	fprintf(pf, "frmRead.Width=%d\n", m_form_width);
	// write lastTab and totalTabs
	fprintf(pf, "LastTab=%d\n", m_lastPage);
	fprintf(pf, "TotalTabs=%d\n", m_TabNum);
	
	// write tab item...
	for (i = 0; i < m_TabNum; i++)
	{
		fprintf(pf, "\n[Tab %d]\n", i+1);
		fprintf(pf, "TabName=%s\n", m_ReadTabInfo[i].tabName);
		
		for (j = 0; j <m_ReadTabInfo[i].itemNum; j++)
		{
			fprintf(pf, "%d=%s\n", j, m_ReadTabInfo[i].iteminfo[j].ValName);
		}	
	}
	
	fclose(pf);
	return;
}
void CSatConReadDoc::DeleteReadItem(int pageId, int itemId)
{
	if (pageId < 0 || pageId >= m_TabNum)
		return;

	for(int i=itemId;i<m_ReadTabInfo[pageId].itemNum;i++)
	{
		memcpy(&m_ReadTabInfo[pageId].iteminfo[i],&m_ReadTabInfo[pageId].iteminfo[i+1],sizeof(ItemInfo));
	}
	m_ReadTabInfo[pageId].itemNum--;
}

void CSatConReadDoc::DeleteReadPage(int pageId)
{
	if (pageId < 0 || pageId >= m_TabNum)
		return;
	for(int i=pageId;i<m_TabNum;i++)
	{
		memcpy(&m_ReadTabInfo[i],&m_ReadTabInfo[i+1],sizeof(TabInfo));
	}
	m_TabNum--;
}
