// MainFrm.h : CMainFrame クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__57FDC097_F40A_4504_BB5B_18711E36CE1C__INCLUDED_)
#define AFX_MAINFRM_H__57FDC097_F40A_4504_BB5B_18711E36CE1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AdoDatabase.h"
#include "DBTool.h"	// ClassView によって追加されました。
#include "DBConnectBar.h"

#define	WM_STATUSBAR_MSG	WM_APP + 0x100
#define	WM_END_CREATE_SQL	WM_APP + 0x101
#define	WM_END_THREAD		WM_APP + 0x102

class CMainFrame : public CFrameWnd{
	
protected: // シリアライズ機能のみから作成します。
	void UpdateDataInfo();
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// アトリビュート
public:
	static DWORD WINAPI LoadDBListThread(LPVOID lpParameter);
	static DWORD WINAPI LoadDBDlgThread(LPVOID lpParameter);
	static DWORD WINAPI SqlCreateProc( LPVOID lpParameter );
// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	static void GetDBColumType(CString &strType, int nType, LPCTSTR pszSize);
	void LoadSQLHist();
	void SaveSQLHist();
	bool AddSQLHistory(LPCTSTR pszSQL);
	void SetStatusbarMsg(LPCTSTR pszText);
	void SetInclimentSearch(LPCTSTR pszText);
	void SetOutputMsg(LPCTSTR strMsg);
	void SetOutputMsg(UINT uID);
	static void SetOutputMsg(HWND hWnd, LPCTSTR pszText);
	static void SetOutputMsg(HWND hWnd, UINT uID);
	HANDLE m_hThreadHandle;
	BOOL CheckViewThread();
	CAdoDatabase* GetDBObject();
	BOOL ConnectDB();
	CStringArray m_arrSQLTable;
	CStringArray m_arrSQLProc;
	CString m_strSQLData;
	CStringArray m_arrSQLHistory;		//SQLの履歴
	BOOL m_bIgnoreIdentity;
	BOOL m_bIgnoreNotNull;
	BOOL m_bOutProc;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // コントロール バー用メンバ
	CStatusBar		m_wndStatusBar;
	CToolBar		m_wndToolBar;
	CReBar			m_wndReBar;
	CDBConnectBar	m_wndDlgBar;
	CSplitterWnd	m_wndSplit;
	CSplitterWnd	m_wndSubSplit;

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDbclose();
	afx_msg void OnConnect();
	afx_msg void OnUpdateConnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDbclose(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnDropdownDbCmb();
	afx_msg void OnSeldbBtn();
	afx_msg void OnUpdateSelDB(CCmdUI* pCmdUI);
	afx_msg void OnSelMasterBtn();
	afx_msg void OnUpdateSelMaster(CCmdUI* pCmdUI);
	afx_msg void OnDBRefresh();
	afx_msg void OnUpdateDBRefresh(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDBCmb(CCmdUI* pCmdUI);
	afx_msg void OnSqlNew();
	afx_msg void OnDbbackup();
	afx_msg void OnUpdateDbbackup(CCmdUI* pCmdUI);
	afx_msg void OnDbrestore();
	afx_msg void OnUpdateDbrestore(CCmdUI* pCmdUI);
	afx_msg void OnDberacer();
	afx_msg void OnUpdateDberacer(CCmdUI* pCmdUI);
	afx_msg void OnSqlCreateDb();
	afx_msg void OnUpdateSqlCreateDb(CCmdUI* pCmdUI);
	afx_msg void OnRefresh();
	afx_msg void OnUpdateRefresh(CCmdUI* pCmdUI);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnConfig();
	afx_msg void OnHelp();
	afx_msg void OnSqlhist();
	afx_msg void OnUpdateSqlhist(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMdbCreate();
	afx_msg void OnUpdateMdbCreate(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnStatusbarMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEndCreateSql(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEndThread(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	PTHREADINFO m_pThread;
	BOOL m_bAftConnect;
	CAdoDatabase m_objDB;
	HANDLE m_hSqlThread;
	CWnd* m_pOldFocus;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MAINFRM_H__57FDC097_F40A_4504_BB5B_18711E36CE1C__INCLUDED_)
