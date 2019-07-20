// InfoDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CInfoDlg �_�C�A���O


CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
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
// CInfoDlg ���b�Z�[�W �n���h��

BOOL CInfoDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	m_objOk.EnableWindow(m_bOkUse);

	m_objInfoArea.GetClientRect(m_objDrawArea);
	m_objInfoArea.ShowWindow(SW_HIDE);
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CInfoDlg::OnPaint(){
	CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

	dc.DrawText(m_strInfo, 
				m_strInfo.GetLength(), 
				m_objDrawArea, 
				DT_CENTER | DT_VCENTER | DT_EXPANDTABS | DT_NOPREFIX | DT_WORDBREAK );

}
