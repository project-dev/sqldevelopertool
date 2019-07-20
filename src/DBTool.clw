; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dbtool.h"
LastPage=0

ClassCount=26
Class1=CDBBackupDlg
Class2=CDBConnectBar
Class3=CDBErasureDlg
Class4=CDBListCtrl
Class5=CDBRestoreDlg
Class6=CDBToolApp
Class7=CAboutDlg
Class8=CDBToolDoc
Class9=CDBToolView
Class10=CFuncTabView
Class11=CLoginDlg
Class12=CMainFrame
Class13=CResultView
Class14=CSQLEdit
Class15=CTableCreatorDlg

ResourceCount=17
Resource1=IDD_BASE_CUST
Resource2=IDR_POPUP
Resource3=IDD_CONFIG_DLG
Resource4=IDD_SQLHISTDLG
Resource5=IDD_LOGIN_DLG
Resource6=IDD_DB_ERACER_DLG
Resource7=IDD_ABOUTBOX
Resource8=IDR_MAINFRAME
Class16=CRestorSQLDlg
Resource9=IDD_INFO_DLG
Resource10=IDD_INP_LOGIN_SET_DLG
Class17=CConfDlg
Class18=CBaseCustPage
Resource11=IDD_DB_BACKUP_DLG
Class19=CHistCustPage
Class20=CDBTreeCtrl
Resource12=IDD_TABLE_CREATOR_DLG
Class21=CProcViewDlg
Resource13=IDD_DB_RESTORE_DLG
Class22=CLoginSetNameInpDlg
Resource14=IDD_RESTORESQL_DLG
Class23=CInfoDlg
Resource15=IDD_HIST_CUST
Class24=CSQLHistDlg
Class25=CAoutCmpWnd
Resource16=IDD_PROC_DLG
Class26=CSqlViewDlg
Resource17=IDD_SQL_VIEW_DLG

[CLS:CDBBackupDlg]
Type=0
BaseClass=CDialog
HeaderFile=DBBackupDlg.h
ImplementationFile=DBBackupDlg.cpp

[CLS:CDBConnectBar]
Type=0
BaseClass=CDialogBar
HeaderFile=DBConnectBar.h
ImplementationFile=DBConnectBar.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_DB_CMB

[CLS:CDBErasureDlg]
Type=0
BaseClass=CDialog
HeaderFile=DBErasureDlg.h
ImplementationFile=DBErasureDlg.cpp

[CLS:CDBListCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=DBListCtrl.h
ImplementationFile=DBListCtrl.cpp
Filter=W
VirtualFilter=FWC

[CLS:CDBRestoreDlg]
Type=0
BaseClass=CDialog
HeaderFile=DBRestoreDlg.h
ImplementationFile=DBRestoreDlg.cpp

[CLS:CDBToolApp]
Type=0
BaseClass=CWinApp
HeaderFile=DBTool.h
ImplementationFile=DBTool.cpp
Filter=N
VirtualFilter=AC
LastObject=CDBToolApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DBTool.cpp
ImplementationFile=DBTool.cpp
LastObject=CAboutDlg
Filter=D
VirtualFilter=dWC

[CLS:CDBToolDoc]
Type=0
BaseClass=CDocument
HeaderFile=DBToolDoc.h
ImplementationFile=DBToolDoc.cpp

[CLS:CDBToolView]
Type=0
BaseClass=CView
HeaderFile=DBToolView.h
ImplementationFile=DBToolView.cpp
Filter=W
VirtualFilter=VWC
LastObject=CDBToolView

[CLS:CFuncTabView]
Type=0
BaseClass=CView
HeaderFile=FuncTabView.h
ImplementationFile=FuncTabView.cpp
LastObject=CFuncTabView
Filter=W
VirtualFilter=VWC

[CLS:CLoginDlg]
Type=0
BaseClass=CDialog
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CLoginDlg

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CResultView]
Type=0
BaseClass=CView
HeaderFile=ResultView.h
ImplementationFile=ResultView.cpp
Filter=C
VirtualFilter=VWC
LastObject=IDM_MDB_CREATE

[CLS:CSQLEdit]
Type=0
BaseClass=CEditEx
HeaderFile=SQLEdit.h
ImplementationFile=SQLEdit.cpp
Filter=W
VirtualFilter=WC
LastObject=CSQLEdit

[CLS:CTableCreatorDlg]
Type=0
BaseClass=CDialog
HeaderFile=TableCreatorDlg.h
ImplementationFile=TableCreatorDlg.cpp

[DLG:IDD_DB_BACKUP_DLG]
Type=1
Class=CDBBackupDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DBNAME,edit,1350633600
Control5=IDC_STATIC,static,1342308352
Control6=IDC_REF_DBBACKUP,button,1342242816
Control7=IDC_BACKUP_PATH,edit,1350631552

[DLG:IDR_MAINFRAME]
Type=1
Class=CDBConnectBar
ControlCount=4
Control1=IDC_DB_CMB,combobox,1344341251
Control2=IDC_SELDB_BTN,button,1342278400
Control3=IDC_SEL_MASTER_BTN,button,1342277632
Control4=IDC_REFRESH,button,1342277632

[DLG:IDD_DB_ERACER_DLG]
Type=1
Class=CDBErasureDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DBLIST,SysListView32,1350631433

[DLG:IDD_DB_RESTORE_DLG]
Type=1
Class=CDBRestoreDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_DBNAME,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BACKUP_PATH,edit,1350631552
Control5=IDC_REF_DBBACKUP,button,1342242816
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_RESTORE_PATH,edit,1350631552
Control10=IDC_REF_DBRESTORE,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_ED_SYSINFO,edit,1345394692

[DLG:IDD_LOGIN_DLG]
Type=1
Class=CLoginDlg
ControlCount=23
Control1=IDC_STATIC,button,1342177287
Control2=IDC_LOGINSET_LIST,listbox,1353781635
Control3=IDC_NEW_SET,button,1342242816
Control4=IDC_MODIFY_SET,button,1342242816
Control5=IDC_DEL_SET,button,1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308864
Control8=IDC_DTTYPE_CMB,combobox,1344340995
Control9=IDC_STATIC,static,1342308864
Control10=IDC_SERVER,combobox,1344341250
Control11=IDC_STATIC,static,1342308864
Control12=IDC_USER,combobox,1344341250
Control13=IDC_STATIC,static,1342308864
Control14=IDC_PASSWORD,edit,1350631584
Control15=IDC_AFTERDBSEL,button,1342242819
Control16=IDC_STATIC,static,1342308864
Control17=IDC_DB_CMB,combobox,1344341314
Control18=IDOK,button,1342242817
Control19=IDCANCEL,button,1342242816
Control20=IDC_STATIC,static,1342308864
Control21=IDC_DB_ODBCCMB,combobox,1344341059
Control22=IDC_BTN_REF,button,1342242816
Control23=IDC_ED_INFO,edit,1344342020

[DLG:IDD_TABLE_CREATOR_DLG]
Type=1
Class=CTableCreatorDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TABLELIST,SysListView32,1350664201

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_SQL_NEW
Command2=ID_SQL_SQVE
Command3=ID_SQL_SAVEAS
Command4=ID_CONNECT
Command5=ID_DBCLOSE
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_REFRESH
Command10=ID_SQLRUN
Command11=ID_NEW_SDT
Command12=ID_FILE_PRINT
Command13=ID_APP_ABOUT
CommandCount=13

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_CONNECT
Command2=ID_DBCLOSE
Command3=ID_SQLRUN
Command4=IDM_EXPORTCSV
Command5=IDM_EXPORTHTML
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_ALLSELECT
Command12=IDM_DBRESTORE
Command13=IDM_DBBACKUP
Command14=IDM_DBERACER
Command15=IDM_SQL_CREATE_DB
Command16=IDM_DEL_PROC
Command17=IDM_CONFIG
Command18=IDM_SQLHIST
Command19=IDM_MDB_CREATE
Command20=ID_VIEW_TOOLBAR
Command21=ID_VIEW_STATUS_BAR
Command22=ID_REFRESH
Command23=ID_APP_ABOUT
Command24=ID_HELP
CommandCount=24

[MNU:IDR_POPUP]
Type=1
Class=?
Command1=ID_SQL_NEW
Command2=IDM_TABCLOSE
Command3=ID_REFRESH_VIEW
Command4=IDM_EXPORTCSV
Command5=IDM_EXPORTHTML
Command6=IDM_SQLDELETE
Command7=IDM_OPENPATH
Command8=IDM_DEL_PROC
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_ALLSELECT
Command2=ID_EDIT_COPY
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_SQLFAIRING
Command6=ID_FILE_SAVE
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_REFRESH_VIEW
Command11=ID_REFRESH
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_SQLRUN
Command17=ID_EDIT_CUT
Command18=ID_EDIT_UNDO
CommandCount=18

[DLG:IDD_RESTORESQL_DLG]
Type=1
Class=CRestorSQLDlg
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_IGNORE_IDENTOTY,button,1342242819
Control3=IDC_IGNORE_NOT_NULL,button,1342242819
Control4=IDC_TABLE_LIST,SysListView32,1350664201
Control5=IDC_STATIC,button,1342177287
Control6=IDC_NO_PROC,button,1342242819
Control7=IDC_PROCLIST,SysListView32,1350664201
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816

[CLS:CRestorSQLDlg]
Type=0
HeaderFile=RestorSQLDlg.h
ImplementationFile=RestorSQLDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CRestorSQLDlg

[DLG:IDD_CONFIG_DLG]
Type=1
Class=CConfDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CUST_TAB,SysTabControl32,1342177280

[DLG:IDD_BASE_CUST]
Type=1
Class=CBaseCustPage
ControlCount=5
Control1=IDC_LOGTAB_CHK,button,1342242819
Control2=IDC_INCLIMENTAL,button,1342242819
Control3=IDC_CHK_REC_ALERT,button,1342242819
Control4=IDC_ED_ALERT_REC,edit,1350631552
Control5=IDC_STATIC,static,1342308864

[CLS:CConfDlg]
Type=0
HeaderFile=ConfDlg.h
ImplementationFile=ConfDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[CLS:CBaseCustPage]
Type=0
HeaderFile=BaseCustPage.h
ImplementationFile=BaseCustPage.cpp
BaseClass=CDialog
Filter=D
LastObject=CBaseCustPage
VirtualFilter=dWC

[DLG:IDD_HIST_CUST]
Type=1
Class=CHistCustPage
ControlCount=2
Control1=IDC_HIST_LIST,SysListView32,1350631424
Control2=IDC_HIST_DEL,button,1342242816

[CLS:CHistCustPage]
Type=0
HeaderFile=HistCustPage.h
ImplementationFile=HistCustPage.cpp
BaseClass=CDialog
Filter=D

[CLS:CDBTreeCtrl]
Type=0
HeaderFile=DBTreeCtrl.h
ImplementationFile=DBTreeCtrl.cpp
BaseClass=CTreeCtrlEx
Filter=W
VirtualFilter=GWC

[DLG:IDD_PROC_DLG]
Type=1
Class=CProcViewDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_PROP_EDIT,RICHEDIT,1353791940

[CLS:CProcViewDlg]
Type=0
HeaderFile=ProcViewDlg.h
ImplementationFile=ProcViewDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CProcViewDlg

[DLG:IDD_INP_LOGIN_SET_DLG]
Type=1
Class=CLoginSetNameInpDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NAME,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CLoginSetNameInpDlg]
Type=0
HeaderFile=LoginSetNameInpDlg.h
ImplementationFile=LoginSetNameInpDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CLoginSetNameInpDlg
VirtualFilter=dWC

[DLG:IDD_INFO_DLG]
Type=1
Class=CInfoDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_INFOAREA,button,1342177287

[CLS:CInfoDlg]
Type=0
HeaderFile=InfoDlg.h
ImplementationFile=InfoDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CInfoDlg

[DLG:IDD_SQLHISTDLG]
Type=1
Class=CSQLHistDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SQLLIST,SysListView32,1350631437

[CLS:CSQLHistDlg]
Type=0
HeaderFile=SQLHistDlg.h
ImplementationFile=SQLHistDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSQLHistDlg
VirtualFilter=dWC

[CLS:CAoutCmpWnd]
Type=0
HeaderFile=AoutCmpWnd.h
ImplementationFile=AoutCmpWnd.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=bWC
LastObject=CAoutCmpWnd

[DLG:IDD_SQL_VIEW_DLG]
Type=1
Class=CSqlViewDlg
ControlCount=3
Control1=IDC_SQL_VIEW,RICHEDIT,1353781700
Control2=IDC_SAVE_SQL,button,1342242816
Control3=IDOK,button,1342242817

[CLS:CSqlViewDlg]
Type=0
HeaderFile=SqlViewDlg.h
ImplementationFile=SqlViewDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSqlViewDlg

