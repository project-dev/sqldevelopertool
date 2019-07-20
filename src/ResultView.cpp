// ResultView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DBTool.h"
#include "ResultView.h"
#include "MainFrm.h"
#include "DebugSupport.h"
#include "devlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int CALLBACK CResultView::SortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CResultView

IMPLEMENT_DYNCREATE(CResultView, CView)

CResultView::CResultView()
{
	m_hThreadHandle = NULL;
}

CResultView::~CResultView()
{
}


BEGIN_MESSAGE_MAP(CResultView, CView)
	//{{AFX_MSG_MAP(CResultView)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_COMMAND(ID_REFRESH_VIEW, OnRefreshView)
	ON_UPDATE_COMMAND_UI(ID_REFRESH_VIEW, OnUpdateRefreshView)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_ALLSELECT, OnAllselect)
	ON_UPDATE_COMMAND_UI(ID_ALLSELECT, OnUpdateAllselect)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDC_BTN_FIRST, OnBtnFirst)
	ON_UPDATE_COMMAND_UI(IDC_BTN_FIRST, OnUpdateBtnFirst)
	ON_COMMAND(IDC_BTN_PREV,  OnBtnPrev)
	ON_UPDATE_COMMAND_UI(IDC_BTN_PREV, OnUpdateBtnPrev)
	ON_COMMAND(IDC_BTN_NEXT,  OnBtnNext)
	ON_UPDATE_COMMAND_UI(IDC_BTN_NEXT, OnUpdateBtnNext)
	ON_COMMAND(IDC_BTN_END,   OnBtnEnd)
	ON_UPDATE_COMMAND_UI(IDC_BTN_END, OnUpdateBtnEnd)
	ON_COMMAND(IDC_BTN_SNAP,   OnBtnSnap)
	ON_UPDATE_COMMAND_UI(IDC_BTN_SNAP, OnUpdateBtnSnap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultView 描画

void CResultView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CResultView 診断

#ifdef _DEBUG
void CResultView::AssertValid() const
{
	CView::AssertValid();
}

void CResultView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResultView メッセージ ハンドラ

void CResultView::OnInitialUpdate(){
	CView::OnInitialUpdate();
	CRect rect;
	GetClientRect(rect);
	m_objList.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | LVS_REPORT | LVS_OWNERDRAWFIXED,
					 rect,
					 this,
					 0);
	m_objList.ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	m_objList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_objList.InsertColumn(0, "データなし");
	m_objList.SetAllColumnWidth();

	DWORD dwStyle = WS_CHILD | WS_TABSTOP;
	CRect btnRect;
	m_objBtnFirst.Create(    "|<", dwStyle | BS_PUSHBUTTON, btnRect, this, IDC_BTN_FIRST);
	m_objBtnPrev.Create(     "<<", dwStyle | BS_PUSHBUTTON, btnRect, this, IDC_BTN_PREV);
	m_objBtnNext.Create(     ">>", dwStyle | BS_PUSHBUTTON, btnRect, this, IDC_BTN_NEXT);
	m_objBtnEnd.Create(      ">|", dwStyle | BS_PUSHBUTTON, btnRect, this, IDC_BTN_END);
	m_objEdPage.Create(      dwStyle | WS_BORDER, btnRect, this, IDC_ED_PAGE);
	m_objEdPageBase.Create(  dwStyle | WS_BORDER | ES_READONLY, btnRect, this, IDC_ED_PAGE_BASE);
	m_objBtnSnap.Create(     "Snap", dwStyle | BS_PUSHBUTTON, btnRect, this, IDC_BTN_SNAP);

	CFont *pFont = m_objList.GetFont();
	
	m_objBtnFirst.SetFont(pFont);
	m_objBtnPrev.SetFont(pFont);
	m_objBtnNext.SetFont(pFont);
	m_objBtnEnd.SetFont(pFont);
	m_objEdPage.SetFont(pFont);
	m_objEdPageBase.SetFont(pFont);
	m_objBtnSnap.SetFont(pFont);

	m_objEdPage.SetWindowText("0");
	m_objEdPageBase.SetWindowText("0");
	
	SetCtrlPos();
	
	//スレッド監視用タイマー
	SetTimer(IDS_RESULT_TIMER, 100, NULL);
}

void CResultView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) {
	CString strMsg;
	switch(lHint){
	case DB_OPEN:
		m_objList.DeleteAllItems();
		while(m_objList.DeleteColumn(0)){
		}
		m_objList.InsertColumn(0, "データなし");
		m_objList.SetAllColumnWidth();
		break;
	case DB_CLOSE:
		m_objList.DeleteAllItems();
		while(m_objList.DeleteColumn(0)){
		}
		m_objList.InsertColumn(0, "データなし");
		m_objList.SetAllColumnWidth();
		break;
		break;
	case DB_RESULT:
	case DB_REFRESH:
		{
			if(pHint){
				CString strSQL = *(CString*)pHint;
				Refresh(strSQL);
			}else{
				Refresh(m_strResultSQL);
			}
		}
		break;
	}
}

void CResultView::OnDestroy() {
	CRect rect;
	GetWindowRect(rect);
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	pApp->m_nResultPaneHeight = rect.Height();
	RemoveCellData();
	CView::OnDestroy();
}

DWORD WINAPI CResultView::LoadTableThread(LPVOID lpParameter){
	CWaitCursor objCur;
	::SetEvent(CDBToolApp::m_evSQLRUN);
	
	CWaitCursor objCursor;
	PTHREADINFO pInfo = (PTHREADINFO)lpParameter;
	CResultView *pView = (CResultView*)pInfo->pWnd;
	HWND hWnd = pView->m_hWnd;
#if MODE_PAGE_LIST
	pView->RemoveCellData();
#endif

	pView->SetRedraw(FALSE);
	CDBListCtrl *pList = pView->GetListCtrl();
	pList->DeleteAllItems();
	while(pList->DeleteColumn(0)){
	}

	if(!pInfo->pszSQL){
		pList->InsertColumn(0, "データなし");
		pList->SetAllColumnWidth();
		pView->SetRedraw(TRUE);
		pView->InvalidateRect(NULL);
		::ResetEvent(CDBToolApp::m_evSQLRUN);
		return 0;
	}

	CString strSQL = pInfo->pszSQL;
	if(!strSQL.GetLength()){
		pView->SetRedraw(TRUE);
		pView->InvalidateRect(NULL);
		::ResetEvent(CDBToolApp::m_evSQLRUN);
		return 0;
	}

	CString strMsg;
	strMsg.Format(IDS_OUT_MSG_SQL, pInfo->pszSQL);
	CMainFrame *pFrm = (CMainFrame*)pInfo->pFrm;
	if(pFrm){
		CMainFrame::SetOutputMsg(pFrm->m_hWnd, strMsg);
	}

	CAdoDatabase *pDb = pFrm->GetDBObject();
	int nType = pDb->CheckCommandType(strSQL);
	LPCTSTR pszSQL = strSQL;
	DWORD dwStart = ::GetTickCount();
	_RecordsetPtr rs = pDb->ExecSQL(pszSQL);
	DWORD dwSpan = ::GetTickCount() - dwStart;
	if(pFrm){
		CString strSpan;
		strSpan.Format("SQL実行時間 %d(msec)", dwSpan);
		CMainFrame::SetOutputMsg(pFrm->m_hWnd, strSpan);
	}
	strMsg = pDb->GetError();

	BOOL bIsNull;
	TRY{
		if(!strMsg.IsEmpty()){
			if(pFrm){
				CMainFrame::SetOutputMsg(pFrm->m_hWnd, strMsg);
			}
			if(rs){
				rs->Close();
			}
			pView->SetRedraw(TRUE);
			pView->InvalidateRect(NULL);
			::ResetEvent(CDBToolApp::m_evSQLRUN);
			return FALSE;
		}else{
			CString strSQL = pszSQL;
			strSQL.TrimLeft();

			//暫定対応
			//本当は、実行したSQLが参照系か操作系かを見極めたい。
			if(nType == 0){
				//再取得
				rs = pDb->ExecSQL(pView->m_strResultSQL);
			}

			if(rs != NULL){
#if MODE_PAGE_LIST
				FieldsPtr fields = rs->GetFields();
				LONG nCnt = fields->GetCount();
				_variant_t vIndex;
				CStringArray arrNames;
				for(int i = 0; i < nCnt; i++){
					vIndex = (short)i;
					_variant_t val = fields->GetItem(&vIndex)->GetName();
					CString strName = val.bstrVal;
					arrNames.Add(strName);
					pList->InsertColumn(i, strName);
				}
				int nIndex = 0;
				CString strName;
				_variant_t val;
				CString strValue;
				int nMax = arrNames.GetSize();
				PCELL pCell;
				CArray<PCELL, PCELL>* pArr;
				int nRsCnt = 0;
				while(rs->EndOfFile == VARIANT_FALSE){
					pArr = new CArray<PCELL, PCELL>();

					for(int i = 0; i < nMax; i++){
						pCell = new CELL();
						memset(pCell, 0, sizeof(CELL));

						strName = arrNames.GetAt(i);
						val = pDb->GetFieldValue(rs, strName);
						bIsNull = FALSE;
						if(val.vt == VT_NULL){
							strValue = "(NULL)";
							bIsNull = TRUE;
						}else{
							if(val.vt == VT_BOOL){
								if(val.boolVal){
									strValue.Format("TRUE(%d)", val.boolVal);
								}else{
									strValue.Format("FALSE(%d)", val.boolVal);
								}
							}else{
								val.ChangeType(VT_BSTR);
								strValue = val.bstrVal;
							}
						}
						pCell->isNull = bIsNull;
						int valLen = strValue.GetLength() + 1;
						pCell->pszValue = new char[valLen];
						memset(pCell->pszValue, 0, valLen);
						strcpy(pCell->pszValue, (LPCTSTR)strValue);
						pArr->Add(pCell);
					}
					pView->m_arrCell.Add(pArr);
					nIndex++;
					rs->MoveNext();
					nRsCnt++;
				}

				pView->m_nCurPage = nRsCnt ? 1 : 0;
				pView->m_nPage = (nRsCnt / MAX_PAGE_ROW_CNT) + 1;

				pView->ViewPage(1);

				pList->SetAllColumnWidth();
				rs->Close();
				if(nType == 1){
					pView->m_strResultSQL = pInfo->pszSQL;
				}

#else
				FieldsPtr fields = rs->GetFields();
				LONG nCnt = fields->GetCount();
				_variant_t vIndex;
				CStringArray arrNames;
				for(int i = 0; i < nCnt; i++){
					vIndex = (short)i;
					_variant_t val = fields->GetItem(&vIndex)->GetName();
					CString strName = val.bstrVal;
					arrNames.Add(strName);
					pList->InsertColumn(i, strName);
				}
				
				int nIndex = 0;
				CString strName;
				_variant_t val;
				CString strValue;
				int nMax = arrNames.GetSize();
				while(rs->EndOfFile == VARIANT_FALSE){
					for(int i = 0; i < nMax; i++){
						strName = arrNames.GetAt(i);
						val = pDb->GetFieldValue(rs, strName);
						bIsNull = FALSE;
						if(val.vt == VT_NULL){
							strValue = "(NULL)";
							bIsNull = TRUE;
						}else{
							if(val.vt == VT_BOOL){
								if(val.boolVal){
									strValue.Format("TRUE(%d)", val.boolVal);
								}else{
									strValue.Format("FALSE(%d)", val.boolVal);
								}
							}else{
								val.ChangeType(VT_BSTR);
								strValue = val.bstrVal;
							}
						}
						if(i == 0){
							pList->InsertItem(nIndex, strValue, 0);
						}else{
							pList->SetItemText(nIndex, i, strValue);
						}
						pList->SetIsNull(nIndex, i, bIsNull);
					}
					nIndex++;
					rs->MoveNext();
				}

				pList->SetAllColumnWidth();
				rs->Close();
				if(nType == 1){
					pView->m_strResultSQL = pInfo->pszSQL;
				}
#endif
			}
			strMsg = "SQLの実行が完了しました\r\n";
			if(pFrm){
				CMainFrame::SetOutputMsg(pFrm->m_hWnd, strMsg);
			}
			pView->SetRedraw(TRUE);
			pView->InvalidateRect(NULL);
		}
	}CATCH_ALL(e){
		strMsg = pDb->GetError();
		if(pFrm){
			CMainFrame::SetOutputMsg(pFrm->m_hWnd, strMsg);
		}
		if(rs){
			rs->Close();
		}
		pView->SetRedraw(TRUE);
		pView->InvalidateRect(NULL);
	}END_CATCH_ALL
	::ResetEvent(CDBToolApp::m_evSQLRUN);
	
	return 0;
}

void CResultView::ViewPage(int page){
	m_objList.SetRedraw(FALSE);

	m_objList.DeleteAllItems();
	
	if((page > m_nPage) || (page < 1)){
		m_objEdPage.SetWindowText("0");
		m_objEdPageBase.SetWindowText("0");
	}else{
		CString strPage;
		strPage.Format("%d", m_nCurPage);
		m_objEdPage.SetWindowText(strPage);
		strPage.Format("%d", m_nPage);
		m_objEdPageBase.SetWindowText(strPage);

		int start = (page - 1) * MAX_PAGE_ROW_CNT + 1;
		int end = start + MAX_PAGE_ROW_CNT;
		if(end > m_arrCell.GetSize()){
			end = m_arrCell.GetSize();
		}

		PCELL pCell;
		CArray<PCELL, PCELL>* pArr;

		for(int i = start; i <= end; i++){
			int nIndex = i - 1;
			pArr = m_arrCell.GetAt(nIndex);
			if(!pArr){
				continue;
			}

			int nLstIdx = i - start;
			for(int j = 0; j < pArr->GetSize(); j++){
				pCell = pArr->GetAt(j);
				if(j == 0){
					m_objList.InsertItem(nLstIdx, pCell->pszValue, 0);
				}else{
					m_objList.SetItemText(nLstIdx, j, pCell->pszValue);
				}
				m_objList.SetIsNull(nLstIdx, j, pCell->isNull);
			}
		}
	}
	m_objList.SetRedraw(TRUE);
	m_objList.InvalidateRect(NULL);
}
#if 0
BOOL CResultView::LoadTable(LPCTSTR szSQL){
	m_objList.DeleteAllItems();
	while(m_objList.DeleteColumn(0)){
	}
	if(!szSQL){
		m_objList.InsertColumn(0, "データなし");
		m_objList.SetAllColumnWidth();
		return FALSE;
	}

	if(strlen(szSQL) == 0){
		return FALSE;
	}
	CString strMsg;
	strMsg.Format(IDS_OUT_MSG_SQL, szSQL);
	CDocument *pDoc = GetDocument();
	pDoc->UpdateAllViews(NULL, DB_ADDMSG, (CObject*)&strMsg);

	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	if(pFrm){
		pFrm->SetOutputMsg(strMsg);
	}
	
	CAdoDatabase *pDb = pFrm->GetDBObject();
	int nType = pDb->CheckCommandType(szSQL);
	_RecordsetPtr rs = pDb->ExecSQL(szSQL);
	strMsg = pDb->GetError();
	

	TRY{
		if(!strMsg.IsEmpty() || (rs == NULL) || (rs->GetRecordCount() == 0)){
			if(!strMsg.IsEmpty()){
				GetDocument()->UpdateAllViews(NULL, DB_ADDMSG, (CObject*)&strMsg);
				if(rs){
					rs->Close();
				}
				m_objList.InsertColumn(0, "データなし");
				m_objList.SetAllColumnWidth();
				return FALSE;
			}
		}else{
			FieldsPtr fields = rs->GetFields();
			LONG nCnt = fields->GetCount();
			_variant_t vIndex;
			CStringArray arrNames;
			for(int i = 0; i < nCnt; i++){
				vIndex = (short)i;
				_variant_t val = fields->GetItem(&vIndex)->GetName();
				CString strName = val.bstrVal;
				arrNames.Add(strName);
				m_objList.InsertColumn(i, strName);
			}
			
			m_objList.SetRedraw(FALSE);
			int nIndex = 0;
			CString strName;
			_variant_t val;
			CString strValue;
			int nMax = arrNames.GetSize();
			while(rs->EndOfFile == VARIANT_FALSE){
				for(int i = 0; i < nMax; i++){
					strName = arrNames.GetAt(i);
					val = pDb->GetFieldValue(rs, strName);
					if(val.vt == VT_NULL){
						strValue = "";
					}else{
						val.ChangeType(VT_BSTR);
						strValue = val.bstrVal;
					}
					if(i == 0){
						m_objList.InsertItem(nIndex, strValue, 0);
					}else{
						m_objList.SetItemText(nIndex, i, strValue);
					}
				}
				nIndex++;
				rs->MoveNext();
			}

			m_objList.SetAllColumnWidth();
			m_objList.SetRedraw(TRUE);
			m_objList.InvalidateRect(NULL);

			strMsg = "SQLの実行が完了しました";
			GetDocument()->UpdateAllViews(NULL, DB_ADDMSG, (CObject*)&strMsg);
			if((nType == 1) || (rs != NULL)){
				rs->Close();
				m_strResultSQL = szSQL;
			}
		}
	}CATCH_ALL(e){
		strMsg = pDb->GetError();
		GetDocument()->UpdateAllViews(NULL, DB_ADDMSG, (CObject*)&strMsg);
		if(rs){
			rs->Close();
		}
		m_objList.InsertColumn(0, "データなし");
		m_objList.SetAllColumnWidth();
	}END_CATCH_ALL
	return TRUE;

}
#endif

CDBListCtrl* CResultView::GetListCtrl(){
	return &m_objList;
}



BOOL CResultView::PreTranslateMessage(MSG* pMsg){

	return CView::PreTranslateMessage(pMsg);
}

void CResultView::OnTimer(UINT nIDEvent){
	if(nIDEvent != IDS_RESULT_TIMER){
		return;
	}
	try{
		if(m_hThreadHandle){
			switch(::WaitForSingleObject(m_hThreadHandle, 0)){
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
			case WAIT_TIMEOUT:
				break;
			case WAIT_FAILED:
				break;
			}
		}	
	}catch(CException *e){
		char szErr[1024];
		memset(szErr, 0, 1024);
		if(e->GetErrorMessage(szErr, 1024)){
			AfxMessageBox(szErr);
		}else{
			AfxMessageBox("致命的エラー");
		}
		e->Delete();
	}catch(const char *e){
			AfxMessageBox(e);
	}catch(...){
		AfxMessageBox("致命的エラー");
	}
	CView::OnTimer(nIDEvent);
}

void CResultView::OnRefreshView(){
	Refresh(m_strResultSQL);

}

void CResultView::OnUpdateRefreshView(CCmdUI* pCmdUI){
	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	int nCount = m_objList.GetItemCount();
	if(nCount && m_strResultSQL.GetLength() && pFrm){
		CAdoDatabase *pDB = pFrm->GetDBObject();
		pCmdUI->Enable(pDB->IsConnect());
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CResultView::Refresh(LPCTSTR pszSQL){
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();

	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	CAdoDatabase* pDb = pFrm->GetDBObject();
	if(pDb){
		BOOL bConnect = pDb->IsConnect();
		if(!bConnect){
			pFrm->SetOutputMsg("コネクションが確立されていないためSQLを実行することができません。");
		}else{
//			if(m_hThreadHandle){
//				::WaitForSingleObject(m_hThreadHandle, 1000);
//			}

			if(!m_hThreadHandle){
				try{
					CString strSQL;
					if(pszSQL){
						strSQL = pszSQL;
					}else{
						strSQL = "";
					}
					//実行前の確認
					if(pApp->m_bRecAlert){
						CString chkSQL = strSQL;
						chkSQL.TrimLeft();
						if(!chkSQL.Left(6).CompareNoCase("SELECT")){
							chkSQL.Format("SELECT COUNT(*) AS CNT FROM (%s) AS A", strSQL);
							_RecordsetPtr rs = NULL;
							try{
								_RecordsetPtr rs = pDb->OpenRecordSet(chkSQL);
								rs->MoveFirst();
								_variant_t val = pDb->GetFieldValue(rs, "CNT");
								int nChkCnt = val.iVal;
								rs.Release();
								rs = NULL;
								if(nChkCnt >= pApp->m_nRecAlert){
									CString msg;
									msg.Format("大量のレコードを取得する可能性があり、"
											   "処理に時間がかかる可能性があります。\r\n続けますか？\r\n"
											   "(予想レコード数 %d件)", nChkCnt);
									DWORD dwRet = AfxMessageBox(msg, MB_OKCANCEL);
									if(dwRet = IDCANCEL){
										return;
									}
								}
							}catch(...){
								if(rs){
									rs.Release();
									rs = NULL;
								}
							}
						}
					}
					m_pThread = new THREADINFO;
					memset(m_pThread, 0, sizeof(THREADINFO));

					m_pThread->pszSQL = new char[strSQL.GetLength() + 1];
					memset(m_pThread->pszSQL, 0, strSQL.GetLength() + 1);
					strcpy(m_pThread->pszSQL, strSQL);

					// スレッドのセキュリティ属性
					SECURITY_ATTRIBUTES		sa ;
					sa.nLength              = sizeof( sa ) ;
					sa.lpSecurityDescriptor = NULL ;
					sa.bInheritHandle       = TRUE ;

					DWORD dwId;
					m_pThread->pWnd = (LPVOID)this;
					m_pThread->pFrm = GetParentFrame();
					m_pThread->pDoc = GetDocument();
					m_hThreadHandle = CreateThread(&sa,
												   0,
												   LoadTableThread,
												   (LPVOID)m_pThread,
												   0,
												   &dwId);
					if(!m_hThreadHandle){
						DWORD dwError = GetLastError();
						CString strErr = CDebugSupport::GetLastErrorText(dwError);
						CString strMsg;
						strMsg.Format("スレッドの作成ができませんでした。\r\n詳細：%s", strErr); 
						pFrm->SetOutputMsg(strMsg);
					}
				}catch(char *pszErr){
					CString strMsg;
					strMsg.Format("スレッドの作成ができませんでした。\r\n詳細：%s", pszErr); 
					pFrm->SetOutputMsg(strMsg);
					delete pszErr;
					m_hThreadHandle = NULL;
				}catch(...){
					pFrm->SetOutputMsg("スレッドの作成ができませんでした。");
					m_hThreadHandle = NULL;
				}
			}else{
			}
		}
	}
}

void CResultView::OnEditCopy(){
	//選択内容をコピーする
	CHeaderCtrl *pHead = m_objList.GetHeaderCtrl();
	int nColMax = pHead->GetItemCount();
	CString strCopyBuff = "";
	_TCHAR szText[8000];
	HDITEM hItem;
	hItem.mask			= HDI_TEXT;
	hItem.pszText		= szText;
	hItem.cchTextMax	= 8000;
	for(int nLoop = 0; nLoop < nColMax; nLoop++){
		memset(szText, 0, 8000);
		pHead->GetItem(nLoop, &hItem);
		strCopyBuff += szText;
		strCopyBuff += "\t";
	}
	strCopyBuff += "\r\n";

	POSITION pos = m_objList.GetFirstSelectedItemPosition();
	int nIndex;
	CString strItemText;
	while(pos){
		nIndex = m_objList.GetNextSelectedItem(pos);
		for(int i = 0; i < nColMax; i++){
			strItemText = m_objList.GetItemText(nIndex, i);
			strItemText.Replace("\"", "\"\"");
			strCopyBuff += "\"" + strItemText + "\"";
			strCopyBuff += "\t";
		}
		strCopyBuff += "\r\n";
	}

	SetTextToClipBoard(m_hWnd, strCopyBuff, strCopyBuff.GetLength() + 1);
}

void CResultView::OnUpdateEditCopy(CCmdUI* pCmdUI) {
	if(m_objList.GetSelectedCount()){
		pCmdUI->Enable(TRUE);
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CResultView::OnAllselect(){
	int nCnt = m_objList.GetItemCount();
	for(int i = 0; i < nCnt; i++){
		m_objList.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CResultView::OnUpdateAllselect(CCmdUI* pCmdUI){
	if(m_objList.GetItemCount()){
		pCmdUI->Enable(TRUE);
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CResultView::EnableList(BOOL bEnable){
	m_objList.EnableWindow(bEnable);

}

void CResultView::SetCtrlPos(){
	int nCx = 24;
	int nCy = SELECTOR_HEIGHT;
	
	HWND hWnd;
	CRect rect;
	GetClientRect(rect);
	CWnd* arrWnd[] = {
		&m_objBtnFirst, &m_objBtnPrev, 
		&m_objEdPage,   &m_objEdPageBase,
		&m_objBtnNext,  &m_objBtnEnd,
		&m_objBtnSnap
	};
	int size = sizeof(arrWnd) / sizeof(CWnd*);

	rect.bottom -= (nCy + 4);
	hWnd = m_objList.m_hWnd;
	if(::IsWindow(hWnd) && ::IsWindowEnabled(hWnd)){
		m_objList.SetWindowPos(&wndTop, 
							   rect.left, rect.top, 
							   rect.Width(), rect.Height(), 
							   SWP_SHOWWINDOW);
	}

	for(int i = 0; i < size; i++){
		hWnd = arrWnd[i]->m_hWnd;
		if(::IsWindow(hWnd) && ::IsWindowEnabled(hWnd)){
			arrWnd[i]->SetWindowPos(  &wndTop,
									  nCx * i + 2, rect.bottom + 2,
									  nCx,         nCy + 2,
									  SWP_SHOWWINDOW);
		}
	}

}

void CResultView::OnShowWindow(BOOL bShow, UINT nStatus){
	CView::OnShowWindow(bShow, nStatus);
	SetCtrlPos();	
}

void CResultView::OnSize(UINT nType, int cx, int cy){
	CView::OnSize(nType, cx, cy);
	SetCtrlPos();	
}

BOOL CResultView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CRect rect;
	GetClientRect(rect);
	rect.bottom -= (SELECTOR_HEIGHT + 4);

	CRect drawRect(0,  rect.bottom, rect.right, rect.bottom + SELECTOR_HEIGHT + 4);
	CBrush brush;
	brush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
	pDC->FillRect(drawRect, &brush);
	POINT pos[2] = {
		{0,          rect.bottom},
		{rect.right, rect.bottom}
	};
	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CPen *pPen = pDC->SelectObject(&pen);
	pDC->Polyline(pos, 2);
	pDC->SelectObject(pPen);
	pen.DeleteObject();
	return FALSE;	
//	return CView::OnEraseBkgnd(pDC);
}

void CResultView::OnBtnFirst(){
	if(m_nPage < 1){
		return;
	}
	m_nCurPage = 1;
	ViewPage(1);
}
void CResultView::OnBtnPrev(){
	if(m_nPage < 1){
		return;
	}
	m_nCurPage--;
	if(m_nCurPage < 1){
		m_nCurPage = 1;
	}
	ViewPage(m_nCurPage);
}
void CResultView::OnBtnNext(){
	if((m_nPage < 1) || (m_nPage <= m_nCurPage)){
		return;
	}
	m_nCurPage++;
	if(m_nCurPage > m_nPage){
		m_nCurPage = m_nPage;
	}
	ViewPage(m_nCurPage);
}
void CResultView::OnBtnEnd(){
	if(m_nPage < 1){
		return;
	}
	m_nCurPage = m_nPage;
	ViewPage(m_nCurPage);
}
void CResultView::OnUpdateBtnFirst(CCmdUI* pCmdUI){
	if(m_arrCell.GetSize() == 0){
		pCmdUI->Enable(FALSE);
	}else{
		pCmdUI->Enable(TRUE);
	}
}
void CResultView::OnUpdateBtnPrev(CCmdUI* pCmdUI){
	if(m_arrCell.GetSize() == 0){
		pCmdUI->Enable(FALSE);
	}else{
		pCmdUI->Enable(TRUE);
	}
}
void CResultView::OnUpdateBtnNext(CCmdUI* pCmdUI){
	if(m_arrCell.GetSize() == 0){
		pCmdUI->Enable(FALSE);
	}else{
		pCmdUI->Enable(TRUE);
	}
}
void CResultView::OnUpdateBtnEnd(CCmdUI* pCmdUI){
	if(m_arrCell.GetSize() == 0){
		pCmdUI->Enable(FALSE);
	}else{
		pCmdUI->Enable(TRUE);
	}
}

void CResultView::RemoveCellData(){
	int nSize = m_arrCell.GetSize();
	CArray<PCELL, PCELL>* pArr = NULL;
	PCELL pCell = NULL;
	for(int i = 0; i < nSize; i++){
		pArr = (CArray<PCELL, PCELL>*)m_arrCell.GetAt(i);
		if(pArr){
			int arrSize = pArr->GetSize();
			for(int j = 0; j < arrSize; j++){
				pCell = pArr->GetAt(j);
				if(pCell){
					if(pCell->pszValue){
						delete pCell->pszValue;
					}
					delete pCell;
				}
			}
			delete pArr;
		}
	}
	m_arrCell.RemoveAll();
}

void CResultView::OnBtnSnap(){
	int size = m_arrCell.GetSize();
}

void CResultView::OnUpdateBtnSnap(CCmdUI* pCmdUI){
}
