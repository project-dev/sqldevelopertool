#if !defined(AFX_LOGINSETNAMEINPDLG_H__28A68763_89C0_46D7_A5C6_63FFCBA84F50__INCLUDED_)
#define AFX_LOGINSETNAMEINPDLG_H__28A68763_89C0_46D7_A5C6_63FFCBA84F50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginSetNameInpDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CLoginSetNameInpDlg �_�C�A���O

class CLoginSetNameInpDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CLoginSetNameInpDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CLoginSetNameInpDlg)
	enum { IDD = IDD_INP_LOGIN_SET_DLG };
	CString	m_strName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLoginSetNameInpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CLoginSetNameInpDlg)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LOGINSETNAMEINPDLG_H__28A68763_89C0_46D7_A5C6_63FFCBA84F50__INCLUDED_)
