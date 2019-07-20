// DBTool.cpp : �A�v���P�[�V�����p�N���X�̋@�\��`���s���܂��B
//

#include "stdafx.h"
#include "DBTool.h"

#include "MainFrm.h"
#include "DBToolDoc.h"
#include "DBToolView.h"
#include "devlib.h"
#include "DebugSupport.h"
#include "SDTPlugin.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE CDBToolApp::m_evSQLRUN = ::CreateEvent(NULL, TRUE, FALSE, "SDT_SQL_EXECUTE_EVENT");


/////////////////////////////////////////////////////////////////////////////
// CDBToolApp

BEGIN_MESSAGE_MAP(CDBToolApp, CWinApp)
	//{{AFX_MSG_MAP(CDBToolApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_NEW_SDT, OnNewSdt)
	//}}AFX_MSG_MAP
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBToolApp �N���X�̍\�z

CDBToolApp::CDBToolApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CDBToolApp �I�u�W�F�N�g

CDBToolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDBToolApp �N���X�̏�����

BOOL CDBToolApp::InitInstance(){
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();		// ���L DLL �̒��� MFC ���g�p����ꍇ�ɂ͂������Ăяo���Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N���Ă���ꍇ�ɂ͂������Ăяo���Ă��������B
#endif
	char szPath[MAX_PATH];
	memset(szPath, 0, MAX_PATH);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	m_strBasePath = szPath;
	int nPos = m_strBasePath.ReverseFind('\\');
	m_strBasePath = m_strBasePath.Left(nPos + 1);
	m_strIniFilePath.Format("%sSDT.ini", m_strBasePath);
	m_strDBListFile.Format("%sDBList.dat", m_strBasePath);
	m_strServerListFile.Format("%sServerList.dat", m_strBasePath);
	m_strUserListFile.Format("%sUserList.dat", m_strBasePath);

	LoadIni();

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDBToolDoc),
		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
		RUNTIME_CLASS(CDBToolView));
	AddDocTemplate(pDocTemplate);

	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �R�}���h���C���Ńf�B�X�p�b�` �R�}���h���w�肵�܂��B
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	void GetDLLVersion(LPCTSTR pszFileName, CString& strInfo);
	BOOL GetRegStringData(HKEY hKey, LPCTSTR pszKey, LPCTSTR pszValueName, CString& strValue);
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CEdit	m_objSysInfo;
	CString	m_strSysInfo;
	//}}AFX_DATA

	// ClassWizard ���z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CFont m_objNewFont;

};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_strSysInfo = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_ED_SYSINFO, m_objSysInfo);
	DDX_Text(pDX, IDC_ED_SYSINFO, m_strSysInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CDBToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDBToolApp ���b�Z�[�W �n���h��

void CDBToolApp::SaveIni(){
	CString strVal;

	::WriteInifileInt("DBTool", "POS_X", m_nPosX, m_strIniFilePath);	
	::WriteInifileInt("DBTool", "POS_Y", m_nPosY, m_strIniFilePath);	
	::WriteInifileInt("DBTool", "WIDTH", m_nWidth, m_strIniFilePath);	
	::WriteInifileInt("DBTool", "HEIGHT", m_nHeight, m_strIniFilePath);	
	::WriteInifileInt("DBTool", "LEFT_WIDTH", m_nLeftPaneWidth, m_strIniFilePath);	
	::WriteInifileInt("DBTool", "RESULT_HEIGHT", m_nResultPaneHeight, m_strIniFilePath);	
	::WriteInifileInt("DBTool", "LogTabActive", m_bLogTabActive, m_strIniFilePath);	
	::WriteInifileInt("DBTool", "InclimentalSearch", m_bIncSearch, m_strIniFilePath);	
	::WriteInifileInt("DBTool", "RecordAlert", m_bRecAlert, m_strIniFilePath);	
	::WriteInifileInt("DBTool", "RecordAlertNum", m_nRecAlert, m_strIniFilePath);	

	::WriteInifileString("DBTool", "USER", m_strActiveUser, m_strIniFilePath);
	::WriteInifileString("DBTool", "PASS", m_strActivePass, m_strIniFilePath);
	::WriteInifileString("DBTool", "DB", m_strActiveDB, m_strIniFilePath);
	::WriteInifileString("DBTool", "SERVER", m_strActiveServer, m_strIniFilePath);

}

void CDBToolApp::LoadIni(){
	m_nPosX				= ::GetInifileInt("DBTool", "POS_X",  0, m_strIniFilePath);
	m_nPosY				= ::GetInifileInt("DBTool", "POS_Y",  0, m_strIniFilePath);
	m_nWidth			= ::GetInifileInt("DBTool", "WIDTH",  640, m_strIniFilePath);
	m_nHeight			= ::GetInifileInt("DBTool", "HEIGHT", 480, m_strIniFilePath);
	m_nLeftPaneWidth	= ::GetInifileInt("DBTool", "LEFT_WIDTH", 200, m_strIniFilePath);
	m_nResultPaneHeight = ::GetInifileInt("DBTool", "RESULT_HEIGHT", 280, m_strIniFilePath);
	m_bLogTabActive		= ::GetInifileInt("DBTool", "LogTabActive", 1, m_strIniFilePath);
	m_bIncSearch		= ::GetInifileInt("DBTool", "InclimentalSearch", 1, m_strIniFilePath);
	m_bRecAlert			= ::GetInifileInt("DBTool", "RecordAlert", 1, m_strIniFilePath);
	m_nRecAlert			= ::GetInifileInt("DBTool", "RecordAlertNum", 1000, m_strIniFilePath);
	
	char szValue[MAX_PATH];
	
	memset(szValue, 0, MAX_PATH);
	::GetInifileString("DBTool", "USER", "sa", szValue, MAX_PATH, m_strIniFilePath);
	m_strActiveUser = szValue;

	memset(szValue, 0, MAX_PATH);
	::GetInifileString("DBTool", "PASS", "", szValue, MAX_PATH, m_strIniFilePath);
	m_strActivePass = szValue;

	memset(szValue, 0, MAX_PATH);
	::GetInifileString("DBTool", "DB", "", szValue, MAX_PATH, m_strIniFilePath);
	m_strActiveDB = szValue;

	memset(szValue, 0, MAX_PATH);
	::GetInifileString("DBTool", "SERVER", "(local)", szValue, MAX_PATH, m_strIniFilePath);
	m_strActiveServer = szValue;
}

int CDBToolApp::ExitInstance(){
	SaveIni();
	
	return CWinApp::ExitInstance();
}

void CDBToolApp::LoadDBList(){
	
	WIN32_FIND_DATA wfd;
	HANDLE hRet = ::FindFirstFile(m_strDBListFile, &wfd);
	if(hRet == INVALID_HANDLE_VALUE){
		return;
	}
	::FindClose(hRet);
	
	CStdioFile file;
	TRY{
		file.Open(m_strDBListFile, CFile::modeRead);
		m_arrDBs.RemoveAll();
		CString strLine;
		while(file.ReadString(strLine)){
			m_arrDBs.Add(strLine);
		}
		file.Close();
	}CATCH_ALL(e){
	}END_CATCH_ALL
}

void CDBToolApp::LoadServerList(){
	
	WIN32_FIND_DATA wfd;
	HANDLE hRet = ::FindFirstFile(m_strServerListFile, &wfd);
	if(hRet == INVALID_HANDLE_VALUE){
		return;
	}
	::FindClose(hRet);
	
	CStdioFile file;
	TRY{
		file.Open(m_strServerListFile, CFile::modeRead);
		m_arrServers.RemoveAll();
		CString strLine;
		while(file.ReadString(strLine)){
			m_arrServers.Add(strLine);
		}
		file.Close();
	}CATCH_ALL(e){
	}END_CATCH_ALL
}

void CDBToolApp::LoadUserList(){
	
	WIN32_FIND_DATA wfd;
	HANDLE hRet = ::FindFirstFile(m_strUserListFile, &wfd);
	if(hRet == INVALID_HANDLE_VALUE){
		return;
	}
	::FindClose(hRet);
	
	CStdioFile file;
	TRY{
		file.Open(m_strUserListFile, CFile::modeRead);
		m_arrUsers.RemoveAll();
		CString strLine;
		while(file.ReadString(strLine)){
			m_arrUsers.Add(strLine);
		}
		file.Close();
	}CATCH_ALL(e){
	}END_CATCH_ALL
}

void CDBToolApp::SaveDBList(){
	CStdioFile file;
	TRY{
		file.Open(m_strDBListFile, CFile::modeCreate | CFile::modeWrite);
		int nMax = m_arrDBs.GetSize();
		CString strLine;
		CString strDBName;
		for(int i = 0; i < nMax; i++){
			strDBName = m_arrDBs.GetAt(i);
			strDBName.TrimLeft();
			strDBName.TrimRight();
			if(!strDBName.IsEmpty()){
				strLine.Format("%s\n", m_arrDBs.GetAt(i));
				file.WriteString(strLine);
			}
		}
		file.Flush();
		file.Close();
	}CATCH_ALL(e){
	}END_CATCH_ALL

}

void CDBToolApp::SaveServerList(){
	CStdioFile file;
	TRY{
		file.Open(m_strServerListFile, CFile::modeCreate | CFile::modeWrite);
		int nMax = m_arrServers.GetSize();
		CString strLine;
		CString strServerName;
		for(int i = 0; i < nMax; i++){
			strServerName = m_arrServers.GetAt(i);
			strServerName.TrimLeft();
			strServerName.TrimRight();
			if(!strServerName.IsEmpty()){
				strLine.Format("%s\n", m_arrServers.GetAt(i));
				file.WriteString(strLine);
			}
		}
		file.Flush();
		file.Close();
	}CATCH_ALL(e){
	}END_CATCH_ALL

}

void CDBToolApp::SaveUserList(){
	CStdioFile file;
	TRY{
		file.Open(m_strUserListFile, CFile::modeCreate | CFile::modeWrite);
		int nMax = m_arrUsers.GetSize();
		CString strLine;
		CString strUserName;
		for(int i = 0; i < nMax; i++){
			strUserName = m_arrUsers.GetAt(i);
			strUserName.TrimLeft();
			strUserName.TrimRight();
			if(!strUserName.IsEmpty()){
				strLine.Format("%s\n", m_arrUsers.GetAt(i));
				file.WriteString(strLine);
			}
		}
		file.Flush();
		file.Close();
	}CATCH_ALL(e){
	}END_CATCH_ALL

}

void CDBToolApp::OnNewSdt(){
	char szFileName[MAX_PATH];
	memset(szFileName, 0, MAX_PATH);
	::GetModuleFileName(NULL, szFileName, MAX_PATH);
	::ShellExecute(NULL, "open", szFileName, NULL, NULL, SW_SHOWNORMAL);	
}

BOOL CDBToolApp::ProcessShellCommand( CCommandLineInfo& rCmdInfo ){
	__try{
		return CWinApp::ProcessShellCommand(rCmdInfo);
	}__except(CDebugSupport::Except(GetExceptionInformation())){
		return FALSE;
	}
}

int CDBToolApp::Run() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	__try{
		return CWinApp::Run();
	}__except(CDebugSupport::Except(GetExceptionInformation())){
		return 1;
	}	
	return CWinApp::Run();
}

BOOL CAboutDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	LOGFONT lFont;
	memset(&lFont, 0,sizeof(LOGFONT));
	CFont* pFont = m_objSysInfo.GetFont();

//	pFont->GetLogFont(&lFont);
	strcpy(lFont.lfFaceName, "�l�r �S�V�b�N");1
	m_objNewFont.CreateFontIndirect(&lFont);
	m_objSysInfo.SetFont(&m_objNewFont, true);
	

	m_strSysInfo = "";
	
	//�e��o�[�W�����̒���
	//��Windows
	m_strSysInfo += "[Windows]\r\n";

	OSVERSIONINFO verInfo;
	memset(&verInfo, 0, sizeof(OSVERSIONINFO));
	verInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	::GetVersionEx(&verInfo);
	
	CString strOsVer = "";
	CString strOsName = "";
	if(verInfo.dwPlatformId == 1){
		if(verInfo.dwMajorVersion == 4){
			switch(verInfo.dwMinorVersion){
			case 0:
				//Windows 95
				strOsName = "Windows 95";
				break;
			case 10:
				//Windows 98
				strOsName = "Windows 98";
				break;
			case 90:
				//Windows Me
				strOsName = "Windows Me";
				break;
			}
		}else{
		}
	}else if(verInfo.dwPlatformId == 2){
		if(verInfo.dwMajorVersion == 4){
			strOsName = "Windows NT 4.0";
		}else if(verInfo.dwMajorVersion == 5){
			switch(verInfo.dwMinorVersion){
			case 0:
				//Windows 2000
				strOsName = "Windows 2000";
				break;
			case 1:
				//Windows Xp
				strOsName = "Windows 98";
				break;
			case 2:
				//Windows Xp x64 or Windows Server 2003 or Windows Server 2003 R2
				strOsName = "Windows Me";
				break;
			}
		}else if(verInfo.dwMajorVersion == 6){
			switch(verInfo.dwMinorVersion){
			case 0:
				strOsName = "Windows Vista";
				break;
			}
		}
	}
		
	strOsVer.Format("  %s %d.%02d.%d %s\r\n", strOsName, verInfo.dwMajorVersion, verInfo.dwMinorVersion, verInfo.dwBuildNumber, verInfo.szCSDVersion);
	m_strSysInfo += strOsVer;

	CString strDllPath;
	CString strInfo;
	char szSysDir[MAX_PATH];
	char szWinDir[MAX_PATH];
	char szPrgDir[MAX_PATH];
	memset(szWinDir, 0, MAX_PATH);
	memset(szSysDir, 0, MAX_PATH);
	memset(szPrgDir, 0, MAX_PATH);
	::GetEnvironmentVariable("ProgramFiles",szPrgDir ,MAX_PATH);
	::GetWindowsDirectory(szWinDir, MAX_PATH);
	::GetSystemDirectory(szSysDir, MAX_PATH);

	//��Microsoft JET
	//Msjet40.dll 
	//Msjet351.dll 
	m_strSysInfo += "[Microsoft JET 3.51]\r\n";

	strDllPath.Format("%s\\Msjet351.dll", szWinDir);
	GetDLLVersion(strDllPath, strInfo);
	m_strSysInfo += strInfo;
	
	strDllPath.Format("%s\\Msjet351.dll", szSysDir);
	GetDLLVersion(strDllPath, strInfo);
	m_strSysInfo += strInfo;

	m_strSysInfo += "[Microsoft JET 4.0]\r\n";
	strDllPath.Format("%s\\Msjet40.dll", szWinDir);
	GetDLLVersion(strDllPath, strInfo);
	m_strSysInfo += strInfo;
	
	strDllPath.Format("%s\\Msjet40.dll", szSysDir);
	GetDLLVersion(strDllPath, strInfo);
	m_strSysInfo += strInfo;

	//JRO
	//C:\PROGRAM FILES\COMMON FILES\System\ado\MSJRO.DLL
	//SHGetFolderPath �ŁACSIDL_PROGRAM_FILES 
	//ExpandEnvironmentStrings
	m_strSysInfo += "[Microsoft JET]\r\n";
	strDllPath.Format("%s\\COMMON FILES\\System\\ado\\MSJRO.dll", szPrgDir);
	GetDLLVersion(strDllPath, strInfo);
	m_strSysInfo += strInfo;

	//��MDAC
	//HKEY_LOCAL_MACHINE\Software\Microsoft\DataAccess
	//FullInstallVer
	//Version 
	m_strSysInfo += "[MDAC]\r\n";
	CString strFullInsVer = "";
	CString strVersion    = "";
	if(!GetRegStringData(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\DataAccess", "FullInstallVer", strFullInsVer)){
		strFullInsVer = "unknow";
	}
	if(!GetRegStringData(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\DataAccess", "Version", strVersion)){
		strVersion = "unknow";
	}
	strInfo.Format("  FullInstallVer : %s\r\n"
				   "  Version        : %s\r\n"
				   ,strFullInsVer
				   ,strVersion);
	m_strSysInfo += strInfo;
	UpdateData(FALSE);


	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

BOOL CAboutDlg::GetRegStringData(HKEY hKey, LPCTSTR pszKey, LPCTSTR pszValueName, CString& strValue){
	HKEY key = NULL;
	BOOL bRet = FALSE;
	LONG lRet = ::RegOpenKeyEx(hKey, pszKey, NULL, KEY_READ, &key);
	DWORD dwType;
	if(lRet == ERROR_SUCCESS){
		DWORD dwSize = 0;
		lRet = ::RegQueryValueEx(key, "FullInstallVer", NULL, &dwType, NULL, &dwSize);
		if(lRet == ERROR_SUCCESS){
			BYTE* buff = new BYTE[dwSize];
			memset(buff, 0, dwSize);
			lRet = ::RegQueryValueEx(key, "FullInstallVer", NULL, &dwType, buff, &dwSize);
			if(lRet == ERROR_SUCCESS){
				strValue = buff;
				bRet = TRUE;
			}
			delete[] buff;
		}
		::RegCloseKey(key);
	}
	return bRet;
}

typedef struct tagLANGANDCODEPAGE {
	WORD wLanguage;
	WORD wCodePage;
} LANGANDCODEPAGE, *LPLANGANDCODEPAGE;

void CAboutDlg::GetDLLVersion(LPCTSTR pszFileName, CString &strInfo){
	DWORD dwSize = 0;
	DWORD dwHandle = 0;
	HMODULE hMod = NULL;
	BOOL bRet;
	strInfo.Empty();
	if(!::IsFileExsist(pszFileName)){
		//strInfo.Format(" %s is not exist\r\n", pszFileName);
		return;
	}

	strInfo.Format("  %s\r\n"
                   "  FileVersion    : -\r\n"
				   "  ProductVersion : -\r\n"
				   "  PrivateBuild   : -\r\n"
				   "  SpecialBuild   : -\r\n", pszFileName);
	
	//TRACE("%s\n", pszFileName);
	hMod = ::GetModuleHandle(pszFileName);
	if(!hMod){
		return;
	}
	dwSize = ::GetFileVersionInfoSize((char*)pszFileName, &dwHandle);
	if(!dwSize){
		return;
	}
	char *pszInfo = new char[dwSize + 1];
	if(!pszInfo){
		return;
	}
		
	bRet = ::GetFileVersionInfo((char*)pszFileName, 0, dwSize, pszInfo);
	if(!bRet){
		delete pszInfo;
		return;
	}

	LPLANGANDCODEPAGE lplgcode;
	//DWORD *dwLang;
	UINT uLen;
	bRet = ::VerQueryValue(pszInfo, "\\VarFileInfo\\Translation", (LPVOID*)&lplgcode, &uLen);
	if(!bRet){
		delete pszInfo;
		return;
	}

	CString strLang;
//	strLang.Format("%04x%04x", LOWORD(*dwLang), HIWORD(*dwLang));
	int nLangIdx = 0;
	for(int i = 0; i < uLen / sizeof(LANGANDCODEPAGE); i++){
		if(lplgcode[i].wLanguage = 0x0411){
			nLangIdx = i;
			break;
		}
	}
	strLang.Format("%04x%04x", lplgcode[nLangIdx].wLanguage, lplgcode[nLangIdx].wCodePage);
	
	char *pszFileVer;
	char *pszProdVer;
	char *pszPrivVer;
	char *pszSpecVer;
	UINT uFileLen;
	UINT uProdLen;
	UINT uPrivLen;
	UINT uSpecLen;

	char szSubBlock[MAX_PATH];
	sprintf(szSubBlock, "\\StringFileInfo\\%s\\FileVersion", strLang);
	bRet = ::VerQueryValue(pszInfo, szSubBlock, (void**)&pszFileVer, &uFileLen);
	if(!bRet){
		pszFileVer = NULL;
	}

	sprintf(szSubBlock, "\\StringFileInfo\\%s\\ProductVersion", strLang);
	bRet = ::VerQueryValue(pszInfo, szSubBlock, (void**)&pszProdVer, &uProdLen);
	if(!bRet){
		pszProdVer = NULL;
	}

	sprintf(szSubBlock, "\\StringFileInfo\\%s\\PrivateBuild", strLang);
	bRet = ::VerQueryValue(pszInfo, szSubBlock, (void**)&pszPrivVer, &uPrivLen);
	if(!bRet){
		pszPrivVer = NULL;
	}

	sprintf(szSubBlock, "\\StringFileInfo\\%s\\SpecialBuild", strLang);
	bRet = ::VerQueryValue(pszInfo, szSubBlock, (void**)&pszSpecVer, &uSpecLen);
	if(!bRet){
		pszSpecVer = NULL;
	}

	strInfo.Format("��%s\r\n"
                   "  FileVersion    : %s\r\n"
				   "  ProductVersion : %s\r\n"
				   "  PrivateBuild   : %s\r\n"
				   "  SpecialBuild   : %s\r\n"
				   ,pszFileName ? pszFileName : "-"
				   ,pszFileVer  ? pszFileVer : "-"
				   ,pszProdVer  ? pszProdVer : "-"
				   ,pszPrivVer  ? pszPrivVer : "-"
				   ,pszSpecVer  ? pszSpecVer : "-");
	delete[] pszInfo;

}
