// DBTreeCtrl.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "dbtool.h"
#include "DBTreeCtrl.h"
#include "MainFrm.h"

#include "DBToolView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBTreeCtrl

CDBTreeCtrl::CDBTreeCtrl()
{
}

CDBTreeCtrl::~CDBTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CDBTreeCtrl, CTreeCtrlEx)
	//{{AFX_MSG_MAP(CDBTreeCtrl)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBTreeCtrl メッセージ ハンドラ
void CDBTreeCtrl::ChangeIncrementBuffer(CString strBuff){
	CMainFrame *pFrm = (CMainFrame*)GetParentFrame();
	pFrm->SetInclimentSearch(strBuff);
}

void CDBTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	
	CTreeCtrlEx::OnKeyDown(nChar, nRepCnt, nFlags);

	if(nChar == VK_RETURN){
		CDBToolView *pView = (CDBToolView*)GetParent();
		pView->OpenTree();
	}
}
