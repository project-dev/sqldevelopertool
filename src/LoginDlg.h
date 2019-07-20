#if !defined(AFX_LOGINDLG_H__9A0E7A1E_1974_4B1F_B664_AA58C278B45B__INCLUDED_)
#define AFX_LOGINDLG_H__9A0E7A1E_1974_4B1F_B664_AA58C278B45B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg �_�C�A���O

class CLoginDlg : public CDialog
{
// �R���X�g���N�V����
public:
	BOOL CheckSafeValue();
	BOOL CheckUpdate(LPCTSTR pszLoginSet);
	BOOL LoadConnectInfo(LPCTSTR pszInfoName, LPTSTR pszDBType, LPTSTR pszServer, LPTSTR pszUser, LPTSTR pszPass, LPTSTR pszDB, LPTSTR pszODBCType, BOOL &bAftDBSel);
	CString m_strSelSet;
	CLoginDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	static  bool CALLBACK LoginSetEnum(const char* pszFile, WIN32_FIND_DATA* pwfd, LPARAM lParam);
// �_�C�A���O �f�[�^
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGIN_DLG };
	CButton	m_objBtnRef;
	CComboBox	m_objDbOdbcCmb;
	CListBox	m_objLoginSetList;
	CComboBox	m_objUser;
	CComboBox	m_objServer;
	CButton	m_objAftDBSelBtn;
	CComboBox	m_objDBType;
	CComboBox	m_objDbNameCmb;
	CString	m_strPassword;
	CString	m_strServer;
	CString	m_strUser;
	CString	m_strDBName;
	BOOL	m_bAftDBSel;
	int		m_nDBType;
	CString	m_strLoginSetName;
	CString	m_strOdbcType;
	CString	m_strInfo;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CLoginDlg)
	afx_msg void OnAfterdbsel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeDttypeCmb();
	afx_msg void OnSelchangeLoginsetList();
	afx_msg void OnDelSet();
	afx_msg void OnDoubleclickedDelSet();
	afx_msg void OnNewSet();
	afx_msg void OnDoubleclickedNewSet();
	afx_msg void OnModifySet();
	afx_msg void OnDoubleclickedModifySet();
	afx_msg void OnBtnRef();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL SaveConnectInfo(CString &strLoginSet);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LOGINDLG_H__9A0E7A1E_1974_4B1F_B664_AA58C278B45B__INCLUDED_)
