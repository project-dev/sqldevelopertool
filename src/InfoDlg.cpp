// InfoDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "dbtool.h"
#include "InfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg ダイアログ


CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
	m_bOkUse = FALSE;
}


void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDlg)
	DDX_Control(pDX, IDOK, m_objOk);
	DDX_Control(pDX, IDC_INFOAREA, m_objInfoArea);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CInfoDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg メッセージ ハンドラ

BOOL CInfoDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	m_objOk.EnableWindow(m_bOkUse);

	m_objInfoArea.GetClientRect(m_objDrawArea);
	m_objInfoArea.ShowWindow(SW_HIDE);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CInfoDlg::OnPaint(){
	CPaintDC dc(this); // 描画用のデバイス コンテキスト

	dc.DrawText(m_strInfo, 
				m_strInfo.GetLength(), 
				m_objDrawArea, 
				DT_CENTER | DT_VCENTER | DT_EXPANDTABS | DT_NOPREFIX | DT_WORDBREAK );

}
