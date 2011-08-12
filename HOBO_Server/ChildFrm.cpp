// ChildFrm.cpp : CChildFrame クラスの実装
//
#include "stdafx.h"
#include "HOBO_Server.h"

#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()
//	ON_WM_INITMENU()
ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CChildFrame コンストラクション/デストラクション

CChildFrame::CChildFrame()
{
	// TODO: メンバ初期化コードをここに追加してください。
	m_bLeftMost = FALSE;
	m_LeftRelatedSliderBar = NULL;
	m_RightRelatedSliderBar = NULL;
}

CChildFrame::~CChildFrame()
{
}

//BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
//{
//	return m_wndSplitter.Create(this,
//		2, 2,			// TODO: 行と列の数を調整してください。
//		CSize(10, 10),	// TODO: 最小ペインのサイズを変更します。
//		pContext);
//}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs を変更して、Window クラスまたはスタイルを変更します。
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	//cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
	//	| FWS_ADDTOTITLE | WS_THICKFRAME;

	cs.style &= ~WS_THICKFRAME;
	cs.style &= ~WS_CAPTION;
	cs.style &= ~WS_BORDER;

	return TRUE;
}


// CChildFrame 診断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CChildFrame メッセージ ハンドラ

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ここに特定な作成コードを追加してください。
	CMainFrame * pMain = (CMainFrame *)GetMDIFrame( );

	CString title;
	title.Format("%s%d","Tab",pMain->m_iCurrWndCnt);
	m_tabTitle = pMain->m_iCurrWndCnt == 1 ? "自分" :  title ;

	return 0;
}

void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CMainFrame * pMain = (CMainFrame *)GetMDIFrame( );
	CRect rcClient(pMain->m_OldClientRect);

	//新しい扉が開くとき親扉の空間を全て占める
	switch(pMain->m_iCurrWndCnt){
		case 1:
			this->m_bLeftMost = TRUE;
			break;
	}
	CRect lR;
	if(pMain->m_bSlided){
		lR = pMain->m_leftRect;
	}
	else
		lR = CRect(rcClient.left-1,rcClient.top+21,rcClient.right,rcClient.bottom-68);

	this->SetWindowPos(&CWnd::wndBottom   ,lR.left,lR.top,lR.right,lR.bottom,SWP_NOREDRAW);


	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CChildFrame::DestroyWindow()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CMainFrame * pMain = (CMainFrame *)GetMDIFrame( );
	pMain->m_iCurrWndCnt--;
	if(pMain->m_bSlided ){
		if(m_LeftRelatedSliderBar || m_RightRelatedSliderBar)	
			pMain->RemoveSlider(m_LeftRelatedSliderBar == NULL ? (long)m_RightRelatedSliderBar : (long)m_LeftRelatedSliderBar,this);
	}
	else{
		if(pMain->m_iCurrWndCnt >= 1){
			pMain->MDINext();
			CChildFrame* pChild = ((CChildFrame * ) pMain->MDIGetActive());
			pChild->m_bLeftMost = TRUE;
		}
	}

	return CMDIChildWnd::DestroyWindow();
}

//最初化するところ
void CChildFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CMDIChildWnd::OnShowWindow(bShow, nStatus);

	// TODO: ここにメッセージ ハンドラ コードを追加します。
	CMainFrame * pMain = (CMainFrame *)GetMDIFrame( );

	//ラン状態のOFFを設置
	CMenu * pMainMenu = pMain->GetMenu();
	CMenu * pSubMenu = pMainMenu->GetSubMenu(3);
	CMenu * pSSubMenu = pSubMenu->GetSubMenu(5);
	pSSubMenu->CheckMenuRadioItem(ID_STATE_ONLINE,ID_STATE_OFFLINE,ID_STATE_OFFLINE,MF_BYCOMMAND);
}
