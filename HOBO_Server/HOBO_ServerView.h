// HOBO_ServerView.h : CHOBO_ServerView クラスのインターフェイス
//


#pragma once


class CHOBO_ServerView : public CEditView
{
protected: // シリアル化からのみ作成します。
	CHOBO_ServerView();
	DECLARE_DYNCREATE(CHOBO_ServerView)

public:
	enum{ IDD = IDD_HOBO_SERVER_FORM };

// 属性
public:
	CHOBO_ServerDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void OnInitialUpdate(); // 構築後に初めて呼び出されます。

// 実装
public:
	virtual ~CHOBO_ServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // HOBO_ServerView.cpp のデバッグ バージョン
inline CHOBO_ServerDoc* CHOBO_ServerView::GetDocument() const
   { return reinterpret_cast<CHOBO_ServerDoc*>(m_pDocument); }
#endif

