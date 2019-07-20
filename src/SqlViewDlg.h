#if !defined(AFX_SQLVIEWDLG_H__57D3688E_3FE9_477C_B963_94D2D9662FAA__INCLUDED_)
#define AFX_SQLVIEWDLG_H__57D3688E_3FE9_477C_B963_94D2D9662FAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SqlViewDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSqlViewDlg ダイアログ

class CSqlViewDlg : public CDialog
{
// コンストラクション
public:
	CSqlViewDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSqlViewDlg)
	enum { IDD = IDD_SQL_VIEW_DLG };
	CRichEditCtrl	m_objSqlEdit;
	CString	m_strSql;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSqlViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSqlViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSaveSql();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SQLVIEWDLG_H__57D3688E_3FE9_477C_B963_94D2D9662FAA__INCLUDED_)
