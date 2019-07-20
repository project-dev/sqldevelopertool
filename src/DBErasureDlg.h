#if !defined(AFX_DBERASUREDLG_H__7E5569A8_23D9_46B6_B51A_198678A76485__INCLUDED_)
#define AFX_DBERASUREDLG_H__7E5569A8_23D9_46B6_B51A_198678A76485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBErasureDlg.h : �w�b�_�[ �t�@�C��
//
#include "AdoDatabase.h"

/////////////////////////////////////////////////////////////////////////////
// CDBErasureDlg �_�C�A���O
#include "DBListCtrl.h"
class CDBErasureDlg : public CDialog
{
// �R���X�g���N�V����
public:
	BOOL GetDatabases();
	CAdoDatabase* m_pDB;
	CStringArray m_arrDBNames;
	CDBErasureDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDBErasureDlg)
	enum { IDD = IDD_DB_ERACER_DLG };
	CDBListCtrl	m_objList;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDBErasureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDBErasureDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DBERASUREDLG_H__7E5569A8_23D9_46B6_B51A_198678A76485__INCLUDED_)
