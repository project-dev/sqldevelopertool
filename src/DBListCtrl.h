#if !defined(AFX_DBLISTCTRL_H__8E387DEC_7B30_4C3D_B10B_70CF487CDCC5__INCLUDED_)
#define AFX_DBLISTCTRL_H__8E387DEC_7B30_4C3D_B10B_70CF487CDCC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBListCtrl.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDBListCtrl �E�B���h�E
#include <afxtempl.h>
class CDBListCtrl : public CListCtrl{
// �R���X�g���N�V����
public:
	CDBListCtrl();
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDBListCtrl)
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	//}}AFX_VIRTUAL


// �C���v�������e�[�V����
public:
	void DeleleAllIsNull();
	void SetIsNull(int nIndex, int nCol, BOOL bIsNull);
	virtual ~CDBListCtrl();
	void SetAllColumnWidth();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CDBListCtrl)
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSqlNew();
	afx_msg void OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteallitems(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	CArray< CArray<BOOL, BOOL>*, CArray<BOOL, BOOL>* > m_arrIsNull;
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DBLISTCTRL_H__8E387DEC_7B30_4C3D_B10B_70CF487CDCC5__INCLUDED_)
