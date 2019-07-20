#if !defined(AFX_DBRESTOREDLG_H__C2CC35E2_4760_446C_99AE_444036ACAFDE__INCLUDED_)
#define AFX_DBRESTOREDLG_H__C2CC35E2_4760_446C_99AE_444036ACAFDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBRestoreDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDBRestoreDlg �_�C�A���O

class CDBRestoreDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CDBRestoreDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDBRestoreDlg)
	enum { IDD = IDD_DB_RESTORE_DLG };
	CString	m_strBackupPath;
	CString	m_strDBName;
	CString	m_strRestorePath;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDBRestoreDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDBRestoreDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRefDbbackup();
	virtual void OnOK();
	afx_msg void OnDoubleclickedOk();
	afx_msg void OnRefDbrestore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DBRESTOREDLG_H__C2CC35E2_4760_446C_99AE_444036ACAFDE__INCLUDED_)
