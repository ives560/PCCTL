// ADO.h: interface for the ADO class.
//access���ݿ���
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
    _ConnectionPtr m_pConnection;					//���Ӷ���ָ��
	_RecordsetPtr  m_pRecordset;					//��¼������ָ��
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
	void OnInitADOConn(CString path);							//�������ݿ�
	_RecordsetPtr&  OpenRecordset(CString tableName);		//�򿪼�¼��
	void CloseRecordset();							//�رռ�¼��
	void CloseConn();								//�ر����ݿ�����
	UINT GetRecordCount(_RecordsetPtr pRecordset);	//��ü�¼��	
};

#endif // !defined(AFX_ADO_H__E0F8432E_F797_4979_8FB0_EAC60CA6C7F9__INCLUDED_)
