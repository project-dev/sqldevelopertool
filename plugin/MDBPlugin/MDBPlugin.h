// MDBPlugin.h : MDBPLUGIN �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_MDBPLUGIN_H__ED3E0B75_0B64_48B9_B25C_E9B55A91B217__INCLUDED_)
#define AFX_MDBPLUGIN_H__ED3E0B75_0B64_48B9_B25C_E9B55A91B217__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��
#include "SDTPlugin.h"
/////////////////////////////////////////////////////////////////////////////
// CMDBPluginApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� MDBPlugin.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CMDBPluginApp : public CWinApp
{
public:
	CMDBPluginApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMDBPluginApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMDBPluginApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MDBPLUGIN_H__ED3E0B75_0B64_48B9_B25C_E9B55A91B217__INCLUDED_)
