#if !defined(AFX_RESULTVIEW_H__4989B291_BE4C_470D_82C5_1182E878033D__INCLUDED_)
#define AFX_RESULTVIEW_H__4989B291_BE4C_470D_82C5_1182E878033D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultView.h : �w�b�_�[ �t�@�C��
//

#include "DBListCtrl.h"
#include "DBTool.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include <AfxTempl.h>

#define MODE_PAGE_LIST 1

/////////////////////////////////////////////////////////////////////////////
// CResultView �r���[

typedef struct tagCELL{
	BOOL isNull;
	char* pszValue;
}CELL, *PCELL;


static const int MAX_PAGE_ROW_CNT = 50;
static const int SELECTOR_HEIGHT = 18;
class CResultView : public CView{
protected:
	CResultView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CResultView)

// �A�g���r���[�g
public:
	//�e�[�u���ǂݍ��݃X���b�h�p�֐�
	static DWORD WINAPI LoadTableThread(LPVOID lpParameter);
	static int CALLBACK SortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	BOOL LoadTable(LPCTSTR szSQL);

// �I�y���[�V����
public:
	void SetCtrlPos();
	void EnableList(BOOL bEnable);
	void Refresh(LPCTSTR pszSQL);
	HANDLE m_hThreadHandle;
	CDBListCtrl* GetListCtrl();
	CString m_strResultSQL;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CResultView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CResultView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CResultView)
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRefreshView();
	afx_msg void OnUpdateRefreshView(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnAllselect();
	afx_msg void OnUpdateAllselect(CCmdUI* pCmdUI);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnBtnFirst();
	afx_msg void OnBtnPrev();
	afx_msg void OnBtnNext();
	afx_msg void OnBtnEnd();
	afx_msg void OnBtnSnap();

	afx_msg void OnUpdateBtnFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnPrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnEnd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnSnap(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	PTHREADINFO m_pThread;
	CDBListCtrl m_objList;
	CButton m_objBtnFirst;
	CButton m_objBtnPrev;
	CEdit   m_objEdPage;
	CEdit   m_objEdPageBase;
	CButton m_objBtnNext;
	CButton m_objBtnEnd;
	CButton m_objBtnSnap;

	void RemoveCellData();
	void ViewPage(int page);
	CArray< CArray<PCELL, PCELL>* , CArray<PCELL, PCELL>* > m_arrCell;
	int m_nCurPage;
	int m_nPage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_RESULTVIEW_H__4989B291_BE4C_470D_82C5_1182E878033D__INCLUDED_)
