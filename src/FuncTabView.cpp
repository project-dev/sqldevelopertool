// FuncTabView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DBTool.h"
#include "FuncTabView.h"
#include "SQLEdit.h"
#include "MainFrm.h"
#include <AfxPriv2.h>
#include "ColumnInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFuncTabView

IMPLEMENT_DYNCREATE(CFuncTabView, CView)

CFuncTabView::CFuncTabView(){
	m_nOldSel = 0;
	m_nPopupTargetIndex = 0;
	m_pFuncEdit = NULL;
	m_nSQLEditCnt = 1;
}

CFuncTabView::~CFuncTabView(){
}


BEGIN_MESSAGE_MAP(CFuncTabView, CView)
	//{{AFX_MSG_MAP(CFuncTabView)
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, ID_FUNCTAB, OnSelchange)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_SQL_SAVEAS, OnSqlSaveas)
	ON_COMMAND(ID_SQL_SQVE, OnSqlSqve)
	ON_UPDATE_COMMAND_UI(ID_SQL_SAVEAS, OnUpdateSqlSaveas)
	ON_UPDATE_COMMAND_UI(ID_SQL_SQVE, OnUpdateSqlSqve)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_TABCLOSE, OnTabclose)
	ON_WM_COPYDATA()
	ON_COMMAND(ID_SQL_NEW, OnSqlNew)
	ON_UPDATE_COMMAND_UI(ID_SQL_NEW, OnUpdateSqlNew)
	ON_COMMAND(ID_ALLSELECT, OnAllselect)
	ON_UPDATE_COMMAND_UI(ID_ALLSELECT, OnUpdateAllselect)
	ON_UPDATE_COMMAND_UI(ID_SQLRUN, OnUpdateSqlrun)
	ON_COMMAND(ID_SQLRUN, OnSqlrun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFuncTabView 描画

void CFuncTabView::OnDraw(CDC* pDC){
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
	CRect rect;
	GetClientRect(rect);
	m_objTab.SetWindowPos(&wndTop, 
						  rect.left, rect.top, 
						  rect.Width(), rect.Height(), 
						  SWP_SHOWWINDOW);

	int nIndex = m_objTab.GetCurSel();
	if(nIndex >= 0){
		TCITEM tcItem;
		memset(&tcItem, 0, sizeof(TCITEM));
		tcItem.mask = TCIF_PARAM;
		m_objTab.GetItem(nIndex, &tcItem);
		CRect rect;
		GetPageRect(rect);
		CWnd *pWnd = (CWnd*)tcItem.lParam;
		if(pWnd){
			pWnd->SetWindowPos(&wndTop,
							   rect.left, rect.top,
							   rect.Width(), rect.Height(),
							   SWP_SHOWWINDOW);		
		}
	}

}

/////////////////////////////////////////////////////////////////////////////
// CFuncTabView 診断

#ifdef _DEBUG
void CFuncTabView::AssertValid() const
{
	CView::AssertValid();
}

void CFuncTabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFuncTabView メッセージ ハンドラ

void CFuncTabView::OnInitialUpdate() {
	CView::OnInitialUpdate();
	CRect rect;
	GetClientRect(rect);
	DWORD dwStyle = WS_VISIBLE | WS_TABSTOP | TCS_SINGLELINE | TCS_TABS /*| TCS_BOTTOM*/;
	m_objTab.Create(dwStyle | WS_CHILD,
					rect,
					this, ID_FUNCTAB);
	m_objTab.ModifyStyle(dwStyle, 0);
	m_objTab.ModifyStyle(0, dwStyle);
	m_objTab.ModifyStyleEx(WS_EX_CLIENTEDGE, WS_EX_CONTROLPARENT);


	memset(&m_lFont, 0, sizeof(LOGFONT));
	CFont *pFont = m_objTab.GetFont();
	if(pFont){
		strcpy(m_lFont.lfFaceName, "ＭＳ ゴシック");
		m_lFont.lfWidth = 0;
		m_lFont.lfHeight= -12;
		m_lFont.lfCharSet = SHIFTJIS_CHARSET;
		if(m_objFont.CreateFontIndirect(&m_lFont)){
			m_objTab.SetFont(&m_objFont);
		}
	}
	
	AddPropertyList();
	AddOutput();
	AddSQLEditor();
	m_objTab.SetCurSel(0);
}

int CFuncTabView::AddTabPage(CWnd *pWnd, LPCTSTR pszTitle, int nIndex, CTabCtrl *pTab){
	if(!pTab){
		pTab = &m_objTab;
	}
	if(nIndex == -1){
		nIndex = pTab->GetItemCount();
	}
	
	int nRet = pTab->InsertItem( TCIF_TEXT | TCIF_PARAM,
								 nIndex,
								 pszTitle, 
								 0, 
								 (LPARAM)pWnd, 
								 0, 0);
	pWnd->SetFont(&m_objFont);
	SetActivePage(pTab->GetCurSel());
	return nRet;
}

BOOL CFuncTabView::AddSQLEditor(){
	CSQLEdit *pEdit = new CSQLEdit();
	CRect rect;
	GetPageRect(rect);
	DWORD dwStyle = WS_TABSTOP | WS_VSCROLL | WS_HSCROLL | WS_BORDER | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL;
	
	pEdit->Create(dwStyle | WS_CHILD,
				  rect, 
				  &m_objTab, 
				  ID_SQLEDITOR);
	
//	pEdit->ModifyStyle(dwStyle, 0);
//	pEdit->ModifyStyle(0, dwStyle);
	pEdit->SetLineShow();
	CScrollBar *pHBar = pEdit->GetScrollBarCtrl(SB_HORZ);
	CScrollBar *pVBar = pEdit->GetScrollBarCtrl(SB_VERT);
	
	if(pHBar){
		pHBar->ModifyStyle(0, WS_BORDER);
	}
	
	if(pVBar){
		pVBar->ModifyStyle(0, WS_BORDER);
	}

	CString strPageName;
	strPageName.Format("SQL(%d)", m_nSQLEditCnt);
	m_nSQLEditCnt++;
	int nRet = AddTabPage(pEdit, strPageName);
	if(nRet == -1){
		return FALSE;
	}
	return TRUE;
}

BOOL CFuncTabView::AddPropertyList(){
	m_pPropTab = new CWndTabCtrl();

	CRect rect;
	m_objTab.GetClientRect(rect);
	DWORD dwStyle = WS_TABSTOP | WS_VISIBLE | WS_TABSTOP | TCS_SINGLELINE | TCS_TABS /*| TCS_BOTTOM*/;
	m_pPropTab->Create(	dwStyle | WS_CHILD,
						rect,
						&m_objTab, ID_PROP_TAB);

	m_pPropTab->ModifyStyle(dwStyle, 0);
	m_pPropTab->ModifyStyle(0, dwStyle);
	m_pPropTab->ModifyStyleEx(0, WS_EX_CLIENTEDGE | WS_EX_CONTROLPARENT);

	int nRet = AddTabPage(m_pPropTab, "プロパティ");
	if(nRet == -1){
		return FALSE;
	}
	SetActivePage(m_objTab.GetCurSel());

	CDBListCtrl *pList;
	m_pPropTab->GetPageRect(rect);

	{
		pList = new CDBListCtrl();
		pList->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | LVS_REPORT | LVS_NOSORTHEADER,
					  rect, 
					  m_pPropTab, 
					  0);

		pList->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
		pList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		pList->InsertColumn(0, "名前");
		pList->InsertColumn(1, "値");
		pList->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		pList->SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_pPropTab->AddNewPage( 0, "テーブル", pList);
	}

	{
		pList = new CDBListCtrl();
		pList->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | LVS_REPORT | LVS_NOSORTHEADER,
					  rect, 
					  m_pPropTab, 
					  0);
		pList->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
		pList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		pList->InsertColumn(0, "名前");
		pList->InsertColumn(1, "値");
		pList->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		pList->SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_pPropTab->AddNewPage( 1, "カラム", pList);
	}

	{
		DWORD dwStyle = WS_VSCROLL | WS_HSCROLL | WS_BORDER | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL;
		m_pFuncEdit = new CSQLEdit();
		m_pFuncEdit->Create(dwStyle | WS_CHILD,
					  rect, 
					  m_pPropTab, 
					  0);
		m_pFuncEdit->SetReadOnly(TRUE);
		
//		m_pFuncEdit->ModifyStyle(dwStyle, 0);
//		m_pFuncEdit->ModifyStyle(0, dwStyle);

		CScrollBar *pHBar = m_pFuncEdit->GetScrollBarCtrl(SB_HORZ);
		CScrollBar *pVBar = m_pFuncEdit->GetScrollBarCtrl(SB_VERT);
		
		if(pHBar){
			pHBar->ModifyStyle(0, WS_BORDER);
		}
		
		if(pVBar){
			pVBar->ModifyStyle(0, WS_BORDER);
		}
		m_pFuncEdit->SetFont(&m_objFont);
		m_pPropTab->AddNewPage( 2, "ストアドプロシージャ", m_pFuncEdit);
		m_pFuncEdit->SetLineShow();	
	}

	m_pPropTab->SetActivePage(2);
	m_pPropTab->SetActivePage(1);
	m_pPropTab->SetActivePage(0);
	return TRUE;
}

BOOL CFuncTabView::AddOutput(){
	CSQLEdit *pEdit = new CSQLEdit();
	CRect rect;
	GetPageRect(rect);
	DWORD dwStyle = WS_TABSTOP | WS_VSCROLL | WS_HSCROLL | WS_BORDER | ES_MULTILINE | ES_READONLY | ES_AUTOHSCROLL | ES_AUTOVSCROLL;
	pEdit->Create(dwStyle | WS_CHILD,
				  rect, 
				  &m_objTab, 
				  ID_SQLEDITOR);
	pEdit->ModifyStyle(dwStyle, 0);
	pEdit->ModifyStyle(0, dwStyle);
	pEdit->m_bRunSQL = FALSE;
	
	CScrollBar *pHBar = pEdit->GetScrollBarCtrl(SB_HORZ);
	CScrollBar *pVBar = pEdit->GetScrollBarCtrl(SB_VERT);
	
	if(pHBar){
		pHBar->ModifyStyle(0, WS_BORDER);
	}
	
	if(pVBar){
		pVBar->ModifyStyle(0, WS_BORDER);
	}

	int nRet = AddTabPage(pEdit, "Log");
	if(nRet == -1){
		return FALSE;
	}
	return TRUE;
}

void CFuncTabView::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult){
	CTabCtrl *pTab = &m_objTab;
	int nIndex = pTab->GetCurSel();

	if(nIndex != m_nOldSel && (m_nOldSel >= 0)){
		//現在表示しているウィンドウを非表示にする
		TCITEM tcItem;
		memset(&tcItem, 0, sizeof(TCITEM));
		tcItem.mask = TCIF_PARAM;
		pTab->GetItem(m_nOldSel, &tcItem);
		CWnd *pWnd = (CWnd*)tcItem.lParam;
		if(pWnd){
			pWnd->ShowWindow(SW_HIDE);
		}
	}

	
	m_nOldSel = nIndex;

	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	pTab->GetItem(nIndex, &tcItem);
	CWnd *pWnd = (CWnd*)tcItem.lParam;
	if(pWnd){
		pWnd->ShowWindow(SW_SHOWNORMAL);
		CRect rect;
		GetPageRect(rect);
		pWnd->SetWindowPos(&wndTop,
						   rect.left, rect.top,
						   rect.Width(), rect.Height(),
						   SWP_SHOWWINDOW);		
	}
}

void CFuncTabView::OnDestroy(){
	TCITEM tcItem;
	CWnd *pWnd;

	//
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(0, &tcItem);
	CWndTabCtrl *pTab = (CWndTabCtrl*)tcItem.lParam;
	if(pTab){
		int nCount = pTab->GetItemCount();
		for(int i = 0; i < nCount; i++){
			memset(&tcItem, 0, sizeof(TCITEM));
			tcItem.mask = TCIF_PARAM;
			pTab->GetItem(0, &tcItem);
			pWnd = (CWnd*)tcItem.lParam;
			pWnd->SendMessage(WM_CLOSE, 0, 0);
			delete pWnd;
		}
		pTab->DeleteAllItems();
	}

	while(m_objTab.GetItemCount()){
		memset(&tcItem, 0, sizeof(TCITEM));
		tcItem.mask = TCIF_PARAM;
		m_objTab.GetItem(0, &tcItem);
		pWnd = (CWnd*)tcItem.lParam;
		pWnd->SendMessage(WM_CLOSE, 0, 0);
		delete pWnd;
		m_objTab.DeleteItem(0);
	}
	CView::OnDestroy();
}

void CFuncTabView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint){
	switch(lHint){
	case DB_OPEN:
		break;
	case DB_CLOSE:
		break;
	case DB_ADDMSG:
		{
			CString strMsg = *(CString*)pHint;
			AddMessage(strMsg);

		}
		break;
	case DB_PROP_CLEAR:
		RefreshPropertyToTable(NULL);
		RefreshPropertyToColumn(NULL);
		break;
	case DB_TABLE_PROP:
		{
			CString strTable = *(CString*)pHint;
			RefreshPropertyToTable(strTable);
			RefreshPropertyToColumn(strTable);
		}
		break;
	case DB_SQLNEW:
		AddSQLEditor();
		break;
	case DB_OPENSQL:
		{
			AddSQLEditor();
			
			int nIndex = m_objTab.GetItemCount() - 1;
			TCITEM tcItem;
			CSQLEdit *pEdit;
			memset(&tcItem, 0, sizeof(TCITEM));
			tcItem.mask = TCIF_PARAM;
			m_objTab.GetItem(nIndex, &tcItem);
			pEdit = (CSQLEdit*)tcItem.lParam;

			CString strFileName = *(CString*)pHint;
			if(pEdit->OpenSQL(strFileName)){
				int nPos = strFileName.ReverseFind('\\');
				CString strShortName = strFileName.Right(strFileName.GetLength() - nPos - 1);
				memset(&tcItem, 0, sizeof(TCITEM));
				tcItem.mask = TCIF_TEXT;
				tcItem.pszText = (LPTSTR)(LPCTSTR)strShortName;
				tcItem.cchTextMax = strShortName.GetLength();
				m_objTab.SetItem(nIndex, &tcItem);
			}
		}
		break;
	case DB_CLOSEWND:
		//保存チェック
		{
			TCITEM tcItem;
			CWnd *pWnd;

			memset(&tcItem, 0, sizeof(TCITEM));
			tcItem.mask = TCIF_PARAM;
			m_objTab.GetItem(0, &tcItem);
			CWndTabCtrl *pTab = (CWndTabCtrl*)tcItem.lParam;

			if(pTab){
				while(pTab->GetItemCount()){
					memset(&tcItem, 0, sizeof(TCITEM));
					tcItem.mask = TCIF_PARAM;
					pTab->GetItem(0, &tcItem);
					pWnd = (CWnd*)tcItem.lParam;
					pTab->DeleteItem(0);
					delete pWnd;
				}
				pTab->DeleteAllItems();
			}
			
			while(m_objTab.GetItemCount()){
				memset(&tcItem, 0, sizeof(TCITEM));
				tcItem.mask = TCIF_PARAM;
				m_objTab.GetItem(0, &tcItem);
				pWnd = (CWnd*)tcItem.lParam;
				SetActivePage(0);
				pWnd->SendMessage(WM_CLOSE, 0, 0);
				delete pWnd;
				m_objTab.DeleteItem(0);
			}
		}
		break;
	case DB_GETFUNC:
		{
			CString strData = *(CString*)pHint;
			m_pFuncEdit->SetSel(0, -1);
			m_pFuncEdit->ReplaceSel(strData, FALSE);
//			m_pFuncEdit->SetWindowText(strData);
			m_pFuncEdit->SetSel(0, 0);
			m_pPropTab->SetCurSel(2);
			m_pPropTab->SetActivePage(2);

		}
		break;
	case DB_RESULT:
		{
			CString strSQL = *(CString*)pHint;
			RefreshPropertyToColumn(strSQL);
		}	
		break;
	}
}

void CFuncTabView::OnEditCopy(){
	TCITEM tcItem;
	CWnd *pWnd;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	int nIndex = m_objTab.GetCurSel();
	m_objTab.GetItem(nIndex, &tcItem);
	pWnd = (CWnd*)tcItem.lParam;
	pWnd->PostMessage(WM_COMMAND, (WPARAM)ID_EDIT_COPY, (LPARAM)pWnd->m_hWnd);
}

void CFuncTabView::OnEditCut(){
	TCITEM tcItem;
	CWnd *pWnd;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	int nIndex = m_objTab.GetCurSel();
	m_objTab.GetItem(nIndex, &tcItem);
	pWnd = (CWnd*)tcItem.lParam;
	pWnd->PostMessage(WM_COMMAND, (WPARAM)ID_EDIT_CUT, (LPARAM)pWnd->m_hWnd);
}

void CFuncTabView::OnEditPaste(){
	TCITEM tcItem;
	CWnd *pWnd;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	int nIndex = m_objTab.GetCurSel();
	m_objTab.GetItem(nIndex, &tcItem);
	pWnd = (CWnd*)tcItem.lParam;
	pWnd->PostMessage(WM_COMMAND, (WPARAM)ID_EDIT_PASTE, (LPARAM)pWnd->m_hWnd);
}

void CFuncTabView::OnEditUndo(){
	TCITEM tcItem;
	CWnd *pWnd;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	int nIndex = m_objTab.GetCurSel();
	m_objTab.GetItem(nIndex, &tcItem);
	pWnd = (CWnd*)tcItem.lParam;
	pWnd->PostMessage(WM_COMMAND, (WPARAM)ID_EDIT_UNDO, (LPARAM)pWnd->m_hWnd);
}

void CFuncTabView::OnAllselect(){
	TCITEM tcItem;
	CWnd *pWnd;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	int nIndex = m_objTab.GetCurSel();
	m_objTab.GetItem(nIndex, &tcItem);
	pWnd = (CWnd*)tcItem.lParam;
	pWnd->PostMessage(WM_COMMAND, (WPARAM)ID_ALLSELECT, (LPARAM)pWnd->m_hWnd);
}

void CFuncTabView::AddMessage(LPCTSTR szMsg){
	CString strText;
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	CEdit *pWnd;
	int nStart;
	int nEnd;
	int nIndex = 1;
	TCITEM tcItem;

	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nIndex, &tcItem);
	
	pWnd = (CEdit*)tcItem.lParam;

	int nOldLineCnt = pWnd->GetLineCount();

	pWnd->GetWindowText(strText);

	pWnd->GetSel(nStart, nEnd);
	strText += szMsg;
	strText += "\r\n";
	pWnd->SetWindowText(strText);
	
	int nLen = strText.GetLength();
	int nNewLineCnt = pWnd->GetLineCount();

	
	if(nLen > nEnd){
		pWnd->SetSel(nLen, nLen, FALSE);
	}else{
		pWnd->SetSel(nStart, nEnd, FALSE);
	}

	if(pApp->m_bLogTabActive){
		m_objTab.SetCurSel(nIndex);
		SetActivePage(nIndex);
	}
}

void CFuncTabView::RefreshPropertyToTable(LPCTSTR pszTable){
	TCITEM tcItem;
	CDBListCtrl *pList;
	CWndTabCtrl *pTab;
	int nIndex = m_objTab.GetCurSel();

	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;

	m_objTab.GetItem(0, &tcItem);
	pTab = (CWndTabCtrl*)tcItem.lParam;

	pTab->GetItem(0, &tcItem);
	pList = (CDBListCtrl*)tcItem.lParam;

	if(!pTab || !::IsWindow(pTab->m_hWnd)){
		return;
	}

	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	
	pTab->GetItem(0, &tcItem);
	pList = (CDBListCtrl*)tcItem.lParam;

	pList->DeleteAllItems();
	if(!pszTable){
		return;
	}

	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	CAdoDatabase *pDb = pFrm->GetDBObject();
//	eDBType eDbType = pDb->GetDBType();
//	eODBCType eOdbcType = pDb->GetODBCType();

//	if((eDbType != ODBC) || ((eDbType == ODBC) && (eOdbcType == ODBC_SQLSERVER))){
		PTABLEINFO pInfo = pDb->GetTableInfo(pszTable);
		if(!pInfo){
			return;
		}
//		pList->InsertItem(0, "TABLE_QUALIFIRE", 0);
//		pList->SetItemText(0, 1, pInfo->szQualifier);

		pList->InsertItem(0, "オーナー", 0);
		pList->SetItemText(0, 1, pInfo->szOwner);

		pList->InsertItem(1, "テーブル名", 0);
		pList->SetItemText(1, 1, pInfo->szTableName);

		pList->InsertItem(2, "種別", 0);
		switch(pInfo->nType){
		case T_TABLE:
			pList->SetItemText(2, 1, "テーブル");
			break;
		case T_SYSTEMTABLE:
			pList->SetItemText(2, 1, "システムテーブル");
			break;
		case T_VIEW:
			pList->SetItemText(2, 1, "ビュー");
			break;
		default:
			pList->SetItemText(2, 1, "不明");
			break;
		}

		pList->SetAllColumnWidth();
//	}else{
//		return;
//	}
}

void CFuncTabView::RefreshPropertyToColumn(LPCTSTR pszTable){
	TCITEM tcItem;
	CDBListCtrl *pList;
	CWndTabCtrl *pTab;
	int nIndex = m_objTab.GetCurSel();

	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;

	m_objTab.GetItem(0, &tcItem);
	pTab = (CWndTabCtrl*)tcItem.lParam;

	if(!pTab || !::IsWindow(pTab->m_hWnd)){
		return;
	}

	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	
	pTab->GetItem(1, &tcItem);
	pList = (CDBListCtrl*)tcItem.lParam;

	if(!pList){
		return;
	}

	pList->DeleteAllItems();
	CHeaderCtrl *pHead = pList->GetHeaderCtrl();
	while(pHead->GetItemCount() > 1){
		pList->DeleteColumn(1);
	}
	
	if(!pszTable){
		return;
	}
	enum rowIndex{
		IDX_TYPE		= 0,
		IDX_LENGTH,
		IDX_ISNULL,
		IDX_IDENTITY,
		IDX_KEY
	};

	pList->SetRedraw(FALSE);
	pList->InsertItem(IDX_TYPE, "型",		0);
	pList->InsertItem(IDX_LENGTH, "長さ",	0);
	pList->InsertItem(IDX_ISNULL, "NULL許可",0);
	pList->InsertItem(IDX_IDENTITY, "IDENTITY",0);
	pList->InsertItem(IDX_KEY, "キー",0);

	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	CAdoDatabase *pDb = pFrm->GetDBObject();
	
	
	CColumnInfo *pInfo = pDb->GetColumnInfo(pszTable);
	if(pInfo){
		CString strVal;
		int nType;
		int nCol = 1;
		int nCnt = pInfo->GetSize();
		PCOLUMNINFO pColInfo;
		for(int i = 0; i < nCnt; i++){
			nCol = nCnt + 1;
			pColInfo = pInfo->GetInfo(i);

			//カラム名
			strVal = pColInfo->szColumnName;
			nCol = pList->InsertColumn(nCol, strVal);
			
			//型
			if(strlen(pColInfo->szTypeName)){
				strVal = pColInfo->szTypeName;
			}else{
				nType = pColInfo->nType;
				CMainFrame::GetDBColumType(strVal, nType, NULL);
			}
			pList->SetItemText(IDX_TYPE, nCol, strVal);

			//サイズ
			if(!strVal.Compare("char") || !strVal.Compare("wchar")){
				strVal.Format("%d", pColInfo->nLen);
				pList->SetItemText(IDX_LENGTH, nCol, strVal);
			}else{
				pList->SetItemText(IDX_LENGTH, nCol, "");
			}

			//IsNUll
			if(pColInfo->bNull){
				pList->SetItemText(IDX_ISNULL, nCol, "○");
			}else{
				pList->SetItemText(IDX_ISNULL, nCol, "－");
			}

			pList->SetItemText(IDX_IDENTITY, nCol, "－");

			if(pColInfo->bKey){
				pList->SetItemText(IDX_KEY, nCol, "○");
			}else{
				pList->SetItemText(IDX_KEY, nCol, "－");
			}

		}
		delete pInfo;
	}else{
	
		if(pDb->CheckCommandType(pszTable) != 1){
			return;
		}

		_RecordsetPtr rs = NULL;
		
		
		rs = pDb->ExecSQL(pszTable);

		if(rs == NULL){
			//テーブルを再取得させる
			return;
		}

		FieldsPtr fields = rs->GetFields();
		LONG nCnt = fields->GetCount();
		_variant_t vIndex;
		FieldPtr field;
		PropertiesPtr props;
		PropertyPtr property;
		_variant_t val;

		CString strVal;
		int nType;
		int nCol = 1;
		for(int i = 0; i < nCnt; i++){
			vIndex = (short)(nCnt - i - 1);
			field = fields->GetItem(&vIndex);
			props = field->Properties;

			//カラム名
			val = field->GetName();
			if((val.vt == VT_NULL) || (val.vt == VT_EMPTY)){
				strVal = "";
			}else{
				strVal = val.bstrVal;
			}
			nCol = pList->InsertColumn(nCol, strVal);
			
			//型
//			if(strlen(pColInfo->szTypeName)){
//				strVal = pColInfo->szTypeName;
//			}else{
				nType = field->Type;
				CMainFrame::GetDBColumType(strVal, nType, NULL);
//			}
			pList->SetItemText(IDX_TYPE, nCol, strVal);

			//サイズ
			try{
				strVal.Format("%d", field->DefinedSize);
			}catch(_com_error e){
				strVal = "?";
			}catch(...){
				strVal = "?";
			}
			pList->SetItemText(IDX_LENGTH, nCol, strVal);

			//IsNUll
			if(field->Attributes & adFldIsNullable){
				pList->SetItemText(IDX_ISNULL, nCol, "○");
			}else{
				pList->SetItemText(IDX_ISNULL, nCol, "－");
			}

			try{
				property = props->GetItem("ISAUTOINCREMENT");
				if(property){
					_variant_t val = property->GetValue();
					if(val.vt == VT_BOOL){
						if(val.boolVal != 0){
							pList->SetItemText(IDX_IDENTITY, nCol, "○");
						}else{
							pList->SetItemText(IDX_IDENTITY, nCol, "－");
						}
					}else{
						pList->SetItemText(IDX_IDENTITY, nCol, "－");
					}
				}else{
					pList->SetItemText(IDX_IDENTITY, nCol, "－");
				}
			}catch(...){
				pList->SetItemText(IDX_IDENTITY, nCol, "－");
			}
			try{
				property = props->GetItem("KEYCOLUMN");
				if(property){
					val = property->GetValue();
					if(val.vt == VT_BOOL){
						if(val.boolVal != 0){
							pList->SetItemText(IDX_KEY, nCol, "○");
						}else{
							pList->SetItemText(IDX_KEY, nCol, "－");
						}
					}else{
						pList->SetItemText(IDX_KEY, nCol, "－");
					}
				}else{
					pList->SetItemText(IDX_KEY, nCol, "－");
				}
			}catch(...){
				pList->SetItemText(IDX_KEY, nCol, "－");
			}
		}
		rs->Close();
	}
	pList->SetAllColumnWidth();
	pList->SetRedraw(TRUE);
	pList->InvalidateRect(NULL);
}

void CFuncTabView::OnUpdateEditCopy(CCmdUI* pCmdUI){
	int nIndex = m_objTab.GetCurSel();
	if(nIndex <= 0){
		pCmdUI->Enable(FALSE);
		return;
	}
	CSQLEdit *pWnd;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nIndex, &tcItem);
	pWnd = (CSQLEdit*)tcItem.lParam;
	pWnd->OnUpdateEditCopy(pCmdUI);
}

void CFuncTabView::OnUpdateEditCut(CCmdUI* pCmdUI){
	int nIndex = m_objTab.GetCurSel();
	if(nIndex <= 0){
		pCmdUI->Enable(FALSE);
		return;
	}
	CSQLEdit *pWnd;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nIndex, &tcItem);
	pWnd = (CSQLEdit*)tcItem.lParam;
	pWnd->OnUpdateEditCut(pCmdUI);
}

void CFuncTabView::OnUpdateEditPaste(CCmdUI* pCmdUI){
	int nIndex = m_objTab.GetCurSel();
	if(nIndex <= 0){
		pCmdUI->Enable(FALSE);
		return;
	}
	CSQLEdit *pWnd;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nIndex, &tcItem);
	pWnd = (CSQLEdit*)tcItem.lParam;
	pWnd->OnUpdateEditPaste(pCmdUI);
}

void CFuncTabView::OnUpdateEditUndo(CCmdUI* pCmdUI){
	int nIndex = m_objTab.GetCurSel();
	if(nIndex <= 0){
		pCmdUI->Enable(FALSE);
		return;
	}
	CSQLEdit *pWnd;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nIndex, &tcItem);
	pWnd = (CSQLEdit*)tcItem.lParam;
	pWnd->OnUpdateEditUndo(pCmdUI);
}

void CFuncTabView::OnUpdateAllselect(CCmdUI* pCmdUI){
	int nIndex = m_objTab.GetCurSel();
	if(nIndex <= 0){
		pCmdUI->Enable(FALSE);
		return;
	}
	CSQLEdit *pWnd;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nIndex, &tcItem);
	pWnd = (CSQLEdit*)tcItem.lParam;
	pWnd->OnUpdateEditUndo(pCmdUI);	
}


void CFuncTabView::OnSqlSaveas(){
	CSQLEdit *pEdit;
	int nIndex = m_objTab.GetCurSel();
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nIndex, &tcItem);
	pEdit = (CSQLEdit*)tcItem.lParam;
	if(pEdit->SaveSQL(TRUE)){
		CString strFileName = pEdit->GetFileName();
		GetDocument()->UpdateAllViews(this, DB_REFRESH_TREE, (CObject*)&strFileName);

		//タブのラベルを変更
		memset(&tcItem, 0, sizeof(TCITEM));
		int nLen = strFileName.ReverseFind('\\');
		CString strShort = strFileName.Right(strFileName.GetLength() - nLen - 1);
		nLen = strShort.GetLength();
		tcItem.mask = TCIF_TEXT;
		tcItem.pszText = strShort.GetBuffer(nLen);
		tcItem.cchTextMax = nLen;
		m_objTab.SetItem(nIndex, &tcItem);
	}
}

void CFuncTabView::OnSqlSqve(){
	int nIndex = m_objTab.GetCurSel();
	CSQLEdit *pEdit;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nIndex, &tcItem);
	pEdit = (CSQLEdit*)tcItem.lParam;
	if(pEdit->SaveSQL(FALSE)){
		CString strFileName = pEdit->GetFileName();
		GetDocument()->UpdateAllViews(this, DB_REFRESH_TREE, (CObject*)&strFileName);

		//タブのラベルを変更
		memset(&tcItem, 0, sizeof(TCITEM));
		int nLen = strFileName.ReverseFind('\\');
		CString strShort = strFileName.Right(strFileName.GetLength() - nLen - 1);
		nLen = strShort.GetLength();
		tcItem.mask = TCIF_TEXT;
		tcItem.pszText = strShort.GetBuffer(nLen);
		tcItem.cchTextMax = nLen;
		m_objTab.SetItem(nIndex, &tcItem);
	}
}

void CFuncTabView::OnSqlrun(){
	int nIndex = m_objTab.GetCurSel();
	CSQLEdit *pEdit;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nIndex, &tcItem);
	pEdit = (CSQLEdit*)tcItem.lParam;
	pEdit->PostMessage(WM_COMMAND, (WPARAM)ID_SQLRUN, (LPARAM)pEdit->m_hWnd);
}


void CFuncTabView::OnUpdateSqlSaveas(CCmdUI* pCmdUI){
	int nSel = m_objTab.GetCurSel();
	if(nSel < 2){
		pCmdUI->Enable(FALSE);
		return;
	}

	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	if(pFrm->m_hThreadHandle){
		pCmdUI->Enable(FALSE);
//	}else{
//		pCmdUI->Enable(pFrm->GetDBObject()->IsConnect());
	}
}

void CFuncTabView::OnUpdateSqlSqve(CCmdUI* pCmdUI){
	int nSel = m_objTab.GetCurSel();
	if(nSel < 2){
		pCmdUI->Enable(FALSE);
		return;
	}
	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	if(pFrm->m_hThreadHandle){
		pCmdUI->Enable(FALSE);
//	}else{
//		pCmdUI->Enable(pFrm->GetDBObject()->IsConnect());
	}
}

void CFuncTabView::OnUpdateSqlrun(CCmdUI* pCmdUI){
	int nSel = m_objTab.GetCurSel();
	if(nSel < 2){
		pCmdUI->Enable(FALSE);
		return;
	}

	CSQLEdit *pEdit;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nSel, &tcItem);
	pEdit = (CSQLEdit*)tcItem.lParam;

	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	if(pFrm->m_hThreadHandle){
		pCmdUI->Enable(FALSE);
	}else if(!pFrm->GetDBObject()->IsConnect()){
		pCmdUI->Enable(FALSE);
	}else{
		pEdit->OnUpdateEditUndo(pCmdUI);
	}
}

void CFuncTabView::OnContextMenu(CWnd* pWnd, CPoint point){
	CPoint HitPoint = point;
	m_objTab.ScreenToClient(&HitPoint);
	
	TCHITTESTINFO tcHitTest;
	tcHitTest.pt = HitPoint;
	tcHitTest.flags = TCHT_ONITEM;
	m_nPopupTargetIndex = m_objTab.HitTest(&tcHitTest);
	if(m_nPopupTargetIndex == -1){
		return;
	}

	CMenu objMenu;
	objMenu.LoadMenu(IDR_POPUP);
	CMenu *pPopup = objMenu.GetSubMenu(0);

	if(m_nPopupTargetIndex < 2){
		pPopup->EnableMenuItem(IDM_TABCLOSE, MF_BYCOMMAND | MF_GRAYED);
	}else{
		pPopup->EnableMenuItem(IDM_TABCLOSE, MF_BYCOMMAND | MF_ENABLED);
	}
	
	pPopup->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
		
}

void CFuncTabView::OnTabclose(){
	if(m_nPopupTargetIndex == -1){
		return;
	}
	CloseTab(m_nPopupTargetIndex);
}	

void CFuncTabView::SetActivePage(int nIndex){
	if(nIndex == -1){
		nIndex = m_objTab.GetCurSel();
	}

	if(nIndex != m_nOldSel && (m_nOldSel >= 0)){
		//現在表示しているウィンドウを非表示にする
		TCITEM tcItem;
		memset(&tcItem, 0, sizeof(TCITEM));
		tcItem.mask = TCIF_PARAM;
		m_objTab.GetItem(m_nOldSel, &tcItem);
		CWnd *pWnd = (CWnd*)tcItem.lParam;
		if(pWnd){
			pWnd->ShowWindow(SW_HIDE);
		}
	}

	m_nOldSel = nIndex;

	SetPagePos(nIndex);
}

void CFuncTabView::SetPagePos(int nIndex){
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nIndex, &tcItem);
	CWnd *pWnd = (CWnd*)tcItem.lParam;
	if(pWnd){
		pWnd->ShowWindow(SW_SHOWNORMAL);
		CRect rect;
		GetPageRect(rect);
		pWnd->SetWindowPos(&wndTop,
						   rect.left, rect.top,
						   rect.Width(), rect.Height(),
						   SWP_SHOWWINDOW);	
		m_objTab.InvalidateRect(NULL);
	}
}

BOOL CFuncTabView::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct){
	return CView::OnCopyData(pWnd, pCopyDataStruct);
}

void CFuncTabView::OnSqlNew(){
	AddSQLEditor();
}

void CFuncTabView::OnUpdateSqlNew(CCmdUI* pCmdUI){
}

BOOL CFuncTabView::CloseTab(int nIndex){
	if(nIndex < 2){
		return FALSE;
	}
	int nNowIndex = m_objTab.GetCurSel();

	CWnd *pWnd;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nIndex, &tcItem);
	pWnd = (CWnd*)tcItem.lParam;

	pWnd->SendMessage(WM_CLOSE, 0, 0);
	delete pWnd;

	m_objTab.DeleteItem(nIndex);
	
	int nNewIndex = nIndex - 1;
	m_objTab.SetCurSel(nNewIndex);
	SetActivePage(nNewIndex);
	return TRUE;
}

BOOL CFuncTabView::PreTranslateMessage(MSG* pMsg) {
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください

	switch(pMsg->message){
	case WM_MBUTTONDOWN:
		if(pMsg->hwnd == m_objTab.m_hWnd){
			int nX = LOWORD(pMsg->lParam);
			int nY = HIWORD(pMsg->lParam);
			CPoint HitPoint(nX, nY);
//			m_objTab.ScreenToClient(&HitPoint);
			
			TCHITTESTINFO tcHitTest;
			tcHitTest.pt = HitPoint;
			tcHitTest.flags = TCHT_ONITEM;
			int nIndex = m_objTab.HitTest(&tcHitTest);
			if(nIndex >= 2){
				//タブを閉じる
				CloseTab(nIndex);
			}
		}
		break;
	}
	return CView::PreTranslateMessage(pMsg);
}

void CFuncTabView::GetPageRect(CRect &rect, CTabCtrl *pTab){
	if(!pTab){
		pTab = &m_objTab;
	}
	pTab->GetClientRect(rect);
	pTab->AdjustRect(FALSE, rect);
	rect.left	+= 2;
	rect.top	+= 2;
	rect.right	-= 2;
	rect.bottom	-= 2;
}

BOOL CFuncTabView::CheckSaveSQL(){
	int nCnt = m_objTab.GetItemCount();

	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	for(int i = 2; i < nCnt; i++){
		m_objTab.GetItem(i, &tcItem);

		CSQLEdit *pEdit = (CSQLEdit*)tcItem.lParam;
		if(pEdit && pEdit->m_bRunSQL && pEdit->GetModify()){
			int nRet = AfxMessageBox("保存されていないSQLがありますが、終了しますか？\n(保存されていないSQLは終了時に保存確認ダイアログが表示されます。)", MB_OKCANCEL);
			if(nRet == IDOK){
				return TRUE;
			}else{
				return FALSE;
			}
		}
	}
	return TRUE;
}



void CFuncTabView::EnableSQLEdit(BOOL bEnable){
	int nCnt = m_objTab.GetItemCount();

	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	CSQLEdit *pEdit;
	for(int i = 2; i < nCnt; i++){
		m_objTab.GetItem(i, &tcItem);

		pEdit = (CSQLEdit*)tcItem.lParam;
		pEdit->EnableWindow(bEnable);
	}
}


