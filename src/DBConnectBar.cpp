// DBConnectBar.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DBTool.h"
#include "DBConnectBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBConnectBar ダイアログ


CDBConnectBar::CDBConnectBar()
//	: CDialogBar(CDBConnectBar::IDD, pParent)
{
	/*
	//{{AFX_DATA_INIT(CDBConnectBar)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
	*/
}

void CDBConnectBar::DoDataExchange(CDataExchange* pDX){
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBConnectBar)
	DDX_Control(pDX, IDC_DB_CMB, m_objDBSelCmb);
	DDX_Control(pDX, IDC_SELDB_BTN, m_objSelBtn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBConnectBar, CDialogBar)
	//{{AFX_MSG_MAP(CDBConnectBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBConnectBar メッセージ ハンドラ

BOOL CDBConnectBar::Create(CWnd *pParentWnd, UINT nStyle, UINT nID){
	return CDialogBar::Create(pParentWnd, IDD, nStyle, nID);
}

BOOL CDBConnectBar::OnInitDialog(){
//	CDialogBar::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

int CDBConnectBar::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください
	
	return 0;
}
