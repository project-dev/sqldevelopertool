// SQLHistDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "dbtool.h"
#include "SQLHistDlg.h"
#include "MainFrm.h"
#include "devlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQLHistDlg ダイアログ


CSQLHistDlg::CSQLHistDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSQLHistDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSQLHistDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CSQLHistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQLHistDlg)
	DDX_Control(pDX, IDC_SQLLIST, m_objSQLList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSQLHistDlg, CDialog)
	//{{AFX_MSG_MAP(CSQLHistDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQLHistDlg メッセージ ハンドラ

BOOL CSQLHistDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_objSQLList.InsertColumn(0, "No");
	m_objSQLList.InsertColumn(1, "SQL文");

	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	int nSize = pFrm->m_arrSQLHistory.GetSize();
	CString strItem;
	CString strSQL;
	for(int i = 0; i < nSize; i++){
		strItem.Format("%d", i);
		m_objSQLList.InsertItem(i, strItem, 0);
		m_objSQLList.SetItemText(i, 1, pFrm->m_arrSQLHistory.GetAt(i));
	
	}
	SetColumnWidth();

	m_objSQLList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CSQLHistDlg::SetColumnWidth(){
	CHeaderCtrl *pHead = m_objSQLList.GetHeaderCtrl();
	if(!pHead){
		return;
	}
	int nMax = pHead->GetItemCount();
	for(int j = 0; j < nMax; j++){
		m_objSQLList.SetColumnWidth(j, LVSCW_AUTOSIZE);
		int nWidth1 = m_objSQLList.GetColumnWidth(j);
		m_objSQLList.SetColumnWidth(j, LVSCW_AUTOSIZE_USEHEADER );
		int nWidth2 = m_objSQLList.GetColumnWidth(j);
		if(nWidth1 > nWidth2){
			m_objSQLList.SetColumnWidth(j, LVSCW_AUTOSIZE);
		}
	}

}

void CSQLHistDlg::OnOK(){
	//選択した内容をクリップボードにコピーする	
	int nIndex = m_objSQLList.GetSelectionMark();
	if(nIndex != -1){
		CString strSQL = m_objSQLList.GetItemText(nIndex, 1);
		SetTextToClipBoard(m_hWnd, strSQL, strSQL.GetLength() + 1);
	}

	CDialog::OnOK();
}

