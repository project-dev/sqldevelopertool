// DBToolView.h : CDBToolView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTOOLVIEW_H__4ABEC825_F408_476E_A778_08AD6B46CF0D__INCLUDED_)
#define AFX_DBTOOLVIEW_H__4ABEC825_F408_476E_A778_08AD6B46CF0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DBToolDoc.h"
#include "DBTreeCtrl.h"
class CDBToolView : public CView{
protected: // シリアライズ機能のみから作成します。
	CDBToolView();
	DECLARE_DYNCREATE(CDBToolView)

// アトリビュート
public:
	CDBToolDoc* GetDocument();
	static int CALLBACK CDBToolView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDBToolView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void EnableTree(BOOL bEnable);
	BOOL IsSQLFullPath(CString &strPath);
	BOOL IsSQLFilePath(CString &strRetPath);
	void OpenTree();
	void DeleteChild(HTREEITEM hParent);
	void RefreshRecord();
	virtual ~CDBToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CDBToolView)
	afx_msg void OnTreeDBClick(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnTreeSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnExportcsv();
	afx_msg void OnRefreshView();
	afx_msg void OnUpdateRefreshView(CCmdUI* pCmdUI);
	afx_msg void OnExporthtml();
	afx_msg void OnUpdateExportcsv(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExporthtml(CCmdUI* pCmdUI);
	afx_msg void OnDelProc();
	afx_msg void OnUpdateDelProc(CCmdUI* pCmdUI);
	afx_msg void OnSqldelete();
	afx_msg void OnUpdateSqldelete(CCmdUI* pCmdUI);
	afx_msg void OnOpenpath();
	afx_msg void OnUpdateOpenpath(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HTREEITEM FindTreeText(LPCTSTR pszText, HTREEITEM hParent);
	CString m_strKeyBuff;
	BOOL FindSQL(LPCTSTR pszFindPath, HTREEITEM hParent);
	CBitmap m_objIconBmp;
	CImageList m_objIcons;
	CDBTreeCtrl m_objTree;
	HTREEITEM m_hRecord;
	HTREEITEM m_hSysRecord;
	HTREEITEM m_hView;
	HTREEITEM m_hSql;
	HTREEITEM m_hProc;
};

#ifndef _DEBUG  // DBToolView.cpp ファイルがデバッグ環境の時使用されます。
inline CDBToolDoc* CDBToolView::GetDocument()
   { return (CDBToolDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DBTOOLVIEW_H__4ABEC825_F408_476E_A778_08AD6B46CF0D__INCLUDED_)
