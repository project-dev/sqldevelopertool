#if !defined(AFX_PROCVIEWDLG_H__C6B479E1_E9D1_4AF8_97FD_5A060FE75817__INCLUDED_)
#define AFX_PROCVIEWDLG_H__C6B479E1_E9D1_4AF8_97FD_5A060FE75817__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcViewDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CProcViewDlg �_�C�A���O

class CProcViewDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CString m_strFuncData;
	CProcViewDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CProcViewDlg)
	enum { IDD = IDD_PROC_DLG };
	CString	m_strProc;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CProcViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CProcViewDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PROCVIEWDLG_H__C6B479E1_E9D1_4AF8_97FD_5A060FE75817__INCLUDED_)
