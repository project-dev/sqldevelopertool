#if !defined(AFX_PROCVIEWDLG_H__C6B479E1_E9D1_4AF8_97FD_5A060FE75817__INCLUDED_)
#define AFX_PROCVIEWDLG_H__C6B479E1_E9D1_4AF8_97FD_5A060FE75817__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcViewDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CProcViewDlg ダイアログ

class CProcViewDlg : public CDialog
{
// コンストラクション
public:
	CString m_strFuncData;
	CProcViewDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CProcViewDlg)
	enum { IDD = IDD_PROC_DLG };
	CString	m_strProc;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CProcViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CProcViewDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PROCVIEWDLG_H__C6B479E1_E9D1_4AF8_97FD_5A060FE75817__INCLUDED_)
