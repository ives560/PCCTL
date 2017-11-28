; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyChart
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SatCon.h"
LastPage=0

ClassCount=33
Class1=CSatConApp
Class2=CSatConReadDoc
Class3=CSatConReadView
Class4=CMainFrame
Class7=SatConWriteView
Class9=CSatConBitShowView

ResourceCount=27
Resource1=IDD_SEL_DIRECTORY_DIALOG
Resource2=IDR_MYCHART_TMPL
Resource3=IDD_SATCON_WRITE_FORM
Resource4=IDD_SETPARA_DIALOG
Class10=CSatConBitShowDoc
Resource5=IDD_CALENDAR_DIALOG
Resource6=IDD_ABOUTBOX
Resource7=IDR_MAINFRAME
Resource8=IDD_TOPREADSET_DIALOG
Class5=CChildFrame
Class6=CAboutDlg
Class8=SatConWriteDoc
Class11=BitShowBar
Resource9=IDD_BITSHOW_DIALOGBAR
Class12=CSubDlg
Class13=SetParaDlg
Class14=VarNameSetDlg
Resource10=IDD_TOPBITSET_DIALOG
Class15=SubWriteDlg
Resource11=IDD_BIT_SET_DIALOG
Resource12=IDD_SUB_DIALOG
Class16=BitSet
Resource13=IDD_PASSWORD_DIALOG
Class17=CCommSet
Resource14=IDD_MYCHART_FORM
Class18=ButtonBar
Resource15=IDD_SUB_DIALOG_WRITE
Class19=CPassWord
Class20=SubBitDlg
Resource16=IDD_SATCON_READ_FORM
Resource17=IDD_DIALOGBAR_BIT
Class21=TopReadSet
Class22=TopBitSet
Resource18=IDR_SATCONTYPE
Resource19=IDD_OLDCHART_DIALOG
Class23=DialogBarBit
Class24=DlaglogBarRW
Resource20=IDD_VARNAME_SET_DIALOG
Class25=CSelectDir
Resource21=IDD_COMMSET_DIALOG
Class26=CMyChart
Resource22=IDD_DIALOGBAR_RW
Class27=CMyChartDoc
Resource23=IDD_SUB_DIALOG_BIT
Class28=COldChartShow
Class29=CChartControl
Class30=CCalendarShow
Resource24=IDD_SATCON_BITSHOW_FORM
Class31=COldChart
Resource25=IDD_BUTTON_DIALOGBAR
Class32=CCalendar
Resource26=IDD_CALENDAR_SHOW
Class33=CMyCalendarDlg
Resource27=IDD_MYCALENDAR_DIALOG

[CLS:CSatConApp]
Type=0
HeaderFile=SatCon.h
ImplementationFile=SatCon.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CSatConReadDoc]
Type=0
HeaderFile=SatConReadDoc.h
ImplementationFile=SatConReadDoc.cpp
Filter=N

[CLS:CSatConReadView]
Type=0
HeaderFile=SatConReadView.h
ImplementationFile=SatConReadView.cpp
Filter=D
LastObject=IDC_READER_TAB
BaseClass=CFormView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_MENU_DOWNLOAD_PC_DSP
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC


[CLS:CAboutDlg]
Type=0
HeaderFile=SatCon.cpp
ImplementationFile=SatCon.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_MENU_OPR_SHUT
Command2=ID_MENU_OPR_RESET
Command3=ID_MENU_OPR_START
Command4=ID_MENU_OPR_STOP
Command5=ID_MENU_OPR_CNTPCS
Command6=ID_MENU_OPR_DISCNTPCS
Command7=ID_MENU_OPR_CNNSET
Command8=ID_MENU_OPR_USERLEVEL
Command9=ID_MENU_OPR_SERCERLEVEL
Command10=ID_MENU_OPR_SYSLEVEL
Command11=ID_APP_EXIT
Command12=ID_MENU_BITSHOW
Command13=ID_MENU_WRITER
Command14=ID_MENU_READER
Command15=ID_MENU_SET_PARAMETERS
Command16=ID_MENU_UPLOAD_DSP_PC
Command17=ID_MENU_DOWNLOAD_PC_DSP
CommandCount=17

[MNU:IDR_SATCONTYPE]
Type=1
Class=CSatConReadView
Command1=ID_MENU_OPR_SHUT
Command2=ID_MENU_OPR_RESET
Command3=ID_MENU_OPR_START
Command4=ID_MENU_OPR_STOP
Command5=ID_MENU_OPR_CNTPCS
Command6=ID_MENU_OPR_DISCNTPCS
Command7=ID_MENU_OPR_CNNSET
Command8=ID_MENU_OPR_USERLEVEL
Command9=ID_MENU_OPR_SERCERLEVEL
Command10=ID_MENU_OPR_SYSLEVEL
Command11=ID_APP_EXIT
Command12=ID_MENU_BITSHOW
Command13=ID_MENU_WRITER
Command14=ID_MENU_READER
Command15=ID_MENU_SET_PARAMETERS
Command16=ID_MENU_UPLOAD_DSP_PC
Command17=ID_MENU_DOWNLOAD_PC_DSP
CommandCount=17

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_SATCON_READ_FORM]
Type=1
Class=CSatConReadView
ControlCount=1
Control1=IDC_READER_TAB,SysTabControl32,1342177280

[DLG:IDD_SATCON_WRITE_FORM]
Type=1
Class=SatConWriteView
ControlCount=5
Control1=IDC_WRITE_TAB,SysTabControl32,1342177280
Control2=IDC_SAVEALL_BUTTON,button,1342242816
Control3=IDC_LOADFPC_BUTTON,button,1342242816
Control4=IDC_LOADFDSP_BUTTON,button,1342242816
Control5=IDC_CLEAR_BUTTON,button,1342242816

[CLS:SatConWriteView]
Type=0
HeaderFile=SatConWriteView.h
ImplementationFile=SatConWriteView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=IDC_SAVEALL_BUTTON

[CLS:SatConWriteDoc]
Type=0
HeaderFile=SatConWriteDoc.h
ImplementationFile=SatConWriteDoc.cpp
BaseClass=CDocument
Filter=N
LastObject=ID_APP_EXIT

[DLG:IDD_SATCON_BITSHOW_FORM]
Type=1
Class=CSatConBitShowView
ControlCount=1
Control1=IDC_BITSHOW_TAB,SysTabControl32,1342177280

[CLS:CSatConBitShowView]
Type=0
HeaderFile=SatConBitShowView.h
ImplementationFile=SatConBitShowView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=IDC_BITSHOW_TAB

[CLS:CSatConBitShowDoc]
Type=0
HeaderFile=SatConBitShowDoc.h
ImplementationFile=SatConBitShowDoc.cpp
BaseClass=CDocument
Filter=N
LastObject=CSatConBitShowDoc

[CLS:BitShowBar]
Type=0
HeaderFile=BitShowBar.h
ImplementationFile=BitShowBar.cpp
BaseClass=CDialogBar
Filter=D
LastObject=BitShowBar
VirtualFilter=dWC

[DLG:IDD_SUB_DIALOG]
Type=1
Class=CSubDlg
ControlCount=3
Control1=IDC_READ_VAL_EDIT,edit,1350633600
Control2=IDC_READ_UNIT_EDIT,edit,1350633600
Control3=IDC_READ_BASE_GROUP,button,1342177287

[CLS:CSubDlg]
Type=0
HeaderFile=SubDlg.h
ImplementationFile=SubDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSubDlg

[DLG:IDD_SETPARA_DIALOG]
Type=1
Class=SetParaDlg
ControlCount=31
Control1=IDC_NAME_COMBO,combobox,1344339970
Control2=IDC_VALUE_EDIT,edit,1350631552
Control3=IDC_ADDERSS_EDIT,edit,1350639744
Control4=IDC_STEP_EDIT,edit,1350631552
Control5=IDC_MIN_EDIT,edit,1350631552
Control6=IDC_COMMENT_EDIT,edit,1350631552
Control7=IDC_WABLE_CHECK,button,1342242819
Control8=IDC_RABLE_CHECK,button,1342242819
Control9=IDC_RCONT_CHECK,button,1342242819
Control10=IDC_DECADAL_EDIT,edit,1350631552
Control11=IDC_BINARY_EDIT,edit,1350631552
Control12=IDC_FORMAT_EDIT,edit,1350631552
Control13=IDC_SAVE_BUTTON,button,1342242816
Control14=IDC_RESET_BUTTON,button,1342242816
Control15=IDCANCEL,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_UNIT_EDIT,edit,1350631552
Control29=IDC_MAX_EDIT,edit,1350631552
Control30=IDC_STATIC,static,1476526080
Control31=IDC_STATIC,static,1342308352

[CLS:SetParaDlg]
Type=0
HeaderFile=SetParaDlg.h
ImplementationFile=SetParaDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_NAME_COMBO

[DLG:IDD_VARNAME_SET_DIALOG]
Type=1
Class=VarNameSetDlg
ControlCount=5
Control1=IDC_VARNAME_COMBO,combobox,1344339970
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342242816
Control4=IDC_TABNAME_EDIT,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[CLS:VarNameSetDlg]
Type=0
HeaderFile=VarNameSetDlg.h
ImplementationFile=VarNameSetDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_SUB_DIALOG_WRITE]
Type=1
Class=SubWriteDlg
ControlCount=13
Control1=IDC_WRITE_GROUP,button,1342177287
Control2=IDC_WRITE_VRL_EDIT,edit,1350633600
Control3=IDC_WRITE_CURRVAL_EDIT,edit,1350631552
Control4=IDC_WRITE_UNIT_EDIT,edit,1350633600
Control5=IDC_WRITE_STEP_EDIT,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDOK,button,1342242816
Control11=IDC_SAVE_BUTTON,button,1342242816
Control12=IDC_ADD_BUTTON,button,1342242816
Control13=IDC_DEC_BUTTON,button,1342242816

[CLS:SubWriteDlg]
Type=0
HeaderFile=SubWriteDlg.h
ImplementationFile=SubWriteDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_WRITE_VRL_EDIT
VirtualFilter=dWC

[DLG:IDD_BITSHOW_DIALOGBAR]
Type=1
Class=BitShowBar
ControlCount=0

[DLG:IDD_SUB_DIALOG_BIT]
Type=1
Class=SubBitDlg
ControlCount=1
Control1=IDC_BITNAME_STATIC,static,1342308352

[DLG:IDD_BIT_SET_DIALOG]
Type=1
Class=BitSet
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_VARNAME_COMBO,combobox,1344339970
Control4=IDC_BITNO_COMBO,combobox,1344339970
Control5=IDC_DISPLAY0_EDIT,edit,1350631552
Control6=IDC_DISPLAY1_EDIT,edit,1350631552
Control7=IDC_BITCOM_EDIT,edit,1350631552
Control8=IDC_TABNAME_EDIT,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_ITEMNUM_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_SELCOLOR0_STATIC,static,1342308608
Control14=IDC_SELCOLOR1_STATIC,static,1342308608
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352

[CLS:BitSet]
Type=0
HeaderFile=BitSet.h
ImplementationFile=BitSet.cpp
BaseClass=CDialog
Filter=D
LastObject=BitSet
VirtualFilter=dWC

[DLG:IDD_COMMSET_DIALOG]
Type=1
Class=CCommSet
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PORT_COMBO,combobox,1344339970
Control5=IDC_BAUD_COMBO,combobox,1344339970
Control6=IDC_PARITY_COMBO,combobox,1344339970
Control7=IDC_DATA_COMBO,combobox,1344339970
Control8=IDC_STOP_COMBO,combobox,1344339970
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352

[CLS:CCommSet]
Type=0
HeaderFile=CommSet.h
ImplementationFile=CommSet.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_PARITY_COMBO

[CLS:ButtonBar]
Type=0
HeaderFile=ButtonBar.h
ImplementationFile=ButtonBar.cpp
BaseClass=CDialogBar
Filter=D
LastObject=ButtonBar
VirtualFilter=dWC

[DLG:IDD_BUTTON_DIALOGBAR]
Type=1
Class=ButtonBar
ControlCount=4
Control1=IDC_SHUTDOWN_BUTTON,button,1342242944
Control2=IDC_RESET_BUTTON,button,1342242944
Control3=IDC_START_BUTTON,button,1342242944
Control4=IDC_STOP_BUTTON,button,1342242944

[DLG:IDD_PASSWORD_DIALOG]
Type=1
Class=CPassWord
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PASSWORD_EDIT,edit,1350631600
Control4=IDC_PASSWORD_STATIC,button,1342177287
Control5=IDC_PROMPT_STATIC,static,1342308352

[CLS:CPassWord]
Type=0
HeaderFile=PassWord.h
ImplementationFile=PassWord.cpp
BaseClass=CDialog
Filter=D
LastObject=CPassWord
VirtualFilter=dWC

[CLS:SubBitDlg]
Type=0
HeaderFile=SubBitDlg.h
ImplementationFile=SubBitDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_EXIT
VirtualFilter=dWC

[DLG:IDD_TOPBITSET_DIALOG]
Type=1
Class=TopBitSet
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_VARIABLE_COMBO,combobox,1344340226
Control3=IDC_BIT_COMBO,combobox,1344339970

[DLG:IDD_TOPREADSET_DIALOG]
Type=1
Class=TopReadSet
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_NAME_COMBO,combobox,1344339970
Control3=IDC_COLOR_STATIC,static,1342308608
Control4=IDC_STATIC,static,1342308352

[CLS:TopBitSet]
Type=0
HeaderFile=TopBitSet.h
ImplementationFile=TopBitSet.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BIT_COMBO
VirtualFilter=dWC

[CLS:TopReadSet]
Type=0
HeaderFile=TopReadSet.h
ImplementationFile=TopReadSet.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_NAME_COMBO
VirtualFilter=dWC

[DLG:IDD_DIALOGBAR_BIT]
Type=1
Class=DialogBarBit
ControlCount=1
Control1=IDC_BIT_STATIC,static,1342308608

[DLG:IDD_DIALOGBAR_RW]
Type=1
Class=DlaglogBarRW
ControlCount=2
Control1=IDC_VALNAMEBAR_STATIC,static,1342308608
Control2=IDC_VALBAR_STATIC,static,1342308352

[CLS:DialogBarBit]
Type=0
HeaderFile=DialogBarBit.h
ImplementationFile=DialogBarBit.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BIT_STATIC
VirtualFilter=dWC

[CLS:DlaglogBarRW]
Type=0
HeaderFile=DlaglogBarRW.h
ImplementationFile=DlaglogBarRW.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_VALBAR_STATIC
VirtualFilter=dWC

[DLG:IDD_SEL_DIRECTORY_DIALOG]
Type=1
Class=CSelectDir
ControlCount=7
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TITLE_STATIC,static,1342308352
Control5=IDC_BROWSE_BUTTON,button,1342242816
Control6=IDC_DIRECTORY_COMBO,combobox,1344339970
Control7=IDC_ERROR_STATIC,static,1342308352

[CLS:CSelectDir]
Type=0
HeaderFile=SelectDir.h
ImplementationFile=SelectDir.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_DIRECTORY_COMBO
VirtualFilter=dWC

[DLG:IDD_MYCHART_FORM]
Type=1
Class=CMyChart
ControlCount=3
Control1=IDC_COMBO_PARA,combobox,1344340226
Control2=IDC_STATIC,static,1342308352
Control3=IDC_OLDCHART_BUTTON,button,1342242816

[CLS:CMyChart]
Type=0
HeaderFile=MyChart.h
ImplementationFile=MyChart.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=IDC_COMBO_PARA

[MNU:IDR_MYCHART_TMPL]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

[CLS:CMyChartDoc]
Type=0
HeaderFile=MyChart.h
ImplementationFile=MyChart.cpp
BaseClass=CDocument
Filter=N

[CLS:COldChartShow]
Type=0
HeaderFile=OldChartShow.h
ImplementationFile=OldChartShow.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_MONTHCALENDAR
VirtualFilter=dWC

[CLS:CChartControl]
Type=0
HeaderFile=ChartControl.h
ImplementationFile=ChartControl.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CChartControl

[DLG:IDD_CALENDAR_SHOW]
Type=1
Class=CCalendarShow
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CCalendarShow]
Type=0
HeaderFile=CalendarShow.h
ImplementationFile=CalendarShow.cpp
BaseClass=CDialog
Filter=D
LastObject=CCalendarShow
VirtualFilter=dWC

[DLG:IDD_OLDCHART_DIALOG]
Type=1
Class=COldChart
ControlCount=0

[CLS:COldChart]
Type=0
HeaderFile=OldChart.h
ImplementationFile=OldChart.cpp
BaseClass=CDialog
Filter=D
LastObject=COldChart
VirtualFilter=dWC

[DLG:IDD_CALENDAR_DIALOG]
Type=1
Class=CCalendar
ControlCount=0

[CLS:CCalendar]
Type=0
HeaderFile=Calendar.h
ImplementationFile=Calendar.cpp
BaseClass=CDialog

[DLG:IDD_MYCALENDAR_DIALOG]
Type=1
Class=CMyCalendarDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CMyCalendarDlg]
Type=0
HeaderFile=MyCalendarDlg.h
ImplementationFile=MyCalendarDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

