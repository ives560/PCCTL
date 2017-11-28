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
       m_pConnection.CreateInstance("ADODB.Connection");  //创建连接对象实例
	   CString con;
	   con.Format("DRIVER={Microsoft Access Driver (*.mdb)};uid=;pwd=;DBQ=%s;",path);
	   _bstr_t strConnect=con;
	   m_pConnection->Open(strConnect,"","",adModeUnknown); //打开数据库
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
	ASSERT(!tableName.IsEmpty());										//SQL语句不能为空
	try
	{
		CString str;
		str.Format("select * from %s",tableName);
		m_pRecordset.CreateInstance(__uuidof(Recordset)); //创建记录集对象实例
		m_pRecordset->Open(_bstr_t(str), m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockOptimistic, adCmdText); 	//执行SQL得到记录集
	}
	catch(_com_error e)											//捕获可能的异常
	{
		AfxMessageBox(e.Description());
	}
	return m_pRecordset;
}

void ADO::CloseRecordset()
{
	if(m_pRecordset->GetState() == adStateOpen)	//判断当前的记录集状态
		m_pRecordset->Close();					//关闭记录集
}

void ADO::CloseConn()
{
	m_pConnection->Close();									//关闭数据库连接
	::CoUninitialize();										//释放COM环境
}

UINT ADO::GetRecordCount(_RecordsetPtr pRecordset)
{
	int nCount = 0;											//声明保存记录数的变量
	try{
		pRecordset->MoveFirst();								//将记录集指针移动到第一条记录
	}
	catch(...)												//捕捉可能出现的错误
	{
		return 0;											//产生错误时返回0
	}
	if(pRecordset->adoEOF)									//判断记录集中是否没有记录
		return 0;											//无记录时返回0
	while (!pRecordset->adoEOF)								//当记录集指针没有指向最后时
	{
		pRecordset->MoveNext();								//将记录集指针移动到下一条记录
		nCount = nCount + 1;								//记录个数的变量加1
	}
	pRecordset->MoveFirst();									//将记录集指针移动到第一条记录
	return nCount;											//返回记录数
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
//获得程序当前路径
CString ADO::GetAppPath()
{
	/*TCHAR   exeFullName[MAX_PATH]; 
	::GetModuleFileName(NULL,exeFullName,MAX_PATH); 
	CString   mPath=exeFullName; 
	
	int   mPos=mPath.ReverseFind( '\\ ');   
	
	if(mPos==-1)return   " "; //没有发现 
	
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
		//AfxMessageBox(e.Description()); //弹出错误处理
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
		AfxMessageBox(e.Description()); //弹出错误处理
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
		AfxMessageBox(e.Description()); //弹出错误处理
	}
}

bool ADO::NewDataTable(CString tableName)
{
	CString sql;
	sql.Format("CREATE TABLE %s (时间 TEXT PRIMARY KEY,值 double,最大值 double,单位 TEXT)",tableName);
	if(NewTableConnection(sql)==true)
		return true;
	else
		return false;
}

bool ADO::NewNameTable(CString tableName)
{
	CString sql;
	sql.Format("CREATE TABLE %s (名字 TEXT PRIMARY KEY)",tableName);
	if(NewTableConnection(sql)==true)
		return true;
	else
		return false;
}

void ADO::AddRowNameTable(CString row)
{
	try
	{
		m_pRecordset = OpenRecordset("表名");
		m_pRecordset->AddNew(); //添加新行
		m_pRecordset->PutCollect("名字",(_bstr_t)row);
		m_pRecordset->Update(); //更新数据表记录
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
			pchart->YMax=(int)(double)m_pRecordset->GetCollect("最大值");
			pchart->Yaxis=pchart->YMax/5;
			pchart->YaxisStr=(char*)(_bstr_t)m_pRecordset->GetCollect("单位");
		}
		CString str=(char*)(_bstr_t)m_pRecordset->GetCollect("时间");
		CTime time=pchart->StrToTime(str);
		double var=(double)m_pRecordset->GetCollect("值");
		pchart->GetPoints(time,var);
		m_pRecordset->MoveNext();//将记录集指针移动到下一条记录
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
				m_pRecordset->AddNew(); //添加新行
				m_pRecordset->PutCollect("时间",(_bstr_t)tstr);
				m_pRecordset->PutCollect("值",d);
				if(i==0)
				{
					if(pchart->m_pinfo!=NULL)
					{
						m_pRecordset->PutCollect("最大值",pchart->m_pinfo->max);
						m_pRecordset->PutCollect("单位",(_bstr_t)pchart->m_pinfo->unit);
					}
				}
			}
			m_pRecordset->Update(); //更新数据表记录
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //弹出错误处理
	}
	CloseRecordset();
}
