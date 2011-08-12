#pragma once

class CViewManager
{
public:
	CViewManager();
	virtual ~CViewManager();

public:
	void OnActivateView(const BOOL bActivate, CView * pView);
	void RemoveAll();
	void RemoveView(CView * pView);
	void AddView(const char * csName, CView * pView);

	CPtrArray		arViews;
	CStringArray	arViewTitles;

	bool			bClosing;

};
