// HBTab.cpp : 実装ファイル
//

#include "stdafx.h"
#include "HOBO_Server.h"
#include "HBTab.h"


// CHBTab

IMPLEMENT_DYNAMIC(CHBTab, CTabCtrl)

CHBTab::CHBTab()
{

}

CHBTab::~CHBTab()
{
}


BEGIN_MESSAGE_MAP(CHBTab, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTab)
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// CHBTab メッセージ ハンドラ

void CHBTab::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int idx = GetCurSel();

	TC_ITEM ti;
	ti.mask = TCIF_PARAM;
	GetItem(idx, &ti);
	CView * pView = (CView *) ti.lParam;
	//((CMDIFrameWnd *)AfxGetMainWnd())->MDIActivate((pView->GetParent())->GetParent());
	
	// maximize or restore MDIChild window based on its current state
	BOOL bMaximize=FALSE;
	//CWnd* pActiveWnd=((CMDIFrameWnd *)AfxGetMainWnd())->MDIGetActive(&bMaximize);
	//if(bMaximize)
	//	((CMDIFrameWnd *)AfxGetMainWnd())->MDIRestore(pActiveWnd);
	//else
	//	((CMDIFrameWnd *)AfxGetMainWnd())->MDIMaximize(pActiveWnd);
}

void CHBTab::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int idx = GetCurSel();
	TC_ITEM ti;
	ti.mask = TCIF_PARAM;


	//LOGFONT lFont;
	//this->GetFont()->GetLogFont(&lFont);
	//lFont.lfWeight = FW_BOLD;
	//CFont font;
	//font.CreateFontIndirect(&lFont);


	//this->SetFont(&font);

	GetItem(idx, &ti);
	CView * pView = (CView *) ti.lParam;
	((CMDIFrameWnd *)AfxGetMainWnd())->MDIActivate(pView->GetParentFrame());
	*pResult = 0;
	*pResult = 0;
}

