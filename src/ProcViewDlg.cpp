// ProcViewDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "dbtool.h"
#include "ProcViewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcViewDlg ダイアログ


CProcViewDlg::CProcViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcViewDlg)
	m_strProc = _T("");
	//}}AFX_DATA_INIT
	AfxInitRichEdit();
}


void CProcViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcViewDlg)
	DDX_Text(pDX, IDC_PROP_EDIT, m_strProc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcViewDlg, CDialog)
	//{{AFX_MSG_MAP(CProcViewDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcViewDlg メッセージ ハンドラ

BOOL CProcViewDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_strProc = m_strFuncData;
	UpdateData(FALSE);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
