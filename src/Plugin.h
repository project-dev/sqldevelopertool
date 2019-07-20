// Plugin.h: CPlugin クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLUGIN_H__F536EAEF_75A4_46BD_B27C_AD29B6CBE932__INCLUDED_)
#define AFX_PLUGIN_H__F536EAEF_75A4_46BD_B27C_AD29B6CBE932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SDTPlugin.h"
#include "PluginException.h"

class CPlugin{
public:
	BOOL ReleasePlugin();
	BOOL LoadPlugin(LPCTSTR pszPluginPath);
	CPlugin(HWND hWnd);
	virtual ~CPlugin();

	LPCTSTR GetPluginName();
	LPCTSTR GetMenuName();
	LPCTSTR GetPluginInfo();

	void GetInfo() throw(CPluginException);
	void SetEnable(BOOL bEbable) throw(CPluginException);
	BOOL PluginEnd() throw(CPluginException);
	BOOL OnSetting() throw(CPluginException);
	void OnMenu() throw(CPluginException);

private:

	void InitFuncPointer();
	PGetInfoFunc   pGetInfo;
	PSetEnableFunc pSetEnable;
	PPluginEndFunc pPluginEnd;
	POnSettingFunc pOnSetting;
	POnMenuFunc    pOnMenu;

	SDTPLGINFO m_objInfo;

	HWND m_hWnd;
	CString m_strName;
	CString m_strMenuName;
	CString m_strInfo;
};

#endif // !defined(AFX_PLUGIN_H__F536EAEF_75A4_46BD_B27C_AD29B6CBE932__INCLUDED_)
