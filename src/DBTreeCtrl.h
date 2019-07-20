#if !defined(AFX_DBTREECTRL_H__B081374E_A28E_404E_B2DB_30DC34BF9D1D__INCLUDED_)
#define AFX_DBTREECTRL_H__B081374E_A28E_404E_B2DB_30DC34BF9D1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBTreeCtrl.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDBTreeCtrl ウィンドウ
#include "TreeCtrlEx.h"

class CDBTreeCtrl : public CTreeCtrlEx
{
// コンストラクション
public:
	CDBTreeCtrl();

// アトリビュート
public:

// オペレーション
public:
	virtual void ChangeIncrementBuffer(CString strBuff);

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDBTreeCtrl)
	//}}AFX_VIRTUAL
// インプリメンテーション
public:
	virtual ~CDBTreeCtrl();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CDBTreeCtrl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DBTREECTRL_H__B081374E_A28E_404E_B2DB_30DC34BF9D1D__INCLUDED_)
