#if !defined(AFX_SQLHISTDLG_H__5F20A3D8_FC07_4BA1_B024_7CB3C9847D32__INCLUDED_)
#define AFX_SQLHISTDLG_H__5F20A3D8_FC07_4BA1_B024_7CB3C9847D32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SQLHistDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSQLHistDlg �_�C�A���O

class CSQLHistDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CSQLHistDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSQLHistDlg)
	enum { IDD = IDD_SQLHISTDLG };
	CListCtrl	m_objSQLList;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSQLHistDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSQLHistDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetColumnWidth();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SQLHISTDLG_H__5F20A3D8_FC07_4BA1_B024_7CB3C9847D32__INCLUDED_)
