// SQLEdit.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DBTool.h"
#include "SQLEdit.h"
#include "MainFrm.h"
#include "ResultView.h"
#include "DBToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQLEdit

CSQLEdit::CSQLEdit(){
	m_strFileName = "";
	m_bModify = FALSE;
	m_bRunSQL = TRUE;
}

CSQLEdit::~CSQLEdit(){
}

#if USE_RICHEDIT
BEGIN_MESSAGE_MAP(CSQLEdit, CRichEditCtrlEx)
#else
BEGIN_MESSAGE_MAP(CSQLEdit, CEditEx)
#endif
	//{{AFX_MSG_MAP(CSQLEdit)
	ON_WM_CREATE()
	ON_COMMAND(ID_SQLRUN, OnSqlrun)
	ON_COMMAND(ID_SQLFAIRING, OnSqlfairing)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_ALLSELECT, OnAllselect)
	ON_UPDATE_COMMAND_UI(ID_ALLSELECT, OnUpdateAllselect)
	ON_UPDATE_COMMAND_UI(ID_SQLRUN, OnUpdateSqlrun)
	ON_WM_COPYDATA()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQLEdit メッセージ ハンドラ

BOOL CSQLEdit::PreTranslateMessage(MSG* pMsg){
    if(m_acl != NULL){
        if(::TranslateAccelerator(m_hWnd, m_acl, pMsg)){
            return TRUE;
        }
    }	


	switch(pMsg->message){
	case WM_KEYDOWN:
		{
			SHORT shState = ::GetKeyState(VK_CONTROL);
			DWORD dwStyle = ES_READONLY & GetStyle() ;	
			if((shState < 0) && (pMsg->wParam == VK_SPACE) && (dwStyle == 0)){
				ShowAoutCompWnd();
				return TRUE;
			}else if(pMsg->wParam == VK_ESCAPE){
#if AOUT_CMP
				if(m_objAutCmpWnd.IsWindowVisible()){
					m_objAutCmpWnd.ShowWindow(SW_HIDE);
				}
#endif
			}else if((pMsg->wParam == VK_UP) || (pMsg->wParam == VK_DOWN)){
#if AOUT_CMP
				if((pMsg->hwnd == m_hWnd) && (m_objAutCmpWnd.IsWindowVisible())){
					m_objAutCmpWnd.SetActiveWindow();
					m_objAutCmpWnd.SetFocus();
					m_objAutCmpWnd.PostMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
					return TRUE;
				}
#endif
			}
		}
		break;
	}
#if USE_RICHEDIT
	return CRichEditCtrlEx::PreTranslateMessage(pMsg);
#else
	return CEditEx::PreTranslateMessage(pMsg);
#endif
}

int CSQLEdit::OnCreate(LPCREATESTRUCT lpCreateStruct){
#if USE_RICHEDIT
	if (CRichEditCtrlEx::OnCreate(lpCreateStruct) == -1)
		return -1;
#else
	if (CEditEx::OnCreate(lpCreateStruct) == -1)
		return -1;
#endif
	
    m_acl = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
#if AOUT_CMP
	CRect rect(0,0,0,0);
	m_objAutCmpWnd.Create(0, rect, this, 0);
#endif

	m_bModify = FALSE;

	return 0;
}

void CSQLEdit::OnSqlrun(){
	if(!m_bRunSQL){
		return;
	}

	CString strSQL;
	GetWindowText(strSQL);
	if(strSQL.IsEmpty()){
		return;
	}

	strSQL.Replace("\r\n", " \r\n");

	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	CAdoDatabase *pDb = pFrm->GetDBObject();
	pFrm->AddSQLHistory(strSQL);
	pFrm->GetActiveDocument()->UpdateAllViews(NULL, DB_RESULT, (CObject*)&strSQL);
}

void CSQLEdit::OnAllselect() {
	SetSel(0, -1);
}

void CSQLEdit::OnSqlfairing(){
	if(!m_bRunSQL){
		return;
	}
	CString strSQL;
	GetWindowText(strSQL);
	if(strSQL.IsEmpty()){
		return;
	}
/*
	//本当はSQLを解析してちゃんと整形したい
	SQLKey arrkeys[] = {
		{"SELECT",	"DISTINCT",	FALSE},
		{"SELECT",	NULL,		FALSE},
		{"FROM",	NULL,		FALSE},
		{"WHERE",	NULL,		FALSE},	
		{"OR",		NULL,		FALSE},	
		{"AND",		NULL,		FALSE},	
		{"ORDER",	"BY",		FALSE},	
		{"GROUP",	"BY",		FALSE},	
		{"JOIN",	"LEFT",		TRUE},	
		{"JOIN",	"RIGHT",	TRUE},	
		{"JOIN",	"INNER",	TRUE},	
		{"JOIN",	NULL,		FALSE},	
		{"UNION",	"SELECT",	FALSE},
	};

	int nCnt;
	CString strCheck;
	int nSize = sizeof(arrkeys) / sizeof(SQLKey);
	BOOL bIsPrimary = FALSE;
	BOOL bIsSubKey	= FALSE;
	CString strAftText = "";
	CString strKey;
	while(TRUE){
		char ch = strSQL.GetAt(nCnt);
		if(ch == ' '){
			if(!bPrimary && !bIsSubKey){
				strAftText += strCheck;
				strAftText += " ";
				strCheck.Empty();
			}else if(bPrimary){
			}
		}else{
			strCheck += ch;
			for(int i = 0; i < nSize; i++){
				if(!bIsPrimary && !bSubKey){
					int keyLen = strlen(arrkeys[i].pszPrimary);
					if(keyLen > strCheck.GetLength()){
						continue;
					}else{
						if(strCheck.CompareNoCase()){
						}
						if(!arrkeys[i].pszSubKey){
							bIsSubKey = FALSE;
							strAftText += "\n";
							strAftText += strCheck;
							strCheck.Empty();
						}else{
							strKey = strCheck;
							strCheck.Empty();
							bIsSubKey = TRUE;
						}
					}
				}else if(bIsSubKey){
					if(!arrkeys[i].pszSubKey){
						continue;
					}
					int keyLen = strlen(arrkeys[i].pszSubKey);
					if(keyLen > strCheck.GetLength()){
						continue;
					}else{
					}
				}
			}
		}
		nCnt++;
	}
*/
	strSQL.Replace(",", ",\r\n");
	strSQL.Replace(" OR ", "\r\nOR ");
	strSQL.Replace(" AND ", "\r\nAND ");
	strSQL.Replace(" FROM ", "\r\nFROM ");
	strSQL.Replace(" WHERE ", "\r\nWHERE ");
	strSQL.Replace(" ORDER BY ", "\r\nORDER BY ");
	strSQL.Replace(" GROUP BY ", "\r\nGROUP BY ");
	strSQL.Replace(" LEFT JOIN ", "\r\nLEFT JOIN ");
	strSQL.Replace(" RIGHT JOIN ", "\r\nRIGHT JOIN ");
	strSQL.Replace(" INNER JOIN ", "\r\nINNER JOIN ");
	
	SetWindowText(strSQL);
}

void CSQLEdit::OnEditCopy(){
	Copy();
}

void CSQLEdit::OnUpdateEditCopy(CCmdUI* pCmdUI){
	int nStart = 0;
	int nEnd = 0;
#if USE_RICHEDIT
//	GetSel(nStart, nEnd);
#else
	GetSel(nStart, nEnd);
#endif
	if(nStart == nEnd){
		pCmdUI->Enable(FALSE);
	}else{
		pCmdUI->Enable(TRUE);
	}
}

void CSQLEdit::OnEditCut(){
	Cut();
}

void CSQLEdit::OnUpdateEditCut(CCmdUI* pCmdUI){
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	if(dwStyle & ES_READONLY){
		pCmdUI->Enable(FALSE);
		return;
	}

	int nStart = 0;
	int nEnd = 0;
#if USE_RICHEDIT
//	GetSel(nSelStart, nSelEnd);
#else
	GetSel(nStart, nEnd);
#endif
	if(nStart == nEnd){
		pCmdUI->Enable(FALSE);
	}else{
		pCmdUI->Enable(TRUE);
	}
}

void CSQLEdit::OnEditPaste(){
	Paste();
}

void CSQLEdit::OnUpdateEditPaste(CCmdUI* pCmdUI){
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	if(dwStyle & ES_READONLY){
		pCmdUI->Enable(FALSE);
	}
}

void CSQLEdit::OnEditUndo(){
	Undo();
}

void CSQLEdit::OnUpdateEditUndo(CCmdUI* pCmdUI){
	pCmdUI->Enable(CanUndo());
}

BOOL CSQLEdit::OpenSQL(LPCTSTR pszFileName){
	m_strFileName = pszFileName;
	CStdioFile file;
	CString strLine;
	CString strBuff = "";
	TRY{
		file.Open(pszFileName, CFile::modeRead);
		while(file.ReadString(strLine)){
			strBuff += strLine;
			strBuff += "\r\n";
		}
	}CATCH_ALL(e){
		return FALSE;
	}END_CATCH_ALL
	SetWindowText(strBuff);
	return TRUE;

}

BOOL CSQLEdit::SaveSQL(BOOL bSaveAs){
	m_strFileName.TrimLeft();
	m_strFileName.TrimRight();
	if(m_strFileName.IsEmpty()){
		bSaveAs = TRUE;
	}

	if(bSaveAs || m_strFileName.IsEmpty()){
		CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
		CString strSQLPath;
		strSQLPath.Format("%s\\sql\\*.*", pApp->m_strBasePath);

		_TCHAR szFilePath[MAX_PATH];
		memset(szFilePath, 0, MAX_PATH);
		OPENFILENAME ofn;
		strcpy(szFilePath, "*.sql");
		memset(&ofn, 0, sizeof(OPENFILENAME));
		ofn.Flags				= OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING | OFN_HIDEREADONLY;
		ofn.lStructSize			= sizeof(OPENFILENAME);
		ofn.hwndOwner			= m_hWnd;
		ofn.lpstrFile			= szFilePath;
		ofn.nMaxFile			= MAX_PATH;
		ofn.lpstrFilter			= "SQL形式(*.sql)\0*.sql\0テキスト形式(*.txt)\0*.txt\0すべてのファイル(*.*)\0*.*\0\0";
		ofn.nFilterIndex		= 0;
		ofn.lpstrInitialDir		= strSQLPath;
		ofn.lpstrDefExt			= "sql";
		BOOL bRet =  ::GetSaveFileName(&ofn);
		if(!bRet){
			return FALSE;
		}
		m_strFileName = szFilePath;

		CStdioFile file;
		TRY{
			file.Open(m_strFileName, CFile::modeCreate | CFile::modeReadWrite);
			CString strBuff;
			GetWindowText(strBuff);
			file.WriteString(strBuff);
			file.Flush();
			file.Close();
		}CATCH_ALL(e){
			AfxMessageBox("保存に失敗しました");
		}END_CATCH_ALL
	}
	m_bModify = FALSE;
	InvalidateRect(NULL);
	return TRUE;
}
LPCTSTR CSQLEdit::GetFileName(){
	return m_strFileName;
}
void CSQLEdit::OnClose(){
	if(m_bRunSQL && m_bModify){
		switch(AfxMessageBox("現在の内容を保存しますか？\r\n(\"はい\"で保存。\"いいえ\"で破棄。)", MB_YESNO)){
		case IDYES:
			SaveSQL(FALSE);
			break;
		}
	}	
#if USE_RICHEDIT
	CRichEditCtrlEx::OnClose();
#else
	CEditEx::OnClose();
#endif
}

void CSQLEdit::OnDestroy() {
#if USE_RICHEDIT
	CRichEditCtrlEx::OnDestroy();
#else
	CEditEx::OnDestroy();
#endif

}


void CSQLEdit::OnUpdateAllselect(CCmdUI* pCmdUI){
	CString strText;
	GetWindowText(strText);	
	pCmdUI->Enable(!strText.IsEmpty());
}

void CSQLEdit::OnUpdateSqlrun(CCmdUI* pCmdUI){
#if 0
	if(!m_bRunSQL){
		pCmdUI->Enable(FALSE);
		return;
	}
	CString strSQL;
	GetWindowText(strSQL);
	pCmdUI->Enable(!strSQL.IsEmpty());
#else

	if(::WaitForSingleObject(CDBToolApp::m_evSQLRUN, 0) != WAIT_OBJECT_0){
		if(!m_bRunSQL){
			pCmdUI->Enable(FALSE);
			return;
		}
		CString strSQL;
		GetWindowText(strSQL);
		pCmdUI->Enable(!strSQL.IsEmpty());
	}else{
		pCmdUI->Enable(FALSE);
	}
#endif
}

BOOL CSQLEdit::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) {
#if AOUT_CMP
	if(pWnd->m_hWnd == m_objAutCmpWnd.m_hWnd){
		CString strData = (LPCTSTR)pCopyDataStruct->lpData;
		//キャレットの座標を取得
#if USE_RICHEDIT
		long nSelStart;
		long nSelEnd;
		GetSel(nSelStart, nSelEnd);
		int nIndex;
		int nPos;
		CharFromPos(nIndex, nPos);
#else
		int nSelStart;
		int nSelEnd;
		GetSel(nSelStart, nSelEnd);
		CPoint pos = GetCaretPos();
		int nIndex = CharFromPos(pos);
		
		//文字の位置を取得
		int nPos = LOWORD(nIndex);

		//行番号を取得
		nIndex = HIWORD(nIndex);
#endif

		//行の長さを取得
		int nLen = LineLength(nIndex);
		CString strLine = "";
		if(nLen > 0){
			char *pszLine = new char[nLen + 1];
			memset(pszLine, 0, nLen + 1);
			GetLine(nIndex, pszLine, nLen);
			strLine = pszLine;
			delete pszLine;
		}
		//カーソル位置までの文字を取得
		strLine = strLine.Left(nPos);

		int nStartPos = strLine.ReverseFind(' ');
		if(nStartPos == -1){
			SetSel(nSelStart - strLine.GetLength(), nSelStart);
		}else{ 
			SetSel(nSelStart - (strLine.GetLength() - nStartPos) + 1, nSelStart);
		}

		ReplaceSel(strData, TRUE);
	}
#endif
#if USE_RICHEDIT
	return CRichEditCtrlEx::OnCopyData(pWnd, pCopyDataStruct);
#else
	return CEditEx::OnCopyData(pWnd, pCopyDataStruct);
#endif
}

BOOL CSQLEdit::ShowAoutCompWnd(){
#if AOUT_CMP
	CFont *pFont = GetFont();
	m_objAutCmpWnd.SetFont(pFont);


	//キャレットの座標を取得
	CPoint pos = GetCaretPos();

#if USE_RICHEDIT
	int nIndex;
	int nPos;
	CharFromPos(nIndex, nPos);
#else
	int nIndex = CharFromPos(pos);
	//文字の位置を取得
	int nPos = LOWORD(nIndex);

	//行番号を取得
	nIndex = HIWORD(nIndex);
#endif
	

	//行の長さを取得
	int nLen = LineLength(nIndex);

	//行の文字を取得
	CString strLine = "";
	if(nLen > 0){
		char *pszLine = new char[nLen + 1];
		memset(pszLine, 0, nLen + 1);
		GetLine(nIndex, pszLine, nLen);
		strLine = pszLine;
		delete pszLine;
	}
	//カーソル位置までの文字を取得
	strLine = strLine.Left(nPos);
/*
	//補完対象の文字列を取得
	int nEndPos = strLine.ReverseFind(' ');
	if(nEndPos != -1){
		strLine = strLine.Right(strLine.GetLength() - nEndPos);			
	}
*/
	//補完ウィンドウを表示
	CRect rect;
	m_objAutCmpWnd.GetClientRect(rect);
	
	CDC *pDC = GetDC();
	CSize addSize = pDC->GetTextExtent("0");
	pos.y += addSize.cy;

	if((rect.left != pos.x) || (rect.left != pos.y)){
		m_objAutCmpWnd.SetPickData(&arrPickData_sql[0], sizeof(arrPickData_sql) / sizeof(PICKDATA));
		m_objAutCmpWnd.SetPickString(strLine);
		m_objAutCmpWnd.SetWindowPos(&wndTop, 
									pos.x, pos.y,
									300, 100,
									SWP_SHOWWINDOW);
	}
//	m_objAutCmpWnd.SetActiveWindow();
//	m_objAutCmpWnd.SetFocus();
#endif
	return TRUE;
}

void CSQLEdit::OnLButtonDown(UINT nFlags, CPoint point){
#if AOUT_CMP
	m_objAutCmpWnd.ShowWindow(SW_HIDE);
#endif
#if USE_RICHEDIT
	CRichEditCtrlEx::OnLButtonDown(nFlags, point);
#else
	CEditEx::OnLButtonDown(nFlags, point);
#endif
}

void CSQLEdit::OnRButtonDown(UINT nFlags, CPoint point){
#if AOUT_CMP
	m_objAutCmpWnd.ShowWindow(SW_HIDE);
#endif
#if USE_RICHEDIT
	CRichEditCtrlEx::OnRButtonDown(nFlags, point);
#else
	CEditEx::OnRButtonDown(nFlags, point);
#endif
}

void CSQLEdit::OnMButtonDown(UINT nFlags, CPoint point){
#if AOUT_CMP
	m_objAutCmpWnd.ShowWindow(SW_HIDE);
#endif
#if USE_RICHEDIT
	CRichEditCtrlEx::OnMButtonDown(nFlags, point);
#else
	CEditEx::OnMButtonDown(nFlags, point);
#endif
}

void CSQLEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
#if USE_RICHEDIT
	CRichEditCtrlEx::OnKeyDown(nChar, nRepCnt, nFlags);
#else
	CEditEx::OnKeyDown(nChar, nRepCnt, nFlags);
#endif
}

void CSQLEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
#if AOUT_CMP
	if(m_objAutCmpWnd.IsWindowVisible()){
		ShowAoutCompWnd();
	}
#endif
#if USE_RICHEDIT
	CRichEditCtrlEx::OnKeyUp(nChar, nRepCnt, nFlags);
#else
	CEditEx::OnKeyUp(nChar, nRepCnt, nFlags);
#endif
}
