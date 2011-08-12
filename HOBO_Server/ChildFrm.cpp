// ChildFrm.cpp : CChildFrame �N���X�̎���
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


// CChildFrame �R���X�g���N�V����/�f�X�g���N�V����

CChildFrame::CChildFrame()
{
	// TODO: �����o�������R�[�h�������ɒǉ����Ă��������B
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
//		2, 2,			// TODO: �s�Ɨ�̐��𒲐����Ă��������B
//		CSize(10, 10),	// TODO: �ŏ��y�C���̃T�C�Y��ύX���܂��B
//		pContext);
//}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs ��ύX���āAWindow �N���X�܂��̓X�^�C����ύX���܂��B
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	//cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
	//	| FWS_ADDTOTITLE | WS_THICKFRAME;

	cs.style &= ~WS_THICKFRAME;
	cs.style &= ~WS_CAPTION;
	cs.style &= ~WS_BORDER;

	return TRUE;
}


// CChildFrame �f�f

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


// CChildFrame ���b�Z�[�W �n���h��

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �����ɓ���ȍ쐬�R�[�h��ǉ����Ă��������B
	CMainFrame * pMain = (CMainFrame *)GetMDIFrame( );

	CString title;
	title.Format("%s%d","Tab",pMain->m_iCurrWndCnt);
	m_tabTitle = pMain->m_iCurrWndCnt == 1 ? "����" :  title ;

	return 0;
}

void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CMainFrame * pMain = (CMainFrame *)GetMDIFrame( );
	CRect rcClient(pMain->m_OldClientRect);

	//�V���������J���Ƃ��e���̋�Ԃ�S�Đ�߂�
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
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
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

//�ŏ�������Ƃ���
void CChildFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CMDIChildWnd::OnShowWindow(bShow, nStatus);

	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
	CMainFrame * pMain = (CMainFrame *)GetMDIFrame( );

	//������Ԃ�OFF��ݒu
	CMenu * pMainMenu = pMain->GetMenu();
	CMenu * pSubMenu = pMainMenu->GetSubMenu(3);
	CMenu * pSSubMenu = pSubMenu->GetSubMenu(5);
	pSSubMenu->CheckMenuRadioItem(ID_STATE_ONLINE,ID_STATE_OFFLINE,ID_STATE_OFFLINE,MF_BYCOMMAND);
}
