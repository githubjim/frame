// HOBO_ServerDoc.cpp : CHOBO_ServerDoc �N���X�̎���
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


// CHOBO_ServerDoc �R���X�g���N�V����/�f�X�g���N�V����

CHOBO_ServerDoc::CHOBO_ServerDoc()
{
	// TODO: ���̈ʒu�� 1 �x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CHOBO_ServerDoc::~CHOBO_ServerDoc()
{
}

BOOL CHOBO_ServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)
	CMainFrame * pMain = ((CMainFrame*)AfxGetMainWnd());
	pMain->m_iCurrWndCnt++;

	CString tabTitle;
	tabTitle.Format("Tab%d", pMain->m_iCurrWndCnt-1);
	this->SetTitle(pMain->m_iCurrWndCnt == 1 ? "����" : tabTitle);

	return TRUE;
}




// CHOBO_ServerDoc �V���A����

void CHOBO_ServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �i�[����R�[�h�������ɒǉ����Ă��������B
	}
	else
	{
		// TODO: �ǂݍ��ރR�[�h�������ɒǉ����Ă��������B
	}
}


// CHOBO_ServerDoc �f�f

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


// CHOBO_ServerDoc �R�}���h
