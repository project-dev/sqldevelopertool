// DBConnectBar.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "DBTool.h"
#include "DBConnectBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBConnectBar �_�C�A���O


CDBConnectBar::CDBConnectBar()
//	: CDialogBar(CDBConnectBar::IDD, pParent)
{
	/*
	//{{AFX_DATA_INIT(CDBConnectBar)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
	*/
}

void CDBConnectBar::DoDataExchange(CDataExchange* pDX){
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBConnectBar)
	DDX_Control(pDX, IDC_DB_CMB, m_objDBSelCmb);
	DDX_Control(pDX, IDC_SELDB_BTN, m_objSelBtn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBConnectBar, CDialogBar)
	//{{AFX_MSG_MAP(CDBConnectBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBConnectBar ���b�Z�[�W �n���h��

BOOL CDBConnectBar::Create(CWnd *pParentWnd, UINT nStyle, UINT nID){
	return CDialogBar::Create(pParentWnd, IDD, nStyle, nID);
}

BOOL CDBConnectBar::OnInitDialog(){
//	CDialogBar::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

int CDBConnectBar::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: ���̈ʒu�ɌŗL�̍쐬�p�R�[�h��ǉ����Ă�������
	
	return 0;
}
