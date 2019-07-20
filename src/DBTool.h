// DBTool.h : DBTOOL �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#if !defined(AFX_DBTOOL_H__597A8D18_B479_440A_A4C7_3D33DD4920C0__INCLUDED_)
#define AFX_DBTOOL_H__597A8D18_B479_440A_A4C7_3D33DD4920C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

#define DB_OPEN			0x00000001
#define DB_CLOSE		0x00000002
#define DB_RESULT		0x00000003	
#define DB_ADDMSG		0x00000004
#define DB_PROP_CLEAR	0x00000005
#define DB_TABLE_PROP	0x00000006
#define DB_SQLNEW		0x00000007
#define DB_SQLOPEN		0x00000008
#define DB_REFRESH		0x00000009
#define DB_REFRESH_TREE 0x0000000A
#define DB_OPENSQL		0x0000000B
#define DB_GETFUNC		0x0000000C

#define DB_CLOSEWND		0xFFFFFFFF

typedef struct tagThreadInfo{
	LPVOID	pWnd;			//�X���b�h�̌Ăяo�����N���X�̃|�C���^
	LPVOID	pDoc;			//�h�L�������g�N���X
	LPVOID	pFrm;			//�t���[���N���X
	LPTSTR	pszSQL;			//�Q�Ƃ���SQL�ւ̃|�C���^
	LPVOID	pReserved;		//���܂��|�C���^

}THREADINFO, *PTHREADINFO;

/////////////////////////////////////////////////////////////////////////////
// CDBToolApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� DBTool.cpp �t�@�C�����Q�Ƃ��Ă��������B
//
class CDBToolApp : public CWinApp{
public:
	CString m_strUserListFile;
	void SaveUserList();
	void LoadUserList();

	CString m_strServerListFile;
	void SaveServerList();
	void LoadServerList();
	
	CString m_strDBListFile;
	void SaveDBList();
	void LoadDBList();
	
	int m_nResultPaneHeight;
	int m_nLeftPaneWidth;
	CStringArray m_arrDBs;
	CStringArray m_arrPaswords;
	CStringArray m_arrUsers;
	CStringArray m_arrServers;
	CStringArray m_arrODBCs;
	CString m_strActiveDB;
	CString m_strActivePass;
	CString m_strActiveUser;
	CString m_strActiveServer;
	BOOL m_bLogTabActive;
	BOOL m_bIncSearch;
	BOOL m_bRecAlert;
	int m_nRecAlert;
	int m_nHeight;
	int m_nWidth;
	int m_nPosY;
	int m_nPosX;
	CString m_strIniFilePath;
	CString m_strBasePath;
	void LoadIni();
	void SaveIni();
	static HANDLE m_evSQLRUN;
	
	CDBToolApp();
	BOOL ProcessShellCommand( CCommandLineInfo& rCmdInfo );

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDBToolApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	//{{AFX_MSG(CDBToolApp)
	afx_msg void OnAppAbout();
	afx_msg void OnNewSdt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DBTOOL_H__597A8D18_B479_440A_A4C7_3D33DD4920C0__INCLUDED_)
