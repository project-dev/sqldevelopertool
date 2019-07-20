#if !defined(AFX_FUNCTABVIEW_H__0C64C872_0F03_470D_BA10_E808A6EEE472__INCLUDED_)
#define AFX_FUNCTABVIEW_H__0C64C872_0F03_470D_BA10_E808A6EEE472__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FuncTabView.h : ヘッダー ファイル
//

#include "DBListCtrl.h"
#include "WndTabCtrl.h"
#include "SQLEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CFuncTabView ビュー

class CFuncTabView : public CView{
protected:
	CFuncTabView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CFuncTabView)

// アトリビュート
public:

// オペレーション
public:
	void EnableSQLEdit(BOOL bEnable);
	BOOL CheckSaveSQL();
	void SetPagePos(int nIndex);
	void SetActivePage(int nIndex);
	void AddMessage(LPCTSTR szMsg);

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CFuncTabView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CFuncTabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CFuncTabView)
	afx_msg void OnDestroy();
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnSqlSaveas();
	afx_msg void OnSqlSqve();
	afx_msg void OnUpdateSqlSaveas(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSqlSqve(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTabclose();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnSqlNew();
	afx_msg void OnUpdateSqlNew(CCmdUI* pCmdUI);
	afx_msg void OnAllselect();
	afx_msg void OnUpdateAllselect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSqlrun(CCmdUI* pCmdUI);
	afx_msg void OnSqlrun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nSQLEditCnt;
	int m_nOldSelProp;
	CTabCtrl m_objTab;
	CWndTabCtrl *m_pPropTab;
//	CRichEditCtrl *m_pFuncEdit;
	CSQLEdit	  *m_pFuncEdit;
	CFont m_objFont;
	LOGFONT m_lFont;
	int m_nOldSel;

	void GetPageRect(CRect &rect, CTabCtrl *pTab = NULL);
	BOOL CloseTab(int nIndex);
	int m_nPopupTargetIndex;
	void RefreshPropertyToTable(LPCTSTR pszTable);
	void RefreshPropertyToColumn(LPCTSTR pszTable);
	BOOL AddOutput();
	BOOL AddPropertyList();
	void OnTabChange(WPARAM wParam, LPARAM lParam);
	BOOL AddSQLEditor();
	int AddTabPage(CWnd *pWnd, LPCTSTR pszTitle, int nIndex = -1, CTabCtrl *pTab = NULL);


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_FUNCTABVIEW_H__0C64C872_0F03_470D_BA10_E808A6EEE472__INCLUDED_)
