// HistCustPage.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "dbtool.h"
#include "HistCustPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistCustPage ダイアログ


CHistCustPage::CHistCustPage(CWnd* pParent /*=NULL*/)
	: CDialog(CHistCustPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHistCustPage)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CHistCustPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHistCustPage)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHistCustPage, CDialog)
	//{{AFX_MSG_MAP(CHistCustPage)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistCustPage メッセージ ハンドラ
