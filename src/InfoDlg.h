#if !defined(AFX_INFODLG_H__AD57B934_A290_42C1_895E_9A95C8F835B3__INCLUDED_)
#define AFX_INFODLG_H__AD57B934_A290_42C1_895E_9A95C8F835B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg �_�C�A���O

class CInfoDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CString m_strInfo;
	BOOL m_bOkUse;
	CInfoDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CInfoDlg)
	enum { IDD = IDD_INFO_DLG };
	CButton	m_objOk;
	CButton	m_objInfoArea;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect m_objDrawArea;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_INFODLG_H__AD57B934_A290_42C1_895E_9A95C8F835B3__INCLUDED_)
