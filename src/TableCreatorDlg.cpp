// TableCreatorDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DBTool.h"
#include "TableCreatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableCreatorDlg ダイアログ


CTableCreatorDlg::CTableCreatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTableCreatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableCreatorDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CTableCreatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableCreatorDlg)
	DDX_Control(pDX, IDC_TABLELIST, m_objList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableCreatorDlg, CDialog)
	//{{AFX_MSG_MAP(CTableCreatorDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableCreatorDlg メッセージ ハンドラ

BOOL CTableCreatorDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_objList.InsertColumn(0, "テーブル名");
	m_objList.InsertColumn(1, "属性");
	m_objList.InsertColumn(2, "NULL許可");
	m_objList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_objList.SetAllColumnWidth();
	return TRUE;
}
