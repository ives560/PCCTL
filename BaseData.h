#ifndef __BASEDATA_H__
#define __BASEDATA_H__

//para.ini
#define PARA_COM_STR_LEN 10
#define PARA_COM_LONGSTR_LEN 40
#define MAX_PARA_INI_NUM    1000	//���֧��MAX_PARA_INI_NUM������item
/*�����ļ�����ṹ�壬����һ�������е����б���*/
typedef struct
{
    int itemBmFlag; // = SIGN_ADDR|SIGN_UNIT|SIGN_VFORMAT
	bool commable;	//���ڿɶ�
    char writeable; //=1
    char readable;  //=1
    char RdContinue;    //=0
    char dh[4];
    int address; //

    float min;
    float max;
//    float value;		//����ֵ
	float curval;		//��ǰֵ
    float decscale;
    float binscale;
    float step;

	char cmin[PARA_COM_STR_LEN];
	char cmax[PARA_COM_STR_LEN];
	char cvalue[PARA_COM_STR_LEN];
	char cfval[PARA_COM_STR_LEN];	//��������ַ���
	char cdecscale[PARA_COM_STR_LEN];
	char cbinscale[PARA_COM_STR_LEN];
	char cstep[PARA_COM_STR_LEN];

    char unit[PARA_COM_STR_LEN];    //=kwh
    char vformat[PARA_COM_STR_LEN]; //0.000
    char itemName[PARA_COM_LONGSTR_LEN];
    char comt[PARA_COM_LONGSTR_LEN];  //�֧��30��˵���ִ�
}PARAINI_INFO;
/****���������ǽṹ��************/
typedef enum{
    SIGN_ADDR = 0x1,
	SIGN_UNIT = 0x2,
	SIGN_VFORMAT = 0x4,
	SIGN_COMT = 0x8,
	SIGN_WRITEABLE = 0x10,
	SIGN_READABLE = 0x20,
	SIGN_READCTN = 0x40,
	SIGN_MIN = 0x80,
	SIGN_MAX = 0x100,
	SIGN_VALUE = 0x200,
	SIGN_DESCALE = 0x400,
	SIGN_BINSCALE = 0x800,
	SIGN_STEP = 0x1000,
	SIGN_DH = 0x2000
}PARA_SIGN;


#define ITEM_OUTER_WIDTH 10//item�ؼ����
#define ITEM_OUTER_HEIGHT 10//item�ؼ��߶�
//frmRead.ini
#define TAB_MAX_NUM	50	//tab�ؼ���һҳ��ʾ�����item��
#define ITEM_MAX_NUM	200	//���֧��200��
#define TAB_NAME_LEN	40//tab�ؼ����ֵ���󳤶�
#define MAX_BIT_NUM     16
#define ITEM_NAME_LEN	PARA_COM_LONGSTR_LEN
#define MAX_VAL_NUM 3000
#define MAX_READCOM_NUM 500
/////////////////////////////////////////////
typedef struct  
{
	char Displ[2][ITEM_NAME_LEN];
	char Color[2][ITEM_NAME_LEN];
	char Comment[ITEM_NAME_LEN];
}BitInfo;//λ��Ϣ
typedef struct
{
	char ValName[ITEM_NAME_LEN];
	BitInfo bitinfo[MAX_BIT_NUM];
	
}ParaValInfo;//������Ϣ
////////////////////////////////////////////////
typedef struct  
{
	char ValName[ITEM_NAME_LEN];
	PARAINI_INFO* ValInfo;		//����������Ϣָ��
	int BitNo;					//item��ʾ����λ��only bitshow��
	ParaValInfo *	pvalbitinfo;	//����λ��Ϣָ�루only bitshow��
}ItemInfo;//item��Ϣ

typedef struct
{
	char tabName[TAB_NAME_LEN];//tabҳ��
	int itemNum;				//page��item�ĸ���
	ItemInfo iteminfo[ITEM_MAX_NUM];//item��Ϣ
	
}TabInfo;//tab��Ϣ
typedef struct
{
	char Dply_Name[ITEM_NAME_LEN];
	char Dply_Color[ITEM_NAME_LEN];
	PARAINI_INFO *ValInfo;
}MainVal;
typedef struct 
{
	char Bit_Vname[ITEM_NAME_LEN];
	int Bit_No;
	PARAINI_INFO *ValInfo;
	ParaValInfo *pvalbitinfo;

}MainBit;

#define FORM_MAX_NUM	10
#define MAINITEM_MAX_NUM 20
typedef struct
{
	char FormShow[FORM_MAX_NUM][ITEM_NAME_LEN];
	MainVal mainval[MAINITEM_MAX_NUM];
	MainBit mainbit[MAINITEM_MAX_NUM];

}MainInfo;

typedef struct  
{
	int TxAddss;
	char TxData[3];
}BUFFER_STRUCT;
//////////////////////////////////////////
typedef struct  
{
	CString Button;
	CString Comment;
	CString Vname;
	int Value;
	PARAINI_INFO *pinfo;
}CMD_BUTTON;

#endif	//__BASEDATA_H__
