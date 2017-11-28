// ADO.h: interface for the ADO class.
//access数据库类
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADO_H__E0F8432E_F797_4979_8FB0_EAC60CA6C7F9__INCLUDED_)
#define AFX_ADO_H__E0F8432E_F797_4979_8FB0_EAC60CA6C7F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChartControl.h"

class ADO  
{
public:
    _ConnectionPtr m_pConnection;					//连接对象指针
	_RecordsetPtr  m_pRecordset;					//记录集对象指针
	_CommandPtr	   m_pCommand;

public:
	void SaveTable(CString tableName,CChartControl* pchart);
	void ReadTable(CString tableName,CChartControl* pchart);
	void AddRowNameTable(CString row);
	bool NewNameTable(CString tableName);
	bool NewDataTable(CString tableName);
	void ClearTable(CString tableName);
	bool SearchBaseData(CString path);
	void DeleteTableConnection(CString TableName);
	bool NewTableConnection(CString sql);
	CString GetAppPath();
	bool CreateBaseData(CString path);
	ADO();
	virtual ~ADO();
	void OnInitADOConn(CString path);							//连接数据库
	_RecordsetPtr&  OpenRecordset(CString tableName);		//打开记录集
	void CloseRecordset();							//关闭记录集
	void CloseConn();								//关闭数据库连接
	UINT GetRecordCount(_RecordsetPtr pRecordset);	//获得记录数	
};

#endif // !defined(AFX_ADO_H__E0F8432E_F797_4979_8FB0_EAC60CA6C7F9__INCLUDED_)
