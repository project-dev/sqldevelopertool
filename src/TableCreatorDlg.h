#if !defined(AFX_TABLECREATORDLG_H__C60826F5_C5A8_43F3_9EC0_2D8C4F6758AD__INCLUDED_)
#define AFX_TABLECREATORDLG_H__C60826F5_C5A8_43F3_9EC0_2D8C4F6758AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableCreatorDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CTableCreatorDlg ダイアログ

#include "DBListCtrl.h"
class CTableCreatorDlg : public CDialog{
// コンストラクション
public:
	CTableCreatorDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CTableCreatorDlg)
	enum { IDD = IDD_TABLE_CREATOR_DLG };
	CDBListCtrl	m_objList;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CTableCreatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CTableCreatorDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TABLECREATORDLG_H__C60826F5_C5A8_43F3_9EC0_2D8C4F6758AD__INCLUDED_)
