#if !defined(AFX_DBLISTCTRL_H__8E387DEC_7B30_4C3D_B10B_70CF487CDCC5__INCLUDED_)
#define AFX_DBLISTCTRL_H__8E387DEC_7B30_4C3D_B10B_70CF487CDCC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBListCtrl.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDBListCtrl ウィンドウ
#include <afxtempl.h>
class CDBListCtrl : public CListCtrl{
// コンストラクション
public:
	CDBListCtrl();
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDBListCtrl)
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	//}}AFX_VIRTUAL


// インプリメンテーション
public:
	void DeleleAllIsNull();
	void SetIsNull(int nIndex, int nCol, BOOL bIsNull);
	virtual ~CDBListCtrl();
	void SetAllColumnWidth();

	// 生成されたメッセージ マップ関数
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
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DBLISTCTRL_H__8E387DEC_7B30_4C3D_B10B_70CF487CDCC5__INCLUDED_)
