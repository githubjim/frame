// SliderBar.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "HOBO_Server.h"
#include "SliderBar.h"

#include "MainFrm.h"

// CSliderBar �_�C�A���O

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


// CSliderBar ���b�Z�[�W �n���h��

void CSliderBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	CMainFrame * pMain = ((CMainFrame*)this->GetParent());
	pMain->m_bSliding = m_bSliding = TRUE;
	
	pMain->m_bRightMostSliding = m_bRightMost;

	HCURSOR hDragCursor = AfxGetApp()->LoadCursor(IDC_MOUSE_OVER);
	SetCursor(hDragCursor);

	CDialog::OnLButtonDown(nFlags, point);
}

void CSliderBar::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	HCURSOR hDragCursor = AfxGetApp()->LoadCursor(IDC_MOUSE_OVER);
    SetCursor(hDragCursor);

	CDialog::OnMouseMove(nFlags, point);
}
