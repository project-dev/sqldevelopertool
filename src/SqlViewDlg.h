#if !defined(AFX_SQLVIEWDLG_H__57D3688E_3FE9_477C_B963_94D2D9662FAA__INCLUDED_)
#define AFX_SQLVIEWDLG_H__57D3688E_3FE9_477C_B963_94D2D9662FAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SqlViewDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSqlViewDlg �_�C�A���O

class CSqlViewDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CSqlViewDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSqlViewDlg)
	enum { IDD = IDD_SQL_VIEW_DLG };
	CRichEditCtrl	m_objSqlEdit;
	CString	m_strSql;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSqlViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSqlViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSaveSql();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SQLVIEWDLG_H__57D3688E_3FE9_477C_B963_94D2D9662FAA__INCLUDED_)
