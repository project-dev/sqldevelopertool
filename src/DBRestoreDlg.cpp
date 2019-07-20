// DBRestoreDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DBTool.h"
#include "DBRestoreDlg.h"
#include "FolderDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBRestoreDlg ダイアログ


CDBRestoreDlg::CDBRestoreDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBRestoreDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBRestoreDlg)
	m_strBackupPath = _T("");
	m_strDBName = _T("");
	m_strRestorePath = _T("");
	//}}AFX_DATA_INIT
}


void CDBRestoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBRestoreDlg)
	DDX_Text(pDX, IDC_BACKUP_PATH, m_strBackupPath);
	DDX_Text(pDX, IDC_DBNAME, m_strDBName);
	DDX_Text(pDX, IDC_RESTORE_PATH, m_strRestorePath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBRestoreDlg, CDialog)
	//{{AFX_MSG_MAP(CDBRestoreDlg)
	ON_BN_CLICKED(IDC_REF_DBBACKUP, OnRefDbbackup)
	ON_BN_DOUBLECLICKED(IDOK, OnDoubleclickedOk)
	ON_BN_CLICKED(IDC_REF_DBRESTORE, OnRefDbrestore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBRestoreDlg メッセージ ハンドラ

BOOL CDBRestoreDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDBRestoreDlg::OnRefDbbackup(){
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
	if(m_strDBName.IsEmpty()){
		CString strDBName = m_strBackupPath;
		int nPos = strDBName.ReverseFind('\\');
		strDBName = strDBName.Right(strDBName.GetLength() - nPos - 1);
		nPos = strDBName.Find('.');
		m_strDBName = strDBName.Left(nPos);
	}
	UpdateData(FALSE);

}

void CDBRestoreDlg::OnOK(){
	UpdateData();
	if(m_strBackupPath.IsEmpty() || m_strDBName.IsEmpty()){
		AfxMessageBox("情報を設定してください");
		return;		
	}
	CDialog::OnOK();
}

void CDBRestoreDlg::OnDoubleclickedOk(){
}



void CDBRestoreDlg::OnRefDbrestore(){
	UpdateData();
	CFolderDialog folDlg(m_hWnd, "復元先の選択");
	if(!folDlg.DoModal()){
		return;
	}
	m_strRestorePath = folDlg.GetFolder();
	UpdateData(FALSE);
}
