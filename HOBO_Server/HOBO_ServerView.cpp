// HOBO_ServerView.cpp : CHOBO_ServerView クラスの実装
//

#include "stdafx.h"
#include "HOBO_Server.h"
#include "MainFrm.h"

#include "HOBO_ServerDoc.h"
#include "HOBO_ServerView.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHOBO_ServerView

IMPLEMENT_DYNCREATE(CHOBO_ServerView, CEditView)

BEGIN_MESSAGE_MAP(CHOBO_ServerView, CEditView)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CHOBO_ServerView コンストラクション/デストラクション

CHOBO_ServerView::CHOBO_ServerView()
{
	// TODO: 構築コードをここに追加します。

}

CHOBO_ServerView::~CHOBO_ServerView()
{
	((CMainFrame*)AfxGetMainWnd())->m_ViewManager.RemoveView(this);
}

void CHOBO_ServerView::DoDataExchange(CDataExchange* pDX)
{
	CEditView::DoDataExchange(pDX);
}

BOOL CHOBO_ServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CEditView::PreCreateWindow(cs);
}

void CHOBO_ServerView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CHOBO_ServerDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CString cs=pDoc->GetTitle();
	CMainFrame * pMain = ((CMainFrame*)AfxGetMainWnd());
	//CChildFrame * pChild = (CChildFrame*)this->GetParentFrame();
	//if(pChild->m_wndSplitter.GetRowCount() == 1 && pChild->m_wndSplitter.GetColumnCount() == 1)
		
	pMain->m_ViewManager.AddView(cs,this);
}


// CHOBO_ServerView 診断

#ifdef _DEBUG
void CHOBO_ServerView::AssertValid() const
{
	CEditView::AssertValid();
}

void CHOBO_ServerView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CHOBO_ServerDoc* CHOBO_ServerView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHOBO_ServerDoc)));
	return (CHOBO_ServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CHOBO_ServerView メッセージ ハンドラ

void CHOBO_ServerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CChildFrame * pChildFrame = (CChildFrame*)this->GetParentFrame();
	CMainFrame * pMainFrame = (CMainFrame*)pChildFrame->GetMDIFrame();
	
	if(pMainFrame->m_bSliding) {
		//if(pChildFrame->m_parentPoint.x > pChildFrame->m_oppChildRect.right)//左
		//if(pChildFrame->m_sSpcDes.Compare("l") == 0){
			//TRACE2("des: %d,%d;", pChildFrame->m_oppChildRect.left + point.x, point.y);
		if(pMainFrame->m_bRightMostSliding){
			CChildFrame * pRChild = NULL;
			CChildFrame * pLChild = (CChildFrame *)(( (CHOBO_ServerView *)(pMainFrame->m_ViewManager.arViews.GetAt(pMainFrame->m_SliderBarList.GetCount())) )->GetParentFrame());
			if(pMainFrame->m_ViewManager.arViews.GetCount() - 2 >= (pMainFrame->m_SliderBarList.GetCount()) )
				pRChild = (CChildFrame *)(( (CHOBO_ServerView *)(pMainFrame->m_ViewManager.arViews.GetAt(pMainFrame->m_SliderBarList.GetCount() + 1)) )->GetParentFrame());
			
			pMainFrame->Slide(pLChild,pRChild);
		}
		else
			pMainFrame->SendMessage(WM_SLIDE_END,(long)pChildFrame,pChildFrame->m_oppChildRect.left + point.x);
			
		pMainFrame->m_bSliding = FALSE;//メインフォルムから移転した

		//}
		//if((pChildFrame->m_parentPoint.x > pChildFrame->m_oppChildRect.left)//右
		//if(pChildFrame->m_sSpcDes.Compare("r") == 0){
		//	//TRACE2("des: %d,%d\r\n", pChildFrame->m_oppChildRect.left + point.x, point.y);
		//	pMainFrame->SendMessage(WM_SLIDE_END,0,
		//		pChildFrame->m_oppChildRect.left + point.x);
		//}
		
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}

	CEditView::OnLButtonUp(nFlags, point);
}

void CHOBO_ServerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CChildFrame * pChildFrame = (CChildFrame*)(this->GetParentFrame());
	CMainFrame * pMainFrame = (CMainFrame*)pChildFrame->GetMDIFrame();
	if(pMainFrame->m_bSliding) {
		HCURSOR hcur = AfxGetApp()->LoadCursor(IDC_MOUSE_OVER);
		SetCursor(hcur);
	}


	CEditView::OnMouseMove(nFlags, point);
}
