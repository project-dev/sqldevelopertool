#if !defined(AFX_DBCONNECTBAR_H__B73AE184_0EA4_4AD9_A1ED_4FB3B34DA2FD__INCLUDED_)
#define AFX_DBCONNECTBAR_H__B73AE184_0EA4_4AD9_A1ED_4FB3B34DA2FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBConnectBar.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDBConnectBar ダイアログ

class CDBConnectBar : public CDialogBar
{
// コンストラクション
public:
	BOOL Create( CWnd* pParentWnd, UINT nStyle, UINT nID = IDD);
	CDBConnectBar();   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDBConnectBar)
	enum { IDD = IDR_MAINFRAME };
	CComboBox	m_objDBSelCmb;
	CButton	m_objSelBtn;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDBConnectBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDBConnectBar)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DBCONNECTBAR_H__B73AE184_0EA4_4AD9_A1ED_4FB3B34DA2FD__INCLUDED_)
