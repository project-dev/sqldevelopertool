// SqlViewDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CSqlViewDlg �_�C�A���O


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
// CSqlViewDlg ���b�Z�[�W �n���h��

BOOL CSqlViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CSqlViewDlg::OnSaveSql() {
	CFileDialogEx dlg(m_hWnd, 
					  NULL, 
					  "*.sql", 
					  "SQL�̕ۑ�",
					  "SQL�t�@�C��\0*.sql\0�S�Ẵt�@�C��\0*.*\0\0",
					  0,
					  NULL,
					  "SQL�̕ۑ�",
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
		AfxMessageBox("SQL�̕ۑ��Ɏ��s���܂���");
	}END_CATCH_ALL
}
