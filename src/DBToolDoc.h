// DBToolDoc.h : CDBToolDoc �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTOOLDOC_H__8D99B843_2038_493C_BD36_BB08B6267A42__INCLUDED_)
#define AFX_DBTOOLDOC_H__8D99B843_2038_493C_BD36_BB08B6267A42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDBToolDoc : public CDocument{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CDBToolDoc();
	DECLARE_DYNCREATE(CDBToolDoc)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

//�I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDBToolDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CDBToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CDBToolDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DBTOOLDOC_H__8D99B843_2038_493C_BD36_BB08B6267A42__INCLUDED_)
