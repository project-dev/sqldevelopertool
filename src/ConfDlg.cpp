// ConfDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CConfDlg �_�C�A���O


CConfDlg::CConfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
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
// CConfDlg ���b�Z�[�W �n���h��

BOOL CConfDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	m_objBaseCustPage.Create(CBaseCustPage::IDD, &m_objTab);
	m_objHistCustPage.Create(CHistCustPage::IDD, &m_objTab);
	m_objTab.AddNewPage(0, "��{�ݒ�",	m_objBaseCustPage.m_hWnd);
	//m_objTab.AddNewPage(1, "����",		m_objHistCustPage.m_hWnd);

	m_objTab.SetActivePage(0);
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
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
