#if !defined(AFX_DBERASUREDLG_H__7E5569A8_23D9_46B6_B51A_198678A76485__INCLUDED_)
#define AFX_DBERASUREDLG_H__7E5569A8_23D9_46B6_B51A_198678A76485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBErasureDlg.h : ヘッダー ファイル
//
#include "AdoDatabase.h"

/////////////////////////////////////////////////////////////////////////////
// CDBErasureDlg ダイアログ
#include "DBListCtrl.h"
class CDBErasureDlg : public CDialog
{
// コンストラクション
public:
	BOOL GetDatabases();
	CAdoDatabase* m_pDB;
	CStringArray m_arrDBNames;
	CDBErasureDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDBErasureDlg)
	enum { IDD = IDD_DB_ERACER_DLG };
	CDBListCtrl	m_objList;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDBErasureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDBErasureDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DBERASUREDLG_H__7E5569A8_23D9_46B6_B51A_198678A76485__INCLUDED_)
