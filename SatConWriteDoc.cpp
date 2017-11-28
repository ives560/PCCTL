// SatConWriteDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "SatConWriteDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CString path;
extern 	int m_WriteTabNum;
extern 	TabInfo m_WriteTabInfo[TAB_MAX_NUM];
/////////////////////////////////////////////////////////////////////////////
// SatConWriteDoc

IMPLEMENT_DYNCREATE(SatConWriteDoc, CDocument)

SatConWriteDoc::SatConWriteDoc()
{
	m_WriteTabNum = 0;
	m_lastPage = 0;
	memset(m_WriteTabInfo, 0, TAB_MAX_NUM*sizeof(TabInfo));
	m_pMainFram = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	processWriteIni();
}

BOOL SatConWriteDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	SetTitle("Writer");
	return TRUE;
}

SatConWriteDoc::~SatConWriteDoc()
{
	WritebackWriteIni();
}


BEGIN_MESSAGE_MAP(SatConWriteDoc, CDocument)
	//{{AFX_MSG_MAP(SatConWriteDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SatConWriteDoc diagnostics

#ifdef _DEBUG
void SatConWriteDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void SatConWriteDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// SatConWriteDoc serialization

void SatConWriteDoc::Serialize(CArchive& ar)
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
// SatConWriteDoc commands
//过滤字串，去除无效字符
void SatConWriteDoc::filterStr(char *str)
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
//从配置文件frmWrite.ini中读取数据并填充结构体m_WriteTabInfo
void SatConWriteDoc::processWriteIni()
{
	char lineBuff[256];
	char *pTmp;
	FILE *pf;
	int curTab = -1, curItem=0, flag = 0;
	
	pf = fopen(path+"\\files\\frmWrite.ini", "r");
	if (!pf)
	{
		//create and init.
		pf = fopen(path+"\\files\\frmWrite.ini", "w");
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
		if (READ_CHECK_STR("frmWrite.Top="))
		{
			m_form_top = READ_GET_VALUE("frmWrite.Top=");
		}
		if (READ_CHECK_STR("frmWrite.Left="))
		{
			m_form_left = READ_GET_VALUE("frmWrite.Left=");
		}
		if (READ_CHECK_STR("frmWrite.Height="))
		{
			m_form_height = READ_GET_VALUE("frmWrite.Height=");
		}
		if (READ_CHECK_STR("frmWrite.Width="))
		{
			m_form_width = READ_GET_VALUE("frmWrite.Width=");
		}
		
		// read last_tab/total_tabs
		else if (READ_CHECK_STR("LastTab="))	//((pTmp = strstr(lineBuff, "LastTab=")) != NULL)
		{
			m_lastPage = READ_GET_VALUE("LastTab=");
		}
		else if(READ_CHECK_STR("TotalTabs="))	//((pTmp = strstr(lineBuff, "TotalTabs=")) != NULL)
		{
			m_WriteTabNum = READ_GET_VALUE("TotalTabs=");	//最小为1
		}
		// read item...
		else if (READ_CHECK_STR("[Tab"))
		{
			if (curTab >= 0)
			{
				m_WriteTabInfo[curTab].itemNum = curItem;
			}
			flag = 1;	//开启flag
			curTab++;
			curItem = 0;
			if (curTab >= TAB_MAX_NUM || curTab >= m_WriteTabNum)
			{
				break;
			}
		}
		else if (READ_CHECK_STR("TabName="))
		{
			//strcpy(m_pageName[curTab], pTmp + strlen("TabName="));
			READ_GET_STR(m_WriteTabInfo[curTab].tabName, "TabName=");
		}
		else if (flag == 1 && READ_CHECK_STR("="))
		{			
			READ_GET_STR(m_WriteTabInfo[curTab].iteminfo[curItem].ValName, "=");	//获得变量名
			if(strlen(m_WriteTabInfo[curTab].iteminfo[curItem].ValName)>0)
			m_WriteTabInfo[curTab].iteminfo[curItem].ValInfo = m_pMainFram->GetVariableInfo(m_WriteTabInfo[curTab].iteminfo[curItem].ValName);//添加item变量信息
			curItem++;
		}
		
	}
	m_WriteTabInfo[curTab].itemNum = curItem;	//填充最后一条的数量最小为1
	fclose(pf);
	return;
}
//数据写回到配置文件中去
void SatConWriteDoc::WritebackWriteIni()
{
	FILE *pf;
	int i, j;
	
	pf = fopen(path+"\\files\\frmWrite.ini", "w");
	if (!pf)
	{
		AfxMessageBox("Write frmWrite.ini failed!");
		return;
	}
	
	//  write FORM
	fprintf(pf, "[Form]\n");
	fprintf(pf, "frmWrite.Top=%d\n", m_form_top);
	fprintf(pf, "frmWrite.Left=%d\n", m_form_left);
	fprintf(pf, "frmWrite.Height=%d\n", m_form_height);
	fprintf(pf, "frmWrite.Width=%d\n", m_form_width);
	// write lastTab and totalTabs
	fprintf(pf, "LastTab=%d\n", m_lastPage);
	fprintf(pf, "TotalTabs=%d\n", m_WriteTabNum);
	
	// write tab item...
	for (i = 0; i < m_WriteTabNum; i++)
	{
		fprintf(pf, "\n[Tab %d]\n", i+1);
		fprintf(pf, "TabName=%s\n", m_WriteTabInfo[i].tabName);
		
		for (j = 0; j <m_WriteTabInfo[i].itemNum; j++)
		{
			fprintf(pf, "%d=%s\n", j, m_WriteTabInfo[i].iteminfo[j].ValName);
		}	
	}
	
	fclose(pf);
	return;
}
void SatConWriteDoc::DeleteWriteItem(int pageId, int itemId)
{
	if (pageId < 0 || pageId >= m_WriteTabNum)
		return;

	for(int i=itemId;i<m_WriteTabInfo[pageId].itemNum;i++)
	{
		memcpy(&m_WriteTabInfo[pageId].iteminfo[i],&m_WriteTabInfo[pageId].iteminfo[i+1],sizeof(ItemInfo));
	}
	m_WriteTabInfo[pageId].itemNum--;
}

void SatConWriteDoc::DeleteWritePage(int pageId)
{
	if (pageId < 0 || pageId >= m_WriteTabNum)
		return;
	for(int i=pageId;i<m_WriteTabNum;i++)
	{
		memcpy(&m_WriteTabInfo[i],&m_WriteTabInfo[i+1],sizeof(TabInfo));
	}
	m_WriteTabNum--;
}
