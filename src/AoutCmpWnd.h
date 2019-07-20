#if !defined(AFX_AOUTCMPWND_H__8FD8FCDB_CA52_41CE_A754_FA222B857BE1__INCLUDED_)
#define AFX_AOUTCMPWND_H__8FD8FCDB_CA52_41CE_A754_FA222B857BE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AoutCmpWnd.h : �w�b�_�[ �t�@�C��
//

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CAoutCmpWnd �E�B���h�E

#define AC_SELECT_TEXT	0x0001

typedef struct tagPICKDATA{
	char szPickString[1024];		//���ۂ̕�����
	char szPickDispString[2048];	//�\���p
}PICKDATA, *PPICKDATA;

class CAoutCmpWnd : public CListCtrl{
// �R���X�g���N�V����

public:
	CAoutCmpWnd();
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAoutCmpWnd)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	BOOL SetPickString(LPCTSTR strPickString);
	void SetPickData(CArray<PPICKDATA, PPICKDATA> &arrPickList);
	void SetPickData(PPICKDATA pDatas, int nSize);
	virtual ~CAoutCmpWnd();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CAoutCmpWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void SendSelectData();
	void DeletePickData();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_AOUTCMPWND_H__8FD8FCDB_CA52_41CE_A754_FA222B857BE1__INCLUDED_)
