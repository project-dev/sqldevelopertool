#if !defined(AFX_SQLHISTDLG_H__5F20A3D8_FC07_4BA1_B024_7CB3C9847D32__INCLUDED_)
#define AFX_SQLHISTDLG_H__5F20A3D8_FC07_4BA1_B024_7CB3C9847D32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SQLHistDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSQLHistDlg ダイアログ

class CSQLHistDlg : public CDialog
{
// コンストラクション
public:
	CSQLHistDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSQLHistDlg)
	enum { IDD = IDD_SQLHISTDLG };
	CListCtrl	m_objSQLList;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSQLHistDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSQLHistDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetColumnWidth();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SQLHISTDLG_H__5F20A3D8_FC07_4BA1_B024_7CB3C9847D32__INCLUDED_)
