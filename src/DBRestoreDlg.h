#if !defined(AFX_DBRESTOREDLG_H__C2CC35E2_4760_446C_99AE_444036ACAFDE__INCLUDED_)
#define AFX_DBRESTOREDLG_H__C2CC35E2_4760_446C_99AE_444036ACAFDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBRestoreDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDBRestoreDlg ダイアログ

class CDBRestoreDlg : public CDialog
{
// コンストラクション
public:
	CDBRestoreDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDBRestoreDlg)
	enum { IDD = IDD_DB_RESTORE_DLG };
	CString	m_strBackupPath;
	CString	m_strDBName;
	CString	m_strRestorePath;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDBRestoreDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDBRestoreDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRefDbbackup();
	virtual void OnOK();
	afx_msg void OnDoubleclickedOk();
	afx_msg void OnRefDbrestore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DBRESTOREDLG_H__C2CC35E2_4760_446C_99AE_444036ACAFDE__INCLUDED_)
