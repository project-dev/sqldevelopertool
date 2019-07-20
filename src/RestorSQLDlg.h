#if !defined(AFX_RESTORSQLDLG_H__64635801_050A_4016_B063_415F51B9F705__INCLUDED_)
#define AFX_RESTORSQLDLG_H__64635801_050A_4016_B063_415F51B9F705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RestorSQLDlg.h : ヘッダー ファイル
//
#include "DBListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CRestorSQLDlg ダイアログ

class CRestorSQLDlg : public CDialog
{
// コンストラクション
public:
	void SetSelectListCheck(CListCtrl *pList);
	CStringArray m_arrTables;
	CStringArray m_arrProcs;
	CRestorSQLDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CRestorSQLDlg)
	enum { IDD = IDD_RESTORESQL_DLG };
	CButton	m_objOkBtn;
	CButton	m_objIgnoreNotNull;
	CButton	m_objIgnoreIdentity;
	CButton	m_objOutProc;
	CDBListCtrl	m_objProcList;
	CDBListCtrl	m_objList;
	BOOL	m_bIgnoreIdentity;
	BOOL	m_bIgnoreNotNull;
	BOOL	m_bOutProc;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRestorSQLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CRestorSQLDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKeydownTableList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownProclist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNoProc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RESTORSQLDLG_H__64635801_050A_4016_B063_415F51B9F705__INCLUDED_)
