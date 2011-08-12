// HOBO_ServerDoc.cpp : CHOBO_ServerDoc クラスの実装
//

#include "stdafx.h"
#include "HOBO_Server.h"

#include "HOBO_ServerDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHOBO_ServerDoc

IMPLEMENT_DYNCREATE(CHOBO_ServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CHOBO_ServerDoc, CDocument)
END_MESSAGE_MAP()


// CHOBO_ServerDoc コンストラクション/デストラクション

CHOBO_ServerDoc::CHOBO_ServerDoc()
{
	// TODO: この位置に 1 度だけ呼ばれる構築用のコードを追加してください。

}

CHOBO_ServerDoc::~CHOBO_ServerDoc()
{
}

BOOL CHOBO_ServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)
	CMainFrame * pMain = ((CMainFrame*)AfxGetMainWnd());
	pMain->m_iCurrWndCnt++;

	CString tabTitle;
	tabTitle.Format("Tab%d", pMain->m_iCurrWndCnt-1);
	this->SetTitle(pMain->m_iCurrWndCnt == 1 ? "自分" : tabTitle);

	return TRUE;
}




// CHOBO_ServerDoc シリアル化

void CHOBO_ServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 格納するコードをここに追加してください。
	}
	else
	{
		// TODO: 読み込むコードをここに追加してください。
	}
}


// CHOBO_ServerDoc 診断

#ifdef _DEBUG
void CHOBO_ServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHOBO_ServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHOBO_ServerDoc コマンド
