// MainFrm.h : CMainFrame クラスのインターフェイス
//


#pragma once

#include "HBTab.h"
#include "ViewManager.h"
#include "SliderBar.h"
#include "ChildFrm.h"

#define WM_SLIDE_END WM_USER+1 //a sliding end

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 属性
public:
	CRect m_leftRect;
	BOOL m_bSliding;////ドラッグしてるか
	int m_iCurrWndCnt;
	BOOL m_bSlided;
	CRect m_OldClientRect;
	BOOL m_bRightMostSliding;
	CPtrList m_SliderBarList;
	CHBTab m_HBTab;
    CViewManager m_ViewManager;

// 操作
public:
	int Slide(CMDIChildWnd* pLeftChild, CMDIChildWnd* pRightChild, BOOL bEqual = FALSE, BOOL bMostRight = TRUE);

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 実装
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // コントロール バー用メンバ
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
    CDialog  m_wndTabBar;
	CSliderBar m_RightMostBar;

// 生成された、メッセージ割り当て関数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSlideEnd(WPARAM w, LPARAM l);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	void RemoveSlider(long lSlider, CMDIChildWnd * DestroyChild);

private:
	void ToolbarImgChange(int iDest, int iSrc);
	void EquShow();
	void AlignLeftUnslideCld();
	CMDIChildWnd * FindLeftMostCld();
	void ClearSliderBarList(void);
	void RetainTab(void);

public:
	virtual void GetMessageString(UINT nID, CString& rMessage) const;
private:
	BOOL m_bLANState;
	BOOL m_bChatState;
public:
	afx_msg void OnUpdateLanState(UINT nID);
	afx_msg void OnSideWndSelect(UINT nID);
	afx_msg void OnUpdateMainViewState(UINT nID);
	afx_msg void OnUpdateDesktopState(UINT nID);
	afx_msg void OnUpdateListState(UINT nID);
	afx_msg void OnUpdateSortState(UINT nID);
	afx_msg void OnUpdateGroupState(UINT nID);
	afx_msg void OnUpdateStandState(UINT nID);
	afx_msg void OnUpdateChatState(UINT nID);
	afx_msg void OnIphoneShare();
	afx_msg void OnGroupSet();
	afx_msg void OnPartnerRecruit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
//	virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
};


