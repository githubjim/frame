// ChildFrm.h : CChildFrame クラスのインターフェイス
//


#pragma once


class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 属性
protected:

public:
	//CSplitterWnd m_wndSplitter;
	CRect m_oppChildRect;//メインの中に位置
	BOOL m_bLeftMost;
	CSliderBar * m_LeftRelatedSliderBar;
	CSliderBar * m_RightRelatedSliderBar;
	CString m_tabTitle;

// 操作
public:

// オーバーライド
	public:
	public:
//	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 実装
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void ActivateFrame(int nCmdShow = -1);
	virtual BOOL DestroyWindow();
//	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
