// HOBO_Server.h : HOBO_Server �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��


// CHOBO_ServerApp:
// ���̃N���X�̎����ɂ��ẮAHOBO_Server.cpp ���Q�Ƃ��Ă��������B
//

class CHOBO_ServerApp : public CWinApp
{
public:
	CHOBO_ServerApp();


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFolderNew();
};

extern CHOBO_ServerApp theApp;