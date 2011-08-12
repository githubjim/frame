// SliderBar.cpp : 実装ファイル
//

#include "stdafx.h"
#include "HOBO_Server.h"
#include "SliderBar.h"

#include "MainFrm.h"

// CSliderBar ダイアログ

IMPLEMENT_DYNAMIC(CSliderBar, CDialog)

CSliderBar::CSliderBar(CWnd* pParent /*=NULL*/)

{
	m_bRightMost = FALSE;

}

CSliderBar::~CSliderBar()
{
}

void CSliderBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSliderBar, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CSliderBar メッセージ ハンドラ

void CSliderBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CMainFrame * pMain = ((CMainFrame*)this->GetParent());
	pMain->m_bSliding = m_bSliding = TRUE;
	
	pMain->m_bRightMostSliding = m_bRightMost;

	HCURSOR hDragCursor = AfxGetApp()->LoadCursor(IDC_MOUSE_OVER);
	SetCursor(hDragCursor);

	CDialog::OnLButtonDown(nFlags, point);
}

void CSliderBar::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	HCURSOR hDragCursor = AfxGetApp()->LoadCursor(IDC_MOUSE_OVER);
    SetCursor(hDragCursor);

	CDialog::OnMouseMove(nFlags, point);
}
