#if !defined(AFX_TABLECREATORDLG_H__C60826F5_C5A8_43F3_9EC0_2D8C4F6758AD__INCLUDED_)
#define AFX_TABLECREATORDLG_H__C60826F5_C5A8_43F3_9EC0_2D8C4F6758AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableCreatorDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CTableCreatorDlg �_�C�A���O

#include "DBListCtrl.h"
class CTableCreatorDlg : public CDialog{
// �R���X�g���N�V����
public:
	CTableCreatorDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CTableCreatorDlg)
	enum { IDD = IDD_TABLE_CREATOR_DLG };
	CDBListCtrl	m_objList;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CTableCreatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CTableCreatorDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_TABLECREATORDLG_H__C60826F5_C5A8_43F3_9EC0_2D8C4F6758AD__INCLUDED_)
