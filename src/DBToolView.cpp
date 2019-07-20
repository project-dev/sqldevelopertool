// DBToolView.cpp : CDBToolView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "DBTool.h"
#include "AdoDatabase.h"
#include "DBToolDoc.h"
#include "DBToolView.h"
#include "MainFrm.h"
#include "ProcViewDlg.h"
#include "DebugSupport.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDBToolView

IMPLEMENT_DYNCREATE(CDBToolView, CView)

BEGIN_MESSAGE_MAP(CDBToolView, CView)
	//{{AFX_MSG_MAP(CDBToolView)
	ON_NOTIFY(NM_DBLCLK, ID_INFOTREE, OnTreeDBClick)
	ON_WM_DESTROY()
	ON_NOTIFY(TVN_SELCHANGED, ID_INFOTREE, OnTreeSelChanged)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_EXPORTCSV, OnExportcsv)
	ON_COMMAND(ID_REFRESH_VIEW, OnRefreshView)
	ON_UPDATE_COMMAND_UI(ID_REFRESH_VIEW, OnUpdateRefreshView)
	ON_COMMAND(IDM_EXPORTHTML, OnExporthtml)
	ON_UPDATE_COMMAND_UI(IDM_EXPORTCSV, OnUpdateExportcsv)
	ON_UPDATE_COMMAND_UI(IDM_EXPORTHTML, OnUpdateExporthtml)
	ON_COMMAND(IDM_DEL_PROC, OnDelProc)
	ON_UPDATE_COMMAND_UI(IDM_DEL_PROC, OnUpdateDelProc)
	ON_COMMAND(IDM_SQLDELETE, OnSqldelete)
	ON_UPDATE_COMMAND_UI(IDM_SQLDELETE, OnUpdateSqldelete)
	ON_COMMAND(IDM_OPENPATH, OnOpenpath)
	ON_UPDATE_COMMAND_UI(IDM_OPENPATH, OnUpdateOpenpath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBToolView クラスの構築/消滅

CDBToolView::CDBToolView()
{
	// TODO: この場所に構築用のコードを追加してください。
	m_strKeyBuff = "";
}

CDBToolView::~CDBToolView()
{
}

BOOL CDBToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDBToolView クラスの描画

void CDBToolView::OnDraw(CDC* pDC)
{
	CDBToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rect;
	GetClientRect(rect);

	m_objTree.SetWindowPos(&wndTop, 
						   rect.left, rect.top, 
						   rect.Width(), rect.Height(), 
						   SWP_SHOWWINDOW);
}

/////////////////////////////////////////////////////////////////////////////
// CDBToolView クラスの診断

#ifdef _DEBUG
void CDBToolView::AssertValid() const
{
	CView::AssertValid();
}

void CDBToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDBToolDoc* CDBToolView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBToolDoc)));
	return (CDBToolDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBToolView クラスのメッセージ ハンドラ

void CDBToolView::OnInitialUpdate(){
	CView::OnInitialUpdate();
	
	CRect rect;
	GetClientRect(rect);
	m_objTree.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
					 rect, this, ID_INFOTREE);
	m_objTree.ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

	m_objIconBmp.LoadBitmap(IDB_TREEICON);
	m_objIcons.Create(16, 16, ILC_COLOR8 | ILC_MASK, 10, 1);
	m_objIcons.Add(&m_objIconBmp, RGB(0xFF, 0xFF, 0xFF));
	m_objTree.SetImageList(&m_objIcons, TVSIL_NORMAL);

	m_hRecord		= m_objTree.InsertItem("テーブル",				0, 0);
	m_hSysRecord	= m_objTree.InsertItem("システムテーブル",		0, 0);
	m_hView			= m_objTree.InsertItem("ビュー",				0, 0);
	m_hProc			= m_objTree.InsertItem("プロシージャ",			5, 5);
	m_hSql			= m_objTree.InsertItem("SQLファイル",			2, 2);
	m_objTree.SetIncrementalSearch(TRUE);
	RefreshRecord();
}

void CDBToolView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) {
	switch(lHint){
	case DB_OPEN:
	case DB_REFRESH:
	case DB_REFRESH_TREE:
		//ツリーの構築
		m_objTree.CancelSearch();
		RefreshRecord();
		break;
	case DB_CLOSE:
		//ツリーの初期化
		m_objTree.CancelSearch();
		DeleteChild(m_hRecord);
		DeleteChild(m_hSysRecord);
		DeleteChild(m_hView);
		DeleteChild(m_hProc);
		break;
	}



}

void CDBToolView::RefreshRecord(){
	m_objTree.Select(m_hRecord, TVGN_CARET);

	DeleteChild(m_hRecord);
	DeleteChild(m_hSysRecord);
	DeleteChild(m_hView);
	DeleteChild(m_hSql);
	DeleteChild(m_hProc);


	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	CAdoDatabase *pDb = pFrm->GetDBObject();

	CString strTitle = GetDocument()->GetTitle();

	_RecordsetPtr rs = NULL;
	HTREEITEM hInsItem;
	
	if(pDb->IsConnect()){
#if defined(NEW_DBTYPE)
		if((pFrm->GetDBObject()->GetDBType() == ODBC_DATASRC)
		|| strTitle.IsEmpty() 
		|| !strTitle.Compare("切断")){
#else
		if((pFrm->GetDBObject()->GetDBType() == ODBC)
		|| strTitle.IsEmpty() 
		|| !strTitle.Compare("切断")){
#endif
			rs = pDb->GetTables();
		}else{
			rs = pDb->GetTables(strTitle);
		}

		if((rs == NULL) || ((rs != NULL) && !rs->GetRecordCount())){
			CString strError;
			strError.Format("テーブル一覧の取得に失敗しました。\n%s", pDb->GetError());
			AfxMessageBox(strError);
			if(rs){
				rs->Close();
			}
		}else{
//			eODBCType odbc = pDb->GetODBCType();
//			eDBType dbType = pDb->GetDBType();
			while(rs->EndOfFile == VARIANT_FALSE){
				_variant_t val = pDb->GetFieldValue(rs, "TABLE_NAME");
				_variant_t valType = pDb->GetFieldValue(rs, "TABLE_TYPE");
				if(valType.vt != VT_NULL){
					CString strType = valType.bstrVal;
					if(!strType.CompareNoCase("TABLE")){
						if(val.vt != VT_NULL){
							CString strName = val.bstrVal;
							hInsItem = m_objTree.InsertItem(strName, 1, 1, m_hRecord);
						}
					}else if(!strType.CompareNoCase("SYSTEM TABLE")){
						if(val.vt != VT_NULL){
							CString strName = val.bstrVal;
							hInsItem = m_objTree.InsertItem(strName, 1, 1, m_hSysRecord);
						}
					}else if(!strType.CompareNoCase("VIEW")){
						if(val.vt != VT_NULL){
							CString strName = val.bstrVal;
							hInsItem = m_objTree.InsertItem(strName, 1, 1, m_hView);
						}
					}
				}
/*
				if((dbType == ODBC) && (odbc != ODBC_SQLSERVER) && (odbc != ODBC_UNKNOW)){
					if(odbc == ODBC_DB2){
						_variant_t val = pDb->GetFieldValue(rs, "TABNAME");
						_variant_t valType = pDb->GetFieldValue(rs, "TYPE");
						if(valType.vt != VT_NULL){
							CString strType = valType.bstrVal;
							if(!strType.CompareNoCase("T")){
								if(val.vt != VT_NULL){
									CString strName = val.bstrVal;
									hInsItem = m_objTree.InsertItem(strName, 1, 1, m_hRecord);
								}
							}else if(!strType.CompareNoCase("V")){
								if(val.vt != VT_NULL){
									CString strName = val.bstrVal;
									hInsItem = m_objTree.InsertItem(strName, 1, 1, m_hView);
								}
							}
						}
					}else if(odbc == ODBC_ORACLE){
						_variant_t val = pDb->GetFieldValue(rs, "TABLE_NAME");
						if(val.vt != VT_NULL){
							CString strName = val.bstrVal;
							hInsItem = m_objTree.InsertItem(strName, 1, 1, m_hRecord);
						}
					}
				}else{
					_variant_t val = pDb->GetFieldValue(rs, "TABLE_NAME");
					_variant_t valType = pDb->GetFieldValue(rs, "TABLE_TYPE");
					if(valType.vt != VT_NULL){
						CString strType = valType.bstrVal;
						if(!strType.CompareNoCase("TABLE")){
							if(val.vt != VT_NULL){
								CString strName = val.bstrVal;
								hInsItem = m_objTree.InsertItem(strName, 1, 1, m_hRecord);
							}
						}else if(!strType.CompareNoCase("SYSTEM TABLE")){
							if(val.vt != VT_NULL){
								CString strName = val.bstrVal;
								hInsItem = m_objTree.InsertItem(strName, 1, 1, m_hSysRecord);
							}
						}else if(!strType.CompareNoCase("VIEW")){
							if(val.vt != VT_NULL){
								CString strName = val.bstrVal;
								hInsItem = m_objTree.InsertItem(strName, 1, 1, m_hView);
							}
						}
					}
				}				
*/
				m_objTree.SetItemData(hInsItem, (LPARAM)hInsItem);
				rs->MoveNext();	
			}
			rs->Close();
		}
	}

	//子階層にSQLが無いか検索する
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	CString strSQLFindPath;
	strSQLFindPath.Format("%ssql", pApp->m_strBasePath);
	FindSQL(strSQLFindPath, m_hSql);

	TVSORTCB tvSort;
	tvSort.hParent = m_hSql;
	tvSort.lpfnCompare = CompareFunc;
	tvSort.lParam = (LPARAM)&m_objTree;
	m_objTree.SortChildrenCB(&tvSort);
	
	m_objTree.InvalidateRect(NULL);

	//ストアドプロシージャの列挙

	_RecordsetPtr procRs = pDb->GetProcedures();
	if(procRs){
		_variant_t name;
		CString strProcName;
		while(procRs->EndOfFile == VARIANT_FALSE){
			name = pDb->GetFieldValue(procRs, "name");
			if((name.vt != VT_NULL) && (name.vt != VT_EMPTY)){
				strProcName = name.bstrVal;
				hInsItem = m_objTree.InsertItem(strProcName, 6, 6, m_hProc);
				m_objTree.SetItemData(hInsItem, (LPARAM)hInsItem);
			}
			procRs->MoveNext();
		}

		procRs->Close();
		tvSort.hParent = m_hProc;
		tvSort.lpfnCompare = CompareFunc;
		tvSort.lParam = (LPARAM)&m_objTree;
		m_objTree.SortChildrenCB(&tvSort);
	}
}

int CALLBACK CDBToolView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	//ソートを行う
	HTREEITEM pTVItem1 = (HTREEITEM)lParam1;
	HTREEITEM pTVItem2 = (HTREEITEM)lParam2;

	if((pTVItem1 == NULL) && (pTVItem2 == NULL)){
		return 0;
	}else if(pTVItem1 == NULL){
		//文字列比較
		return 1;
	}else if(lParam2 == NULL){
		//比較元がフォルダ
		return -1;
	}

	CTreeCtrl *pTree = (CTreeCtrl*)lParamSort;
	if(pTree == NULL){
		return 0;
	}

	CString strItem1 = pTree->GetItemText(pTVItem1);
	CString strItem2 = pTree->GetItemText(pTVItem2);
	int nImg1;
	int nImg2;
	int nSelImg1;
	int nSelImg2;
	pTree->GetItemImage(pTVItem1, nImg1, nSelImg1);
	pTree->GetItemImage(pTVItem2, nImg2, nSelImg2);

	HTREEITEM hParent = pTree->GetParentItem(pTVItem1);
	int nParentImg;
	int nParentSelImg;
	pTree->GetItemImage(hParent, nParentImg, nParentSelImg);


	switch(nParentImg){
	case 2:
	case 3:
	case 4:
		if(nImg1 < nImg2){
			return 1;
		}else if(nImg1 > nImg2){
			return -1;
		}
		break;
	}

	return strItem1.CompareNoCase(strItem2);
}

BOOL CDBToolView::FindSQL(LPCTSTR pszFindPath, HTREEITEM hParent){
	WIN32_FIND_DATA wfd;
	HANDLE hRet;
	BOOL bFirst = TRUE;
	CString strSQLFindPath;
	strSQLFindPath.Format("%s\\*", pszFindPath);
	HTREEITEM hInsItem;
	while(TRUE){
		if(bFirst){
			hRet = ::FindFirstFile(strSQLFindPath, &wfd);
			bFirst = FALSE;
			if(hRet == INVALID_HANDLE_VALUE){
				break;
			}
		}else{
			if(!::FindNextFile(hRet, &wfd)){
				break;
			}
		}
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			CString strChildFindPath;
			CString strFile = wfd.cFileName;
			if(strFile.Left(1).Compare(".")){
				strChildFindPath.Format("%s\\%s", pszFindPath, wfd.cFileName);
				hInsItem = m_objTree.InsertItem(wfd.cFileName, 3, 4, hParent);
				m_objTree.SetItemData(hInsItem, (LPARAM)hInsItem);
				FindSQL(strChildFindPath, hInsItem);
			}
		}else{
			CString strFileName = wfd.cFileName;
			if(!strFileName.Right(4).CompareNoCase(".sql")){
				hInsItem = m_objTree.InsertItem(wfd.cFileName, 2, 2, hParent);
				m_objTree.SetItemData(hInsItem, (LPARAM)hInsItem);
			}
		}
		TVSORTCB tvSort;
		tvSort.hParent = hParent;
		tvSort.lpfnCompare = CompareFunc;
		tvSort.lParam = (LPARAM)&m_objTree;
		m_objTree.SortChildrenCB(&tvSort);
	}
	::FindClose(hRet);
	return TRUE;
}

void CDBToolView::OnTreeDBClick(WPARAM wParam, LPARAM lParam){
	OpenTree();
}

void CDBToolView::OnTreeSelChanged(WPARAM wParam, LPARAM lParam){
	LPNMTREEVIEW pnmtv = (LPNMTREEVIEW)lParam;
	HTREEITEM hTree = m_objTree.GetSelectedItem();
	HTREEITEM hParent = m_objTree.GetParentItem(hTree);
	if((hParent == m_hRecord) || (hParent == m_hSysRecord)){
		CString strName = m_objTree.GetItemText(hTree);
		GetDocument()->UpdateAllViews(NULL, DB_TABLE_PROP, (CObject*)&strName);
	}else{
		//プロパティクリア
		GetDocument()->UpdateAllViews(NULL, DB_PROP_CLEAR, NULL);
	}

}


void CDBToolView::OnDestroy() {
	CRect rect;
	GetWindowRect(rect);
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	pApp->m_nLeftPaneWidth = rect.Width();

	CView::OnDestroy();
}

void CDBToolView::DeleteChild(HTREEITEM hParent){
	HTREEITEM hChild = m_objTree.GetChildItem(hParent);
	while(hChild){
		m_objTree.DeleteItem(hChild);
		hChild = m_objTree.GetChildItem(hParent);
	}
}

void CDBToolView::OnContextMenu(CWnd* pWnd, CPoint point) {
	CPoint HitPoint = point;
	m_objTree.ScreenToClient(&HitPoint);
	
	TVHITTESTINFO tvHitTest;
	tvHitTest.pt = HitPoint;
	tvHitTest.flags = TCHT_ONITEM;
	HTREEITEM hItem = m_objTree.HitTest(&tvHitTest);
	if(hItem == NULL){
		return;
	}
	m_objTree.SelectItem(hItem);

	CMenu objMenu;
	objMenu.LoadMenu(IDR_POPUP);
	CMenu *pPopup = objMenu.GetSubMenu(1);

	HTREEITEM hParent = m_objTree.GetParentItem(hItem);
	if((hParent != m_hRecord) && (hParent != m_hSysRecord) && (hParent != m_hProc)){
		pPopup->EnableMenuItem(IDM_EXPORTCSV,	MF_BYCOMMAND | MF_GRAYED);
		pPopup->EnableMenuItem(IDM_EXPORTHTML,	MF_BYCOMMAND | MF_GRAYED);
		pPopup->EnableMenuItem(IDM_EXPORTXML,	MF_BYCOMMAND | MF_GRAYED);
		pPopup->EnableMenuItem(IDM_DEL_PROC,	MF_BYCOMMAND | MF_GRAYED);
	}else if(hParent == m_hProc){
		pPopup->EnableMenuItem(IDM_EXPORTCSV,	MF_BYCOMMAND | MF_GRAYED);
		pPopup->EnableMenuItem(IDM_EXPORTHTML,	MF_BYCOMMAND | MF_GRAYED);
		pPopup->EnableMenuItem(IDM_EXPORTXML,	MF_BYCOMMAND | MF_GRAYED);
		pPopup->EnableMenuItem(IDM_DEL_PROC,	MF_BYCOMMAND | MF_ENABLED);
	}else{
		pPopup->EnableMenuItem(IDM_EXPORTCSV,	MF_BYCOMMAND | MF_ENABLED);
		pPopup->EnableMenuItem(IDM_EXPORTHTML,	MF_BYCOMMAND | MF_ENABLED);
		pPopup->EnableMenuItem(IDM_EXPORTXML,	MF_BYCOMMAND | MF_ENABLED);
		pPopup->EnableMenuItem(IDM_DEL_PROC,	MF_BYCOMMAND | MF_GRAYED);
	}

	CString strPath;
	if(IsSQLFilePath(strPath)){
		pPopup->EnableMenuItem(IDM_SQLDELETE,	MF_BYCOMMAND | MF_ENABLED);
	}else{
		pPopup->EnableMenuItem(IDM_SQLDELETE,	MF_BYCOMMAND | MF_GRAYED);
	}

	if(IsSQLFullPath(strPath)){
		pPopup->EnableMenuItem(IDM_OPENPATH,	MF_BYCOMMAND | MF_ENABLED);
	}else{
		pPopup->EnableMenuItem(IDM_OPENPATH,	MF_BYCOMMAND | MF_GRAYED);
	}

	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	if(pFrm){
		CAdoDatabase *pDB = pFrm->GetDBObject();
		if(pDB->IsConnect()){
			pPopup->EnableMenuItem(ID_REFRESH_VIEW, MF_BYCOMMAND | MF_ENABLED);
		}else{
			pPopup->EnableMenuItem(ID_REFRESH_VIEW, MF_BYCOMMAND | MF_GRAYED);
		}
	}else{
		pPopup->EnableMenuItem(ID_REFRESH_VIEW, MF_BYCOMMAND | MF_GRAYED);
	}	

	pPopup->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}

void CDBToolView::OnExporthtml(){
	HTREEITEM hItem = m_objTree.GetSelectedItem();
	if(!hItem){
		return;
	}

	//レコードを取得し、HTMLに出力する
	CString strTable = m_objTree.GetItemText(hItem);
	CString strSQL;
	strSQL.Format("SELECT * FROM %s", strTable);
	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	CAdoDatabase *pDb = pFrm->GetDBObject();
	_RecordsetPtr rs = pDb->OpenRecordSet(strSQL);
	if(rs == NULL){
		CString strError = pDb->GetError();
		pFrm->SetOutputMsg(strError);
		return;
	}

	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	_TCHAR szFilePath[MAX_PATH];
	memset(szFilePath, 0, MAX_PATH);
	strcpy(szFilePath, "*.htm;*.html");
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.Flags				= OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING | OFN_HIDEREADONLY;
	ofn.lStructSize			= sizeof(OPENFILENAME);
	ofn.hwndOwner			= m_hWnd;
	ofn.lpstrFile			= szFilePath;
	ofn.nMaxFile			= MAX_PATH;
	ofn.lpstrFilter			= "HTML形式(*.htm;*.html)\0*.htm;*.html\0すべてのファイル(*.*)\0*.*\0\0";
	ofn.nFilterIndex		= 1;
	ofn.lpstrInitialDir		= pApp->m_strBasePath;
	ofn.lpstrDefExt			= "html";
	BOOL bRet =  ::GetSaveFileName(&ofn);
	if(!bRet){
		return;
	}
	CString strSavePath = szFilePath;

	_RecordsetPtr rsColumn = pDb->GetColumns(strSQL);

	//カラム一覧の生成
	FieldsPtr fields = rs->GetFields();
	LONG nCnt = fields->GetCount();
	_variant_t vIndex;
	CString strHtml;
	strHtml = "<html lang=\"ja\">\r\n"
			  "<head>\r\n"
			  "<title></title>\r\n"
			  "</head>\r\n"
			  "<body>\r\n"
			  "<table border>\r\n"
			  "<tr>";
	CStringArray arrNames;
	for(int i = 0; i < nCnt; i++){
		vIndex = (short)i;
		_variant_t val = fields->GetItem(&vIndex)->GetName();
		CString strName = val.bstrVal;
		arrNames.Add(strName);
		strHtml += "<td>" + strName + "</td>";
	}
	strHtml += "</tr>\r\n";

	//データ出力
	int nMax = arrNames.GetSize();
	_variant_t val;
	CString strVal;
	while(rs->EndOfFile == VARIANT_FALSE){
		strHtml += "<tr>";
		for(int i = 0; i < nMax; i++){
			val = pDb->GetFieldValue(rs, arrNames.GetAt(i));
			val.ChangeType(VT_BSTR);
			strVal = val.bstrVal;
			strHtml += "<td>" + strVal + "</td>";
		}
		strHtml += "</tr>\r\n";
		rs->MoveNext();
	}
	strHtml += "</table>\r\n"
			   "</table>\r\n"
			   "</body>\r\n"
			   "</html>";
	
	rs->Close();

	CStdioFile file;
	TRY{
		file.Open(strSavePath, CFile::modeCreate | CFile::modeWrite);
		file.WriteString(strHtml);
		file.Flush();
	}CATCH_ALL(e){
	}END_CATCH_ALL
	file.Close();
}

void CDBToolView::OnExportcsv(){
	HTREEITEM hItem = m_objTree.GetSelectedItem();
	if(!hItem){
		return;
	}

	//レコードを取得し、CSVに出力する
	CString strTable = m_objTree.GetItemText(hItem);
	CString strSQL;
	strSQL.Format("SELECT * FROM %s", strTable);
	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	CAdoDatabase *pDb = pFrm->GetDBObject();
	_RecordsetPtr rs = pDb->OpenRecordSet(strSQL);
	if(rs == NULL){
		CString strError = pDb->GetError();
		pFrm->SetOutputMsg(strError);
		return;
	}

	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	_TCHAR szFilePath[MAX_PATH];
	memset(szFilePath, 0, MAX_PATH);
	strcpy(szFilePath, "*.csv");
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.Flags				= OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING | OFN_HIDEREADONLY;
	ofn.lStructSize			= sizeof(OPENFILENAME);
	ofn.hwndOwner			= m_hWnd;
	ofn.lpstrFile			= szFilePath;
	ofn.nMaxFile			= MAX_PATH;
	ofn.lpstrFilter			= "CSV形式(*.csv)\0*.csv\0すべてのファイル(*.*)\0*.*\0\0";
	ofn.nFilterIndex		= 1;
	ofn.lpstrInitialDir		= pApp->m_strBasePath;
	ofn.lpstrDefExt			= "csv";
	BOOL bRet =  ::GetSaveFileName(&ofn);
	if(!bRet){
		return;
	}
	CString strSavePath = szFilePath;

	_RecordsetPtr rsColumn = pDb->GetColumns(strSQL);

	//カラム一覧の生成
	FieldsPtr fields = rs->GetFields();
	LONG nCnt = fields->GetCount();
	_variant_t vIndex;
	CString strCSV;
	CStringArray arrNames;
	for(int i = 0; i < nCnt; i++){
		vIndex = (short)i;
		_variant_t val = fields->GetItem(&vIndex)->GetName();
		CString strName = val.bstrVal;
		arrNames.Add(strName);
		strCSV += "\"" + strName + "\",";
	}
	strCSV += "\n";

	//データ出力
	int nMax = arrNames.GetSize();
	_variant_t val;
	CString strVal;
	while(rs->EndOfFile == VARIANT_FALSE){
		for(int i = 0; i < nMax; i++){
			val = pDb->GetFieldValue(rs, arrNames.GetAt(i));
			val.ChangeType(VT_BSTR);
			strVal = val.bstrVal;
			strCSV += "\"" + strVal + "\",";
		}
		strCSV += "\n";
		rs->MoveNext();
	}
	
	rs->Close();

	CStdioFile file;
	TRY{
		file.Open(strSavePath, CFile::modeCreate | CFile::modeWrite);
		file.WriteString(strCSV);
		file.Flush();
	}CATCH_ALL(e){
	}END_CATCH_ALL
	file.Close();
}

void CDBToolView::OnRefreshView(){
	RefreshRecord();
}

void CDBToolView::OnDelProc(){
	CString strSQL;
	HTREEITEM hTree = m_objTree.GetSelectedItem();
	CString strName = m_objTree.GetItemText(hTree);
	strSQL.Format("DROP PROCEDURE %s", strName);
	
	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	CAdoDatabase *pDb = pFrm->GetDBObject();
	pDb->ExecSQL(strSQL);	
	LPCTSTR pErr = pDb->GetError();
	if(pErr){
		AfxMessageBox(pErr);
	}
	RefreshRecord();
}

void CDBToolView::OnUpdateDelProc(CCmdUI* pCmdUI){
	HTREEITEM hTree = m_objTree.GetSelectedItem();
	HTREEITEM hParent = m_objTree.GetParentItem(hTree);
	if(hParent != m_hProc){
		pCmdUI->Enable(FALSE);
	}else{
		pCmdUI->Enable(TRUE);
	}
}

void CDBToolView::OnUpdateRefreshView(CCmdUI* pCmdUI){
}

void CDBToolView::OnUpdateExportcsv(CCmdUI* pCmdUI){
	HTREEITEM hTree = m_objTree.GetSelectedItem();
	HTREEITEM hParent = m_objTree.GetParentItem(hTree);
	if((hParent != m_hRecord) && (hParent != m_hSysRecord)){
		pCmdUI->Enable(FALSE);
	}else{
		pCmdUI->Enable(TRUE);
	}
}

void CDBToolView::OnUpdateExporthtml(CCmdUI* pCmdUI){
	HTREEITEM hTree = m_objTree.GetSelectedItem();
	HTREEITEM hParent = m_objTree.GetParentItem(hTree);
	if((hParent != m_hRecord) && (hParent != m_hSysRecord)){
		pCmdUI->Enable(FALSE);
	}else{
		pCmdUI->Enable(TRUE);
	}
}

HTREEITEM CDBToolView::FindTreeText(LPCTSTR pszText, HTREEITEM hItem){
	CString strItemText;
	CString strFindText = pszText;
	CString strTarget;
	while(hItem != NULL){
		strItemText = m_objTree.GetItemText(hItem);
		if(strItemText.GetLength() >= strFindText.GetLength()){
			strTarget = strItemText.Left(strFindText.GetLength());
			if(!strTarget.Compare(strFindText)){
				m_objTree.SelectItem(hItem);
				return hItem;
			}
		}

		if(m_objTree.ItemHasChildren(hItem)){
			HTREEITEM hChild = m_objTree.GetChildItem(hItem);
			HTREEITEM retItem = FindTreeText(pszText, hChild);
			if(retItem){
				m_objTree.Expand(hItem, TVE_EXPAND);
				return retItem;
			}
		}
		hItem = m_objTree.GetNextItem(hItem, TVGN_NEXT);
	}
	return NULL;
}



void CDBToolView::OpenTree(){
	HTREEITEM hTree = m_objTree.GetSelectedItem();
	HTREEITEM hParent = m_objTree.GetParentItem(hTree);
	HTREEITEM hOldParent = NULL;
	while(hParent != NULL){
		hOldParent = hParent;
		hParent = m_objTree.GetParentItem(hParent);
	}
	if(hParent == NULL){
		hParent = hOldParent;
	}

	if((hParent == m_hRecord) || (hParent == m_hSysRecord)){
		CString strName = m_objTree.GetItemText(hTree);

		CString strSql;
		strSql.Format("SELECT * FROM %s", strName);
	
		GetDocument()->UpdateAllViews(NULL, DB_RESULT, (CObject*)&strSql);
	}else if(hParent == m_hProc){
		//ストアドプロシージャの内容を取得する
		CString strName = m_objTree.GetItemText(hTree);

		CString strSql;
		strSql.Format("sp_helptext \'%s\'", strName);
		CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
		CAdoDatabase *pDb = pFrm->GetDBObject();
		_RecordsetPtr rs = pDb->OpenRecordSet(strSql);
		_variant_t val;
		CString strFunc = "";
		if(rs != NULL){
			//レコードセットの内容をﾃｷｽﾄに
			while(rs->EndOfFile == VARIANT_FALSE){
				val = pDb->GetFieldValue(rs, "Text");
				if((val.vt == VT_NULL) || (val.vt == VT_EMPTY)){
					strFunc += "";
				}else{
					strFunc += val.bstrVal;
				}
				rs->MoveNext();
			}

			GetDocument()->UpdateAllViews(NULL, DB_GETFUNC, (CObject*)&strFunc);

/*
			CProcViewDlg cDlg;
			cDlg.m_strFuncData = strFunc;
			int nRet = cDlg.DoModal();
			if((nRet == -1) || (nRet == IDABORT)){
				AfxMessageBox("ダイアログの作成に失敗しました");
			}
*/
		}else{
			AfxMessageBox("ストアドプロシージャの内容が取得できませんでした");
		}
	
//		GetDocument()->UpdateAllViews(NULL, DB_RESULT, (CObject*)&strSql);

	}else if(hParent == m_hSql){
		//SQLファイルを開く
		CString strSQLFile;
		if(IsSQLFilePath(strSQLFile)){
			GetDocument()->UpdateAllViews(this, DB_OPENSQL, (CObject*)&strSQLFile);
		}
	}
}

void CDBToolView::OnSqldelete(){

	CString strPath;
	if(!IsSQLFilePath(strPath)){
		return;
	
	}

	CString strMsg;
	strMsg.Format("%s を削除しますか？", strPath);
	if(AfxMessageBox(strMsg, MB_OKCANCEL) != IDOK){
		return;
	}

	if(!::DeleteFile(strPath)){
		DWORD dwErr = ::GetLastError();
		CString strErr = CDebugSupport::GetLastErrorText(dwErr);
		strMsg.Format("%s の削除に失敗しました\n%s", strPath, strErr);
		AfxMessageBox(strMsg);
	}
	
	//表示の最新化
	OnRefreshView();
}

void CDBToolView::OnUpdateSqldelete(CCmdUI* pCmdUI){
	CString strPath;
	pCmdUI->Enable(IsSQLFilePath(strPath));
}

void CDBToolView::OnOpenpath(){
	CString strPath;
	if(!IsSQLFullPath(strPath)){
		return;
	}

	int nPos = strPath.ReverseFind('.');
	if(nPos != -1){
		CString strFilePath;
		if(IsSQLFilePath(strFilePath)){
			int nPos = strPath.ReverseFind('\\');
			strPath = strPath.Left(nPos);
		}
	}
	::ShellExecute(m_hWnd, "open", strPath, NULL, NULL, SW_SHOWNORMAL);
}

void CDBToolView::OnUpdateOpenpath(CCmdUI* pCmdUI){
	CString strPath;
	pCmdUI->Enable(IsSQLFullPath(strPath));
}

BOOL CDBToolView::IsSQLFilePath(CString &strRetPath){
	HTREEITEM hTree = m_objTree.GetSelectedItem();
	HTREEITEM hParent = m_objTree.GetParentItem(hTree);
	HTREEITEM hOldParent = NULL;
	strRetPath.Empty();
	while(hParent != NULL){
		hOldParent = hParent;
		hParent = m_objTree.GetParentItem(hParent);
	}
	if(hParent == NULL){
		hParent = hOldParent;
	}

	if(hParent != m_hSql){
		return FALSE;
	}
	//SQLファイルを削除する
		
	HTREEITEM hSel = m_objTree.GetSelectedItem();
	//パスの作成
	CString strPath = "";
	while(hSel != m_hSql){
		if(strPath.IsEmpty()){
			strPath = m_objTree.GetItemText(hSel);
		}else{
			strPath = m_objTree.GetItemText(hSel) + "\\" + strPath;
		}
		hSel = m_objTree.GetParentItem(hSel);
	}

	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	strRetPath.Format("%s\\sql\\%s", 
					  pApp->m_strBasePath, 
					  strPath);
	WIN32_FIND_DATA wfd;
	HANDLE hRet = ::FindFirstFile(strRetPath, &wfd);
	if(hRet != INVALID_HANDLE_VALUE){
		if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY){
			::FindClose(hRet);
			return TRUE;
		}
	}
	::FindClose(hRet);
	return FALSE;
}

BOOL CDBToolView::IsSQLFullPath(CString &strRetPath){
	HTREEITEM hTree = m_objTree.GetSelectedItem();
	HTREEITEM hParent = m_objTree.GetParentItem(hTree);
	HTREEITEM hOldParent = NULL;
	strRetPath.Empty();
	if(hTree == m_hSql){
		CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
		strRetPath.Format("%s\\sql", 
						  pApp->m_strBasePath);
		return TRUE;
	}
	while(hParent != NULL){
		hOldParent = hParent;
		hParent = m_objTree.GetParentItem(hParent);
	}
	if(hParent == NULL){
		hParent = hOldParent;
	}

	if(hParent != m_hSql){
		return FALSE;
	}
	//SQLファイルを削除する
		
	HTREEITEM hSel = m_objTree.GetSelectedItem();
	//パスの作成
	CString strPath = "";
	while(hSel != m_hSql){
		if(strPath.IsEmpty()){
			strPath = m_objTree.GetItemText(hSel);
		}else{
			strPath = m_objTree.GetItemText(hSel) + "\\" + strPath;
		}
		hSel = m_objTree.GetParentItem(hSel);
	}

	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	strRetPath.Format("%s\\sql\\%s", 
					  pApp->m_strBasePath, 
					  strPath);
	WIN32_FIND_DATA wfd;
	HANDLE hRet = ::FindFirstFile(strRetPath, &wfd);
	if(hRet != INVALID_HANDLE_VALUE){
		::FindClose(hRet);
		return TRUE;
	}
	::FindClose(hRet);
	return FALSE;

}

void CDBToolView::EnableTree(BOOL bEnable){
	m_objTree.EnableWindow(bEnable);

}
