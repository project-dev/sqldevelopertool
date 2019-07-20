// MDBPlugin.h : MDBPLUGIN アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_MDBPLUGIN_H__ED3E0B75_0B64_48B9_B25C_E9B55A91B217__INCLUDED_)
#define AFX_MDBPLUGIN_H__ED3E0B75_0B64_48B9_B25C_E9B55A91B217__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル
#include "SDTPlugin.h"
/////////////////////////////////////////////////////////////////////////////
// CMDBPluginApp
// このクラスの動作の定義に関しては MDBPlugin.cpp ファイルを参照してください。
//

class CMDBPluginApp : public CWinApp
{
public:
	CMDBPluginApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMDBPluginApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMDBPluginApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MDBPLUGIN_H__ED3E0B75_0B64_48B9_B25C_E9B55A91B217__INCLUDED_)
