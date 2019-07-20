// DBListCtrl.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DBTool.h"
#include "DBListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include <comdef.h>
/////////////////////////////////////////////////////////////////////////////
// CDBListCtrl
int CALLBACK CDBListCtrl::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	int nRet = 0;
/*
	_variant_t val1 = *(_variant_t*)lParam1;
	_variant_t val2 = *(_variant_t*)lParam2;
	if(val1.vt != val2.vt){
		return 0;
	}

	switch(val1.vt){
	case VT_I4:
		if(val1.lVal < val2.lVal){
			nRet = -1;
		}else if(val1.lVal > val2.lVal){
			nRet = 1;
		}
		break;
	case VT_UI1:
		if(val1.bVal < val2.bVal){
			nRet = -1;
		}else if(val1.bVal > val2.bVal){
			nRet = 1;
		}
		break;
	case VT_I2:
		if(val1.iVal < val2.iVal){
			nRet = -1;
		}else if(val1.iVal > val2.iVal){
			nRet = 1;
		}
		break;
	case VT_R4:
		if(val1.fltVal < val2.fltVal){
			nRet = -1;
		}else if(val1.fltVal > val2.fltVal){
			nRet = 1;
		}
		break;
	case VT_R8:
		if(val1.dblVal < val2.dblVal){
			nRet = -1;
		}else if(val1.dblVal > val2.dblVal){
			nRet = 1;
		}
		break;
	case VT_BOOL:
		if(val1.boolVal < val2.boolVal){
			nRet = -1;
		}else if(val1.boolVal > val2.boolVal){
			nRet = 1;
		}
		break;
	case VT_ERROR:
		if(val1.scode < val2.scode){
			nRet = -1;
		}else if(val1.scode > val2.scode){
			nRet = 1;
		}
		break;

//	case VT_CY:
//		if(val1.cyVal.int64 < val2.cyVal.int64){
//			nRet = -1;
//		}else if(val1.cyVal > val2.cyVal.int64){
//			nRet = 1;
//		}
//		break;

	case VT_DATE:
		if(val1.date < val2.date){
			nRet = -1;
		}else if(val1.date > val2.date){
			nRet = 1;
		}
		break;
	case VT_BSTR:
		{
			CString strVal1 = val1.bstrVal;
			CString strVal2 = val2.bstrVal;
			nRet = strVal1.Compare(strVal2);
		}
		break;
	default:
//		if(val1 < val2){
//			nRet = -1;
//		}else if(val1 > val2){
//			nRet = 1;
//		}
		nRet = 0;
		break;
	}
*/
	return nRet;
}

CDBListCtrl::CDBListCtrl(){
}

CDBListCtrl::~CDBListCtrl(){
	DeleleAllIsNull();
}


BEGIN_MESSAGE_MAP(CDBListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CDBListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(ID_SQL_NEW, OnSqlNew)
	ON_NOTIFY_REFLECT(LVN_INSERTITEM, OnInsertitem)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteitem)
	ON_NOTIFY_REFLECT(LVN_DELETEALLITEMS, OnDeleteallitems)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBListCtrl メッセージ ハンドラ
void CDBListCtrl::SetAllColumnWidth(){
	CHeaderCtrl *pHead = GetHeaderCtrl();
	if(!pHead){
		return;
	}
	int nMax = pHead->GetItemCount();
	for(int j = 0; j < nMax; j++){
		SetColumnWidth(j, LVSCW_AUTOSIZE);
		int nWidth1 = GetColumnWidth(j);
		SetColumnWidth(j, LVSCW_AUTOSIZE_USEHEADER );
		int nWidth2 = GetColumnWidth(j);
		if(nWidth1 > nWidth2){
			SetColumnWidth(j, LVSCW_AUTOSIZE);
		}
	}
}

void CDBListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult){
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	SortItems(CDBListCtrl::CompareFunc, NULL);

	*pResult = 0;
}

void CDBListCtrl::OnSqlNew(){
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
}

void CDBListCtrl::OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult){
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	int iItem = pNMListView->iItem;
	CArray<BOOL, BOOL> *pArr = new CArray<BOOL, BOOL>;
	CHeaderCtrl *pHead = GetHeaderCtrl();
	pArr->SetSize(pHead->GetItemCount());
	m_arrIsNull.InsertAt(iItem, pArr);
}

void CDBListCtrl::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult){
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	if(m_arrIsNull.GetSize() <= pNMListView->iItem){
		return;
	}
	CArray<BOOL, BOOL> *pArr = m_arrIsNull.GetAt(pNMListView->iItem);
	delete pArr;
	m_arrIsNull.RemoveAt(pNMListView->iItem);
}

void CDBListCtrl::OnDeleteallitems(NMHDR* pNMHDR, LRESULT* pResult){
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	
	DeleleAllIsNull();
}

void CDBListCtrl::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct ){
	if ((lpDrawItemStruct->CtlType != ODT_LISTVIEW) ||
		(lpDrawItemStruct->itemAction != ODA_DRAWENTIRE)){
		return;
	}
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	int iItem = lpDrawItemStruct->itemID;
	CHeaderCtrl *pHead = GetHeaderCtrl();
	int nColCnt = pHead->GetItemCount();
	CArray<BOOL, BOOL> *pArr = m_arrIsNull.GetAt(iItem);

	CRect rect;
	CString strItemText;
	int nStrLen;
	BOOL bFocus = FALSE;
	BOOL bSelect = FALSE;
	COLORREF crText;
	COLORREF crBack;
	
	if(GetItemState(iItem, LVIS_FOCUSED)){
		bFocus = TRUE;
	}
	
	if(GetItemState(iItem, LVIS_SELECTED)){
		bSelect = TRUE;
	}

	for(int nCnt = 0; nCnt < nColCnt; nCnt++){
		GetSubItemRect(iItem, nCnt, LVIR_LABEL, rect);
		strItemText = GetItemText(iItem, nCnt);

		if(bSelect){
			crBack = GetSysColor(COLOR_HIGHLIGHT);
			crText = GetSysColor(COLOR_HIGHLIGHTTEXT);
		}else{
			crBack = GetSysColor(COLOR_WINDOW);
			crText = GetSysColor(COLOR_WINDOWTEXT);
		}	
		if(pArr->GetAt(nCnt)){
			crText = GetSysColor(COLOR_GRAYTEXT);
		}

		pDC->FillSolidRect(rect, crBack);

		//pDC->SetBkColor(crBack);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(crText);

		rect.left   += 2;

		nStrLen = strItemText.GetLength();
		char *pszText = new char[nStrLen + 1];
		memset(pszText, 0, nStrLen + 1);
		strcpy(pszText, strItemText);
		::DrawTextEx(pDC->m_hDC, pszText, nStrLen, rect, DT_LEFT | DT_SINGLELINE, NULL);
		delete pszText;
	}
	GetItemRect(iItem, rect, LVIR_BOUNDS);
	rect.bottom--;
	rect.left += 2;
	if(bFocus){
		pDC->DrawFocusRect(rect);
	}
		
}

void CDBListCtrl::SetIsNull(int nIndex, int nCol, BOOL bIsNull){
	int nSize = m_arrIsNull.GetSize();
	if(nSize <= nIndex){
		return;
	}
	CArray<BOOL, BOOL> *pArr = m_arrIsNull.GetAt(nIndex);
	pArr->SetAt(nCol, bIsNull);

}

void CDBListCtrl::DeleleAllIsNull(){
	int nSize = m_arrIsNull.GetSize();
	CArray<BOOL, BOOL> *pArr;
	for(int i = 0; i < nSize; i++){
		pArr = m_arrIsNull.GetAt(i);
		delete pArr;
	}
	m_arrIsNull.RemoveAll();
}
