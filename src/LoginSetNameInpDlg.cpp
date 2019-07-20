// LoginSetNameInpDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "dbtool.h"
#include "LoginSetNameInpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginSetNameInpDlg ダイアログ


CLoginSetNameInpDlg::CLoginSetNameInpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginSetNameInpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginSetNameInpDlg)
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CLoginSetNameInpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginSetNameInpDlg)
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginSetNameInpDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginSetNameInpDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginSetNameInpDlg メッセージ ハンドラ
