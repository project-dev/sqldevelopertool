// MainFrm.cpp : CMainFrame クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "DBTool.h"

#include "MainFrm.h"
#include "DBToolView.h"
#include "FuncTabView.h"
#include "ResultView.h"
#include "LoginDlg.h"

#include "TableCreatorDlg.h"
#include "DBErasureDlg.h"
#include "DBBackupDlg.h"
#include "DBRestoreDlg.h"
#include "RestorSqlDlg.h"
#include "SQLHistDlg.h"
#include "DebugSupport.h"
#include "ConfDlg.h"
#include "devlib.h"
#include "SqlViewDlg.h"
#include <AfxPriv2.h>
#include <atlbase.h>
#include <comdef.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_DBCLOSE, OnDbclose)
	ON_COMMAND(ID_CONNECT, OnConnect)
	ON_UPDATE_COMMAND_UI(ID_CONNECT, OnUpdateConnect)
	ON_UPDATE_COMMAND_UI(ID_DBCLOSE, OnUpdateDbclose)
	ON_WM_DESTROY()
	ON_CBN_DROPDOWN(IDC_DB_CMB, OnDropdownDbCmb)
	ON_BN_CLICKED(IDC_SELDB_BTN, OnSeldbBtn)
	ON_UPDATE_COMMAND_UI(IDC_SELDB_BTN, OnUpdateSelDB)
	ON_BN_CLICKED(IDC_SEL_MASTER_BTN, OnSelMasterBtn)
	ON_UPDATE_COMMAND_UI(IDC_SEL_MASTER_BTN, OnUpdateSelMaster)
	ON_BN_CLICKED(IDC_REFRESH, OnDBRefresh)
	ON_UPDATE_COMMAND_UI(IDC_REFRESH, OnUpdateDBRefresh)
	ON_UPDATE_COMMAND_UI(IDC_DB_CMB, OnUpdateDBCmb)
	ON_COMMAND(ID_SQL_NEW, OnSqlNew)
	ON_COMMAND(IDM_DBBACKUP, OnDbbackup)
	ON_UPDATE_COMMAND_UI(IDM_DBBACKUP, OnUpdateDbbackup)
	ON_COMMAND(IDM_DBRESTORE, OnDbrestore)
	ON_UPDATE_COMMAND_UI(IDM_DBRESTORE, OnUpdateDbrestore)
	ON_COMMAND(IDM_DBERACER, OnDberacer)
	ON_UPDATE_COMMAND_UI(IDM_DBERACER, OnUpdateDberacer)
	ON_COMMAND(IDM_SQL_CREATE_DB, OnSqlCreateDb)
	ON_UPDATE_COMMAND_UI(IDM_SQL_CREATE_DB, OnUpdateSqlCreateDb)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_UPDATE_COMMAND_UI(ID_REFRESH, OnUpdateRefresh)
	ON_WM_COPYDATA()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_COMMAND(IDM_CONFIG, OnConfig)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(IDM_SQLHIST, OnSqlhist)
	ON_UPDATE_COMMAND_UI(IDM_SQLHIST, OnUpdateSqlhist)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ACTIVATE()
	ON_COMMAND(IDM_MDB_CREATE, OnMdbCreate)
	ON_UPDATE_COMMAND_UI(IDM_MDB_CREATE, OnUpdateMdbCreate)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_STATUSBAR_MSG, OnStatusbarMsg)
	ON_MESSAGE(WM_END_CREATE_SQL, OnEndCreateSql)
	ON_MESSAGE(WM_END_THREAD, OnEndThread)
	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ステータス ライン インジケータ
	ID_INDICATOR_SEARCH,
	ID_INDICATOR_KANA,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

DWORD WINAPI CMainFrame::SqlCreateProc( LPVOID lpParameter ){
	CMainFrame *pFrm = (CMainFrame*)lpParameter;
	CAdoDatabase *pDB = pFrm->GetDBObject();
	//pDB->SetErrorOut(FALSE);
	
	if(!pDB->IsConnect()){
		pFrm->PostMessage(WM_END_CREATE_SQL, 0, 0);
		return 0;
	}

	//選択されたテーブルを再現するSQLの生成
	int nCnt = pFrm->m_arrSQLTable.GetSize();
	CString strSQL;
	CStringArray arrFields;
	CString strTableName;
	CString strVal;
	CString strSize;
	CString strMsg;
	CString strMsg2;
	int nType;
	int nCnt2;
	_RecordsetPtr rs;
	_variant_t vIndex;
	_variant_t val;
	FieldsPtr fields;
	FieldPtr field;
	CArray<int, int> arrIdentity;
	pFrm->m_strSQLData = "";
	for(int i = 0; i < nCnt; i++){
		strTableName = pFrm->m_arrSQLTable.GetAt(i);
		strMsg.Format("(%d/%d) %s テーブルの SQL生成中", i + 1, nCnt, strTableName);
		pFrm->SendMessage(WM_STATUSBAR_MSG, 1, (LPARAM)(LPCTSTR)strMsg);

		strSQL.Format("SELECT * FROM %s", strTableName);
	
		rs = pDB->ExecSQL(strSQL);
		if(rs == NULL){
			CString strErr = pDB->GetError();
			if(!strErr.IsEmpty()){
				strMsg.Format("Error : %s", strErr);
				pFrm->SendMessage(WM_STATUSBAR_MSG, 1, (LPARAM)(LPCTSTR)strMsg);
			}
			continue;
		}

#ifdef _DEBUG
		LONG lRsCnt = rs->Properties->GetCount();
		for(int nLoopRS = 0; nLoopRS < lRsCnt; nLoopRS++){
			vIndex = (short)(nLoopRS);
			BSTR bstrName = rs->Properties->GetItem(vIndex)->GetName();
			_variant_t val = rs->Properties->GetItem(vIndex)->GetValue();

			CString strName;
			AfxBSTR2CString(&strName, bstrName);
			if(val.vt != VT_NULL){
				val.ChangeType(VT_BSTR);
				CString strVal;
				AfxBSTR2CString(&strVal, val.bstrVal);
				TRACE("%s\t%s\n", strName, strVal);
			}else{
				TRACE("%s\n", strName);
			}
		}
#endif		
		//Fieldsオブジェクトの取得
		fields = rs->GetFields();
		if(fields == NULL){
			continue;
		}
		nCnt2 = fields->GetCount();

		strSQL = "CREATE TABLE " + strTableName + "(";
		arrIdentity.RemoveAll();
		arrFields.RemoveAll();
		for(int j = 0; j < nCnt2; j++){
			strMsg2.Format("%s 処理カラム %d/%d", strMsg, j + 1, nCnt2);
			pFrm->SendMessage(WM_STATUSBAR_MSG, 0, (LPARAM)(LPCTSTR)strMsg2);
			if(j != 0){
				strSQL += ",\r\n\t";
			}else{
				strSQL += "\r\n\t";
			}
			vIndex = (short)(j);
			field = fields->GetItem(&vIndex);

			if(field == NULL){
				continue;
			}
			//カラム名
			val = field->GetName();
			if((val.vt == VT_NULL) || (val.vt == VT_EMPTY)){
				strVal = "";
			}else{
				AfxBSTR2CString(&strVal, val.bstrVal);
			}

			if(pDB->IsReserve(strVal)){
				strSQL += "[" + strVal + "]\t";
			}else{
				strSQL += strVal + "\t";
			}
			arrFields.Add(strVal);
			
			//サイズ
			try{
 				strSize.Format("%d", field->DefinedSize);
			}catch(_com_error e){
				strSize = "0";
			}catch(...){
				strSize = "0";
			}

			//型
//			if(strlen(pColInfo->szTypeName)){
//				strVal = pColInfo->szTypeName;
//			}else{
				nType = field->Type;
				GetDBColumType(strVal, nType, strSize);
//			}

			strSQL += strVal;
			strSQL += "\t";

			//IsNUll
			if((field->Attributes & adFldIsNullable) || pFrm->m_bIgnoreNotNull){
				strSQL += "NULL ";
			}else{
				strSQL += "NOT NULL ";
			}
			
			//IDENTITY指定
			arrIdentity.Add(0);
			if(!pFrm->m_bIgnoreIdentity){
				val = field->Properties->GetItem("ISAUTOINCREMENT")->GetValue();
				if((val.vt == VT_BOOL) && (val.boolVal != 0)){
					strSQL += " IDENTITY";
					arrIdentity.SetAt(j, 1);
				}
			}

			//キーカラム？
			val = field->Properties->GetItem("KEYCOLUMN")->GetValue();
			if((val.vt == VT_BOOL) && (val.boolVal != 0)){
				strSQL += " PRIMARY KEY NONCLUSTERED";
			}

#ifdef _DEBUG
			//プロパティの列挙
			LONG lProCnt = field->Properties->GetCount();
			for(int nLoop = 0; nLoop < lProCnt; nLoop++){
				vIndex = (short)(nLoop);
				BSTR bstrName = field->Properties->GetItem(vIndex)->GetName();
				_variant_t val = field->Properties->GetItem(vIndex)->GetValue();

				CString strName;
				AfxBSTR2CString(&strName, bstrName);

				if(val.vt != VT_NULL){
					val.ChangeType(VT_BSTR);
					CString strVal;
					AfxBSTR2CString(&strVal, val.bstrVal);
					TRACE("%s\t%s\n", strName, strVal);
				}else{
					TRACE("%s\n", strName);
				}
			}
			TRACE("\n");
#endif
		}
		strSQL += ") ";
		pFrm->m_strSQLData += strSQL + "\r\n\r\n";

		//値を再現するSQLを生成する
		int nCntRec = arrFields.GetSize();
		while(rs->EndOfFile == VARIANT_FALSE){
			strSQL = "INSERT INTO " + strTableName + " VALUES(";
			BOOL bFirst = TRUE;
			for(int nValCnt = 0; nValCnt < nCntRec; nValCnt++){
				if(arrIdentity.GetAt(nValCnt) == 1){
					//IDENTITY指定がある場合は、値は設定しない
					continue;
				}
				if(bFirst){
					bFirst = FALSE;
				}else{
					strSQL += ", ";
				}
				_variant_t val = pDB->GetFieldValue(rs, arrFields.GetAt(nValCnt));

				switch(val.vt){
				case VT_NULL:
					strVal = " NULL ";
					break;
				
				case VT_BYREF|VT_I4:
					val.ChangeType(VT_I4);
				case VT_I4:
					strVal.Format("%d", val.lVal);
					break;
				
				case VT_BYREF|VT_UI1:
					val.ChangeType(VT_UI1);
				case VT_UI1:
					strVal.Format("%d", val.bVal);
					break;
				
				case VT_BYREF|VT_I2:
					val.ChangeType(VT_I2);
				case VT_I2:
					strVal.Format("%d", val.iVal);
					break;
				
				case VT_BYREF|VT_R4:
					val.ChangeType(VT_R4);
				case VT_R4:
					strVal.Format("%f", val.fltVal);
					break;
				
				case VT_BYREF|VT_CY:
				case VT_BYREF|VT_R8:
					val.ChangeType(VT_R8);
				case VT_CY:
				case VT_R8:
					strVal.Format("%f", val.dblVal);
					break;
				
				case VT_BYREF|VT_BOOL:
					val.ChangeType(VT_BOOL);
				case VT_BOOL:
					strVal = val.boolVal ? "1" : "0";
					break;
				
				case VT_BYREF|VT_DATE:
					val.ChangeType(VT_DATE);
				case VT_DATE:
					strVal.Format("%d", val.date);
					break;
				
				case VT_BYREF|VT_BSTR:
					val.ChangeType(VT_BSTR);
				case VT_BSTR:
					{
						CString strName;
						AfxBSTR2CString(&strName, val.bstrVal);
						strName.Replace("'", "''");
						strVal.Format("\'%s\'", strName);
					}
					break;
/*
				case VT_BYREF|VT_ERROR:
				case VT_ERROR:
					break;

				case VT_BYREF|VT_UNKNOWN:
					val.ChangeType(VT_UNKNOWN);
				case VT_UNKNOWN:
					{
						IUnknown *iUnknown = val.punkVal;
					}
					break;
				
				case VT_BYREF|VT_DISPATCH:
					val.ChangeType(VT_DISPATCH);
				case VT_DISPATCH:
					{
						IDispatch *iDisp = val.pdispVal;
					}
					break;

				case VT_BYREF|VT_VARIANT:
					LPVARIANT pVal = val.pvarVal;
					break;
*/
				case VT_EMPTY:
				default:
					strVal = "";
					break;
				}

				strSQL += strVal;
			}
			strSQL += ")";
			pFrm->m_strSQLData += strSQL + "\r\n\r\n";
			rs->MoveNext();
		}
		rs->Close();
	}

	//ストアドプロシージャを再現する
	if(pFrm->m_bOutProc){
		CString strProcName;
		nCnt = pFrm->m_arrSQLProc.GetSize();
		for(int i = 0; i < nCnt; i++){
			strProcName = pFrm->m_arrSQLProc.GetAt(i);
			strMsg.Format("(%d/%d)ストアドプロシージャ %s 出力中", i, nCnt, strProcName);
			pFrm->SendMessage(WM_STATUSBAR_MSG, 1, (LPARAM)(LPCTSTR)strMsg);

			CString strSql;
			strSql.Format("sp_helptext \'%s\'", strProcName);
			rs = pDB->OpenRecordSet(strSql);
			CString strFunc = "";
			if(rs != NULL){
				//レコードセットの内容をﾃｷｽﾄに
				while(rs->EndOfFile == VARIANT_FALSE){
					val = pDB->GetFieldValue(rs, "Text");
					strFunc = "";
					if((val.vt != VT_NULL) && (val.vt != VT_EMPTY)){
						AfxBSTR2CString(&strFunc, val.bstrVal);
						pFrm->m_strSQLData += strFunc;
					}
					rs->MoveNext();
				}
				pFrm->m_strSQLData += "\r\n\r\n";
			}
			rs->Close();
		}
	}
	pFrm->PostMessage(WM_END_CREATE_SQL, 0, 0);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの構築/消滅

CMainFrame::CMainFrame(){
	// TODO: この位置にメンバの初期化処理コードを追加してください。
	m_bAftConnect = FALSE;
	m_hThreadHandle = NULL;
	m_pThread = NULL;
	m_hSqlThread = NULL;
	m_pOldFocus = NULL;
}

CMainFrame::~CMainFrame(){
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE
		| /*CBRS_GRIPPER |*/ CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED | CBRS_FLOATING) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)){
		TRACE0("Failed to create toolbar\n");
		return -1;      // 作成に失敗
	}

	if (!m_wndDlgBar.Create(this, CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR)){
		TRACE0("Failed to create dialogbar\n");
		return -1;		// 作成に失敗
	}

	if (!m_wndReBar.Create(this, RBS_BANDBORDERS | RBS_AUTOSIZE | RBS_FIXEDORDER)){
		TRACE0("Failed to create rebar\n");
		return -1;      // 作成に失敗
	}

	//256ツールバー
	{
		CToolBarCtrl &objTBCtrl = m_wndToolBar.GetToolBarCtrl();
		objTBCtrl.ModifyStyle(0, CCS_NODIVIDER /*| CCS_NOHILITE*/ ,0);
#if 1
		int nBtnCnt = 12;//ボタンの数
		//ツールバーのイメージリストを初期化
		CImageList* pImgList =m_wndToolBar.GetToolBarCtrl().GetImageList();

		//イメージリストを破棄する。
		pImgList->DeleteImageList();

		//イメージリストを16bit(3,2000色)で生成する。
		//256色のアイコンは16bit以上でないと色化けしてしまします。
		pImgList->Create(16,16, ILC_COLOR16 | ILC_MASK,nBtnCnt,nBtnCnt);
		//ビットマップを読み込む
		CBitmap bmp;
		bmp.LoadBitmap(IDB_TOOLBAR256);

		//イメージリストに追加する。
		//透過色を２番目の引数で設定している。
		pImgList->Add(&bmp,RGB(192, 192, 192));

		//256アイコンをToolBarに割り当てる
		TRY{
			m_wndToolBar.GetToolBarCtrl().SetImageList(pImgList);
		}CATCH_ALL(e){
//			CDebugSupport::OutputDebugLog("256色アイコンの割り当てに失敗");
		}END_CATCH_ALL
		DeleteObject(bmp);
#endif
	}


	CReBarCtrl &objBarCtrl = m_wndReBar.GetReBarCtrl();

	REBARBANDINFO barInfo;
	memset(&barInfo, 0, sizeof(REBARBANDINFO));

	CToolBarCtrl &objTBCtrl = m_wndToolBar.GetToolBarCtrl();
	CSize size;
	objTBCtrl.GetMaxSize(&size);
	int nWidth = size.cx;
	int nHeight = size.cy;

	//ツールバーをリバーに登録
	barInfo.cbSize		= sizeof(REBARBANDINFO);
	barInfo.fMask		= RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_STYLE ;
	barInfo.fStyle		= RBBS_GRIPPERALWAYS | RBBS_CHILDEDGE ;
	barInfo.hwndChild	= m_wndToolBar.m_hWnd;
	barInfo.cxMinChild	= nWidth;
	barInfo.cyMinChild	= nHeight;
	barInfo.cx			= nWidth;
	objBarCtrl.InsertBand(0, &barInfo);

	//アドレスバーをリバーに登録
	barInfo.cbSize		= sizeof(REBARBANDINFO);
	barInfo.fMask		= RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_STYLE | RBBIM_TEXT;
	barInfo.fStyle		= RBBS_CHILDEDGE | RBBS_GRIPPERALWAYS ;
	barInfo.hwndChild	= m_wndDlgBar.m_hWnd;
	barInfo.lpText		= "データベース";
	barInfo.cch			= strlen("データベース");
	barInfo.cxMinChild	= 16;
	barInfo.cyMinChild	= nHeight;
	objBarCtrl.InsertBand(1, &barInfo);
	objBarCtrl.MaximizeBand(1);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // 作成に失敗
	}

	SetInclimentSearch("");

	// TODO: もしツール チップスが必要ない場合、ここを削除してください。
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	if(!m_objDB.Create()){
		AfxMessageBox("データベースの初期化に失敗しました");
		return 1;
	}

	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	MoveWindow(pApp->m_nPosX, pApp->m_nPosY, 
			   pApp->m_nWidth, pApp->m_nHeight);


	SetTimer(IDS_FRM_TIMER, 100, NULL);

	
	CString strLine;
	CStdioFile file;
	TRY{
		CString strHistPath;
		CString strLine;
		strHistPath.Format("%s\\SQLHistory.dat", pApp->m_strBasePath);
		if(IsFileExsist(strHistPath)){
			file.Open(strHistPath, CFile::modeRead);
			while(file.ReadString(strLine)){
				m_arrSQLHistory.InsertAt(m_arrSQLHistory.GetSize(), strLine);
			}
			file.Close();
		}
	}CATCH_ALL(e){
	}END_CATCH_ALL
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して、Window クラスやスタイルを
	//       修正してください。

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame メッセージ ハンドラ


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) {
	CRect rect;
	GetClientRect(rect);
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();

	CRect rectMain;
	CRect rectSubUp;
	CRect rectSubDown;

	rectMain	= rect;
	rectSubUp	= rect;
	rectSubDown	= rect;

	rectMain.right		= rect.Width() / 5 + rect.left;
	rectSubUp.bottom	= rect.Height() / 3 * 2 + rect.top;
	rectSubDown.top		= rectSubUp.bottom;

	//メインのスプリッター
	m_wndSplit.CreateStatic(this, 1,2);

	//サブのスプリッター
	m_wndSubSplit.CreateStatic(&m_wndSplit, 2, 1, 
							   WS_CHILD | WS_VISIBLE | WS_BORDER,
                               m_wndSplit.IdFromRowCol(0,1));

	//メインにビューを追加
	m_wndSplit.CreateView(0, 0, 
						  RUNTIME_CLASS(CDBToolView), 
						  CSize(pApp->m_nLeftPaneWidth, rect.Height()), 
						  pContext);
	m_wndSubSplit.CreateView(0, 0, 
							 RUNTIME_CLASS(CResultView), 
							 CSize(rect.Width() - pApp->m_nLeftPaneWidth, pApp->m_nResultPaneHeight), 
							 pContext);
	m_wndSubSplit.CreateView(1, 0, 
							 RUNTIME_CLASS(CFuncTabView), 
							 CSize(rect.Width() - pApp->m_nLeftPaneWidth, rect.Height() - pApp->m_nResultPaneHeight), 
							 pContext);

	m_wndSplit.ModifyStyleEx(WS_EX_CLIENTEDGE, WS_EX_CONTROLPARENT);
	m_wndSubSplit.ModifyStyleEx(WS_EX_CLIENTEDGE, WS_EX_CONTROLPARENT);

	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

BOOL CMainFrame::ConnectDB(){
	CWaitCursor objCur;
	CLoginDlg objLogin;
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	if(objLogin.DoModal() != IDOK){
		return FALSE;
	}

	if(m_objDB.IsConnect()
	&& !pApp->m_strActiveServer.Compare(objLogin.m_strServer)
	&& !pApp->m_strActiveUser.Compare(objLogin.m_strUser)
	&& !pApp->m_strActiveDB.Compare(objLogin.m_strDBName)){
		//既に接続しているので接続処理は行なわない
		return TRUE;
	}


	pApp->m_strActivePass = objLogin.m_strPassword;
	pApp->m_strActiveServer = objLogin.m_strServer;
	pApp->m_strActiveUser = objLogin.m_strUser;
	pApp->m_strActiveDB = objLogin.m_strDBName;
	m_bAftConnect = FALSE;

	CDocument *pDoc = GetActiveDocument();
	
	eDBType eDbType = UNKNOW;
	switch(objLogin.m_nDBType){
#if defined(NEW_DBTYPE)
	case SQLSERVER_AUTO:
	case SQLSERVER_ODBC:
	case SQLSERVER_OLEDB:
//	case ORACLE_ODBC:
	case ORACLE_OLEDB:
	case ORACLE_MS_ODBC:
	case ORACLE_MS_OLEDB:
	case ODBC_DATASRC:
	case ACCESS_ODBC:
	case ACCESS_OLEDB:
	case DB2_OLEDB:
#else
	case SQLSERVER:
	case ORACLE:
	case ODBC:
	case ACCESS:
#endif
		eDbType = (eDBType)objLogin.m_nDBType;
		break;
	}
	
	switch(objLogin.m_nDBType){
#if defined(NEW_DBTYPE)
	case SQLSERVER_AUTO:
	case SQLSERVER_ODBC:
	case SQLSERVER_OLEDB:
#else
	case SQLSERVER:
#endif
		m_bAftConnect = objLogin.m_bAftDBSel;
		if(m_bAftConnect){
			pApp->m_strActiveDB = "";
		}
#if defined(NEW_DBTYPE)
		if(!m_objDB.ConnectSqlServer(eDbType,
									 pApp->m_strActiveServer,
									 pApp->m_strActiveUser,
									 pApp->m_strActivePass,
									 pApp->m_strActiveDB)
#else
		if(!m_objDB.ConnectSqlServer(pApp->m_strActiveServer,
									 pApp->m_strActiveUser,
									 pApp->m_strActivePass,
									 pApp->m_strActiveDB)
#endif
		){
			CString strErr = m_objDB.GetError();
			SetOutputMsg(strErr);
			return FALSE;
		}
		break;
#if defined(NEW_DBTYPE)
	case ODBC_DATASRC:
#else
	case ODBC:
#endif
		if(!objLogin.m_strOdbcType.Compare("Microsoft")){
			m_objDB.SetODBCType(ODBC_SQLSERVER);
		}else if(!objLogin.m_strOdbcType.Compare("DB2")){
			m_objDB.SetODBCType(ODBC_DB2);
		}else if(!objLogin.m_strOdbcType.Compare("Oracle")){
			m_objDB.SetODBCType(ODBC_ORACLE);
		}else{
			m_objDB.SetODBCType(ODBC_UNKNOW);
		}
#if defined(NEW_DBTYPE)
		if(!m_objDB.ConnectODBC( eDbType,
								 pApp->m_strActiveServer,
								 pApp->m_strActiveUser,
								 pApp->m_strActivePass,
								 pApp->m_strActiveDB)
#else
		if(!m_objDB.ConnectODBC( pApp->m_strActiveServer,
								 pApp->m_strActiveUser,
								 pApp->m_strActivePass,
								 pApp->m_strActiveDB)
#endif
		){
			CString strErr = m_objDB.GetError();
			SetOutputMsg(strErr);
			return FALSE;
		}
		break;

#if defined(NEW_DBTYPE)
//	case ORACLE_ODBC:
	case ORACLE_OLEDB:
	case ORACLE_MS_ODBC:
	case ORACLE_MS_OLEDB:
#else
	case ORACLE:
#endif
#if defined(NEW_DBTYPE)
		if(!m_objDB.ConnectOracle( eDbType,
								   pApp->m_strActiveServer,
								   pApp->m_strActiveUser,
								   pApp->m_strActivePass)
#else
		if(!m_objDB.ConnectOracle( pApp->m_strActiveServer,
								   pApp->m_strActiveUser,
								   pApp->m_strActivePass)
#endif
		){
			CString strErr = m_objDB.GetError();
			SetOutputMsg(strErr);
			return FALSE;
		}
		break;

#if defined(NEW_DBTYPE)
	case ACCESS_ODBC:
	case ACCESS_OLEDB:
#else
	case ACCESS:
#endif
#if defined(NEW_DBTYPE)
		if(!m_objDB.ConnectAccess( eDbType, pApp->m_strActiveDB, pApp->m_strActiveUser, pApp->m_strActivePass)){
#else
		if(!m_objDB.ConnectAccess( pApp->m_strActiveDB, pApp->m_strActiveUser, pApp->m_strActivePass)){
#endif
			CString strErr = m_objDB.GetError();
			SetOutputMsg(strErr);
			return FALSE;
		}
		break;
#if defined(NEW_DBTYPE)
	case DB2_OLEDB:
		if(!m_objDB.ConnectDB2( eDbType, pApp->m_strActiveDB, pApp->m_strActiveUser, pApp->m_strActivePass)){
			CString strErr = m_objDB.GetError();
			SetOutputMsg(strErr);
			return FALSE;
		}
		break;
#endif
	}
	pDoc->UpdateAllViews(NULL, DB_OPEN);
	GetActiveDocument()->SetTitle("");

	if(m_bAftConnect){
		UpdateDataInfo();
	}else{
		GetActiveDocument()->SetTitle(objLogin.m_strDBName);
	}
	
	CString strMsg = "接続が完了しました";
	SetOutputMsg(strMsg);
	return TRUE;
}

void CMainFrame::OnConnect(){
	CButton *pRefBtn = (CButton*)m_wndDlgBar.GetDlgItem(IDC_REFRESH);
	if(ConnectDB()){
		pRefBtn->EnableWindow(TRUE);
	}else{
		pRefBtn->EnableWindow(FALSE);
	}
	pRefBtn->InvalidateRect(NULL);
}

void CMainFrame::OnDbclose(){
	CDocument *pDoc = GetActiveDocument();
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	pApp->m_strActiveDB.Empty();
	pApp->m_strActivePass.Empty();
	pApp->m_strActiveServer.Empty();
	pApp->m_strActiveUser.Empty();
	if(m_objDB.Close()){
		pDoc->UpdateAllViews(NULL, DB_CLOSE);
		CString strMsg = "切断しました。";
		SetOutputMsg(strMsg);

		GetActiveDocument()->SetTitle("切断");

	}else{
		CString strMsg = m_objDB.GetError();
		SetOutputMsg(strMsg);
	}
}

void CMainFrame::OnUpdateConnect(CCmdUI* pCmdUI){
	if(::WaitForSingleObject(m_hThreadHandle, 0) != WAIT_OBJECT_0){
		pCmdUI->Enable(!m_objDB.IsConnect());
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateDbclose(CCmdUI* pCmdUI){
	if(::WaitForSingleObject(m_hThreadHandle, 0) != WAIT_OBJECT_0){
		pCmdUI->Enable(m_objDB.IsConnect());
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnDestroy() {
	CRect rect;
	GetWindowRect(rect);
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	pApp->m_nPosX = rect.left;
	pApp->m_nPosY = rect.top;
	pApp->m_nWidth = rect.Width();
	pApp->m_nHeight = rect.Height();

	if(m_hSqlThread){
		::TerminateThread(m_hSqlThread, 0);
		m_hSqlThread = NULL;
	}
	if(m_hThreadHandle){
		::TerminateThread(m_hThreadHandle, 0);
		m_hThreadHandle = NULL;
	}

	if(m_objDB.IsConnect()){
		m_objDB.Close();
		pApp->m_strActiveDB.Empty();
		pApp->m_strActivePass.Empty();
		pApp->m_strActiveUser.Empty();
		pApp->m_strActiveServer.Empty();
	}

	CFrameWnd::OnDestroy();
}

CAdoDatabase* CMainFrame::GetDBObject(){
	return &m_objDB;

}

void CMainFrame::OnDropdownDbCmb(){
//	UpdateDataInfo();
}

void CMainFrame::OnUpdateSelDB(CCmdUI* pCmdUI){

	if(m_bAftConnect && !m_pThread && !m_hSqlThread){
		pCmdUI->Enable(m_objDB.IsConnect());
	}else{
		pCmdUI->Enable(FALSE);
	}

	//ビューの状態を設定する
	CDBToolView *pDBToolView = (CDBToolView*)m_wndSplit.GetPane(0, 0);
	CResultView *pResultView = (CResultView*)m_wndSubSplit.GetPane(0, 0);
	CFuncTabView *pFuncTabView = (CFuncTabView*)m_wndSubSplit.GetPane(1, 0);
	if(!m_pThread && !m_hSqlThread){
		pDBToolView->EnableTree(TRUE);
		pResultView->EnableList(TRUE);
		pFuncTabView->EnableSQLEdit(TRUE);
	}else{
		pDBToolView->EnableTree(FALSE);
		pResultView->EnableList(FALSE);
		pFuncTabView->EnableSQLEdit(FALSE);
	}
}

void CMainFrame::OnSeldbBtn(){
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	if(!m_objDB.IsConnect()){
		return;
	}

	CComboBox *pCmb = (CComboBox*)m_wndDlgBar.GetDlgItem(IDC_DB_CMB);
	int nIndex = pCmb->GetCurSel();
	if(nIndex == CB_ERR ){
		return;
	}


	CString strDBName;
	pCmb->GetLBText(nIndex, strDBName);
	if(!pApp->m_strActiveDB.Compare(strDBName)){
		return;
	}

	CString strSQL;
	strSQL.Format("USE %s", strDBName);
	m_objDB.ExecSQL(strSQL);
	CString strErr = m_objDB.GetError();
	if(strErr.IsEmpty()){
		GetActiveDocument()->SetTitle(strDBName);
		GetActiveDocument()->UpdateAllViews(NULL, DB_OPEN);
		CString strMsg;
		pApp->m_strActiveDB = strDBName;
		strMsg.Format("データベース %s に接続しました。", strDBName);
		SetOutputMsg(strMsg);
	}else{
		GetActiveDocument()->SetTitle("");
		SetOutputMsg(strErr);
	}
}

void CMainFrame::OnUpdateSelMaster(CCmdUI* pCmdUI){
	if(m_bAftConnect && !m_pThread && !m_hSqlThread){
		pCmdUI->Enable(m_objDB.IsConnect());
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnSelMasterBtn(){
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	if(!m_objDB.IsConnect()){
		return;
	}

	CComboBox *pCmb = (CComboBox*)m_wndDlgBar.GetDlgItem(IDC_DB_CMB);
	int nIndex = pCmb->FindStringExact(-1, "master");
	if(nIndex == CB_ERR){
		return;
	}
	pCmb->SetCurSel(nIndex);
	
	if(!pApp->m_strActiveDB.Compare("master")){
		return;
	}
	pApp->m_strActiveDB = "master";

	nIndex = pCmb->GetCurSel();
	CString strSelDBName;
	if(nIndex != CB_ERR){
		pCmb->GetLBText(nIndex, strSelDBName);
	}

	CString strDBName = "master";
	if(!strSelDBName.CompareNoCase(strDBName)){
		return;
	}

	CString strSQL;
	strSQL.Format("USE %s", strDBName);
	m_objDB.ExecSQL(strSQL);
	CString strErr = m_objDB.GetError();
	if(strErr.IsEmpty()){
		GetActiveDocument()->SetTitle(strDBName);
		GetActiveDocument()->UpdateAllViews(NULL, DB_OPEN);
		CString strMsg;
		strMsg.Format("データベース %s に接続しました。", strDBName);
		SetOutputMsg(strMsg);
	}else{
		GetActiveDocument()->SetTitle("");
		SetOutputMsg(strErr);
	}
}

void CMainFrame::OnUpdateDBRefresh(CCmdUI* pCmdUI){
	if(m_bAftConnect && !m_pThread && !m_hSqlThread){
		pCmdUI->Enable(m_objDB.IsConnect());
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnDBRefresh(){
	OnRefresh();
}

void CMainFrame::OnUpdateDBCmb(CCmdUI* pCmdUI){
	if(m_bAftConnect && !m_pThread && !m_hSqlThread){
		pCmdUI->Enable(m_objDB.IsConnect());
	}else{
		pCmdUI->Enable(FALSE);
	}
}

DWORD WINAPI CMainFrame::LoadDBDlgThread(LPVOID lpParameter){
	return 0;
}

DWORD WINAPI CMainFrame::LoadDBListThread(LPVOID lpParameter){
	PTHREADINFO pInfo = (PTHREADINFO)lpParameter;
	CMainFrame *pWnd = (CMainFrame*)pInfo->pWnd;
	if(!pWnd->m_bAftConnect){
		return 0;
	}

	//データベース一覧を取得し反映する
	SetOutputMsg(pWnd->m_hWnd, "データベース一覧を取得しています。");
	CComboBox *pCmb = (CComboBox*)pWnd->m_wndDlgBar.GetDlgItem(IDC_DB_CMB);
	if(pCmb == NULL){
		pWnd->PostMessage(WM_END_THREAD);
		return 0;
	}


	int nIndex = pCmb->GetCurSel();
	CString strPreDBName;
	if(nIndex != -1){
		pCmb->GetLBText(nIndex, strPreDBName);
	}

	pCmb->ResetContent();

	pCmb->EnableWindow(FALSE);

	CAdoDatabase *pDB = pWnd->GetDBObject();

	if(pWnd == NULL){
		SetOutputMsg(pWnd->m_hWnd, "データベースの一覧の取得に失敗しました。");
		pWnd->PostMessage(WM_END_THREAD);
		return 0;	
	}

	_RecordsetPtr rs = pWnd->m_objDB.GetDatabases();

	if(rs == NULL){
		CString strErr = pDB->GetError();
		SetOutputMsg(pWnd->m_hWnd, strErr);
		pWnd->PostMessage(WM_END_THREAD);
		return 0;
	}

	_variant_t vt;
	CString strDBName;
	CString strMsg;
	while(rs->EndOfFile == VARIANT_FALSE){
		vt = pDB->GetFieldValue(rs, "DATABASE_NAME");
		if(vt.vt != VT_NULL){
			strDBName = vt.bstrVal;
			strMsg.Format("データベース %s を登録", strDBName);
			SetOutputMsg(pWnd->m_hWnd, strMsg);
			pCmb->AddString(strDBName);
		}
		rs->MoveNext();
	}
	rs->Close();

	if(nIndex != -1){
		pCmb->SelectString(0, strPreDBName);
	}
	pCmb->EnableWindow(TRUE);

	SetOutputMsg(pWnd->m_hWnd, "データベース一覧を取得しました。");
	pWnd->PostMessage(WM_END_THREAD);
	return 0;
}

void CMainFrame::UpdateDataInfo(){
	//更新スレッドの起動
	if(!m_hThreadHandle){
		try{
			m_pThread = new THREADINFO;
			memset(m_pThread, 0, sizeof(THREADINFO));
			// スレッドのセキュリティ属性
			SECURITY_ATTRIBUTES		sa ;
			sa.nLength              = sizeof( sa ) ;
			sa.lpSecurityDescriptor = NULL ;
			sa.bInheritHandle       = TRUE ;

			DWORD dwId;
			m_pThread->pWnd = this;
			m_pThread->pFrm = this;
			m_pThread->pDoc = GetActiveDocument();
			m_hThreadHandle = CreateThread(&sa,
										   0,
										   LoadDBListThread,
										   (LPVOID)m_pThread,
										   0,
										   &dwId);
			if(!m_hThreadHandle){
				//スレッド作成失敗
				DWORD dwError = GetLastError();
				CString strErr = CDebugSupport::GetLastErrorText(dwError);
				CString strMsg;
				strMsg.Format(IDS_OUT_ERR_THREAD_CREATE, strErr); 
				SetOutputMsg(strMsg);
			}
		}catch(char *pszErr){
			//スレッド作成失敗
			CString strMsg;
			strMsg.Format(IDS_OUT_ERR_THREAD_CREATE, pszErr); 
			SetOutputMsg(strMsg);
			delete pszErr;
			m_hThreadHandle = NULL;
		}catch(...){
			//スレッド作成失敗
			SetOutputMsg(IDS_OUT_ERR_THREAD_CREATE2);
			m_hThreadHandle = NULL;
		}
	}

}

void CMainFrame::OnSqlNew(){
	GetActiveDocument()->UpdateAllViews(NULL, DB_SQLNEW, NULL);	
}

void CMainFrame::OnDbbackup(){
	CDBBackupDlg objDlg;
	objDlg.m_strBackupName = GetActiveDocument()->GetTitle();
	if(objDlg.DoModal() != IDOK){
		return;
	}

	//バックアップファイルを生成
	CString strMsg;
	WIN32_FIND_DATA wfd;
	HANDLE hRet = ::FindFirstFile(objDlg.m_strBackupPath, &wfd);
	if(hRet != INVALID_HANDLE_VALUE){
		::FindClose(hRet);
		CString strBkName;
		strBkName.Format("%s.bak", objDlg.m_strBackupPath);
		CopyFile(objDlg.m_strBackupPath, strBkName, TRUE);
	}

	CString strSQL;
	strSQL.Format("BACKUP DATABASE %s TO DISK='%s'",
				  objDlg.m_strDBName,
				  objDlg.m_strBackupPath);
	
	strMsg.Format("\r\nデータベース %s をバックアップします\r\n", objDlg.m_strDBName);
	SetOutputMsg(strMsg);
	
	strMsg.Format(IDS_OUT_MSG_SQL, strSQL);
	SetOutputMsg(strMsg);

	m_objDB.ExecSQL(strSQL);
	CString strErr = m_objDB.GetError();
	if(strErr.IsEmpty()){
		UpdateDataInfo();
		strMsg.Format("%s のバックアップを完了しました。", objDlg.m_strDBName); 
		SetOutputMsg(strMsg);
	}else{
		SetOutputMsg(strErr);
		strMsg.Format("%s のバックアップに失敗しました。", objDlg.m_strDBName); 
		SetOutputMsg(strMsg);
	}

}

void CMainFrame::OnDbrestore(){
	CDBRestoreDlg objDlg;
	if(objDlg.DoModal() != IDOK){
		return;
	}


	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	char szName[MAX_PATH];
	char szExit[MAX_PATH];
	_splitpath(objDlg.m_strBackupPath, szDrv, szDir, szName, szExit);
	CString strCopyPath;
	CString strRestore;
	CString strLdf;
	strCopyPath.Format("%s\\%s%s", objDlg.m_strRestorePath, objDlg.m_strDBName, szExit);
	strRestore.Format("%s\\%s.mdf", objDlg.m_strRestorePath, objDlg.m_strDBName);
	strLdf.Format("%s\\%s.ldf", objDlg.m_strRestorePath, objDlg.m_strDBName);

	CopyFile(objDlg.m_strBackupPath, strCopyPath, TRUE);

	CString strSQL;
	strSQL.Format("RESTORE DATABASE %s "
				  "FROM DISK='%s' "
				  "WITH REPLACE, "
				  "MOVE '%s' TO '%s',"
				  "MOVE '%s_log' TO '%s'",
				  objDlg.m_strDBName,
				  strCopyPath,
				  objDlg.m_strDBName,
				  strRestore,
				  objDlg.m_strDBName,
				  strLdf);
	
	CString strMsg;

	strMsg.Format("\r\n%s を復元します\r\n", objDlg.m_strDBName);
	SetOutputMsg(strMsg);
	
	strMsg.Format(IDS_OUT_MSG_SQL, strSQL);
	SetOutputMsg(strMsg);
	m_objDB.ExecSQL(strSQL);
	CString strErr = m_objDB.GetError();
	if(strErr.IsEmpty()){
		UpdateDataInfo();
		strMsg.Format("%s の復元を完了しました。", objDlg.m_strDBName); 
		SetOutputMsg(strMsg);
	}else{
		SetOutputMsg(strErr);
		strMsg.Format("%s の復元に失敗しました。", objDlg.m_strDBName); 
		SetOutputMsg(strMsg);
	}

	::DeleteFile(strCopyPath);
}

void CMainFrame::OnDberacer(){
	CDBErasureDlg objDlg;

	CComboBox *pCmb = (CComboBox*)m_wndDlgBar.GetDlgItem(IDC_DB_CMB);
	if(pCmb == NULL){
		return;
	}

	CString strLbl;
	for(int i = 0; i < pCmb->GetCount(); i++){
		pCmb->GetLBText(i, strLbl);
		objDlg.m_arrDBNames.Add(strLbl);
	}

	objDlg.m_pDB = &m_objDB;
	if(objDlg.DoModal() != IDOK){
		return;
	}

	CString strMsg;
	int nMax = objDlg.m_arrDBNames.GetSize();
	CString strSQL;
	CString strDBName;
	for(int j = 0; j < nMax; j++){
		strDBName = objDlg.m_arrDBNames.GetAt(j);
		strMsg.Format("\r\nデータベース %s を削除します\r\n", strDBName);
		SetOutputMsg(strMsg);

		strSQL.Format("DROP DATABASE %s", strDBName);
		strMsg.Format(IDS_OUT_MSG_SQL, strSQL);
		SetOutputMsg(strMsg);
		m_objDB.ExecSQL(strSQL);

		CString strErr = m_objDB.GetError();
		if(!strErr.IsEmpty()){
			SetOutputMsg(strErr);
		}
	}
	UpdateDataInfo();
}

void CMainFrame::OnSqlCreateDb(){
	if(!m_objDB.IsConnect()){
		return;
	}

	_RecordsetPtr rs = m_objDB.GetTables();
	if((rs == NULL) || (rs->GetRecordCount() == 0)){
		return;
	}

	_variant_t val;
	CString strTableName;
	CRestorSQLDlg objDlg;
	if(rs){
		while(rs->EndOfFile == VARIANT_FALSE){
			val = m_objDB.GetFieldValue(rs, "TABLE_NAME");
			if(val.vt != VT_NULL){
				AfxBSTR2CString(&strTableName, val.bstrVal);
				PTABLEINFO pInfo = m_objDB.GetTableInfo(strTableName);
				if(pInfo->nType == T_TABLE){
					objDlg.m_arrTables.Add(strTableName);
				}
			}
			rs->MoveNext();
		}
		rs->Close();
	}

	_RecordsetPtr procRs = m_objDB.GetProcedures();
	if(procRs){
		_variant_t name;
		CString strProcName;
		while(procRs->EndOfFile == VARIANT_FALSE){
			name = m_objDB.GetFieldValue(procRs, "name");
			if((name.vt != VT_NULL) && (name.vt != VT_EMPTY)){
				AfxBSTR2CString(&strProcName, name.bstrVal);
				objDlg.m_arrProcs.Add(strProcName);
			}
			procRs->MoveNext();
		}
	}

	if(objDlg.DoModal() != IDOK){
		return;
	}
	m_bIgnoreIdentity = objDlg.m_bIgnoreIdentity;
	m_bIgnoreNotNull = objDlg.m_bIgnoreNotNull;
	m_bOutProc = objDlg.m_bOutProc;

	m_arrSQLTable.RemoveAll();
	m_arrSQLTable.Append(objDlg.m_arrTables);

	m_arrSQLProc.RemoveAll();
	if(m_bOutProc){
		m_arrSQLProc.Append(objDlg.m_arrProcs);
	}

	if(!m_hSqlThread){
		m_hSqlThread = ::CreateThread(NULL, 0, SqlCreateProc, this, 0, 0);
	}
}

void CMainFrame::OnRefresh(){
	GetActiveDocument()->UpdateAllViews(NULL, DB_REFRESH, NULL);
	UpdateDataInfo();
}

void CMainFrame::OnUpdateDbbackup(CCmdUI* pCmdUI){
	if(::WaitForSingleObject(m_hThreadHandle, 0) != WAIT_OBJECT_0){
		eDBType dbType = m_objDB.GetDBType();
		eODBCType odbcType = m_objDB.GetODBCType();
#if defined(NEW_DBTYPE)
		if((dbType == ODBC_DATASRC) && (odbcType == ODBC_SQLSERVER)
		|| (dbType == SQLSERVER_ODBC) || (dbType == SQLSERVER_OLEDB) || (dbType == SQLSERVER_AUTO)){
#else
		if((dbType == ODBC) && (odbcType == ODBC_SQLSERVER)
		|| (dbType == SQLSERVER)){
#endif
			CString strName = GetActiveDocument()->GetTitle();
			if(m_objDB.IsConnect()){
				if(strName.IsEmpty() 
				|| !strName.Compare("切断")
				|| !strName.Compare("master")
				|| !strName.Compare("model")
				|| !strName.Compare("msdb")
				|| !strName.Compare("tempdb")
				){
					pCmdUI->Enable(FALSE);
				}else{
					pCmdUI->Enable(TRUE);
				}
			}else{
				pCmdUI->Enable(FALSE);
			}
		}else{
			pCmdUI->Enable(FALSE);
		}
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateDbrestore(CCmdUI* pCmdUI){
	if(::WaitForSingleObject(m_hThreadHandle, 0) != WAIT_OBJECT_0){
		eDBType dbType = m_objDB.GetDBType();
		eODBCType odbcType = m_objDB.GetODBCType();
#if defined(NEW_DBTYPE)
		if((dbType == ODBC_DATASRC) && (odbcType == ODBC_SQLSERVER)
		|| (dbType == SQLSERVER_ODBC) || (dbType == SQLSERVER_OLEDB) || (dbType == SQLSERVER_AUTO)){
#else
		if((dbType == ODBC) && (odbcType == ODBC_SQLSERVER)
		|| (dbType == SQLSERVER)){
#endif
			if(m_hThreadHandle || m_hSqlThread){
				pCmdUI->Enable(FALSE);
			}else{
				pCmdUI->Enable(m_objDB.IsConnect());
			}
		}else{
			pCmdUI->Enable(FALSE);
		}
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateDberacer(CCmdUI* pCmdUI){
	if(::WaitForSingleObject(m_hThreadHandle, 0) != WAIT_OBJECT_0){
		eDBType dbType = m_objDB.GetDBType();
		eODBCType odbcType = m_objDB.GetODBCType();
#if defined(NEW_DBTYPE)
		if((dbType == ODBC_DATASRC) && (odbcType == ODBC_SQLSERVER)
		|| (dbType == SQLSERVER_ODBC) || (dbType == SQLSERVER_OLEDB) || (dbType == SQLSERVER_AUTO)){
#else
		if((dbType == ODBC) && (odbcType == ODBC_SQLSERVER)
		|| (dbType == SQLSERVER)){
#endif
			if(m_hThreadHandle || m_hSqlThread){
				pCmdUI->Enable(FALSE);
			}else{
				pCmdUI->Enable(m_objDB.IsConnect());
			}
		}else{
			pCmdUI->Enable(FALSE);
		}
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateSqlCreateDb(CCmdUI* pCmdUI){
	if(::WaitForSingleObject(m_hThreadHandle, 0) != WAIT_OBJECT_0){
		eDBType dbType = m_objDB.GetDBType();
		eODBCType odbcType = m_objDB.GetODBCType();
#if defined(NEW_DBTYPE)
		if((dbType == ODBC_DATASRC) && (odbcType == ODBC_SQLSERVER)
		|| (dbType == SQLSERVER_ODBC) || (dbType == SQLSERVER_OLEDB) || (dbType == SQLSERVER_AUTO)){
#else
		if((dbType == ODBC) && (odbcType == ODBC_SQLSERVER)
		|| (dbType == SQLSERVER)){
#endif
			if(m_hThreadHandle || m_hSqlThread){
				pCmdUI->Enable(FALSE);
			}else{
				pCmdUI->Enable(m_objDB.IsConnect());
			}
		}else{
			pCmdUI->Enable(FALSE);
		}
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateRefresh(CCmdUI* pCmdUI){
	if(::WaitForSingleObject(m_hThreadHandle, 0) != WAIT_OBJECT_0){
		eDBType dbType = m_objDB.GetDBType();
		eODBCType odbcType = m_objDB.GetODBCType();
#if defined(NEW_DBTYPE)
		if((dbType == ODBC_DATASRC) && (odbcType == ODBC_SQLSERVER)
		|| (dbType == SQLSERVER_ODBC) || (dbType == SQLSERVER_OLEDB) || (dbType == SQLSERVER_AUTO)){
#else
		if((dbType == ODBC) && (odbcType == ODBC_SQLSERVER)
		|| (dbType == SQLSERVER)){
#endif
			if(m_pThread || m_hSqlThread){
				pCmdUI->Enable(FALSE);
			}else{
				pCmdUI->Enable(m_objDB.IsConnect());
			}
		}else{
			pCmdUI->Enable(FALSE);
		}
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::SetOutputMsg(LPCTSTR pszMsg){
	CString strMsg = pszMsg;
	CView *pView = (CView*)m_wndSubSplit.GetPane(0, 0);
	GetActiveDocument()->UpdateAllViews(pView, DB_ADDMSG, (CObject*)&strMsg);
	SetStatusbarMsg(strMsg);
}

void CMainFrame::SetOutputMsg(UINT nID){
	CString strMsg;
	strMsg.LoadString(nID);
	SetOutputMsg(strMsg);
}

void CMainFrame::SetOutputMsg(HWND hWnd, LPCTSTR pszText){
	COPYDATASTRUCT cds;
	memset(&cds, 0, sizeof(COPYDATASTRUCT));
	int nLen = strlen(pszText) + 1;
	char *szText = new char[nLen];
	memset(szText, 0, nLen);
	strcpy(szText, pszText);
	szText[nLen - 1] = '\0';
	cds.dwData = DB_ADDMSG;
	cds.cbData = nLen;
	cds.lpData = szText;
	::SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&cds);
	delete szText;
}

void CMainFrame::SetOutputMsg(HWND hWnd, UINT nID){
	CString strMsg;
	strMsg.LoadString(nID);
	
	COPYDATASTRUCT cds;
	memset(&cds, 0, sizeof(COPYDATASTRUCT));
	int nLen = strMsg.GetLength() + 1;
	char *szText = new char[nLen];
	memset(szText, 0, nLen);
	strcpy(szText, strMsg.GetBuffer(nLen - 1));
	szText[nLen - 1] = '\0';
	cds.dwData = DB_ADDMSG;
	cds.cbData = nLen;
	cds.lpData = szText;
	::SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&cds);
	delete szText;
}


BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct){
	switch(pCopyDataStruct->dwData){
	case DB_ADDMSG:
		{
			CString strMsg = (LPCTSTR)pCopyDataStruct->lpData;
			SetOutputMsg(strMsg);
		}
		break;
	}

	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

BOOL CMainFrame::CheckViewThread(){
	CDBToolView		*pView1	= (CDBToolView*)m_wndSplit.GetPane(0, 0);
	CResultView		*pView2	= (CResultView*)m_wndSubSplit.GetPane(0, 0);
	CFuncTabView	*pView3	= (CFuncTabView*)m_wndSubSplit.GetPane(1, 0);

	if(m_hThreadHandle){
		SetOutputMsg("現在、スレッド処理中です\n");
		//スレッド起動中
		return FALSE;
	}

	if(pView2->m_hThreadHandle){
		SetOutputMsg("現在、スレッド処理中です\n");
		//スレッド起動中
		return FALSE;
	}
	return TRUE;
}

void CMainFrame::OnTimer(UINT nIDEvent) {
	if(nIDEvent != IDS_FRM_TIMER){
		return;
	}
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnClose(){
	//SQLをチェックする
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	CFuncTabView *pView = (CFuncTabView*)m_wndSubSplit.GetPane(1,0);
	if(pView->CheckSaveSQL()){
		//終了

		int nSize = m_arrSQLHistory.GetSize();
		CString strLine;
		CStdioFile file;
		TRY{
			CString strHistPath;
			CString strLine;
			strHistPath.Format("%s\\SQLHistory.dat", pApp->m_strBasePath);
			file.Open(strHistPath, CFile::modeCreate | CFile::modeWrite);
			for(int i = 0; i < nSize; i++){
				strLine = m_arrSQLHistory.GetAt(i);
				file.WriteString(strLine);
				file.WriteString("\n");
			}
			file.Flush();
			file.Close();
		}CATCH_ALL(e){
		}END_CATCH_ALL
		GetActiveDocument()->UpdateAllViews(NULL, DB_CLOSEWND, NULL);
		CFrameWnd::OnClose();
	}
}



void CMainFrame::OnConfig(){
	CConfDlg cnfDlg;
	if(cnfDlg.DoModal() != IDOK){
		return;
	}
}

void CMainFrame::SetInclimentSearch(LPCTSTR pszText){
	CString strText = pszText;
	CString strOutText;
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_SEARCH);
	if(strText.IsEmpty()){
		m_wndStatusBar.SetPaneText(nIndex, "", TRUE);
	}else{
		strOutText.Format("Search : %s", strText);
		m_wndStatusBar.SetPaneText(nIndex, strOutText, TRUE);
	}
}

void CMainFrame::SetStatusbarMsg(LPCTSTR pszText){
	CString strText = pszText;
	if(strText.IsEmpty()){
		m_wndStatusBar.SetPaneText(0, "", TRUE);
	}else{
		m_wndStatusBar.SetPaneText(0, strText, TRUE);
	}
}

void CMainFrame::OnHelp(){
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	CString strHelpPath;
	strHelpPath.Format("%s\\SDT.chm", pApp->m_strBasePath);
	::ShellExecute(m_hWnd, "open", strHelpPath, NULL, pApp->m_strBasePath, SW_SHOWNORMAL);	
}

//SQL履歴に追加
bool CMainFrame::AddSQLHistory(LPCTSTR pszSQL){
	CString strSQL = pszSQL;
	TRY{
		strSQL.Replace("\r\n", " ");
		strSQL.Replace("\n", " ");
		m_arrSQLHistory.InsertAt(m_arrSQLHistory.GetSize(), strSQL);
		while(m_arrSQLHistory.GetSize() > 100){
			m_arrSQLHistory.RemoveAt(m_arrSQLHistory.GetSize() - 1);
		}
	}CATCH_ALL(e){
		return FALSE;
	}END_CATCH_ALL
	return TRUE;
}

void CMainFrame::OnSqlhist(){
	CSQLHistDlg sqlHistDlg;
	if(sqlHistDlg.DoModal() == IDCANCEL){
	
	}
	
}

void CMainFrame::OnUpdateSqlhist(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	
}

void CMainFrame::SaveSQLHist(){
	TRY{
		int nSize = m_arrSQLHistory.GetSize();
		CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
		CString strHistData;
		strHistData.Format("%s\\sqlhist.dat", pApp->m_strBasePath);
		CStdioFile file(strHistData, CFile::modeCreate | CFile::modeWrite);
		for(int i = 0; i < nSize; i++){
			file.WriteString(m_arrSQLHistory.GetAt(i));
		}
		file.Flush();
		file.Close();
	}CATCH_ALL(e){
		AfxMessageBox("SQL履歴の保存に失敗しました");
	}END_CATCH_ALL
}

void CMainFrame::LoadSQLHist(){
	TRY{
		CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
		CString strHistData;
		CString strSQL;
		CStdioFile file(strHistData, CFile::modeRead);

		m_arrSQLHistory.RemoveAll();
		strHistData.Format("%s\\sqlhist.dat", pApp->m_strBasePath);
		
		while(file.ReadString(strSQL)){
			m_arrSQLHistory.InsertAt(0, strSQL);
		}
		file.Close();
	}CATCH_ALL(e){
		AfxMessageBox("SQL履歴の保存に失敗しました");
	}END_CATCH_ALL
}

void CMainFrame::OnStatusbarMsg(WPARAM wParam, LPARAM lParam){
	
	if(wParam == 0){
		SetStatusbarMsg((LPCTSTR)lParam);
	}else{
		SetOutputMsg((LPCTSTR)lParam);
	}
}

void CMainFrame::OnEndCreateSql(WPARAM wParam, LPARAM lParam){
	if(m_hSqlThread){
		switch(::WaitForSingleObject(m_hSqlThread, 0)){
		case WAIT_FAILED:
			AfxMessageBox("スレッド終了待機にエラーが発生しました。");
		case WAIT_TIMEOUT:
			::TerminateThread(m_hSqlThread, 0);
		case WAIT_ABANDONED:
		case WAIT_OBJECT_0:
			::CloseHandle(m_hSqlThread);
			m_hSqlThread = NULL;
			break;
		}
	}

	SetStatusbarMsg("完了");
	CSqlViewDlg dlg;
	dlg.m_strSql = m_strSQLData;

	if(dlg.DoModal()){
	}
}

void CMainFrame::OnEndThread(WPARAM wParam, LPARAM lParam){
	if(m_hThreadHandle){
		switch(::WaitForSingleObject(m_hThreadHandle, 0)){
		case WAIT_FAILED:
			AfxMessageBox("スレッド終了待機にエラーが発生しました。");
		case WAIT_TIMEOUT:
			::TerminateThread(m_hThreadHandle, 0);
		case WAIT_ABANDONED:
		case WAIT_OBJECT_0:
			::CloseHandle(m_hThreadHandle);
			m_hThreadHandle = NULL;
			if(m_pThread->pszSQL){
				delete m_pThread->pszSQL;
			}
			delete m_pThread;
			m_pThread = NULL;
			break;
		}
	}	
}

void CMainFrame::GetDBColumType(CString &strType, int nType, LPCTSTR pszSize){
	switch(nType){

	case adUnsignedBigInt:
	case adBigInt:
		strType = "bigint";			
		break;

	case adUnsignedInt:
	case adInteger:
		strType = "int";			
		break;
	
	case adLongVarBinary:
	case adVarBinary:
		strType = "varbinary";			
		break;

	case adBinary:
		strType = "binary";			
		break;
	
	case adUnsignedSmallInt:
	case adSmallInt:
		strType = "smallint";			
		break;
	
	case adUnsignedTinyInt:
	case adTinyInt:
		strType = "tinyint";			
		break;
	
	case adBoolean:
		strType = "bit";			
		break;
	
	case adDecimal:
		strType = "decimal";			
		break;
	
	case adDouble:
		strType = "real";			
		break;
	
	case adSingle:
		strType = "float";			
		break;

	case adVarNumeric:
	case adNumeric:
		strType = "numeric";			
		break;
	
	case adCurrency:
		strType = "smallmoney";			
		break;
	
	case adDate:
	case adDBDate:
	case adDBTime:
		strType = "datetime";			
		break;

	case adDBTimeStamp:
	case adFileTime:
		strType = "timestamp";			
		break;
	
	case adWChar:
		strType = "wchar";			
		break;
	case adChar:
		strType = "char";			
		break;

	case adLongVarChar:
	case adLongVarWChar:
	case adVarWChar:
	case adVarChar:
		if(pszSize){
			strType.Format("varchar(%s)", pszSize) ;			
		}else{
			strType = "varchar";
		}
		break;

	case adBSTR:
		strType = "text";			
		break;

	case adUserDefined:
		strType = "<user defined>";			
		break;

	case adEmpty:
		strType = "<empty>";			
		break;

	case adError:
		strType = "<error>";			
		break;
	case adChapter:
		strType = "<chapter>";			
		break;
	case adGUID:
		strType = "<GUID>";			
		break;
	case adIDispatch:
		strType = "<IDispatch>";			
		break;
	case adIUnknown:
		strType = "<IUnknown>";			
		break;
	case adPropVariant:
		strType = "<PropVariant>";			
		break;
	case adVariant:
		strType = "<Variant>";			
		break;

	default:
		strType = "<UNKNOW>";			
		break;
	}
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd){
	CFrameWnd::OnSetFocus(pOldWnd);
}

void CMainFrame::OnKillFocus(CWnd* pNewWnd){
	CFrameWnd::OnKillFocus(pNewWnd);
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) {
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
    if(nState == WA_INACTIVE){
		CWnd *pWnd = GetFocus();
		if(pWnd && IsChild(pWnd)){
	        m_pOldFocus = pWnd;
		}
    }else{
        if(m_pOldFocus && ::IsWindow(m_pOldFocus->m_hWnd) && IsChild(m_pOldFocus)){
            m_pOldFocus->SetFocus();
			m_pOldFocus->ShowWindow(SW_SHOWNA);
			m_pOldFocus = NULL;
        }
    }
}

void CMainFrame::OnMdbCreate() {
/*
	::CoInitialize( NULL);
	_CatalogPtr pCtalog = NULL;
	HRESULT hr;
	CString strProvider;
	CFileDialog dlg(TRUE, "mdb");
	if(dlg.DoModal() == IDCANCEL){
		return;
	}
	CString strDBPath = dlg.GetPathName();
	strProvider.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source = %s", strDBPath);

	try{

		hr = pCtalog.CreateInstance( __uuidof( Catalog));
		if( FAILED(hr) == TRUE){
			pCtalog = NULL;
			_com_issue_error( hr);
		}

		//mdbの作成
		pCtalog->Create( (LPCTSTR)strProvider);
		bNew = TRUE;

	}catch( _com_error &e){
	    TRACE( "Err :: %s\n", e.ErrorMessage());
		bRet = FALSE;
	}catch(CDBException* pExp){
		CString strError = pExp->GetErrorMessage();
		AfxMessageBox(strError);
		pExp->Delete();
		//delete pExp;
		bRet = FALSE;
	}
	if( pCtalog != NULL){
		pCtalog.Release();
	}
*/
}

void CMainFrame::OnUpdateMdbCreate(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	
}
