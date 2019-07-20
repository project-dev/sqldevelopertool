#if !defined(AFX_RESULTVIEW_H__4989B291_BE4C_470D_82C5_1182E878033D__INCLUDED_)
#define AFX_RESULTVIEW_H__4989B291_BE4C_470D_82C5_1182E878033D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultView.h : ヘッダー ファイル
//

#include "DBListCtrl.h"
#include "DBTool.h"	// ClassView によって追加されました。
#include <AfxTempl.h>

#define MODE_PAGE_LIST 1

/////////////////////////////////////////////////////////////////////////////
// CResultView ビュー

typedef struct tagCELL{
	BOOL isNull;
	char* pszValue;
}CELL, *PCELL;


static const int MAX_PAGE_ROW_CNT = 50;
static const int SELECTOR_HEIGHT = 18;
class CResultView : public CView{
protected:
	CResultView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CResultView)

// アトリビュート
public:
	//テーブル読み込みスレッド用関数
	static DWORD WINAPI LoadTableThread(LPVOID lpParameter);
	static int CALLBACK SortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	BOOL LoadTable(LPCTSTR szSQL);

// オペレーション
public:
	void SetCtrlPos();
	void EnableList(BOOL bEnable);
	void Refresh(LPCTSTR pszSQL);
	HANDLE m_hThreadHandle;
	CDBListCtrl* GetListCtrl();
	CString m_strResultSQL;

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CResultView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CResultView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
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
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RESULTVIEW_H__4989B291_BE4C_470D_82C5_1182E878033D__INCLUDED_)
