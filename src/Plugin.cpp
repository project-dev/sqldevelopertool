// Plugin.cpp: CPlugin クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dbtool.h"
#include "Plugin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CPlugin::CPlugin(HWND hWnd){
	InitFuncPointer();
	m_hWnd = hWnd;
}

CPlugin::~CPlugin(){
	InitFuncPointer();

}

void CPlugin::InitFuncPointer(){
	pGetInfo   = NULL;
	pSetEnable = NULL;
	pPluginEnd = NULL;
	pOnSetting = NULL;
	pOnMenu    = NULL;
}

BOOL CPlugin::LoadPlugin(LPCTSTR pszPluginPath){
	InitFuncPointer();
	return TRUE;
}

BOOL CPlugin::ReleasePlugin(){
	return TRUE;
}

LPCTSTR CPlugin::GetPluginName(){
	return m_strName;
}

LPCTSTR CPlugin::GetMenuName(){
	return m_strMenuName;
}

LPCTSTR CPlugin::GetPluginInfo(){
	return m_strInfo;
}

void CPlugin::GetInfo() throw(CPluginException){
	if(!pGetInfo){
		throw new CPluginException("GetInfo関数が実装されていません。");
	}
	memset(&m_objInfo, 0, sizeof(SDTPLGINFO));
	pGetInfo(m_objInfo);
}
void CPlugin::SetEnable(BOOL bEnable) throw(CPluginException){
	if(!pSetEnable){
		throw new CPluginException("SetEnable関数が実装されていません。");
	}
	pSetEnable(m_hWnd, bEnable);
}

BOOL CPlugin::PluginEnd() throw(CPluginException){
	if(!pPluginEnd){
		throw new CPluginException("PluginEnd関数が実装されていません。");
	}
	return pPluginEnd(m_hWnd);
}

BOOL CPlugin::OnSetting() throw(CPluginException){
	if(!pOnSetting){
		throw new CPluginException("OnSetting関数が実装されていません。");
	}
	return pOnSetting(m_hWnd);
}

void CPlugin::OnMenu() throw(CPluginException){
	if(!pOnMenu){
		throw new CPluginException("OnMenu関数が実装されていません。");
	}
	pOnMenu(m_hWnd);
}
