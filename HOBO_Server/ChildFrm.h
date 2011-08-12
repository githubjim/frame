// ChildFrm.h : CChildFrame �N���X�̃C���^�[�t�F�C�X
//


#pragma once


class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// ����
protected:

public:
	//CSplitterWnd m_wndSplitter;
	CRect m_oppChildRect;//���C���̒��Ɉʒu
	BOOL m_bLeftMost;
	CSliderBar * m_LeftRelatedSliderBar;
	CSliderBar * m_RightRelatedSliderBar;
	CString m_tabTitle;

// ����
public:

// �I�[�o�[���C�h
	public:
	public:
//	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void ActivateFrame(int nCmdShow = -1);
	virtual BOOL DestroyWindow();
//	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
