# Microsoft Developer Studio Project File - Name="SatCon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SatCon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SatCon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SatCon.mak" CFG="SatCon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SatCon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SatCon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SatCon - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/PCCTL.exe"

!ELSEIF  "$(CFG)" == "SatCon - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SatCon - Win32 Release"
# Name "SatCon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ADO.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseData.h
# End Source File
# Begin Source File

SOURCE=.\BitSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BitShowBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Calendar.cpp
# End Source File
# Begin Source File

SOURCE=.\CalendarShow.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartControl.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CommSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogBarBit.cpp
# End Source File
# Begin Source File

SOURCE=.\DlaglogBarRW.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyCalendarDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyChart.cpp
# End Source File
# Begin Source File

SOURCE=.\OldChart.cpp
# End Source File
# Begin Source File

SOURCE=.\PassWord.cpp
# End Source File
# Begin Source File

SOURCE=.\SatCon.cpp
# End Source File
# Begin Source File

SOURCE=.\SatCon.rc
# End Source File
# Begin Source File

SOURCE=.\SatConBitShowDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SatConBitShowView.cpp
# End Source File
# Begin Source File

SOURCE=.\SatConReadDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SatConReadView.cpp
# End Source File
# Begin Source File

SOURCE=.\SatConWriteDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SatConWriteView.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectDir.cpp
# End Source File
# Begin Source File

SOURCE=.\SerialPort.cpp
# End Source File
# Begin Source File

SOURCE=.\SetParaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SubBitDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubWriteDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TopBitSet.cpp
# End Source File
# Begin Source File

SOURCE=.\TopReadSet.cpp
# End Source File
# Begin Source File

SOURCE=.\UniButton.cpp
# End Source File
# Begin Source File

SOURCE=.\VarNameSetDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ADO.h
# End Source File
# Begin Source File

SOURCE=.\BitSet.h
# End Source File
# Begin Source File

SOURCE=.\BitShowBar.h
# End Source File
# Begin Source File

SOURCE=.\ButtonBar.h
# End Source File
# Begin Source File

SOURCE=.\Calendar.h
# End Source File
# Begin Source File

SOURCE=.\CalendarShow.h
# End Source File
# Begin Source File

SOURCE=.\ChartControl.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CommSet.h
# End Source File
# Begin Source File

SOURCE=.\DialogBarBit.h
# End Source File
# Begin Source File

SOURCE=.\DlaglogBarRW.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyCalendarDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyChart.h
# End Source File
# Begin Source File

SOURCE=.\OldChart.h
# End Source File
# Begin Source File

SOURCE=.\PassWord.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SatCon.h
# End Source File
# Begin Source File

SOURCE=.\SatConBitShowDoc.h
# End Source File
# Begin Source File

SOURCE=.\SatConBitShowView.h
# End Source File
# Begin Source File

SOURCE=.\SatConReadDoc.h
# End Source File
# Begin Source File

SOURCE=.\SatConReadView.h
# End Source File
# Begin Source File

SOURCE=.\SatConWriteDoc.h
# End Source File
# Begin Source File

SOURCE=.\SatConWriteView.h
# End Source File
# Begin Source File

SOURCE=.\SelectDir.h
# End Source File
# Begin Source File

SOURCE=.\SerialPort.h
# End Source File
# Begin Source File

SOURCE=.\SetParaDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubBitDlg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlg.h
# End Source File
# Begin Source File

SOURCE=.\SubWriteDlg.h
# End Source File
# Begin Source File

SOURCE=.\TopBitSet.h
# End Source File
# Begin Source File

SOURCE=.\TopReadSet.h
# End Source File
# Begin Source File

SOURCE=.\UniButton.h
# End Source File
# Begin Source File

SOURCE=.\VarNameSetDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Arrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_satc.ico
# End Source File
# Begin Source File

SOURCE=.\mdi.ico
# End Source File
# Begin Source File

SOURCE=.\res\reset.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Room.ico
# End Source File
# Begin Source File

SOURCE=.\res\SatCon.ico
# End Source File
# Begin Source File

SOURCE=.\res\SatCon.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SatConReadDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\shutdown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\start.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Stop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Trigon.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section SatCon : {D29F1A24-BAFB-4736-B2D8-91BEE291C3E0}
# 	1:19:IDD_CALENDAR_DIALOG:117
# 	2:16:CLASS: CCalendar:CCalendar
# 	2:16:Resource Include:resource.h
# 	2:19:IDD_CALENDAR_DIALOG:IDD_CALENDAR_DIALOG
# 	2:12:Calendar.cpp:Calendar.cpp
# 	2:10:ENUM: enum:enum
# 	2:10:Calendar.h:Calendar.h
# 	2:19:Application Include:SatCon.h
# End Section
# Section SatCon : {ACAC4302-B8E3-4E66-A6D8-DD6AB4E3D928}
# 	1:21:IDD_MYCALENDAR_DIALOG:118
# 	2:16:Resource Include:resource.h
# 	2:21:IDD_MYCALENDAR_DIALOG:IDD_MYCALENDAR_DIALOG
# 	2:17:MyCalendarDlg.cpp:MyCalendarDlg.cpp
# 	2:10:ENUM: enum:enum
# 	2:15:MyCalendarDlg.h:MyCalendarDlg.h
# 	2:21:CLASS: CMyCalendarDlg:CMyCalendarDlg
# 	2:19:Application Include:SatCon.h
# End Section
# Section SatCon : {648A5600-2C6E-101B-82B6-000000000014}
# 	2:21:DefaultSinkHeaderFile:mscomm.h
# 	2:16:DefaultSinkClass:CMSComm
# End Section
# Section SatCon : {E6E17E90-DF38-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CMSComm
# 	2:10:HeaderFile:mscomm.h
# 	2:8:ImplFile:mscomm.cpp
# End Section
