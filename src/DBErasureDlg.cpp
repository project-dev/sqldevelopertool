// DBErasureDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DBTool.h"
#include "DBErasureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBErasureDlg ダイアログ


CDBErasureDlg::CDBErasureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBErasureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBErasureDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CDBErasureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBErasureDlg)
	DDX_Control(pDX, IDC_DBLIST, m_objList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBErasureDlg, CDialog)
	//{{AFX_MSG_MAP(CDBErasureDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBErasureDlg メッセージ ハンドラ

BOOL CDBErasureDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_objList.InsertColumn(0, "データベース名");
	m_objList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);

	int nSize = m_arrDBNames.GetSize();
	if(nSize == 0){
		GetDatabases();
		nSize = m_arrDBNames.GetSize();
	}
	CString strDBName;
	for(int i = 0; i < nSize; i++){
		CString strDBName = m_arrDBNames.GetAt(i);
		if((!strDBName.CompareNoCase("master"))
		|| (!strDBName.CompareNoCase("model"))
		|| (!strDBName.CompareNoCase("tempdb"))
		|| (!strDBName.CompareNoCase("msdb"))
		){
			//削除してはいけないDB
			continue;
		}
		m_objList.InsertItem(i, strDBName);
	}


	m_objList.SetAllColumnWidth();
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

BOOL CDBErasureDlg::GetDatabases(){
	if(!m_pDB){
		return FALSE;
	}
	_RecordsetPtr rs = m_pDB->GetDatabases();
	if(rs == NULL){
		CString strErr = m_pDB->GetError();
		AfxMessageBox(strErr);
		return FALSE;
	}

	_variant_t vt;
	CString strDBName;
	while(rs->EndOfFile == VARIANT_FALSE){
		vt = m_pDB->GetFieldValue(rs, "DATABASE_NAME");
		if(vt.vt != VT_NULL){
			strDBName = vt.bstrVal;
			m_arrDBNames.Add(strDBName);
		}
		rs->MoveNext();
	}
	rs->Close();
	return TRUE;
}

void CDBErasureDlg::OnOK(){
	m_arrDBNames.RemoveAll();
	int nMax = m_objList.GetItemCount();
	for(int i = 0; i < nMax; i++){
		if(m_objList.GetCheck(i)){
			m_arrDBNames.Add(m_objList.GetItemText(i, 0));
		}
	}
	CDialog::OnOK();
}
