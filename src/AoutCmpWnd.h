#if !defined(AFX_AOUTCMPWND_H__8FD8FCDB_CA52_41CE_A754_FA222B857BE1__INCLUDED_)
#define AFX_AOUTCMPWND_H__8FD8FCDB_CA52_41CE_A754_FA222B857BE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AoutCmpWnd.h : ヘッダー ファイル
//

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CAoutCmpWnd ウィンドウ

#define AC_SELECT_TEXT	0x0001

typedef struct tagPICKDATA{
	char szPickString[1024];		//実際の文字列
	char szPickDispString[2048];	//表示用
}PICKDATA, *PPICKDATA;

class CAoutCmpWnd : public CListCtrl{
// コンストラクション

public:
	CAoutCmpWnd();
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAoutCmpWnd)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	BOOL SetPickString(LPCTSTR strPickString);
	void SetPickData(CArray<PPICKDATA, PPICKDATA> &arrPickList);
	void SetPickData(PPICKDATA pDatas, int nSize);
	virtual ~CAoutCmpWnd();

	// 生成されたメッセージ マップ関数
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
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_AOUTCMPWND_H__8FD8FCDB_CA52_41CE_A754_FA222B857BE1__INCLUDED_)
