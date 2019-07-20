// DBErasureDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "DBTool.h"
#include "DBErasureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBErasureDlg �_�C�A���O


CDBErasureDlg::CDBErasureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBErasureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBErasureDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CDBErasureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBErasureDlg)
	DDX_Control(pDX, IDC_DBLIST, m_objList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBErasureDlg, CDialog)
	//{{AFX_MSG_MAP(CDBErasureDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBErasureDlg ���b�Z�[�W �n���h��

BOOL CDBErasureDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	m_objList.InsertColumn(0, "�f�[�^�x�[�X��");
	m_objList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);

	int nSize = m_arrDBNames.GetSize();
	if(nSize == 0){
		GetDatabases();
		nSize = m_arrDBNames.GetSize();
	}
	CString strDBName;
	for(int i = 0; i < nSize; i++){
		CString strDBName = m_arrDBNames.GetAt(i);
		if((!strDBName.CompareNoCase("master"))
		|| (!strDBName.CompareNoCase("model"))
		|| (!strDBName.CompareNoCase("tempdb"))
		|| (!strDBName.CompareNoCase("msdb"))
		){
			//�폜���Ă͂����Ȃ�DB
			continue;
		}
		m_objList.InsertItem(i, strDBName);
	}


	m_objList.SetAllColumnWidth();
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

BOOL CDBErasureDlg::GetDatabases(){
	if(!m_pDB){
		return FALSE;
	}
	_RecordsetPtr rs = m_pDB->GetDatabases();
	if(rs == NULL){
		CString strErr = m_pDB->GetError();
		AfxMessageBox(strErr);
		return FALSE;
	}

	_variant_t vt;
	CString strDBName;
	while(rs->EndOfFile == VARIANT_FALSE){
		vt = m_pDB->GetFieldValue(rs, "DATABASE_NAME");
		if(vt.vt != VT_NULL){
			strDBName = vt.bstrVal;
			m_arrDBNames.Add(strDBName);
		}
		rs->MoveNext();
	}
	rs->Close();
	return TRUE;
}

void CDBErasureDlg::OnOK(){
	m_arrDBNames.RemoveAll();
	int nMax = m_objList.GetItemCount();
	for(int i = 0; i < nMax; i++){
		if(m_objList.GetCheck(i)){
			m_arrDBNames.Add(m_objList.GetItemText(i, 0));
		}
	}
	CDialog::OnOK();
}
