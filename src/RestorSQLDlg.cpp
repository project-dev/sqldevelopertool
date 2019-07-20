// RestorSQLDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "dbtool.h"
#include "RestorSQLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRestorSQLDlg ダイアログ


CRestorSQLDlg::CRestorSQLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRestorSQLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRestorSQLDlg)
	m_bIgnoreIdentity = FALSE;
	m_bIgnoreNotNull = FALSE;
	m_bOutProc = FALSE;
	//}}AFX_DATA_INIT
}


void CRestorSQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRestorSQLDlg)
	DDX_Control(pDX, IDOK, m_objOkBtn);
	DDX_Control(pDX, IDC_IGNORE_NOT_NULL, m_objIgnoreNotNull);
	DDX_Control(pDX, IDC_IGNORE_IDENTOTY, m_objIgnoreIdentity);
	DDX_Control(pDX, IDC_NO_PROC, m_objOutProc);
	DDX_Control(pDX, IDC_PROCLIST, m_objProcList);
	DDX_Control(pDX, IDC_TABLE_LIST, m_objList);
	DDX_Check(pDX, IDC_IGNORE_IDENTOTY, m_bIgnoreIdentity);
	DDX_Check(pDX, IDC_IGNORE_NOT_NULL, m_bIgnoreNotNull);
	DDX_Check(pDX, IDC_NO_PROC, m_bOutProc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRestorSQLDlg, CDialog)
	//{{AFX_MSG_MAP(CRestorSQLDlg)
	ON_NOTIFY(LVN_KEYDOWN, IDC_TABLE_LIST, OnKeydownTableList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_PROCLIST, OnKeydownProclist)
	ON_BN_CLICKED(IDC_NO_PROC, OnNoProc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRestorSQLDlg メッセージ ハンドラ

BOOL CRestorSQLDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	m_objList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
	m_objList.InsertColumn(0, "テーブル名");

	m_objProcList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
	m_objProcList.InsertColumn(0, "プロシージャ名");

	int nEnableItem = 0;

	if(m_arrTables.GetSize() == 0){
		m_objIgnoreIdentity.EnableWindow(FALSE);
		m_objIgnoreNotNull.EnableWindow(FALSE);
		m_objList.EnableWindow(FALSE);
		nEnableItem++;
	}else{
		for(int i = 0; i < m_arrTables.GetSize(); i++){
			m_objList.InsertItem(i, m_arrTables.GetAt(i));
			m_objList.SetCheck(i);
		}
	}

	if(m_arrProcs.GetSize() == 0){
		m_objOutProc.EnableWindow(FALSE);
		nEnableItem++;
	}else{
		for(int j = 0; j < m_arrProcs.GetSize(); j++){
			m_objProcList.InsertItem(j, m_arrProcs.GetAt(j));
			m_objProcList.SetCheck(j);
		}
	}	

	m_objList.SetAllColumnWidth();
	m_objProcList.SetAllColumnWidth();
	m_objProcList.EnableWindow(FALSE);	

	if(nEnableItem >= 2){
		//何もできないのでOKも押せなくする
		m_objOkBtn.EnableWindow(FALSE);
	}

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CRestorSQLDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
	//再現するテーブルだけ残す
	int nCnt = m_objList.GetItemCount();
	for(int i = nCnt - 1; i >= 0; i--){
		if(!m_objList.GetCheck(i)){
			m_arrTables.RemoveAt(i);
		}
	}

	nCnt = m_objProcList.GetItemCount();
	for(int j = nCnt - 1; j >= 0; j--){
		if(!m_objProcList.GetCheck(j)){
			m_arrProcs.RemoveAt(j);
		}
	}
	CDialog::OnOK();
}

void CRestorSQLDlg::OnKeydownTableList(NMHDR* pNMHDR, LRESULT* pResult){
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	*pResult = 0;

	UpdateData();
	if(pLVKeyDow->wVKey == VK_SPACE){
		SetSelectListCheck(&m_objList);
		*pResult = 1;
	}
}

void CRestorSQLDlg::OnKeydownProclist(NMHDR* pNMHDR, LRESULT* pResult){
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	*pResult = 0;

	UpdateData();
	if(pLVKeyDow->wVKey == VK_SPACE){
		SetSelectListCheck(&m_objProcList);
		*pResult = 1;
	}
}

void CRestorSQLDlg::SetSelectListCheck(CListCtrl *pList){
	int nCurIndex = pList->GetSelectionMark();
	BOOL bCheck = !pList->GetCheck(nCurIndex);
	int nSelCnt = pList->GetSelectedCount();
	int nIndex = -1;
	if(nSelCnt == 0){
		return;
	}

	nIndex = pList->GetNextItem(nIndex, LVNI_SELECTED | LVNI_ALL);
	while(nSelCnt){
		nSelCnt--;
		pList->SetCheck(nIndex, bCheck);
		pList->RedrawItems(nIndex, nIndex);
		nIndex = pList->GetNextItem(nIndex, LVNI_SELECTED | LVNI_ALL);
	}
}

void CRestorSQLDlg::OnNoProc() {
	UpdateData();
	m_objProcList.EnableWindow(m_bOutProc);	
}
