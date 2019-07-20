#if !defined(__SDT_PLUGIN__)
#define __SDT_PLUGIN__

typedef struct tagSDTPLGINFO{
	char szName[256];
	char szVersion[32];
	char info[1024];

	BOOL bUseMenu;
	char szMenuName[128];

}SDTPLGINFO, *PSDTPLGINFO;

/**
 * @brif プラグイン情報取得
 */
typedef void (WINAPI *PGetInfoFunc)(SDTPLGINFO& objPlgInfo);

/**
 * @brif プラグイン 有効/無効設定
 */
typedef void (WINAPI *PSetEnableFunc)(HWND hWnd, BOOL bEnable);

/**
 * @brif プラグイン終了関数
 */
typedef BOOL (WINAPI *PPluginEndFunc)(HWND hWnd);

/**
 * @brif 設定呼びだし
 */
typedef BOOL (WINAPI *POnSettingFunc)(HWND hWnd);

/**
 * @brif メニュー呼びだし
 */
typedef void (WINAPI *POnMenuFunc)(HWND hWnd);

#endif