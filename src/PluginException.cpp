// PluginException.cpp: CPluginException クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dbtool.h"
#include "PluginException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CPluginException::CPluginException(LPCTSTR pszMsg){
	m_strMsg = pszMsg;
}

CPluginException::~CPluginException(){

}

BOOL CPluginException::GetErrorMessage( LPTSTR lpszError, UINT nMaxError, PUINT pnHelpContext /*= NULL*/ ){
	if(!lpszError){
		return FALSE;
	}
	strncpy(lpszError, m_strMsg, nMaxError);
	return TRUE;
}