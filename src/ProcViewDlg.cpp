// ProcViewDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CProcViewDlg �_�C�A���O


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
// CProcViewDlg ���b�Z�[�W �n���h��

BOOL CProcViewDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	m_strProc = m_strFuncData;
	UpdateData(FALSE);
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}
