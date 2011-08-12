// HOBO_Server.h : HOBO_Server アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CHOBO_ServerApp:
// このクラスの実装については、HOBO_Server.cpp を参照してください。
//

class CHOBO_ServerApp : public CWinApp
{
public:
	CHOBO_ServerApp();


// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFolderNew();
};

extern CHOBO_ServerApp theApp;