#if !defined(AFX_DBBACKUPDLG_H__594795B4_5757_46B4_99DE_AED6266732F4__INCLUDED_)
#define AFX_DBBACKUPDLG_H__594795B4_5757_46B4_99DE_AED6266732F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBBackupDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDBBackupDlg �_�C�A���O

class CDBBackupDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CString m_strBackupName;
	CDBBackupDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDBBackupDlg)
	enum { IDD = IDD_DB_BACKUP_DLG };
	CString	m_strBackupPath;
	CString	m_strDBName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDBBackupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDBBackupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRefDbbackup();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DBBACKUPDLG_H__594795B4_5757_46B4_99DE_AED6266732F4__INCLUDED_)
