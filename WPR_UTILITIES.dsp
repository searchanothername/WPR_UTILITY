# Microsoft Developer Studio Project File - Name="WPR_UTILITIES" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WPR_UTILITIES - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WPR_UTILITIES.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WPR_UTILITIES.mak" CFG="WPR_UTILITIES - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WPR_UTILITIES - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WPR_UTILITIES - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WPR_UTILITIES - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "WPR_UTILITIES - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD F90 /browser
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib WPRDriverlib.lib ws2_32.lib wsock32.lib ippcore.lib ipps.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/WPR UTILITY.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "WPR_UTILITIES - Win32 Release"
# Name "WPR_UTILITIES - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3DBar.cpp
# End Source File
# Begin Source File

SOURCE=.\AdvancedSettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmSettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmShowDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BasicSettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BeamCodeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ColoredListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorProgressCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DataView.cpp
# End Source File
# Begin Source File

SOURCE=.\DigitalClock.cpp
# End Source File
# Begin Source File

SOURCE=.\DmaSettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DoptestParamDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DspSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\FrequencyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NormalSettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PerformanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RawdataDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticCounter.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusMonitorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TimeSeriesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UPSDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WPR_UTILITIES.cpp
# End Source File
# Begin Source File

SOURCE=.\WPR_UTILITIES.rc
# End Source File
# Begin Source File

SOURCE=.\WPR_UTILITIESDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3DBar.h
# End Source File
# Begin Source File

SOURCE=.\AdvancedSettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\AlarmSettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\AlarmShowDlg.h
# End Source File
# Begin Source File

SOURCE=.\BasicSettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\BeamCodeDlg.h
# End Source File
# Begin Source File

SOURCE=.\ColoredListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ColorProgressCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DataView.h
# End Source File
# Begin Source File

SOURCE=.\DigitalClock.h
# End Source File
# Begin Source File

SOURCE=.\DmaSettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\DoptestParamDlg.h
# End Source File
# Begin Source File

SOURCE=.\DspSetting.h
# End Source File
# Begin Source File

SOURCE=.\FrequencyDlg.h
# End Source File
# Begin Source File

SOURCE=.\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\NormalSettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\PerformanceDlg.h
# End Source File
# Begin Source File

SOURCE=.\RawdataDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StaticCounter.h
# End Source File
# Begin Source File

SOURCE=.\StatusMonitorDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TimeSeriesDlg.h
# End Source File
# Begin Source File

SOURCE=.\UPSDlg.h
# End Source File
# Begin Source File

SOURCE=.\WPR_UTILITIES.h
# End Source File
# Begin Source File

SOURCE=.\WPR_UTILITIESDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Icons\200641472713567.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\200641472717699.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\200641472719289.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\advanced_setting.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\alarm.ICO
# End Source File
# Begin Source File

SOURCE=.\Icons\auto.ico
# End Source File
# Begin Source File

SOURCE=.\Bitmap\BK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BK.bmp
# End Source File
# Begin Source File

SOURCE=.\Icons\dma.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\DspSetting.ico
# End Source File
# Begin Source File

SOURCE=".\Icons\flag red.ico"
# End Source File
# Begin Source File

SOURCE=".\Icons\flag yellow.ico"
# End Source File
# Begin Source File

SOURCE=.\Icons\folder.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\Hein003.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\Hein010.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\Hein018.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\Hein29.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\icon16.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\icon17.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\icon18.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\icon19.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\icon20.ico
# End Source File
# Begin Source File

SOURCE=".\Icons\Jack O'Lantern.ico"
# End Source File
# Begin Source File

SOURCE=.\Icons\JobLab.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\Ledoff.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\Ledon.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\Lock.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\normal_setting.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\north_se.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\passwords.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\POSTL.ICO
# End Source File
# Begin Source File

SOURCE=.\Icons\PP18.ico
# End Source File
# Begin Source File

SOURCE=".\Icons\protect red.ico"
# End Source File
# Begin Source File

SOURCE=.\Icons\RECL.ICO
# End Source File
# Begin Source File

SOURCE=.\Icons\service.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\SINEWAVE.ICO
# End Source File
# Begin Source File

SOURCE=.\Icons\Slayman3.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\south_se.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\spec.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\TimedMsgBox.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\Tokimeki11.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\Icons\west.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\West_enable.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\WPR_UTILITIES.ico
# End Source File
# Begin Source File

SOURCE=.\res\WPR_UTILITIES.rc2
# End Source File
# Begin Source File

SOURCE=.\Icons\WRENCH.ICO
# End Source File
# End Group
# Begin Group "Sub Tasks"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\DataProcess.h
# End Source File
# Begin Source File

SOURCE=.\ProductProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\ProductProcess.h
# End Source File
# Begin Source File

SOURCE=.\ServerTask.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerTask.h
# End Source File
# Begin Source File

SOURCE=.\StatusMonitorTask.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusMonitorTask.h
# End Source File
# Begin Source File

SOURCE=.\TestTask.cpp
# End Source File
# Begin Source File

SOURCE=.\TestTask.h
# End Source File
# Begin Source File

SOURCE=.\UPSMonitorTask.cpp
# End Source File
# Begin Source File

SOURCE=.\UPSMonitorTask.h
# End Source File
# End Group
# Begin Group "Globals"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Global.cpp
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\Global_Advanced.cpp
# End Source File
# Begin Source File

SOURCE=.\Global_Advanced.h
# End Source File
# Begin Source File

SOURCE=.\Global_Alarms.cpp
# End Source File
# Begin Source File

SOURCE=.\Global_Alarms.h
# End Source File
# Begin Source File

SOURCE=.\Global_CtrlWords.cpp
# End Source File
# Begin Source File

SOURCE=.\Global_CtrlWords.h
# End Source File
# Begin Source File

SOURCE=.\Global_DataDef.h
# End Source File
# Begin Source File

SOURCE=.\Global_Network.h
# End Source File
# Begin Source File

SOURCE=.\Global_SM.cpp
# End Source File
# Begin Source File

SOURCE=.\Global_SM.h
# End Source File
# Begin Source File

SOURCE=.\Global_SM_NewTx.h
# End Source File
# Begin Source File

SOURCE=.\global_ups.h
# End Source File
# End Group
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Thread.cpp
# End Source File
# Begin Source File

SOURCE=.\Thread.h
# End Source File
# End Group
# Begin Group "I/O"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\A44_sm_handler.cpp
# End Source File
# Begin Source File

SOURCE=.\A44_sm_handler.h
# End Source File
# Begin Source File

SOURCE=.\Sm_port.cpp
# End Source File
# Begin Source File

SOURCE=.\sm_port.h
# End Source File
# End Group
# Begin Group "Data Handler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataHandlor.cpp
# End Source File
# Begin Source File

SOURCE=.\DataHandlor.h
# End Source File
# Begin Source File

SOURCE=.\IrqQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\IrqQueue.h
# End Source File
# End Group
# Begin Group "NetWork"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ClientContext.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientContext.h
# End Source File
# Begin Source File

SOURCE=.\ClientManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientManager.h
# End Source File
# Begin Source File

SOURCE=.\Server.cpp
# End Source File
# Begin Source File

SOURCE=.\Server.h
# End Source File
# End Group
# Begin Group "Spectra Display"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DFVCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DFVCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DFVDocTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\DFVDocTemplate.h
# End Source File
# Begin Source File

SOURCE=.\DFVDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\DFVDocument.h
# End Source File
# Begin Source File

SOURCE=.\DFVFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\DFVFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\TotalSpecDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TotalSpecDlg.h
# End Source File
# Begin Source File

SOURCE=.\WPR_UTILITY_SPECDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\WPR_UTILITY_SPECDoc.h
# End Source File
# Begin Source File

SOURCE=.\WPR_UTILITY_SPECView.cpp
# End Source File
# Begin Source File

SOURCE=.\WPR_UTILITY_SPECView.h
# End Source File
# Begin Source File

SOURCE=.\ZoomView.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomView.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
