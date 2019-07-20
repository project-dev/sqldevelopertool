// AoutCmpWnd.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "dbtool.h"
#include "AoutCmpWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAoutCmpWnd

CAoutCmpWnd::CAoutCmpWnd(){
}

CAoutCmpWnd::~CAoutCmpWnd(){
}


BEGIN_MESSAGE_MAP(CAoutCmpWnd, CListCtrl)
	//{{AFX_MSG_MAP(CAoutCmpWnd)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR_REFLECT()
	ON_NOTIFY_REFLECT(NM_KILLFOCUS, OnKillfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAoutCmpWnd メッセージ ハンドラ

int CAoutCmpWnd::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetWindowLong(m_hWnd, GWL_STYLE, WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_NOCOLUMNHEADER);
	//ModifyStyleEx(0, LVS_EX_INFOTIP);
	InsertColumn(0, "");
	return 0;
}
void CAoutCmpWnd::SetPickData(PPICKDATA pDatas, int nSize){
	if(pDatas == NULL){
		return;
	}
	PICKDATA pData;
	PPICKDATA lpData;
	DeletePickData();

	for(int i = 0; i < nSize; i++){
		pData = pDatas[i];
		lpData = new PICKDATA;
		memset(lpData, 0, sizeof(PICKDATA));
		memcpy(lpData, &pData, sizeof(PICKDATA));
		InsertItem(i, pData.szPickDispString, 0);
		SetItemData(i, (LPARAM)lpData);
	}
	SetColumnWidth(0, LVSCW_AUTOSIZE);
	SortItems(CompareFunc, 0);
}

void CAoutCmpWnd::SetPickData(CArray<PPICKDATA, PPICKDATA> &arrPickList){
	int nSize = arrPickList.GetSize();
	PPICKDATA pData;
	PPICKDATA lpData;
	DeletePickData();
	for(int i = 0; i < nSize; i++){
		pData = arrPickList.GetAt(i);
		lpData = new PICKDATA;
		memset(lpData, 0, sizeof(PICKDATA));
		memcpy(lpData, pData, sizeof(PICKDATA));
		InsertItem(i, pData->szPickDispString, 0);
		SetItemData(i, (LPARAM)lpData);
	}
	SetColumnWidth(0, LVSCW_AUTOSIZE);
	SortItems(CompareFunc, 0);

}

BOOL CAoutCmpWnd::SetPickString(LPCTSTR pszPickString){


	int nCnt = GetItemCount();
	CString strData;
	CString strPickString = pszPickString;
	int nPickLen = strPickString.GetLength();
	int nDataLen;
	int nIndex = -1;
	PPICKDATA pData;
	CString strCheck;
	for(int i = 0; i < nCnt; i++){
		pData = (PPICKDATA)GetItemData(i);
		strData = pData->szPickString;
		nDataLen = strData.GetLength();
		if(nPickLen <= nDataLen){
			strCheck = strData.Left(nPickLen);
			if(!strPickString.CompareNoCase(strCheck)){
				nIndex = i;
				break;
			}
		}
	}


	if(nIndex == -1){
		return FALSE;
	}

	EnsureVisible(nIndex - 1, FALSE);
	int nTop = GetTopIndex();

	SetRedraw(FALSE);
	CSize size;
	size.cx = 0;
	size.cy = 8;
	int nOldTop = nTop;
	while(nIndex > nTop){
		Scroll(size);
		nTop = GetTopIndex();
		if(nOldTop == nTop){
			break;
		}
	}
	SetRedraw(TRUE);

	SetItemState(nIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	return TRUE;
}

void CAoutCmpWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	CWnd *pWnd = GetParent();
	switch(nChar){
	case VK_RETURN:
		SendSelectData();
		break;
	case VK_ESCAPE:
		pWnd->SetFocus();
		ShowWindow(SW_HIDE);
		break;
	}
	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}



void CAoutCmpWnd::DeletePickData(){
	int nSize = GetItemCount();
	PPICKDATA pData;
	for(int i = 0; i < nSize; i++){
		pData = (PPICKDATA)GetItemData(i);
		delete pData;
	}
	DeleteAllItems();

}

void CAoutCmpWnd::OnLButtonDblClk(UINT nFlags, CPoint point){
	SendSelectData();
	CListCtrl::OnLButtonDblClk(nFlags, point);
}

void CAoutCmpWnd::SendSelectData(){
	CString strData;
	COPYDATASTRUCT cds;
	memset(&cds, 0, sizeof(COPYDATASTRUCT));
	CWnd *pWnd = GetParent();
	int nIndex = GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	PPICKDATA pData;
	if(nIndex != -1 ){
		pData = (PPICKDATA)GetItemData(nIndex);
		strData = pData->szPickString;
		cds.dwData = AC_SELECT_TEXT;
		cds.cbData = strData.GetLength() + 1;
		cds.lpData = (LPVOID)strData.GetBuffer(cds.cbData);
		pWnd->SendMessage(WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cds);
	}
	pWnd->SetFocus();
	ShowWindow(SW_HIDE);
}

void CAoutCmpWnd::OnDestroy(){
	DeletePickData();
	CListCtrl::OnDestroy();
}


HBRUSH CAoutCmpWnd::CtlColor(CDC* pDC, UINT nCtlColor){
/*	
	if(nCtlColor == CTLCOLOR_LISTBOX){
		COLORREF crBk = GetSysColor(COLOR_INFOBK);
		COLORREF crText = GetSysColor(COLOR_INFOTEXT);
		pDC->SetBkMode(TRANSPARENT);
		return GetSysColorBrush(COLOR_INFOBK);
	}
*/
	return NULL;
}

int CALLBACK CAoutCmpWnd::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	PPICKDATA pData1 = (PPICKDATA)lParam1;
	PPICKDATA pData2 = (PPICKDATA)lParam2;
	CString str1 = pData1->szPickString;
	CString str2 = pData2->szPickString;
	return str1.Compare(str2);

}

void CAoutCmpWnd::OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult){
	ShowWindow(SW_HIDE);
	
	GetParent()->SetActiveWindow();
	GetParent()->SetFocus();
	*pResult = 0;
}
