// ADO.cpp: implementation of the ADO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADO::ADO()
{

}

ADO::~ADO()
{

}

void ADO::OnInitADOConn(CString path)
{
	::CoInitialize(NULL);
	try
	{
       m_pConnection.CreateInstance("ADODB.Connection");  //�������Ӷ���ʵ��
	   CString con;
	   con.Format("DRIVER={Microsoft Access Driver (*.mdb)};uid=;pwd=;DBQ=%s;",path);
	   _bstr_t strConnect=con;
	   m_pConnection->Open(strConnect,"","",adModeUnknown); //�����ݿ�
	   /*----------------------------------------------*/
	   m_pCommand.CreateInstance(__uuidof(Command));
	   m_pCommand->ActiveConnection=m_pConnection;
	}
	catch(_com_error e)
	{
		// Notify the user of errors if any.     
		AfxMessageBox(e.ErrorMessage());
	}
}

_RecordsetPtr&  ADO::OpenRecordset(CString tableName)
{
	ASSERT(!tableName.IsEmpty());										//SQL��䲻��Ϊ��
	try
	{
		CString str;
		str.Format("select * from %s",tableName);
		m_pRecordset.CreateInstance(__uuidof(Recordset)); //������¼������ʵ��
		m_pRecordset->Open(_bstr_t(str), m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockOptimistic, adCmdText); 	//ִ��SQL�õ���¼��
	}
	catch(_com_error e)											//������ܵ��쳣
	{
		AfxMessageBox(e.Description());
	}
	return m_pRecordset;
}

void ADO::CloseRecordset()
{
	if(m_pRecordset->GetState() == adStateOpen)	//�жϵ�ǰ�ļ�¼��״̬
		m_pRecordset->Close();					//�رռ�¼��
}

void ADO::CloseConn()
{
	m_pConnection->Close();									//�ر����ݿ�����
	::CoUninitialize();										//�ͷ�COM����
}

UINT ADO::GetRecordCount(_RecordsetPtr pRecordset)
{
	int nCount = 0;											//���������¼���ı���
	try{
		pRecordset->MoveFirst();								//����¼��ָ���ƶ�����һ����¼
	}
	catch(...)												//��׽���ܳ��ֵĴ���
	{
		return 0;											//��������ʱ����0
	}
	if(pRecordset->adoEOF)									//�жϼ�¼�����Ƿ�û�м�¼
		return 0;											//�޼�¼ʱ����0
	while (!pRecordset->adoEOF)								//����¼��ָ��û��ָ�����ʱ
	{
		pRecordset->MoveNext();								//����¼��ָ���ƶ�����һ����¼
		nCount = nCount + 1;								//��¼�����ı�����1
	}
	pRecordset->MoveFirst();									//����¼��ָ���ƶ�����һ����¼
	return nCount;											//���ؼ�¼��
}

bool ADO::CreateBaseData(CString path)
{
	try
	{
		HRESULT hr = S_OK;
		hr = ::CoInitialize(NULL);
		if(SUCCEEDED(hr))
		{
		  HRESULT hr = S_OK;
		  // Define ADOX object pointers.
		  // Initialize pointers on define.
		  // These are in the ADOX::  namespace.
		  ADOX::_CatalogPtr m_pCatalog = NULL;
		  //Set ActiveConnection of Catalog to this string
		  CString str;
		  str.Format("Provider=Microsoft.JET.OLEDB.4.0;Data source=%s",path);
		  //str="Provider=Microsoft.JET.OLEDB.4.0;Data source=c:\\new.mdb";
		  _bstr_t strcnn(str);

		 m_pCatalog.CreateInstance(__uuidof(ADOX::Catalog));
		 m_pCatalog->Create(strcnn);

		}
	}   
	catch(_com_error &e)
	{
		// Notify the user of errors if any.     
		//AfxMessageBox(e.ErrorMessage());
		return false;
	}
	return true;
	
}
//��ó���ǰ·��
CString ADO::GetAppPath()
{
	/*TCHAR   exeFullName[MAX_PATH]; 
	::GetModuleFileName(NULL,exeFullName,MAX_PATH); 
	CString   mPath=exeFullName; 
	
	int   mPos=mPath.ReverseFind( '\\ ');   
	
	if(mPos==-1)return   " "; //û�з��� 
	
	mPath=mPath.Left(mPos); 
	
	if(mPath.Right(1)== "\\ ") 
	{ 
		mPath=mPath.Left(mPos-1); 
	} 
	
	return   mPath; */
	CString   str,path; 
	TCHAR   exeFullName[MAX_PATH]; 
	::GetModuleFileName(NULL,exeFullName,MAX_PATH); 
	path=exeFullName;
	//path=AfxGetApp()-> m_pszHelpFilePath; 
	str=AfxGetApp()-> m_pszExeName; 
	path=path.Left(path.GetLength()-str.GetLength()-5); 
	return path;
}

bool ADO::NewTableConnection(CString sql)
{
	try
	{
		_variant_t RecordsAffected;
		m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(...)
	{
		//AfxMessageBox(e.Description()); //����������
		return false;
	}
	return true;

}

void ADO::DeleteTableConnection(CString TableName)
{
	try
	{
		_variant_t RecordsAffected;
		CString sql;
		sql.Format("DROP TABLE %s",TableName);
		m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //����������
	}

}

bool ADO::SearchBaseData(CString path)
{
	CFileStatus   status; 
	if   (!CFile::GetStatus(path,status)) 
		return false;
	else
		return true;
}

void ADO::ClearTable(CString tableName)
{
	try
	{
		CString str;
		str.Format("DELETE * FROM %s",tableName);
		m_pCommand->CommandText=(class _bstr_t)str;
		
		m_pCommand->Execute(NULL,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //����������
	}
}

bool ADO::NewDataTable(CString tableName)
{
	CString sql;
	sql.Format("CREATE TABLE %s (ʱ�� TEXT PRIMARY KEY,ֵ double,���ֵ double,��λ TEXT)",tableName);
	if(NewTableConnection(sql)==true)
		return true;
	else
		return false;
}

bool ADO::NewNameTable(CString tableName)
{
	CString sql;
	sql.Format("CREATE TABLE %s (���� TEXT PRIMARY KEY)",tableName);
	if(NewTableConnection(sql)==true)
		return true;
	else
		return false;
}

void ADO::AddRowNameTable(CString row)
{
	try
	{
		m_pRecordset = OpenRecordset("����");
		m_pRecordset->AddNew(); //�������
		m_pRecordset->PutCollect("����",(_bstr_t)row);
		m_pRecordset->Update(); //�������ݱ��¼
		CloseRecordset();
	}
	catch(...)
	{
		
	}
}

void ADO::ReadTable(CString tableName, CChartControl* pchart)
{
	bool read=true;
	OpenRecordset(tableName);
	while(!m_pRecordset->adoEOF)
	{
		if(read==true)
		{
			read=false;
			pchart->YMax=(int)(double)m_pRecordset->GetCollect("���ֵ");
			pchart->Yaxis=pchart->YMax/5;
			pchart->YaxisStr=(char*)(_bstr_t)m_pRecordset->GetCollect("��λ");
		}
		CString str=(char*)(_bstr_t)m_pRecordset->GetCollect("ʱ��");
		CTime time=pchart->StrToTime(str);
		double var=(double)m_pRecordset->GetCollect("ֵ");
		pchart->GetPoints(time,var);
		m_pRecordset->MoveNext();//����¼��ָ���ƶ�����һ����¼
	}
	CloseRecordset();
}

void ADO::SaveTable(CString tableName, CChartControl* pchart)
{
	try
	{	
		ClearTable(tableName);
		OpenRecordset(tableName);
		POSITION posT=pchart->Tlist.GetHeadPosition();
		POSITION posD=pchart->Dlist.GetHeadPosition();
		CTime t;
		double d;
		CString tstr;
		int count=pchart->Tlist.GetCount();
		if(count>0)
		{
			for(int i=0;i<count;i++)
			{
				t=pchart->Tlist.GetNext(posT);
				tstr=pchart->TimeToStr(t);
				d=pchart->Dlist.GetNext(posD);
				m_pRecordset->AddNew(); //�������
				m_pRecordset->PutCollect("ʱ��",(_bstr_t)tstr);
				m_pRecordset->PutCollect("ֵ",d);
				if(i==0)
				{
					if(pchart->m_pinfo!=NULL)
					{
						m_pRecordset->PutCollect("���ֵ",pchart->m_pinfo->max);
						m_pRecordset->PutCollect("��λ",(_bstr_t)pchart->m_pinfo->unit);
					}
				}
			}
			m_pRecordset->Update(); //�������ݱ��¼
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //����������
	}
	CloseRecordset();
}
