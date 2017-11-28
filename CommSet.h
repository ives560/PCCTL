
#if !defined(AFX_COMMSET_H__F3C7811E_D9D7_4D67_88F5_B86CD06AB128__INCLUDED_)
#define AFX_COMMSET_H__F3C7811E_D9D7_4D67_88F5_B86CD06AB128__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommSet.h : header file
//
#include "SerialPort.h"
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CCommSet dialog

class CCommSet : public CDialog
{
// Construction
public:
	void WriteDataComm();
	void ReadDataComm();
	void WriteDataTimer();
	void ReadDataTimer();
	CCommSet(CWnd* pParent = NULL);   // standard constructor
	CMainFrame *m_pMainFram;
	CWnd *pReadView;
	CWnd *pBitView;
	CWnd *pWriteView;
	CSerialPort m_SerialPort;		//���ڶ���
	bool RxRWflag;					//���մ��ڶ�д��־(R-false,W-true)
	bool TxRWflag;					//���ʹ��ڶ�д��־(R-false,W-true)
	bool m_ComOpened;				//���ڴ򿪱�־
	unsigned char RxBuffer[255];	//���ջ�����
//	unsigned char TxBuffer[255];	//���ͻ�����
	BUFFER_STRUCT TxBuffer[255];
	int RxIndex;					//���ո���
	int TxIndex;					//���͸���
	int Rxcase;
	CString m_ComData;				//�����ַ���
	int sendval;					//���ͱ�������λ
	int sendsum;					//���͸���
	bool InitComm(void);			//��ʼ������
	void CloseComm(void);			//�رմ���
	int CharToInt(char* data);		//�ַ���ת����
	char HexChar(char c);			//�ַ�ת����
	unsigned int crcchk(unsigned char *data_ad,unsigned int length);//CRCУ��
	void SendReadOrder(int Address,int FunCode,int StartAddress,int Length);//���Ͷ�ָ��
	void SendWriteOrder(int StartAddress,char* dataval);
	char parity;	//У��λ
	char CommState;
	int TimeOut;

	int refreshcount;
	int timesum;
// Dialog Data
	//{{AFX_DATA(CCommSet)
	enum { IDD = IDD_COMMSET_DIALOG };
	CComboBox	m_parity;
	CString	m_baud;
	CString	m_data;
	CString	m_port;
	CString	m_stop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DSPvalToPCval(PARAINI_INFO *parainfo);
	void UpDataView();
	void MSleep( long lTime, bool bProcessMsg);
	// Generated message map functions
	//{{AFX_MSG(CCommSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LONG OnComm(WPARAM ch, LPARAM port);
	virtual void OnOK();
	afx_msg void OnSelchangeParityCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMSET_H__F3C7811E_D9D7_4D67_88F5_B86CD06AB128__INCLUDED_)
