#if !defined(AFX_BASECUSTPAGE_H__414E394C_CF5C_49FA_BB06_1EF64B3740DE__INCLUDED_)
#define AFX_BASECUSTPAGE_H__414E394C_CF5C_49FA_BB06_1EF64B3740DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseCustPage.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CBaseCustPage �_�C�A���O

class CBaseCustPage : public CDialog
{
// �R���X�g���N�V����
public:
	CBaseCustPage(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CBaseCustPage)
	enum { IDD = IDD_BASE_CUST };
	BOOL	m_bLogTabActive;
	BOOL	m_bIncSerach;
	BOOL	m_bRecAlert;
	int		m_nRecAlert;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CBaseCustPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CBaseCustPage)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_BASECUSTPAGE_H__414E394C_CF5C_49FA_BB06_1EF64B3740DE__INCLUDED_)
