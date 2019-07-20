// stdafx.h : 標準のシステム インクルード ファイル、
//            または参照回数が多く、かつあまり変更されない
//            プロジェクト専用のインクルード ファイルを記述します。
//

#if !defined(AFX_STDAFX_H__F19C788C_1D66_4A71_B18A_AAE1C2C24881__INCLUDED_)
#define AFX_STDAFX_H__F19C788C_1D66_4A71_B18A_AAE1C2C24881__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Windows ヘッダーから殆ど使用されないスタッフを除外します。

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdisp.h>        // MFC のオートメーション クラス
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT
/*
#import "C:\Program Files\Common Files\System\ado\msadox.dll" no_namespace

//参考 http://www.alpha-net.ne.jp/users2/uk413/vc/VCT_ADO.html
#define INITGUID		// これはADOを定義するための定数(GUID)の初期化
#pragma warning(disable : 4146)		//ADOの警告抑止

#import "C:\Program Files\Common Files\System\ADO\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile")
using namespace ADOCG;	// 名前空間
*/
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STDAFX_H__F19C788C_1D66_4A71_B18A_AAE1C2C24881__INCLUDED_)
