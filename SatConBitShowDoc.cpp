// SatConBitShowDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "SatConBitShowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CString path;
/////////////////////////////////////////////////////////////////////////////
// CSatConBitShowDoc

IMPLEMENT_DYNCREATE(CSatConBitShowDoc, CDocument)

CSatConBitShowDoc::CSatConBitShowDoc()
{
	memset(m_BitTabInfo, 0, TAB_MAX_NUM*sizeof(TabInfo));
	m_pMainFram = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	ProcessFrmBitIni();
}

BOOL CSatConBitShowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
		SetTitle("BitShow");
	return TRUE;
}

CSatConBitShowDoc::~CSatConBitShowDoc()
{

	WritebackFrmBitIni();
}


BEGIN_MESSAGE_MAP(CSatConBitShowDoc, CDocument)
	//{{AFX_MSG_MAP(CSatConBitShowDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSatConBitShowDoc diagnostics

#ifdef _DEBUG
void CSatConBitShowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSatConBitShowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSatConBitShowDoc serialization

void CSatConBitShowDoc::Serialize(CArchive& ar)
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
// CSatConBitShowDoc commands
void CSatConBitShowDoc::BitShowFilterStr(char *str)
{
	int i, j, len;
	len = strlen(str);
	
	for (i = 0, j = 0; i < len; i++)
	{
		if (str[i] == 0x0D || str[i] == 0x0A||str[i] == ']')
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
//从配置文件中读取数据并填充结构体
void CSatConBitShowDoc::ProcessFrmBitIni()
{
	char lineBuff[256];
	char *pTmp;
	FILE *pf;
	int curTab = -1, curItem=0,totlcurItem=0, flag = 0;
	
	pf = fopen(path+"\\files\\frmBit.ini", "r");
	if (!pf)
	{
		//create and init.
		pf = fopen(path+"\\files\\frmBit.ini", "w");
		fclose(pf);
		return;
	}
	
	while(!feof(pf))
	{
		memset(lineBuff, 0, 256*sizeof(char));
		fgets(lineBuff, 256, pf);
		BitShowFilterStr(lineBuff);
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
				m_BitTabInfo[curTab].itemNum = totlcurItem;
			}
			flag = 1;	//开启flag
			curTab++;
			curItem = 0;
			totlcurItem=0;
			if (curTab >= TAB_MAX_NUM || curTab >= m_TabNum)
			{
				break;
			}
		}
		else if (READ_CHECK_STR("TabName="))
        {
            READ_GET_STR(m_BitTabInfo[curTab].tabName, "TabName=");
        }
		else if ((READ_CHECK_STR("=")) && flag == 1)
		{
			//strcpy(m_pageName[curTab], pTmp + strlen("TabName="));
            pTmp = strstr(lineBuff, "_");
            *pTmp = 0;
            curItem = atoi(lineBuff);
            *pTmp = '_';
			
            if (READ_CHECK_STR("Vname="))
            {
				totlcurItem++;
                READ_GET_STR(m_BitTabInfo[curTab].iteminfo[curItem].ValName, "Vname=");
				if(strlen(m_BitTabInfo[curTab].iteminfo[curItem].ValName)>0)
				m_BitTabInfo[curTab].iteminfo[curItem].ValInfo=m_pMainFram->GetVariableInfo(m_BitTabInfo[curTab].iteminfo[curItem].ValName);
				if(strlen(m_BitTabInfo[curTab].iteminfo[curItem].ValName)>0)
				m_BitTabInfo[curTab].iteminfo[curItem].pvalbitinfo=m_pMainFram->GetValBitInfo(m_BitTabInfo[curTab].iteminfo[curItem].ValName);
            }
            else if (READ_CHECK_STR("BitNo="))
            {
				m_BitTabInfo[curTab].iteminfo[curItem].BitNo=READ_GET_VALUE("BitNo=");
				//READ_GET_STR(m_itemInfo[curTab][curItem].BitNo, "BitNo=");
            }
			if(curItem>totlcurItem)		//有跳跃设置
				totlcurItem=curItem;
		}

	}
	//m_TabNum = curTab;	//创建Tab的个数
	
	m_BitTabInfo[curTab].itemNum = totlcurItem;	//填充最后一条的数量最小为1
	fclose(pf);
	return;
}
//数据写回到配置文件frmBit.ini中去
void CSatConBitShowDoc::WritebackFrmBitIni()
{
	FILE *pf;
	int i, j;
	
	pf = fopen(path+"\\files\\frmBit.ini", "w");
	if (!pf)
	{
		AfxMessageBox("Write frmBit.ini failed!");
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
	for (i = 0; i <m_TabNum; i++)
	{
		fprintf(pf, "\n[Tab %d]\n", i+1);
		fprintf(pf, "TabName=%s\n", m_BitTabInfo[i].tabName);
		
		for (j = 0; j <m_BitTabInfo[i].itemNum; j++)
		{
			fprintf(pf, "%d_Vname=%s\n", j, m_BitTabInfo[i].iteminfo[j].ValName);//变量名
			fprintf(pf, "%d_BitNo=%d\n", j, m_BitTabInfo[i].iteminfo[j].BitNo);//变量位
		}	
	}
	
	fclose(pf);
	return;
}

void CSatConBitShowDoc::DeleteBitItem(int pageId, int itemId)
{
	if (pageId < 0 || pageId >= m_TabNum)
		return;
	
	for(int i=itemId;i<m_BitTabInfo[pageId].itemNum;i++)
	{
		memcpy(&m_BitTabInfo[pageId].iteminfo[i],&m_BitTabInfo[pageId].iteminfo[i+1],sizeof(ItemInfo));
	}
	m_BitTabInfo[pageId].itemNum--;
}

void CSatConBitShowDoc::DeleteBitPage(int pageId)
{
	if (pageId < 0 || pageId >= m_TabNum)
		return;
	for(int i=pageId;i<m_TabNum;i++)
	{
		memcpy(&m_BitTabInfo[i],&m_BitTabInfo[i+1],sizeof(TabInfo));
	}
	m_TabNum--;
}
