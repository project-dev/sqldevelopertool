#if !defined(AFX_CONFDLG_H__05DB9A1B_6429_4199_AF69_C5CE3B3DA5AD__INCLUDED_)
#define AFX_CONFDLG_H__05DB9A1B_6429_4199_AF69_C5CE3B3DA5AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CConfDlg �_�C�A���O

#include "HwndTabCtrl.h"
#include "BaseCustPage.h"
#include "HistCustPage.h"

class CConfDlg : public CDialog{
// �R���X�g���N�V����
public:
	CConfDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	
// �_�C�A���O �f�[�^
	//{{AFX_DATA(CConfDlg)
	enum { IDD = IDD_CONFIG_DLG };
	CHwndTabCtrl	m_objTab;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CConfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CConfDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBaseCustPage m_objBaseCustPage;
	CHistCustPage m_objHistCustPage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CONFDLG_H__05DB9A1B_6429_4199_AF69_C5CE3B3DA5AD__INCLUDED_)
