// HistCustPage.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "dbtool.h"
#include "HistCustPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistCustPage �_�C�A���O


CHistCustPage::CHistCustPage(CWnd* pParent /*=NULL*/)
	: CDialog(CHistCustPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHistCustPage)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CHistCustPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHistCustPage)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHistCustPage, CDialog)
	//{{AFX_MSG_MAP(CHistCustPage)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistCustPage ���b�Z�[�W �n���h��
