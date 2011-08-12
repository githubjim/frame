// HOBO_ServerView.h : CHOBO_ServerView �N���X�̃C���^�[�t�F�C�X
//


#pragma once


class CHOBO_ServerView : public CEditView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CHOBO_ServerView();
	DECLARE_DYNCREATE(CHOBO_ServerView)

public:
	enum{ IDD = IDD_HOBO_SERVER_FORM };

// ����
public:
	CHOBO_ServerDoc* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void OnInitialUpdate(); // �\�z��ɏ��߂ČĂяo����܂��B

// ����
public:
	virtual ~CHOBO_ServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // HOBO_ServerView.cpp �̃f�o�b�O �o�[�W����
inline CHOBO_ServerDoc* CHOBO_ServerView::GetDocument() const
   { return reinterpret_cast<CHOBO_ServerDoc*>(m_pDocument); }
#endif

