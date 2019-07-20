#if !defined(AFX_RESTORSQLDLG_H__64635801_050A_4016_B063_415F51B9F705__INCLUDED_)
#define AFX_RESTORSQLDLG_H__64635801_050A_4016_B063_415F51B9F705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RestorSQLDlg.h : �w�b�_�[ �t�@�C��
//
#include "DBListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CRestorSQLDlg �_�C�A���O

class CRestorSQLDlg : public CDialog
{
// �R���X�g���N�V����
public:
	void SetSelectListCheck(CListCtrl *pList);
	CStringArray m_arrTables;
	CStringArray m_arrProcs;
	CRestorSQLDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CRestorSQLDlg)
	enum { IDD = IDD_RESTORESQL_DLG };
	CButton	m_objOkBtn;
	CButton	m_objIgnoreNotNull;
	CButton	m_objIgnoreIdentity;
	CButton	m_objOutProc;
	CDBListCtrl	m_objProcList;
	CDBListCtrl	m_objList;
	BOOL	m_bIgnoreIdentity;
	BOOL	m_bIgnoreNotNull;
	BOOL	m_bOutProc;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRestorSQLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CRestorSQLDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKeydownTableList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownProclist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNoProc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_RESTORSQLDLG_H__64635801_050A_4016_B063_415F51B9F705__INCLUDED_)
