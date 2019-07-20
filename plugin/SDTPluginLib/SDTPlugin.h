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
 * @brif �v���O�C�����擾
 */
typedef void (WINAPI *PGetInfoFunc)(SDTPLGINFO& objPlgInfo);

/**
 * @brif �v���O�C�� �L��/�����ݒ�
 */
typedef void (WINAPI *PSetEnableFunc)(HWND hWnd, BOOL bEnable);

/**
 * @brif �v���O�C���I���֐�
 */
typedef BOOL (WINAPI *PPluginEndFunc)(HWND hWnd);

/**
 * @brif �ݒ�Ăт���
 */
typedef BOOL (WINAPI *POnSettingFunc)(HWND hWnd);

/**
 * @brif ���j���[�Ăт���
 */
typedef void (WINAPI *POnMenuFunc)(HWND hWnd);

#endif