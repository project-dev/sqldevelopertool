#if !defined(AFX_DBBACKUPDLG_H__594795B4_5757_46B4_99DE_AED6266732F4__INCLUDED_)
#define AFX_DBBACKUPDLG_H__594795B4_5757_46B4_99DE_AED6266732F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBBackupDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDBBackupDlg ダイアログ

class CDBBackupDlg : public CDialog
{
// コンストラクション
public:
	CString m_strBackupName;
	CDBBackupDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDBBackupDlg)
	enum { IDD = IDD_DB_BACKUP_DLG };
	CString	m_strBackupPath;
	CString	m_strDBName;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDBBackupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDBBackupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRefDbbackup();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DBBACKUPDLG_H__594795B4_5757_46B4_99DE_AED6266732F4__INCLUDED_)
