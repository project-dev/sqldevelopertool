#if !defined(AFX_INFODLG_H__AD57B934_A290_42C1_895E_9A95C8F835B3__INCLUDED_)
#define AFX_INFODLG_H__AD57B934_A290_42C1_895E_9A95C8F835B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg ダイアログ

class CInfoDlg : public CDialog
{
// コンストラクション
public:
	CString m_strInfo;
	BOOL m_bOkUse;
	CInfoDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CInfoDlg)
	enum { IDD = IDD_INFO_DLG };
	CButton	m_objOk;
	CButton	m_objInfoArea;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect m_objDrawArea;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_INFODLG_H__AD57B934_A290_42C1_895E_9A95C8F835B3__INCLUDED_)
