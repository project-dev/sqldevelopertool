#if !defined(AFX_CONFDLG_H__05DB9A1B_6429_4199_AF69_C5CE3B3DA5AD__INCLUDED_)
#define AFX_CONFDLG_H__05DB9A1B_6429_4199_AF69_C5CE3B3DA5AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CConfDlg ダイアログ

#include "HwndTabCtrl.h"
#include "BaseCustPage.h"
#include "HistCustPage.h"

class CConfDlg : public CDialog{
// コンストラクション
public:
	CConfDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ
	
// ダイアログ データ
	//{{AFX_DATA(CConfDlg)
	enum { IDD = IDD_CONFIG_DLG };
	CHwndTabCtrl	m_objTab;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CConfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CConfDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBaseCustPage m_objBaseCustPage;
	CHistCustPage m_objHistCustPage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CONFDLG_H__05DB9A1B_6429_4199_AF69_C5CE3B3DA5AD__INCLUDED_)
