// PluginException.h: CPluginException クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLUGINEXCEPTION_H__1647C5CE_6DAF_4D12_A2EE_2E48373C9CEC__INCLUDED_)
#define AFX_PLUGINEXCEPTION_H__1647C5CE_6DAF_4D12_A2EE_2E48373C9CEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPluginException : public CException{
public:
	CPluginException(LPCTSTR pszMsg);
	virtual ~CPluginException();
	virtual BOOL GetErrorMessage( LPTSTR lpszError, UINT nMaxError, PUINT pnHelpContext = NULL );


private:
	CString m_strMsg;
};

#endif // !defined(AFX_PLUGINEXCEPTION_H__1647C5CE_6DAF_4D12_A2EE_2E48373C9CEC__INCLUDED_)
