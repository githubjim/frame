#pragma once


// CHBTab

class CHBTab : public CTabCtrl
{
	DECLARE_DYNAMIC(CHBTab)

public:
	CHBTab();
	virtual ~CHBTab();

protected:
	//{{AFX_MSG(CMyTab)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


