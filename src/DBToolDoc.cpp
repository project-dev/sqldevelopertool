// DBToolDoc.cpp : CDBToolDoc �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "DBTool.h"

#include "DBToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBToolDoc

IMPLEMENT_DYNCREATE(CDBToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CDBToolDoc, CDocument)
	//{{AFX_MSG_MAP(CDBToolDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBToolDoc �N���X�̍\�z/����

CDBToolDoc::CDBToolDoc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CDBToolDoc::~CDBToolDoc()
{
}

BOOL CDBToolDoc::OnNewDocument(){
	SetTitle("�ؒf");
/*
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)
*/
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDBToolDoc �V���A���C�[�[�V����

void CDBToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDBToolDoc �N���X�̐f�f

#ifdef _DEBUG
void CDBToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDBToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBToolDoc �R�}���h
