// MainFrm.cpp : CMainFrame クラスの実装
//

#include "stdafx.h"
#include "HOBO_Server.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
//	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_SLIDE_END, OnSlideEnd)

	ON_COMMAND_RANGE(ID_STATE_ONLINE, ID_STATE_OFFLINE, OnUpdateLanState)
	ON_COMMAND_RANGE(ID_KEY_ASSIGN,ID_ONLINEMEMBER,OnSideWndSelect)
	ON_COMMAND_RANGE(ID_MAINVIEW_LARGE, ID_MAINVIEW_SMALL, OnUpdateMainViewState)
	ON_COMMAND_RANGE(ID_DESKTOP_LARGE,ID_DESKTOP_SMALL,OnUpdateDesktopState)
	ON_COMMAND_RANGE(ID_LIST,ID_LIST_ARRANGE,OnUpdateListState)
	ON_COMMAND_RANGE(ID_LIST,ID_LIST_ARRANGE,OnUpdateListState)
	ON_COMMAND_RANGE(ID_SORT_NAME,ID_SORT_DESC,OnUpdateSortState)
	ON_COMMAND_RANGE(ID_GROUP_NAME,ID_GROUP_DESC,OnUpdateGroupState)
	ON_COMMAND_RANGE(ID_STAND_AUTO,ID_STAND_EQUALSPC,OnUpdateStandState)
	ON_COMMAND_RANGE(ID_CHAT_ON,ID_CHAT_OFF,OnUpdateChatState)
	ON_COMMAND(ID_IPHONE_SHARE, &CMainFrame::OnIphoneShare)
	ON_COMMAND(ID_GROUP_SET, &CMainFrame::OnGroupSet)
	ON_COMMAND(ID_PARTNER_RECRUIT, &CMainFrame::OnPartnerRecruit)

	ON_WM_SIZE()
//	ON_WM_CHILDACTIVATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ステータス ライン インジケータ
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

float round(float fv){
	return fv-(int)fv > 0.5 ? ++fv : fv;
}


// CMainFrame コンストラクション/デストラクション

CMainFrame::CMainFrame()

{
	// TODO: メンバ初期化コードをここに追加してください。
	m_bLANState = 0;
	m_bChatState = 0;

	m_iCurrWndCnt = 0;
	m_bSliding = FALSE;
	m_bSlided = FALSE;
	m_bRightMostSliding = FALSE;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("ツール バーの作成に失敗しました。\n");
		return -1;      // 作成できませんでした。
	}
	//最初隠す
	CToolBarCtrl &tbc = m_wndToolBar.GetToolBarCtrl();
	tbc.SetState(ID_STATE_ONLINE,TBSTATE_HIDDEN);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("ステータス バーの作成に失敗しました。\n");
		return -1;      // 作成できませんでした。
	}

	// TODO: ツール バーをドッキング可能にしない場合は、これらの 3 行を削除してください。
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//TAB
	if (!m_wndTabBar.Create(IDD_TAB_BAR,this))		
	{
			TRACE0("Failed to create dialog bar m_wndDialogbar\n");
			return -1;		// fail to create
	}
	m_wndTabBar.ShowWindow(SW_SHOW);
	m_HBTab.SubclassDlgItem(IDC_TAB, &m_wndTabBar); 

	//Right Most Slider
	if (!m_RightMostBar.Create(IDD_SLIDE_BAR,this))
	{
		TRACE0("Failed to create dialog bar m_wndDialogbar\n");
		return -1;		// fail to create
	}
	m_RightMostBar.m_bRightMost = TRUE;
	
	//起動前に値を設定
	ClearSliderBarList();


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	cs.style = WS_OVERLAPPED | WS_CAPTION /*| FWS_ADDTOTITLE*/
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	//cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}


// CMainFrame 診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame メッセージ ハンドラ

void CMainFrame::ToolbarImgChange(int iDest, int iSrc)
{
	//CToolBarCtrl & tbc = m_wndToolBar.GetToolBarCtrl(); 
	//CImageList * pTbi = tbc.GetImageList(); 
	//pTbi->Copy(iSpcHold,iDest);
	//pTbi->Copy(iDest,iSrc);
	//pTbi->Copy(iSrc,iSpcHold);
	//tbc.SetImageList(pTbi); 
	//m_wndToolBar.Invalidate();

	CToolBarCtrl &tbc = m_wndToolBar.GetToolBarCtrl();
	tbc.SetState(iDest,TBSTATE_ENABLED);
	tbc.SetState(iSrc,TBSTATE_HIDDEN);
}

void CMainFrame::GetMessageString(UINT nID, CString& rMessage) const
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	//if(m_bLANState && nID==ID_STATE_OFFLINE){
	//	rMessage = _T("オンライン");
	//	return;
	//}
	return CMDIFrameWnd::GetMessageString(nID, rMessage);
}

void CMainFrame::OnSideWndSelect(UINT nID){
	CMenu * pMainMenu = this->GetMenu();
	CMenu * pSubMenu = pMainMenu->GetSubMenu(2);
	CMenu * pSSubMenu = pSubMenu->GetSubMenu(2);

	UINT state = pSSubMenu->GetMenuState(nID,MF_BYCOMMAND);

	pSSubMenu->CheckMenuItem(nID, (state == MF_CHECKED ? MF_UNCHECKED : MF_CHECKED)  | MF_BYCOMMAND); 
}

void CMainFrame::OnUpdateLanState(UINT nID){
	CMenu * pMainMenu = this->GetMenu();
	CMenu * pSubMenu = pMainMenu->GetSubMenu(3);
	CMenu * pSSubMenu = pSubMenu->GetSubMenu(5);

	pSSubMenu->GetMenuState

	pSSubMenu->CheckMenuRadioItem(ID_STATE_ONLINE,ID_STATE_OFFLINE,
		nID == ID_STATE_ONLINE ? ID_STATE_OFFLINE : ID_STATE_ONLINE,
		MF_BYCOMMAND);

	//6ー＞8、７－＞６、８－＞７、この三回交換
	m_bLANState = !m_bLANState;
	m_bLANState ? ToolbarImgChange(ID_STATE_ONLINE,ID_STATE_OFFLINE) : ToolbarImgChange(ID_STATE_OFFLINE,ID_STATE_ONLINE) ;

}

void CMainFrame::OnUpdateMainViewState(UINT nID){
	CMenu * pMainMenu = this->GetMenu();
	CMenu * pSubMenu = pMainMenu->GetSubMenu(2);
	CMenu * pSSubMenu = pSubMenu->GetSubMenu(4);
	CMenu * pSSSubMenu = pSSubMenu->GetSubMenu(0);

	pSSSubMenu->CheckMenuRadioItem(ID_MAINVIEW_LARGE,ID_MAINVIEW_SMALL,
		nID,
		MF_BYCOMMAND);
}

void CMainFrame::OnUpdateDesktopState(UINT nID){
	CMenu * pMainMenu = this->GetMenu();
	CMenu * pSubMenu = pMainMenu->GetSubMenu(2);
	CMenu * pSSubMenu = pSubMenu->GetSubMenu(4);
	CMenu * pSSSubMenu = pSSubMenu->GetSubMenu(1);

	pSSSubMenu->CheckMenuRadioItem(ID_DESKTOP_LARGE,ID_DESKTOP_SMALL,
		nID,
		MF_BYCOMMAND);
}

void CMainFrame::OnUpdateListState(UINT nID){
	CMenu * pMainMenu = this->GetMenu();
	CMenu * pSubMenu = pMainMenu->GetSubMenu(2);
	CMenu * pSSubMenu = pSubMenu->GetSubMenu(4);
	CMenu * pSSSubMenu = pSSubMenu->GetSubMenu(2);

	pSSSubMenu->CheckMenuRadioItem(ID_LIST,ID_LIST_ARRANGE,
		nID,
		MF_BYCOMMAND);
}

void CMainFrame::OnUpdateSortState(UINT nID){
	CMenu * pMainMenu = this->GetMenu();
	CMenu * pSubMenu = pMainMenu->GetSubMenu(2);
	CMenu * pSSubMenu = pSubMenu->GetSubMenu(5);

	pSSubMenu->CheckMenuRadioItem(ID_SORT_NAME,ID_SORT_DESC,
		nID,
		MF_BYCOMMAND);
}

void CMainFrame::OnUpdateGroupState(UINT nID){
	CMenu * pMainMenu = this->GetMenu();
	CMenu * pSubMenu = pMainMenu->GetSubMenu(2);
	CMenu * pSSubMenu = pSubMenu->GetSubMenu(6);

	pSSubMenu->CheckMenuRadioItem(ID_GROUP_NAME,ID_GROUP_DESC,
		nID,
		MF_BYCOMMAND);
}

void CMainFrame::OnUpdateStandState(UINT nID){
	CMenu * pMainMenu = this->GetMenu();
	CMenu * pSubMenu = pMainMenu->GetSubMenu(2);
	CMenu * pSSubMenu = pSubMenu->GetSubMenu(7);

	UINT state = pSSubMenu->GetMenuState(nID,MF_BYCOMMAND);

	pSSubMenu->CheckMenuItem(nID, (state == MF_CHECKED ? MF_UNCHECKED : MF_CHECKED)  | MF_BYCOMMAND); 
}

void CMainFrame::OnUpdateChatState(UINT nID){
	CMenu * pMainMenu = this->GetMenu();
	CMenu * pSubMenu = pMainMenu->GetSubMenu(4);
	CMenu * pSSubMenu = pSubMenu->GetSubMenu(2);

	pSSubMenu->CheckMenuRadioItem(ID_CHAT_ON,ID_CHAT_OFF,
		nID,
		MF_BYCOMMAND);
}

void CMainFrame::OnIphoneShare()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
}

void CMainFrame::OnGroupSet()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
}

void CMainFrame::OnPartnerRecruit()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIFrameWnd::OnSize(nType, cx, cy);

	// TODO: ここにメッセージ ハンドラ コードを追加します。
	RetainTab();

    CMDIChildWnd* child = MDIGetActive();

	CRect rcClient;
	GetClientRect(&rcClient);
	int icx = cx - 9 ;                                                                  
	int iChldTop = rcClient.top + 21;
	int iChldBottom = rcClient.bottom -68;
	m_RightMostBar.SetWindowPos(&CWnd::wndTop,icx+2,iChldTop+26,5,iChldBottom,SWP_DRAWFRAME);
	m_RightMostBar.ShowWindow(SW_SHOW);//必要

	if(m_bSlided){
		int iSlideX;
		
		POSITION oldPos = NULL;
		POSITION pos = m_SliderBarList.GetHeadPosition();
		int iStep = 0;
		CRect tR;
		CChildFrame * pRChild;
		float fProportional = (float)icx/(float)m_OldClientRect.right;
		int iFactor;
		while(pos != 0){
			oldPos = pos;

			CSliderBar  * pSliderBar = (CSliderBar  *)m_SliderBarList.GetNext(pos);
			CChildFrame * pLChild = (CChildFrame * )pSliderBar->m_leftChild;
			pRChild = (CChildFrame * )pSliderBar->m_rightChild;
			tR = pLChild->m_oppChildRect;

			iFactor = round(tR.right * fProportional);
			tR = CRect(pLChild->m_bLeftMost ? -1 : /*round*/(iSlideX+4),iChldTop,iFactor,iChldBottom);

			pLChild->SetWindowPos(&CWnd::wndBottom,tR.left,tR.top,tR.right,tR.bottom,SWP_DRAWFRAME);
			pLChild->m_oppChildRect = tR;
			if(!iStep) m_leftRect = tR;

			iSlideX = /*round*/(pSliderBar->m_oppSliderRect.left * fProportional);
			if(iSlideX != (tR.left + iFactor + 3) ) iSlideX = tR.left + iFactor + 3;//ちょっこと調整する
			pSliderBar->SetWindowPos(&CWnd::wndTop,iSlideX,iChldTop+26,5,iChldBottom,SWP_DRAWFRAME);
			pSliderBar->m_oppSliderRect = CRect(iSlideX,iChldTop+26,5,iChldBottom);

			iStep++;
		}
		if(m_SliderBarList.GetCount()){
			tR = CRect((tR.left + tR.right + 7),tR.top,iFactor,tR.bottom);
			icx--;
			if((tR.left + iFactor) > icx) tR.right -= ((tR.left + iFactor) - icx);//ちょっこと調整する
			if((tR.left + iFactor) < icx) tR.right += (icx -(tR.left + iFactor)) ;
			pRChild->SetWindowPos(&CWnd::wndBottom,tR.left,tR.top,tR.right,tR.bottom,SWP_DRAWFRAME);
			pRChild->m_oppChildRect = tR;

			AlignLeftUnslideCld();
		}
	}
	else{
		CRect rc = CRect(rcClient.left-1, iChldTop,icx,iChldBottom);
		for(int i=0;i<m_HBTab.GetItemCount( );i++){
			TC_ITEM ti;
			if(m_HBTab.GetItem(i,&ti)){
				CView * pView = (CView *) ti.lParam;
				CChildFrame * pChildFrame = (CChildFrame*)pView->GetParentFrame();
				
				pChildFrame->SetWindowPos(&CWnd::wndBottom,rc.left,rc.top,rc.right,rc.bottom,SWP_DRAWFRAME);
			}
	   }
	}

	if(child)
		this->MDIActivate(child);

	m_OldClientRect = rcClient;
	m_OldClientRect.right -= 9;
}

LRESULT CMainFrame::OnSlideEnd(WPARAM w, LPARAM l)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	int iSlided;
	TRACE1("%d\r\n", iSlided = (int)l);
	CChildFrame * pDropChild = (CChildFrame *)w;
	CSliderBar * pSliderBar = NULL;
	CChildFrame * lChild = NULL;
	CChildFrame * rChild = NULL;
	CRect lR;
	CRect rR;
	
	if(pDropChild->m_LeftRelatedSliderBar && pDropChild->m_LeftRelatedSliderBar->m_bSliding){
		//right drag
		pSliderBar = pDropChild->m_LeftRelatedSliderBar;
		rChild = pDropChild;
		rR = pDropChild->m_oppChildRect;
		lChild = (CChildFrame *)pSliderBar->m_leftChild;
		lR = lChild->m_oppChildRect;

		pDropChild->m_LeftRelatedSliderBar->m_bSliding = FALSE;
	}
	else if(pDropChild->m_RightRelatedSliderBar && pDropChild->m_RightRelatedSliderBar->m_bSliding){
		//left drag
		pSliderBar = pDropChild->m_RightRelatedSliderBar;
		lChild = pDropChild;
		lR = pDropChild->m_oppChildRect;
		rChild = (CChildFrame *)pSliderBar->m_rightChild;
		rR =  rChild->m_oppChildRect;

		pDropChild->m_RightRelatedSliderBar->m_bSliding = FALSE;
	}
	else
		return 1;



	if(iSlided < lR.left + 130) {/*left*/ 
		//lChild->PostMessageA(WM_CLOSE);
		iSlided = lR.left + 130; 
		//return 3;
	}
	if(iSlided > (rR.left + rR.right - 135 )){
		if(!rChild->m_RightRelatedSliderBar){ 
			rChild->PostMessageA(WM_CLOSE);
			return 4;
		}
		iSlided = rR.left + rR.right - 135; 
	}
	
	int iOffset = 0;
	if(iSlided <  rR.left-7)//左へ
		iOffset = rR.left-7+3 - iSlided;//SlideBarの左と今のSlidedの値の差
	//if(iSlided == lR.right) return 0 ;
	//if(iSlided > lR.right && iSlided - lR.right == 2 ) return 0;
	
	if(iSlided > rR.left)//右へ
		iOffset = rR.left-4 - iSlided;
	//if(iSlided == rR.left) return 0;
	//if(iSlided < rR.left && iSlided - rR.left == -4) return 0;

	if(!iOffset) return 2;

	//左ウィンドウ
	lR = CRect(lR.left,lR.top,lR.right-iOffset,lR.bottom);
	if(lChild->m_bLeftMost)
		m_leftRect = lR;
	lChild->SetWindowPos(&CWnd::wndBottom,lR.left,lR.top,lR.right,lR.bottom,SWP_DRAWFRAME);
	lChild->m_oppChildRect = lR;
	
	//右ウィンドウ
	rR = CRect(iSlided+4,rR.top,rR.right+iOffset,rR.bottom);
	rChild->SetWindowPos(&CWnd::wndBottom,rR.left,rR.top,rR.right,rR.bottom,SWP_DRAWFRAME);//
	rChild->m_oppChildRect = rR;
	
	pSliderBar->SetWindowPos(&CWnd::wndTop,iSlided,lR.top+26,5,lR.bottom,SWP_DRAWFRAME);

	return 0;
}

CMDIChildWnd * CMainFrame::FindLeftMostCld(){
	for(int i=0;i<m_HBTab.GetItemCount( );i++){
		TC_ITEM ti;
		if(m_HBTab.GetItem(i,&ti)){
			CView * pView = (CView *) ti.lParam;
			CChildFrame * pChildFrame = (CChildFrame*)pView->GetParentFrame();

			if(pChildFrame->m_bLeftMost){
				return pChildFrame;
			}
		}
	}
	return NULL;
}

void CMainFrame::AlignLeftUnslideCld(){
	CChildFrame * pChildFrame = (CChildFrame * )FindLeftMostCld();
	if(!pChildFrame) return;

	CRect tr(pChildFrame->m_oppChildRect);
	for(int i=0;i<m_HBTab.GetItemCount( );i++){
		TC_ITEM ti;
		if(m_HBTab.GetItem(i,&ti)){
			CView * pView = (CView *) ti.lParam;
			CChildFrame * pChildFrame = (CChildFrame*)pView->GetParentFrame();

			if(!pChildFrame->m_LeftRelatedSliderBar &&  !pChildFrame->m_RightRelatedSliderBar){
				pChildFrame->SetWindowPos(&CWnd::wndBottom,tr.left,tr.top,tr.right,tr.bottom,SWP_DRAWFRAME);//
				pChildFrame->m_oppChildRect = tr;
			}
		}
	}
}

int CMainFrame::Slide(CMDIChildWnd* pLeftChild, CMDIChildWnd* pRightChild, BOOL bEqual, BOOL bMostRight){
	if(!pLeftChild || !pRightChild) return 1;//パラメータの値は空きの場合

	CChildFrame * lChild = (CChildFrame *)pLeftChild;
	CChildFrame * rChild = (CChildFrame *)pRightChild;
	
	if(lChild->m_RightRelatedSliderBar && lChild->m_RightRelatedSliderBar->m_rightChild == pRightChild) return 2; //このペーア既にある
	if(lChild->m_LeftRelatedSliderBar && lChild->m_LeftRelatedSliderBar->m_leftChild == pRightChild) return 2; //このペーア既にある

	RetainTab();

	CMDIChildWnd* child = MDIGetActive();//事前に今のアクティブウィンドウ

	CRect lClient = m_bSlided ? lChild->m_oppChildRect : m_OldClientRect ;
	int iHalf = round((float)(lClient.right - (m_bSlided ? 0 : -1) - 7 )/2);
	int iSlidex = (m_bSlided ? lClient.left : -1) + iHalf + 3;
	int iChldTop = m_bSlided ? lClient.top : (lClient.top + 21);
	int iChldBottom =m_bSlided ? lClient.bottom: (lClient.bottom - 68);
	CSliderBar * pSliderBar = new CSliderBar();
	pSliderBar->Create(IDD_SLIDE_BAR,this);

	//左ウィンドウ
	CRect leftRect = CRect(m_bSlided ? lClient.left : -1,iChldTop,iHalf,iChldBottom);
	lChild->SetWindowPos(&CWnd::wndBottom   ,leftRect.left,leftRect.top,leftRect.right,leftRect.bottom,SWP_DRAWFRAME);
	lChild->m_oppChildRect = leftRect;
	CSliderBar * pOldSliderBar;
	if(!bMostRight){
		pOldSliderBar = lChild->m_LeftRelatedSliderBar;
	}
	if(!m_bSlided){
		m_leftRect = leftRect;
		lChild->m_bLeftMost = TRUE;
	}
	lChild->m_RightRelatedSliderBar = pSliderBar;
	pSliderBar->m_leftChild = lChild;

	//右のウィンドウ
	CRect rR((m_bSlided ? lClient.left : -1)+iHalf+7,iChldTop,iHalf,iChldBottom);
	int iAllowWeight = (2 * iHalf) + 7;//ちょっこと調整する
	if(iAllowWeight > lClient.right) rR.right -= (iAllowWeight - lClient.right);
	if(iAllowWeight < lClient.right) rR.right += (lClient.right - iAllowWeight );
	rChild->SetWindowPos(&CWnd::wndBottom,rR.left,rR.top,rR.right,rR.bottom,SWP_DRAWFRAME);
	rChild->m_oppChildRect = rR;
	rChild->m_LeftRelatedSliderBar = pSliderBar;
	pSliderBar->m_rightChild = rChild;

	if(!bMostRight){//転向
		pOldSliderBar->m_leftChild = rChild;
		rChild->m_RightRelatedSliderBar = pOldSliderBar;
	}

	m_SliderBarList.AddTail(pSliderBar);

	CRect sR = CRect(iSlidex,iChldTop+26,5,iChldBottom);
	pSliderBar->SetWindowPos(&CWnd::wndTop,sR.left,sR.top,sR.right,sR.bottom,SWP_DRAWFRAME);
	pSliderBar->ShowWindow(SW_SHOW);//必要
	pSliderBar->m_oppSliderRect = sR;
	pSliderBar->m_parentPoint.x = iSlidex;
	pSliderBar->m_parentPoint.y = lClient.top+30;

	if(bEqual) EquShow();

	AlignLeftUnslideCld();

	if(child)
		this->MDIActivate(child);

	m_bSlided = TRUE;

	return 0;
}

//均一でショーする
void CMainFrame::EquShow(){

	RetainTab();

	int iChildCnt =  m_SliderBarList.GetCount() ;
	int iFactor = (m_OldClientRect.right - (-1) - 7 * iChildCnt)/(iChildCnt+1);//左の値がー１よりだから
	int iSlideX;
	int iChldTop = m_OldClientRect.top + 21;
	int iChldBottom = m_OldClientRect.bottom -68;

	POSITION oldPos = NULL;
	POSITION pos = m_SliderBarList.GetHeadPosition();
	int iStep = 0;
	CRect tR;
	int iLeft;
	CChildFrame * pRChild;
	while(pos != 0){
		oldPos = pos;

		CSliderBar  * pSliderBar = (CSliderBar  *)m_SliderBarList.GetNext(pos);
		CChildFrame * pLChild = (CChildFrame * )pSliderBar->m_leftChild;
		pRChild = (CChildFrame * )pSliderBar->m_rightChild;
		iLeft = iFactor*iStep + iStep*7 - 1;
		tR = CRect(iLeft,iChldTop,iFactor,iChldBottom);
		pLChild->SetWindowPos(&CWnd::wndBottom,tR.left,tR.top,tR.right,tR.bottom,SWP_DRAWFRAME);
		pLChild->m_oppChildRect = tR;
		if(!iStep) m_leftRect = tR;

		iSlideX = iFactor*(iStep+1) + 7*iStep + 2;
		if(iSlideX != (tR.left + iFactor + 3) ) iSlideX = tR.left + iFactor + 3;//ちょっこと調整する
		pSliderBar->SetWindowPos(&CWnd::wndTop,iSlideX,iChldTop+26,5,iChldBottom,SWP_DRAWFRAME);
		pSliderBar->m_oppSliderRect = CRect(iSlideX,iChldTop+26,5,iChldBottom);

		iStep++;
	}
	tR = CRect(tR.left + tR.right + 7,tR.top,iFactor,tR.bottom);
	int icx = m_OldClientRect.right - 1;
	if((tR.left + iFactor) > icx) tR.right -= ((tR.left + iFactor) - icx);//ちょっこと調整する
	if((tR.left + iFactor) < icx) tR.right += (icx -(tR.left + iFactor)) ;
	pRChild->SetWindowPos(&CWnd::wndBottom,tR.left,tR.top,tR.right,tR.bottom,SWP_DRAWFRAME);
	pRChild->m_oppChildRect = tR;
}


void CMainFrame::ClearSliderBarList(void)
{
	POSITION pos = m_SliderBarList.GetHeadPosition();
	while(pos != 0){
		CSliderBar  * pSliderBar = (CSliderBar  *)m_SliderBarList.GetNext(pos);
		delete pSliderBar;
	}
	m_SliderBarList.RemoveAll();

}

void CMainFrame::OnClose()
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	ClearSliderBarList();

	CMDIFrameWnd::OnClose();
}


void CMainFrame::RemoveSlider(long lSlider, CMDIChildWnd * DestroyChild)
{
	BOOL bFound = FALSE;
	CSliderBar  * pSliderBar;

	POSITION oldPos = NULL;
	POSITION pos = m_SliderBarList.GetHeadPosition();
	while(pos != 0){
		oldPos = pos;
		pSliderBar = (CSliderBar  *)m_SliderBarList.GetNext(pos);
		if(pSliderBar == (CSliderBar *)lSlider){
			m_SliderBarList.RemoveAt(oldPos);
			bFound = TRUE;
			break;
		}
	}
	m_bSlided = (m_SliderBarList.GetCount() >= 1) ;

	if(!bFound) return;
	
	CChildFrame * RemoveChild = (CChildFrame *)DestroyChild ;

	CChildFrame * pLChild = (CChildFrame *)pSliderBar->m_leftChild;
	CChildFrame * pRChild = (CChildFrame *)pSliderBar->m_rightChild;
	
	CRect clRect = CRect(pLChild->m_oppChildRect.left, pLChild->m_oppChildRect.top, 
		/*pLChild->m_oppChildRect.left + */pLChild->m_oppChildRect.right + pRChild->m_oppChildRect.right + 7,
		pLChild->m_oppChildRect.bottom);
	//if(m_iCurrWndCnt == 1) clRect.right += (int)clRect.left == -1 ;//ちょっこと調整する

	CChildFrame * clChild = (RemoveChild == pLChild) ? pRChild : pLChild ;//反対面の値をとる
	if(pLChild->m_bLeftMost || pRChild->m_bLeftMost){
		m_leftRect = clRect;
		clChild->m_bLeftMost = TRUE;
		RemoveChild->m_bLeftMost = FALSE;
	}
	clChild->SetWindowPos(&CWnd::wndBottom,clRect.left,clRect.top,clRect.right,clRect.bottom,SWP_DRAWFRAME);
	clChild->m_oppChildRect = clRect;
	if(pSliderBar->m_leftChild == RemoveChild )
		clChild->m_LeftRelatedSliderBar = NULL;
	else{
		if(m_bSlided && RemoveChild->m_RightRelatedSliderBar){
			clChild->m_RightRelatedSliderBar = RemoveChild->m_RightRelatedSliderBar;
			clChild->m_RightRelatedSliderBar->m_leftChild = clChild;
		}
		else
			clChild->m_RightRelatedSliderBar = NULL;
	}
	
	delete pSliderBar;

	AlignLeftUnslideCld();

}


void CMainFrame::RetainTab(void)
{
	CRect ClientRect;
	GetClientRect(&ClientRect);
	m_wndTabBar.SetWindowPos(&CWnd::wndTop,
		ClientRect.left,ClientRect.top+24,ClientRect.right-ClientRect.left,24,SWP_DRAWFRAME);
    CRect rcTab;
    m_wndTabBar.GetClientRect(&rcTab);
	CTabCtrl *pMyTab=(CTabCtrl *)(m_wndTabBar.GetDlgItem(IDC_TAB));
	pMyTab->MoveWindow(rcTab,TRUE);
}

