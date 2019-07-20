// DBBackupDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DBTool.h"
#include "DBBackupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBBackupDlg ダイアログ


CDBBackupDlg::CDBBackupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBBackupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBBackupDlg)
	m_strBackupPath = _T("");
	m_strDBName = _T("");
	//}}AFX_DATA_INIT
}


void CDBBackupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBBackupDlg)
	DDX_Text(pDX, IDC_BACKUP_PATH, m_strBackupPath);
	DDX_Text(pDX, IDC_DBNAME, m_strDBName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBBackupDlg, CDialog)
	//{{AFX_MSG_MAP(CDBBackupDlg)
	ON_BN_CLICKED(IDC_REF_DBBACKUP, OnRefDbbackup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBBackupDlg メッセージ ハンドラ

BOOL CDBBackupDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	m_strDBName = m_strBackupName;
	UpdateData(FALSE);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDBBackupDlg::OnRefDbbackup(){
	UpdateData();
	CString strFileName = "*.*";

	CFileDialog fDlg(TRUE,
					 "*.*",
					 strFileName,
					 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					 "*.*|すべて(*.*)|",
					 this);
	if(fDlg.DoModal() != IDOK){
		return;
	}

	m_strBackupPath = fDlg.GetPathName();
	UpdateData(FALSE);
}

void CDBBackupDlg::OnOK(){
	CDialog::OnOK();
}
