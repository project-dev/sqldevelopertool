// DBRestoreDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CDBRestoreDlg �_�C�A���O


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
// CDBRestoreDlg ���b�Z�[�W �n���h��

BOOL CDBRestoreDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CDBRestoreDlg::OnRefDbbackup(){
	UpdateData();
	CString strFileName = "*.*";

	CFileDialog fDlg(TRUE,
					 "*.*",
					 strFileName,
					 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					 "*.*|���ׂ�(*.*)|",
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
		AfxMessageBox("����ݒ肵�Ă�������");
		return;		
	}
	CDialog::OnOK();
}

void CDBRestoreDlg::OnDoubleclickedOk(){
}



void CDBRestoreDlg::OnRefDbrestore(){
	UpdateData();
	CFolderDialog folDlg(m_hWnd, "������̑I��");
	if(!folDlg.DoModal()){
		return;
	}
	m_strRestorePath = folDlg.GetFolder();
	UpdateData(FALSE);
}
