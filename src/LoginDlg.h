#if !defined(AFX_LOGINDLG_H__9A0E7A1E_1974_4B1F_B664_AA58C278B45B__INCLUDED_)
#define AFX_LOGINDLG_H__9A0E7A1E_1974_4B1F_B664_AA58C278B45B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg ダイアログ

class CLoginDlg : public CDialog
{
// コンストラクション
public:
	BOOL CheckSafeValue();
	BOOL CheckUpdate(LPCTSTR pszLoginSet);
	BOOL LoadConnectInfo(LPCTSTR pszInfoName, LPTSTR pszDBType, LPTSTR pszServer, LPTSTR pszUser, LPTSTR pszPass, LPTSTR pszDB, LPTSTR pszODBCType, BOOL &bAftDBSel);
	CString m_strSelSet;
	CLoginDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ
	static  bool CALLBACK LoginSetEnum(const char* pszFile, WIN32_FIND_DATA* pwfd, LPARAM lParam);
// ダイアログ データ
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGIN_DLG };
	CButton	m_objBtnRef;
	CComboBox	m_objDbOdbcCmb;
	CListBox	m_objLoginSetList;
	CComboBox	m_objUser;
	CComboBox	m_objServer;
	CButton	m_objAftDBSelBtn;
	CComboBox	m_objDBType;
	CComboBox	m_objDbNameCmb;
	CString	m_strPassword;
	CString	m_strServer;
	CString	m_strUser;
	CString	m_strDBName;
	BOOL	m_bAftDBSel;
	int		m_nDBType;
	CString	m_strLoginSetName;
	CString	m_strOdbcType;
	CString	m_strInfo;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CLoginDlg)
	afx_msg void OnAfterdbsel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeDttypeCmb();
	afx_msg void OnSelchangeLoginsetList();
	afx_msg void OnDelSet();
	afx_msg void OnDoubleclickedDelSet();
	afx_msg void OnNewSet();
	afx_msg void OnDoubleclickedNewSet();
	afx_msg void OnModifySet();
	afx_msg void OnDoubleclickedModifySet();
	afx_msg void OnBtnRef();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL SaveConnectInfo(CString &strLoginSet);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_LOGINDLG_H__9A0E7A1E_1974_4B1F_B664_AA58C278B45B__INCLUDED_)
