// SqlViewDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "dbtool.h"
#include "SqlViewDlg.h"
#include "FileDialogEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSqlViewDlg ダイアログ


CSqlViewDlg::CSqlViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSqlViewDlg::IDD, pParent)
{
	AfxInitRichEdit();

	//{{AFX_DATA_INIT(CSqlViewDlg)
	m_strSql = _T("");
	//}}AFX_DATA_INIT
}


void CSqlViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSqlViewDlg)
	DDX_Control(pDX, IDC_SQL_VIEW, m_objSqlEdit);
	DDX_Text(pDX, IDC_SQL_VIEW, m_strSql);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSqlViewDlg, CDialog)
	//{{AFX_MSG_MAP(CSqlViewDlg)
	ON_BN_CLICKED(IDC_SAVE_SQL, OnSaveSql)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSqlViewDlg メッセージ ハンドラ

BOOL CSqlViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CSqlViewDlg::OnSaveSql() {
	CFileDialogEx dlg(m_hWnd, 
					  NULL, 
					  "*.sql", 
					  "SQLの保存",
					  "SQLファイル\0*.sql\0全てのファイル\0*.*\0\0",
					  0,
					  NULL,
					  "SQLの保存",
					  "sql");
	if(dlg.DoModal() != IDOK){
		return;
	}
	CString strFileName = dlg.GetFileName();
	CStdioFile file;
	TRY{
		int nCnt = m_objSqlEdit.GetLineCount();
		int nLen;
		char *pLine;
		CString strLine;
		file.Open(strFileName, CFile::modeCreate | CFile::modeWrite);
		for(int i = 0; i < nCnt; i++){
			nLen = m_objSqlEdit.LineLength(i);
			pLine = new char[nLen + 1];
			memset(pLine, 0, nLen + 1);
			m_objSqlEdit.GetLine(i, pLine, nLen);
			strLine = pLine;
			strLine.Replace("\r\n", "\n");
			file.WriteString(strLine);
			delete pLine;
		}
		file.Flush();
		file.Close();
	}CATCH_ALL(e){
		AfxMessageBox("SQLの保存に失敗しました");
	}END_CATCH_ALL
}
