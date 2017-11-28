
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
	CSerialPort m_SerialPort;		//串口对象
	bool RxRWflag;					//接收串口读写标志(R-false,W-true)
	bool TxRWflag;					//发送串口读写标志(R-false,W-true)
	bool m_ComOpened;				//串口打开标志
	unsigned char RxBuffer[255];	//接收缓存区
//	unsigned char TxBuffer[255];	//发送缓存区
	BUFFER_STRUCT TxBuffer[255];
	int RxIndex;					//接收个数
	int TxIndex;					//发送个数
	int Rxcase;
	CString m_ComData;				//接收字符串
	int sendval;					//发送变量数组位
	int sendsum;					//发送个数
	bool InitComm(void);			//初始化串口
	void CloseComm(void);			//关闭串口
	int CharToInt(char* data);		//字符串转数字
	char HexChar(char c);			//字符转数字
	unsigned int crcchk(unsigned char *data_ad,unsigned int length);//CRC校验
	void SendReadOrder(int Address,int FunCode,int StartAddress,int Length);//发送读指令
	void SendWriteOrder(int StartAddress,char* dataval);
	char parity;	//校验位
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
