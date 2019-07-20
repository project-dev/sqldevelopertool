# Microsoft Developer Studio Project File - Name="DBTool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DBTool - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "DBTool.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "DBTool.mak" CFG="DBTool - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "DBTool - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "DBTool - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DBTool - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\Release"
# PROP Intermediate_Dir "..\lib\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\project_dev_lib\release\include\devlib" /I "..\..\project_dev_lib\release\include\devmfc" /I "..\..\project_dev_lib\release\include\devdb" /I "..\plugin\sdtpluginlib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "NEW_DBTYPE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 devlib.lib devmfc.lib devdb.lib Version.lib /nologo /subsystem:windows /machine:I386 /out:"..\bin\Release/SDT.exe" /libpath:"..\..\project_dev_lib\release\lib\release"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy /Y ..\..\project_dev_lib\release\bin\release\*.dll ..\bin\release	..\..\_common\upx.exe -9 ..\bin\release\SDT.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "DBTool - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\Debug"
# PROP Intermediate_Dir "..\lib\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\project_dev_lib\release\include\devlib" /I "..\..\project_dev_lib\release\include\devmfc" /I "..\..\project_dev_lib\release\include\devdb" /I "..\plugin\sdtpluginlib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "NEW_DBTYPE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 devlib.lib devmfc.lib devdb.lib Version.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\bin\Debug/SDT.exe" /pdbtype:sept /libpath:"..\..\project_dev_lib\release\lib\debug"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy /Y ..\..\project_dev_lib\release\bin\debug\*.dll ..\bin\debug
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "DBTool - Win32 Release"
# Name "DBTool - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AoutCmpWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseCustPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DBBackupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DBConnectBar.cpp
# End Source File
# Begin Source File

SOURCE=.\DBErasureDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DBListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DBRestoreDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTool.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTool.rc
# End Source File
# Begin Source File

SOURCE=.\DBToolDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DBToolView.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FuncTabView.cpp
# End Source File
# Begin Source File

SOURCE=.\HistCustPage.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginSetNameInpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Plugin.cpp
# End Source File
# Begin Source File

SOURCE=.\PluginAdmin.cpp
# End Source File
# Begin Source File

SOURCE=.\PluginException.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RestorSQLDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultView.cpp
# End Source File
# Begin Source File

SOURCE=.\SQLEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\SQLHistDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SqlViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TableCreatorDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AoutCmpWnd.h
# End Source File
# Begin Source File

SOURCE=.\BaseCustPage.h
# End Source File
# Begin Source File

SOURCE=.\ComDBTool.h
# End Source File
# Begin Source File

SOURCE=.\ConfDlg.h
# End Source File
# Begin Source File

SOURCE=.\DBBackupDlg.h
# End Source File
# Begin Source File

SOURCE=.\DBConnectBar.h
# End Source File
# Begin Source File

SOURCE=.\DBErasureDlg.h
# End Source File
# Begin Source File

SOURCE=.\DBListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DBRestoreDlg.h
# End Source File
# Begin Source File

SOURCE=.\DBTool.h
# End Source File
# Begin Source File

SOURCE=.\DBToolDoc.h
# End Source File
# Begin Source File

SOURCE=.\DBToolView.h
# End Source File
# Begin Source File

SOURCE=.\DBTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\FuncTabView.h
# End Source File
# Begin Source File

SOURCE=.\HistCustPage.h
# End Source File
# Begin Source File

SOURCE=.\InfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\LoginSetNameInpDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\Oracle\include\OraOLEDB.h
# End Source File
# Begin Source File

SOURCE=.\Plugin.h
# End Source File
# Begin Source File

SOURCE=.\PluginAdmin.h
# End Source File
# Begin Source File

SOURCE=.\PluginException.h
# End Source File
# Begin Source File

SOURCE=.\ProcViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RestorSQLDlg.h
# End Source File
# Begin Source File

SOURCE=.\ResultView.h
# End Source File
# Begin Source File

SOURCE=.\SQLEdit.h
# End Source File
# Begin Source File

SOURCE=.\SQLHistDlg.h
# End Source File
# Begin Source File

SOURCE=.\SqlViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TableCreatorDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DBTool.ico
# End Source File
# Begin Source File

SOURCE=.\res\DBTool.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DBToolDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\treeicon.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
