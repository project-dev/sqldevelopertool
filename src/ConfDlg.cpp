// ConfDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "dbtool.h"
#include "ConfDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfDlg ダイアログ


CConfDlg::CConfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfDlg)
	DDX_Control(pDX, IDC_CUST_TAB, m_objTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfDlg, CDialog)
	//{{AFX_MSG_MAP(CConfDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfDlg メッセージ ハンドラ

BOOL CConfDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	m_objBaseCustPage.Create(CBaseCustPage::IDD, &m_objTab);
	m_objHistCustPage.Create(CHistCustPage::IDD, &m_objTab);
	m_objTab.AddNewPage(0, "基本設定",	m_objBaseCustPage.m_hWnd);
	//m_objTab.AddNewPage(1, "履歴",		m_objHistCustPage.m_hWnd);

	m_objTab.SetActivePage(0);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CConfDlg::OnOK(){
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	m_objBaseCustPage.UpdateData();
	pApp->m_bLogTabActive = m_objBaseCustPage.m_bLogTabActive;
	pApp->m_bIncSearch = m_objBaseCustPage.m_bIncSerach;
	pApp->m_nRecAlert = m_objBaseCustPage.m_nRecAlert;
	pApp->m_bRecAlert = m_objBaseCustPage.m_bRecAlert;
	pApp->SaveIni();
	CDialog::OnOK();
}
