// BaseCustPage.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "dbtool.h"
#include "BaseCustPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseCustPage ダイアログ


CBaseCustPage::CBaseCustPage(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseCustPage::IDD, pParent)
{
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	//{{AFX_DATA_INIT(CBaseCustPage)
	m_bLogTabActive = pApp->m_bLogTabActive;
	m_bIncSerach = pApp->m_bIncSearch;
	m_bRecAlert = pApp->m_bRecAlert;
	m_nRecAlert = pApp->m_nRecAlert;
	//}}AFX_DATA_INIT
}


void CBaseCustPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBaseCustPage)
	DDX_Check(pDX, IDC_LOGTAB_CHK, m_bLogTabActive);
	DDX_Check(pDX, IDC_INCLIMENTAL, m_bIncSerach);
	DDX_Check(pDX, IDC_CHK_REC_ALERT, m_bRecAlert);
	DDX_Text(pDX, IDC_ED_ALERT_REC, m_nRecAlert);
	DDV_MinMaxInt(pDX, m_nRecAlert, 0, 2147483647);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBaseCustPage, CDialog)
	//{{AFX_MSG_MAP(CBaseCustPage)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseCustPage メッセージ ハンドラ
