// DBToolDoc.cpp : CDBToolDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "DBTool.h"

#include "DBToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBToolDoc

IMPLEMENT_DYNCREATE(CDBToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CDBToolDoc, CDocument)
	//{{AFX_MSG_MAP(CDBToolDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBToolDoc クラスの構築/消滅

CDBToolDoc::CDBToolDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CDBToolDoc::~CDBToolDoc()
{
}

BOOL CDBToolDoc::OnNewDocument(){
	SetTitle("切断");
/*
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)
*/
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDBToolDoc シリアライゼーション

void CDBToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDBToolDoc クラスの診断

#ifdef _DEBUG
void CDBToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDBToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBToolDoc コマンド
