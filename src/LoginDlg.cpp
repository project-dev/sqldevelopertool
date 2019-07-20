// LoginDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "DBTool.h"
#include "LoginDlg.h"
#include "devlib.h"
#include "LoginSetNameInpDlg.h"
#include "FileDialogEx.h"
#include "AdoDatabase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg �_�C�A���O


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strPassword = pApp->m_strActivePass;
	m_strServer =  pApp->m_strActiveServer;
	m_strUser = pApp->m_strActiveUser;
	m_strDBName =  pApp->m_strActiveDB;
	m_bAftDBSel = FALSE;
	m_nDBType = -1;
	m_strLoginSetName = _T("");
	m_strOdbcType = _T("");
	m_strInfo = _T("");
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Control(pDX, IDC_BTN_REF, m_objBtnRef);
	DDX_Control(pDX, IDC_DB_ODBCCMB, m_objDbOdbcCmb);
	DDX_Control(pDX, IDC_LOGINSET_LIST, m_objLoginSetList);
	DDX_Control(pDX, IDC_USER, m_objUser);
	DDX_Control(pDX, IDC_SERVER, m_objServer);
	DDX_Control(pDX, IDC_AFTERDBSEL, m_objAftDBSelBtn);
	DDX_Control(pDX, IDC_DTTYPE_CMB, m_objDBType);
	DDX_Control(pDX, IDC_DB_CMB, m_objDbNameCmb);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_SERVER, m_strServer);
	DDX_Text(pDX, IDC_USER, m_strUser);
	DDX_CBString(pDX, IDC_DB_CMB, m_strDBName);
	DDX_Check(pDX, IDC_AFTERDBSEL, m_bAftDBSel);
	DDX_CBIndex(pDX, IDC_DTTYPE_CMB, m_nDBType);
	DDX_LBString(pDX, IDC_LOGINSET_LIST, m_strLoginSetName);
	DDX_CBString(pDX, IDC_DB_ODBCCMB, m_strOdbcType);
	DDX_Text(pDX, IDC_ED_INFO, m_strInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_BN_CLICKED(IDC_AFTERDBSEL, OnAfterdbsel)
	ON_CBN_SELCHANGE(IDC_DTTYPE_CMB, OnSelchangeDttypeCmb)
	ON_LBN_SELCHANGE(IDC_LOGINSET_LIST, OnSelchangeLoginsetList)
	ON_BN_CLICKED(IDC_DEL_SET, OnDelSet)
	ON_BN_DOUBLECLICKED(IDC_DEL_SET, OnDoubleclickedDelSet)
	ON_BN_CLICKED(IDC_NEW_SET, OnNewSet)
	ON_BN_DOUBLECLICKED(IDC_NEW_SET, OnDoubleclickedNewSet)
	ON_BN_CLICKED(IDC_MODIFY_SET, OnModifySet)
	ON_BN_DOUBLECLICKED(IDC_MODIFY_SET, OnDoubleclickedModifySet)
	ON_BN_CLICKED(IDC_BTN_REF, OnBtnRef)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg ���b�Z�[�W �n���h��

void CLoginDlg::OnAfterdbsel(){
	UpdateData();
	m_objDbNameCmb.EnableWindow(!m_bAftDBSel);	
}

BOOL CLoginDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	m_objDBType.SetCurSel(0);	
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	pApp->LoadDBList();
	pApp->LoadServerList();
	pApp->LoadUserList();
	pApp->m_arrODBCs.Add("Microsoft");
	pApp->m_arrODBCs.Add("DB2");
	pApp->m_arrODBCs.Add("Oracle");
	pApp->m_arrODBCs.Add("PostgreSQL");

#if defined(NEW_DBTYPE)
	m_objDBType.ResetContent();
	//eDBType�Ɠ������Ԃɂ���
	m_objDBType.AddString("ODBC�f�[�^�\�[�X");
	m_objDBType.AddString("SQLServer");
	m_objDBType.AddString("SQLServer/MSDE OLE DB �v���o�C�_");
	m_objDBType.AddString("SQLServer/MSDE ODBC �v���o�C�_");
	m_objDBType.AddString("MDB(Access) OLE DB �v���o�C�_");
	m_objDBType.AddString("MDB(Access) ODBC �v���o�C�_");
	m_objDBType.AddString("Oracle OLE DB �v���o�C�_");
//	m_objDBType.AddString("Oracle ODBC �v���o�C�_");
	m_objDBType.AddString("Oracle MS��OLE DB �v���o�C�_");
	m_objDBType.AddString("Oracle MS��ODBC �v���o�C�_");
	m_objDBType.AddString("DB2 OLE DB �v���o�C�_");
	m_objDBType.SetCurSel(0);
#endif
	int nMax = pApp->m_arrDBs.GetSize();
	for(int i = 0; i < nMax; i++){
		m_objDbNameCmb.AddString(pApp->m_arrDBs.GetAt(i));
	}

	nMax = pApp->m_arrServers.GetSize();
	for(int j = 0; j < nMax; j++){
		m_objServer.AddString(pApp->m_arrServers.GetAt(j));
	}
	
	nMax = pApp->m_arrUsers.GetSize();
	for(int k = 0; k < nMax; k++){
		m_objUser.AddString(pApp->m_arrUsers.GetAt(k));
	}
	
	if(!m_strServer.IsEmpty()){
		if(m_objServer.FindStringExact(0, m_strServer) == CB_ERR){
			m_objServer.AddString(m_strServer);
		}
		int nIndex = m_objServer.FindStringExact(0, m_strServer) ;
		m_objServer.SetCurSel(nIndex);
	}

	if(!m_strDBName.IsEmpty()){
		if(m_objDbNameCmb.FindStringExact(0, m_strDBName) == CB_ERR){
			m_objDbNameCmb.AddString(m_strDBName);
		}
		int nIndex = m_objDbNameCmb.FindStringExact(0, m_strDBName) ;
		m_objDbNameCmb.SetCurSel(nIndex);
	}

	if(!m_strUser.IsEmpty()){
		if(m_objUser.FindStringExact(0, m_strUser) == CB_ERR){
			m_objUser.AddString(m_strUser);
		}
		int nIndex = m_objUser.FindStringExact(0, m_strUser) ;
		m_objUser.SetCurSel(nIndex);
	}

	m_objDbOdbcCmb.AddString("Microsoft");
	m_objDbOdbcCmb.AddString("DB2");
	m_objDbOdbcCmb.AddString("Oracle");

	//���O�C���ݒ�̌���
	CString strSetPath;
	strSetPath.Format("%s\\*.lsd",pApp->m_strBasePath);

	EnumFiles(LoginSetEnum, strSetPath, (LPARAM)this);

	GotoDlgCtrl(&m_objLoginSetList);
	m_objLoginSetList.SetCurSel(0);
	OnSelchangeLoginsetList();
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

bool CALLBACK CLoginDlg::LoginSetEnum(const char* pszFile, WIN32_FIND_DATA* pwfd, LPARAM lParam){
	CString strFile = pwfd->cFileName;
	strFile.Replace(".lsd", "");
	CLoginDlg *pDlg = (CLoginDlg*)lParam;
	//pDlg->m_objLoginSetCmb.AddString(strFile);
	pDlg->m_objLoginSetList.AddString(strFile);
		
	return TRUE;
}

void CLoginDlg::OnOK(){
	UpdateData();
	if(!CheckSafeValue()){
		AfxMessageBox("�ݒ肳��Ă��Ȃ����ڂ�����܂�");
		return;
	}
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	if(m_objDbNameCmb.FindStringExact(0, m_strDBName) == CB_ERR){
		if(!m_strDBName.IsEmpty()){
			pApp->m_arrDBs.Add(m_strDBName);
			pApp->SaveDBList();
		}
	}
	
	if(m_objServer.FindStringExact(0, m_strServer) == CB_ERR){
		if(!m_strDBName.IsEmpty()){
			pApp->m_arrServers.Add(m_strServer);
			pApp->SaveServerList();
		}
	}
	
	if(m_objUser.FindStringExact(0, m_strUser) == CB_ERR){
		if(!m_strUser.IsEmpty()){
			pApp->m_arrUsers.Add(m_strUser);
			pApp->SaveUserList();
		}
	}

	CString strDBType;
	int nIndex = m_objDBType.GetCurSel();
	m_objDBType.GetLBText(nIndex, strDBType);
	BOOL bSave = FALSE;
//	if(m_objLoginSetCmb.FindStringExact(0, m_strLoginSetName) == CB_ERR){
	if(m_objLoginSetList.FindStringExact(0, m_strLoginSetName) == LB_ERR){
		bSave = TRUE;
	}else{
		if(CheckUpdate(m_strSelSet)){
			bSave = TRUE;		
		}
	}
	if(bSave){
		CString strMsg;
		strMsg.Format("�ݒ肪�ύX����Ă��܂��B�ۑ����܂����H\n���O�C���ݒ薼 : %s", m_strLoginSetName);
		DWORD dwRet = AfxMessageBox(strMsg, MB_YESNO);
		if(dwRet == IDYES){
			if(m_strLoginSetName.IsEmpty()){
				//
				AfxMessageBox("���O�C���ݒ薼���w�肳��Ă��܂���B\n���O�C���ݒ薼���w�肵�Ă��������B");
				return;
			}

			SaveConnectInfo(m_strLoginSetName);
		}
	}

	CDialog::OnOK();
}


void CLoginDlg::OnSelchangeDttypeCmb(){
	UpdateData();
	int nIndex = m_objDBType.GetCurSel();	
#if defined(NEW_DBTYPE)
	switch(nIndex){
	//SQLServer/MSDE
	case SQLSERVER_AUTO:	
		m_objDbNameCmb.EnableWindow(!m_bAftDBSel);
		m_objServer.EnableWindow(TRUE);
		m_objAftDBSelBtn.EnableWindow(TRUE);
		m_objDbOdbcCmb.EnableWindow(FALSE);
		m_objBtnRef.EnableWindow(FALSE);
		m_strInfo = "NT�F�؂̏ꍇ�A���[�U�[��/�p�X���[�h����ɂ��Ă��������B\r\n"
					"SQLServer�F�؂̏ꍇ�́A�C�ӂ̃��[�U�[��/�p�X���[�h�ɂ��ĉ������B\r\n"
					"��SQLServer/MSDE�Őݒ肵���F�ؕ��@�Ń��O�C�����Ă�������";
		break;
	case SQLSERVER_OLEDB:	
		m_objDbNameCmb.EnableWindow(TRUE);
		m_objServer.EnableWindow(TRUE);
		m_objAftDBSelBtn.EnableWindow(FALSE);
		m_objDbOdbcCmb.EnableWindow(FALSE);
		m_objBtnRef.EnableWindow(FALSE);
		m_strInfo = "�܂����������Ă��Ȃ��@�\�ł�";
		break;
	case SQLSERVER_ODBC:	
		m_objDbNameCmb.EnableWindow(TRUE);
		m_objServer.EnableWindow(TRUE);
		m_objAftDBSelBtn.EnableWindow(FALSE);
		m_objDbOdbcCmb.EnableWindow(FALSE);
		m_objBtnRef.EnableWindow(FALSE);
		m_strInfo = "�܂����������Ă��Ȃ��@�\�ł��BMDAC���K�v(���Ǝv���܂�)";
		break;
	//ODBC
	case ODBC_DATASRC:	
		m_objServer.EnableWindow(TRUE);
		m_objAftDBSelBtn.EnableWindow(FALSE);
		m_objDbNameCmb.EnableWindow(TRUE);
		m_objDbOdbcCmb.EnableWindow(TRUE);
		m_objBtnRef.EnableWindow(FALSE);
		m_strInfo = "ODBC�ڑ��́A�\�����؂��Ă��܂���B\r\n"
					"�ꕔ�̋@�\�����p�ł��܂���B�B\r\n";
		break;
	//ACCESS
	case ACCESS_OLEDB: 
		m_objServer.EnableWindow(FALSE);
		m_objAftDBSelBtn.EnableWindow(FALSE);
		m_objDbNameCmb.EnableWindow(TRUE);
		m_objDbOdbcCmb.EnableWindow(FALSE);
		m_objBtnRef.EnableWindow(TRUE);
		m_strInfo = "DB/�f�[�^�\�[�X�Ƀt�@�C����(MDB)��ݒ肵�Ă��������B\r\n"
					"�ꕔ�̋@�\�����p�ł��܂���B";
		break;
	case ACCESS_ODBC: 
		m_objServer.EnableWindow(FALSE);
		m_objAftDBSelBtn.EnableWindow(FALSE);
		m_objDbNameCmb.EnableWindow(TRUE);
		m_objDbOdbcCmb.EnableWindow(FALSE);
		m_objBtnRef.EnableWindow(TRUE);
		m_strInfo = "DB/�f�[�^�\�[�X�Ƀt�@�C����(MDB)��ݒ肵�Ă��������B\r\n"
					"�ꕔ�̋@�\�����p�ł��܂���BMDAC���K�v(���Ǝv���܂�)";
		break;
	//ORACLE
	case ORACLE_OLEDB: 
	//case ORACLE_ODBC: 
	case ORACLE_MS_OLEDB: 
		m_objServer.EnableWindow(TRUE);
		m_objAftDBSelBtn.EnableWindow(FALSE);
		m_objDbNameCmb.EnableWindow(TRUE);
		m_objDbOdbcCmb.EnableWindow(FALSE);
		m_objBtnRef.EnableWindow(TRUE);
		m_strInfo = "�܂����������Ă��Ȃ��@�\�ł�";
		break;
	case ORACLE_MS_ODBC: 
		m_objServer.EnableWindow(TRUE);
		m_objAftDBSelBtn.EnableWindow(FALSE);
		m_objDbNameCmb.EnableWindow(TRUE);
		m_objDbOdbcCmb.EnableWindow(FALSE);
		m_objBtnRef.EnableWindow(TRUE);
		m_strInfo = "�܂����������Ă��Ȃ��@�\�ł��BMDAC���K�v(���Ǝv���܂�)";
		break;
	case DB2_OLEDB: 
		m_objServer.EnableWindow(FALSE);
		m_objAftDBSelBtn.EnableWindow(FALSE);
		m_objDbNameCmb.EnableWindow(TRUE);
		m_objDbOdbcCmb.EnableWindow(FALSE);
		m_objBtnRef.EnableWindow(TRUE);
		m_strInfo = "�܂����������Ă��Ȃ��@�\�ł��B";
		break;
	default:
		m_objBtnRef.EnableWindow(FALSE);
		m_strInfo = "";
		break;

	}
#else
	switch(nIndex){
	case 0:	//SQLServer/MSDE
		m_objDbNameCmb.EnableWindow(!m_bAftDBSel);
		m_objServer.EnableWindow(TRUE);
		m_objAftDBSelBtn.EnableWindow(TRUE);
		m_objDbOdbcCmb.EnableWindow(FALSE);
		m_objBtnRef.EnableWindow(FALSE);
		m_strInfo = "NT�F�؂̏ꍇ�A���[�U�[��/�p�X���[�h����ɂ��Ă��������B\r\n"
					"SQLServer�F�؂̏ꍇ�́A�C�ӂ̃��[�U�[��/�p�X���[�h�ɂ��ĉ������B\r\n"
					"��SQLServer/MSDE�Őݒ肵���F�ؕ��@�Ń��O�C�����Ă�������";
		break;
	case 1:	//ODBC
		m_objServer.EnableWindow(TRUE);
		m_objAftDBSelBtn.EnableWindow(FALSE);
		m_objDbNameCmb.EnableWindow(TRUE);
		m_objDbOdbcCmb.EnableWindow(TRUE);
		m_objBtnRef.EnableWindow(FALSE);
		m_strInfo = "ODBC�ڑ��́A�\�����؂��Ă��܂���B\r\n"
					"�ꕔ�̋@�\�����p�ł��܂���B�B\r\n";
		break;
	case 2: //ACCESS
		m_objServer.EnableWindow(FALSE);
		m_objAftDBSelBtn.EnableWindow(FALSE);
		m_objDbNameCmb.EnableWindow(TRUE);
		m_objDbOdbcCmb.EnableWindow(FALSE);
		m_objBtnRef.EnableWindow(TRUE);
		m_strInfo = "DB/�f�[�^�\�[�X�Ƀt�@�C����(MDB)��ݒ肵�Ă��������B\r\n"
					"�ꕔ�̋@�\�����p�ł��܂���B";
		break;
	default:
		m_objBtnRef.EnableWindow(FALSE);
		m_strInfo = "";
		break;

	}
#endif
	UpdateData(FALSE);
}

BOOL CLoginDlg::SaveConnectInfo(CString &strLoginSet){
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();

	CString strDBType;
	int nIndex = m_objDBType.GetCurSel();
	m_objDBType.GetLBText(nIndex, strDBType);

	CString strSetPath;
	strSetPath.Format("%s\\%s.lsd",pApp->m_strBasePath, strLoginSet);
	WriteInifileString("LOGINSET", "dbtype",	strDBType,		strSetPath);
	WriteInifileString("LOGINSET", "server",	m_strServer,	strSetPath);
	WriteInifileString("LOGINSET", "user",		m_strUser,		strSetPath);
	WriteInifileString("LOGINSET", "pass",		m_strPassword,	strSetPath);
	WriteInifileString("LOGINSET", "db",		m_strDBName,	strSetPath);
	WriteInifileInt(   "LOGINSET", "dbaftsel",	m_bAftDBSel,	strSetPath);
	WriteInifileString("LOGINSET", "odbctype",	m_strOdbcType,	strSetPath);
	return TRUE;

}

BOOL CLoginDlg::LoadConnectInfo(LPCTSTR pszInfoName, LPTSTR pszDBType, LPTSTR pszServer, LPTSTR pszUser, LPTSTR pszPass, LPTSTR pszDBName, LPTSTR pzODBCType, BOOL &bAftDBSel){
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	CString strSetPath;
	strSetPath.Format("%s\\%s.lsd",pApp->m_strBasePath, pszInfoName);
	
	GetInifileString("LOGINSET",			"dbtype",	"SQLServer/MSDE",	pszDBType,	MAX_PATH, strSetPath);
	GetInifileString("LOGINSET",			"server",	"(local)",			pszServer,	MAX_PATH, strSetPath);
	GetInifileString("LOGINSET",			"user",		"sa",				pszUser,	MAX_PATH, strSetPath);
	GetInifileString("LOGINSET",			"pass",		"",					pszPass,	MAX_PATH, strSetPath);
	GetInifileString("LOGINSET",			"db",		"",					pszDBName,	MAX_PATH, strSetPath);
	GetInifileString("LOGINSET",			"odbctype",	"Microsoft",		pzODBCType,	MAX_PATH, strSetPath);
	bAftDBSel = GetInifileInt("LOGINSET",	"dbaftsel",	1,										  strSetPath);
	return TRUE;

}

BOOL CLoginDlg::CheckUpdate(LPCTSTR pszLoginSet){
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	char pszDBType[MAX_PATH];
	char pszServer[MAX_PATH];
	char pszUser[MAX_PATH];
	char pszPass[MAX_PATH];
	char pszDBName[MAX_PATH];
	char pszODBCType[MAX_PATH];
	BOOL bAftDBSel = FALSE;
	memset(pszDBType, 0, MAX_PATH);
	memset(pszServer, 0, MAX_PATH);
	memset(pszUser, 0, MAX_PATH);
	memset(pszPass, 0, MAX_PATH);
	memset(pszDBName, 0, MAX_PATH);
	memset(pszODBCType, 0, MAX_PATH);

	CString strLoginSet = pszLoginSet;
	CString strDBType;
	int nIndex = m_objDBType.GetCurSel();
	if(nIndex == -1){
		nIndex = 0;
	}
	m_objDBType.GetLBText(nIndex, strDBType);
	if(!strLoginSet.IsEmpty()){
		LoadConnectInfo(strLoginSet, pszDBType, pszServer, pszUser, pszPass, pszDBName, pszODBCType, bAftDBSel);
		//�I��ύX�O�̏����擾����
		if(strDBType.Compare(pszDBType)
		|| m_strDBName.Compare(pszDBName)
		|| m_strPassword.Compare(pszPass)
		|| m_strServer.Compare(pszServer)
		|| m_strUser.Compare(pszUser)
		|| m_bAftDBSel != bAftDBSel
		|| m_strOdbcType.Compare(pszODBCType)
		){
			return TRUE;
		}
	}	
	return FALSE;
}

BOOL CLoginDlg::CheckSafeValue(){
	int nIndex = m_objDBType.GetCurSel();
	if(nIndex == -1){
		return FALSE;
	}
/*
	if((!m_bAftDBSel && m_strDBName.IsEmpty())
//	|| m_strPassword.IsEmpty()
//	|| m_strServer.IsEmpty()
//	|| m_strUser.IsEmpty()
	){
		return FALSE;
	}
*/
	return TRUE;
}

void CLoginDlg::OnSelchangeLoginsetList(){
	CString strName;
	int nSel = m_objLoginSetList.GetCurSel();
	if(nSel == LB_ERR ){
		return;
	}
	m_objLoginSetList.GetText(nSel, strName);
	if(!m_strLoginSetName.Compare(strName)){
		return;
	}

	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	//���O�C���ݒ�̓ǂݍ���
	UpdateData();
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	char pszDBType[MAX_PATH];
	char pszServer[MAX_PATH];
	char pszUser[MAX_PATH];
	char pszPass[MAX_PATH];
	char pszDBName[MAX_PATH];
	char pszODBCType[MAX_PATH];
	BOOL bAftDBSel = FALSE;
	memset(pszDBType, 0, MAX_PATH);
	memset(pszServer, 0, MAX_PATH);
	memset(pszUser, 0, MAX_PATH);
	memset(pszPass, 0, MAX_PATH);
	memset(pszDBName, 0, MAX_PATH);
	memset(pszODBCType, 0, MAX_PATH);

	CString strDBType;
	int nIndex = m_objDBType.GetCurSel();
	if(nIndex == -1){
		nIndex = 0;
	}
	m_objDBType.GetLBText(nIndex, strDBType);
	if(!m_strSelSet.IsEmpty()){
		//�I��ύX�O�̏����擾����
		//LoadConnectInfo(m_strSelSet, pszDBType, pszServer, pszUser, pszPass, pszDBName, bAftDBSel);
		if(CheckUpdate(m_strSelSet)){
			//�ύX�L��
			DWORD dwRet = AfxMessageBox("�ݒ肪�ύX����Ă��܂��B�ۑ����܂����H", MB_YESNO);
			if(dwRet == IDYES){
				//�ۑ�����
				SaveConnectInfo(m_strSelSet);
			}
		}
	}	

	memset(pszDBType, 0, MAX_PATH);
	memset(pszServer, 0, MAX_PATH);
	memset(pszUser, 0, MAX_PATH);
	memset(pszPass, 0, MAX_PATH);
	memset(pszDBName, 0, MAX_PATH);
	bAftDBSel = FALSE;

//	int nSel = m_objLoginSetCmb.GetCurSel();
//	m_objLoginSetCmb.GetLBText(nSel, m_strLoginSetName);
//	int nSel = m_objLoginSetList.GetCurSel();
	m_objLoginSetList.GetText(nSel, m_strLoginSetName);

	if(!m_strLoginSetName.IsEmpty()){
		//�����擾����
		LoadConnectInfo(m_strLoginSetName, pszDBType, pszServer, pszUser, pszPass, pszDBName, pszODBCType, bAftDBSel);
	}	
	m_strDBName		= pszDBName;
	m_strPassword	= pszPass;
	m_strServer		= pszServer;
	m_strUser		= pszUser;
	m_strSelSet		= m_strLoginSetName;
	m_bAftDBSel		= bAftDBSel;
	m_strOdbcType	= pszODBCType;

	UpdateData(FALSE);
	int nPos = m_objDBType.SelectString(-1, pszDBType);
	if(nPos == CB_ERR){
		m_objDBType.SetCurSel(-1);
	}
	OnAfterdbsel();
	OnSelchangeDttypeCmb();
	
}

void CLoginDlg::OnDelSet(){
	if(AfxMessageBox("�ݒ���폜���܂����H", MB_OKCANCEL) == IDCANCEL){
		return;
	}
	UpdateData(TRUE);
	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();
	int nSel = m_objLoginSetList.GetCurSel();
	CString strOldName;
	m_objLoginSetList.GetText(nSel, strOldName);
	CString strOldPath;
	strOldPath.Format("%s\\%s.lsd",pApp->m_strBasePath, strOldName);
	::DeleteFile(strOldPath);
	m_objLoginSetList.DeleteString(nSel);
	m_objLoginSetList.SetSel(0, TRUE);
	m_objLoginSetList.GetText(0, m_strSelSet);
	m_strLoginSetName = m_strSelSet;
	UpdateData(FALSE);
}

void CLoginDlg::OnDoubleclickedDelSet(){
}

void CLoginDlg::OnNewSet(){
	CLoginSetNameInpDlg objInpDlg;
	if(objInpDlg.DoModal() != IDOK){
		return;
	}

	int nPos = m_objLoginSetList.FindStringExact(-1, objInpDlg.m_strName);
	if(nPos != LB_ERR){
		AfxMessageBox("���ɑ��݂��閼�O�ł�");
		return;
	}

	m_objLoginSetList.AddString(objInpDlg.m_strName);

}

void CLoginDlg::OnDoubleclickedNewSet(){
}

void CLoginDlg::OnModifySet(){
	CLoginSetNameInpDlg objInpDlg;
	int nSel = m_objLoginSetList.GetCurSel();
	CString strOldName;
	m_objLoginSetList.GetText(nSel, strOldName);
	objInpDlg.m_strName = strOldName;
	if(objInpDlg.DoModal() != IDOK){
		return;
	}

	int nPos = m_objLoginSetList.FindStringExact(-1, objInpDlg.m_strName);
	if(nPos != LB_ERR){
		AfxMessageBox("���ɑ��݂��閼�O�ł�");
		return;
	}

	CDBToolApp *pApp = (CDBToolApp*)AfxGetApp();

	CString strOldPath;
	strOldPath.Format("%s\\%s.lsd",pApp->m_strBasePath, strOldName);

	CString strNewPath;
	strNewPath.Format("%s\\%s.lsd",pApp->m_strBasePath, objInpDlg.m_strName);

	::MoveFile(strOldPath, strNewPath);

	m_objLoginSetList.SetSel(nSel, FALSE);
	m_objLoginSetList.DeleteString(nSel);
	m_objLoginSetList.InsertString(nSel, objInpDlg.m_strName);
//	SaveConnectInfo(objInpDlg.m_strName);
	m_objLoginSetList.SetSel(nSel, TRUE);
	m_strSelSet = objInpDlg.m_strName;
	UpdateData(FALSE);
}

void CLoginDlg::OnDoubleclickedModifySet(){
}

void CLoginDlg::OnBtnRef(){
	CFileDialogEx dlg(m_hWnd, NULL, "", "", "*.mdb", 0, NULL, "MDB�̑I��", "mdb");
	if(dlg.DoModal() != IDOK){
		return;
	}
	int nIndex = m_objDbNameCmb.AddString(dlg.GetFileName());
	m_objDbNameCmb.SetCurSel(nIndex);
}
