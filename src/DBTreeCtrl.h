#if !defined(AFX_DBTREECTRL_H__B081374E_A28E_404E_B2DB_30DC34BF9D1D__INCLUDED_)
#define AFX_DBTREECTRL_H__B081374E_A28E_404E_B2DB_30DC34BF9D1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBTreeCtrl.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDBTreeCtrl �E�B���h�E
#include "TreeCtrlEx.h"

class CDBTreeCtrl : public CTreeCtrlEx
{
// �R���X�g���N�V����
public:
	CDBTreeCtrl();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:
	virtual void ChangeIncrementBuffer(CString strBuff);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDBTreeCtrl)
	//}}AFX_VIRTUAL
// �C���v�������e�[�V����
public:
	virtual ~CDBTreeCtrl();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CDBTreeCtrl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DBTREECTRL_H__B081374E_A28E_404E_B2DB_30DC34BF9D1D__INCLUDED_)
