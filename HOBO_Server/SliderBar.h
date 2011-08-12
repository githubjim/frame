#pragma once


// CSliderBar ダイアログ

class CSliderBar : public CDialog
{
	DECLARE_DYNAMIC(CSliderBar)

public:
	CSliderBar(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSliderBar();

// ダイアログ データ
//	enum { IDD = IDD_SLIDE_BAR };

public:
	CPoint m_srcPoint;
	CPoint m_desPoint;
	CPoint m_parentPoint;

	BOOL m_bSliding;
	CMDIChildWnd * m_leftChild;
	CMDIChildWnd * m_rightChild;
	CRect m_oppSliderRect;
	BOOL m_bRightMost;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

public:

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
