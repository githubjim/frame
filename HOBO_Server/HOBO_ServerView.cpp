// HOBO_ServerView.cpp : CHOBO_ServerView �N���X�̎���
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

// CHOBO_ServerView �R���X�g���N�V����/�f�X�g���N�V����

CHOBO_ServerView::CHOBO_ServerView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

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
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

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


// CHOBO_ServerView �f�f

#ifdef _DEBUG
void CHOBO_ServerView::AssertValid() const
{
	CEditView::AssertValid();
}

void CHOBO_ServerView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CHOBO_ServerDoc* CHOBO_ServerView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHOBO_ServerDoc)));
	return (CHOBO_ServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CHOBO_ServerView ���b�Z�[�W �n���h��

void CHOBO_ServerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	CChildFrame * pChildFrame = (CChildFrame*)this->GetParentFrame();
	CMainFrame * pMainFrame = (CMainFrame*)pChildFrame->GetMDIFrame();
	
	if(pMainFrame->m_bSliding) {
		//if(pChildFrame->m_parentPoint.x > pChildFrame->m_oppChildRect.right)//��
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
			
		pMainFrame->m_bSliding = FALSE;//���C���t�H��������ړ]����

		//}
		//if((pChildFrame->m_parentPoint.x > pChildFrame->m_oppChildRect.left)//�E
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
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	CChildFrame * pChildFrame = (CChildFrame*)(this->GetParentFrame());
	CMainFrame * pMainFrame = (CMainFrame*)pChildFrame->GetMDIFrame();
	if(pMainFrame->m_bSliding) {
		HCURSOR hcur = AfxGetApp()->LoadCursor(IDC_MOUSE_OVER);
		SetCursor(hcur);
	}


	CEditView::OnMouseMove(nFlags, point);
}
