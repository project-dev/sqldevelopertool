#if !defined(AFX_BASECUSTPAGE_H__414E394C_CF5C_49FA_BB06_1EF64B3740DE__INCLUDED_)
#define AFX_BASECUSTPAGE_H__414E394C_CF5C_49FA_BB06_1EF64B3740DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseCustPage.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CBaseCustPage ダイアログ

class CBaseCustPage : public CDialog
{
// コンストラクション
public:
	CBaseCustPage(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CBaseCustPage)
	enum { IDD = IDD_BASE_CUST };
	BOOL	m_bLogTabActive;
	BOOL	m_bIncSerach;
	BOOL	m_bRecAlert;
	int		m_nRecAlert;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CBaseCustPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CBaseCustPage)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BASECUSTPAGE_H__414E394C_CF5C_49FA_BB06_1EF64B3740DE__INCLUDED_)
