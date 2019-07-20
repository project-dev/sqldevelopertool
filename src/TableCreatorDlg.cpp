// TableCreatorDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "DBTool.h"
#include "TableCreatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableCreatorDlg �_�C�A���O


CTableCreatorDlg::CTableCreatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTableCreatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableCreatorDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CTableCreatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableCreatorDlg)
	DDX_Control(pDX, IDC_TABLELIST, m_objList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableCreatorDlg, CDialog)
	//{{AFX_MSG_MAP(CTableCreatorDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableCreatorDlg ���b�Z�[�W �n���h��

BOOL CTableCreatorDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	m_objList.InsertColumn(0, "�e�[�u����");
	m_objList.InsertColumn(1, "����");
	m_objList.InsertColumn(2, "NULL����");
	m_objList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_objList.SetAllColumnWidth();
	return TRUE;
}
