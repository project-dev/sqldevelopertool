#if !defined(AFX_HISTCUSTPAGE_H__1B12F5D2_217F_44EA_AF02_EA8B55EC1DF6__INCLUDED_)
#define AFX_HISTCUSTPAGE_H__1B12F5D2_217F_44EA_AF02_EA8B55EC1DF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistCustPage.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CHistCustPage �_�C�A���O

class CHistCustPage : public CDialog
{
// �R���X�g���N�V����
public:
	CHistCustPage(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CHistCustPage)
	enum { IDD = IDD_HIST_CUST };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CHistCustPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CHistCustPage)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_HISTCUSTPAGE_H__1B12F5D2_217F_44EA_AF02_EA8B55EC1DF6__INCLUDED_)
