#if !defined(AFX_DBCONNECTBAR_H__B73AE184_0EA4_4AD9_A1ED_4FB3B34DA2FD__INCLUDED_)
#define AFX_DBCONNECTBAR_H__B73AE184_0EA4_4AD9_A1ED_4FB3B34DA2FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBConnectBar.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDBConnectBar �_�C�A���O

class CDBConnectBar : public CDialogBar
{
// �R���X�g���N�V����
public:
	BOOL Create( CWnd* pParentWnd, UINT nStyle, UINT nID = IDD);
	CDBConnectBar();   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDBConnectBar)
	enum { IDD = IDR_MAINFRAME };
	CComboBox	m_objDBSelCmb;
	CButton	m_objSelBtn;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDBConnectBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDBConnectBar)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DBCONNECTBAR_H__B73AE184_0EA4_4AD9_A1ED_4FB3B34DA2FD__INCLUDED_)
