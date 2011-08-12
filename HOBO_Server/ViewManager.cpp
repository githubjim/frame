#include "StdAfx.h"
#include "ViewManager.h"
#include "MainFrm.h"
#include "HBTab.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CViewManager::CViewManager()
{
	bClosing = false;
}

CViewManager::~CViewManager()
{
	arViews.RemoveAll();
	arViewTitles.RemoveAll();
}

void CViewManager::AddView(const char * csName, CView * pView)
{
	if (bClosing) return;

	CString cs(csName);

	arViews.Add(pView);
	arViewTitles.Add(cs);
	if ( ((CMainFrame*)AfxGetMainWnd())->m_HBTab.GetSafeHwnd())
	{
		TC_ITEM ti;
		ti.mask = TCIF_TEXT|TCIF_PARAM;
		ti.pszText = cs.LockBuffer();
		ti.lParam = (long) pView;
		   ((CMainFrame*)AfxGetMainWnd())->m_HBTab.InsertItem(   ((CMainFrame*)AfxGetMainWnd())->m_HBTab.GetItemCount(), &ti);
		cs.UnlockBuffer();
		((CMainFrame*)AfxGetMainWnd())->m_HBTab.SetMinTabWidth(110);

		OnActivateView(TRUE, pView);
	}
}

void CViewManager::RemoveView(CView * pView)
{
	if (bClosing || arViews.GetSize() <= 0) return;

	int t;

	if (   ((CMainFrame*)AfxGetMainWnd())->m_HBTab.GetSafeHwnd())
	{
		for (t = 0; t <    ((CMainFrame*)AfxGetMainWnd())->m_HBTab.GetItemCount(); t++)
		{
			TC_ITEM ti;
			ti.mask = TCIF_PARAM;
			   ((CMainFrame*)AfxGetMainWnd())->m_HBTab.GetItem(t, &ti);
			if (ti.lParam == (long) pView)
			{
				   ((CMainFrame*)AfxGetMainWnd())->m_HBTab.DeleteItem(t);
				break;
			}
		}
	}


	for (t = 0; t < arViews.GetSize(); t++)
	{
		if ((CView *)(arViews.GetAt(t)) == pView)
		{
			arViewTitles.RemoveAt(t);
			arViews.RemoveAt(t);
			return;
		}
	}
}

void CViewManager::RemoveAll()
{
	arViews.RemoveAll();
	arViewTitles.RemoveAll();
}



void CViewManager::OnActivateView(const BOOL bActivate, CView * pView)
{
	if (bActivate)
	{
		if (   ((CMainFrame*)AfxGetMainWnd())->m_HBTab.GetSafeHwnd())
		{
			for (int t = 0; t <    ((CMainFrame*)AfxGetMainWnd())->m_HBTab.GetItemCount(); t++)
			{
				TC_ITEM ti;
				ti.mask = TCIF_PARAM;
				   ((CMainFrame*)AfxGetMainWnd())->m_HBTab.GetItem(t, &ti);
				if (ti.lParam == (long) pView)
				{
					   ((CMainFrame*)AfxGetMainWnd())->m_HBTab.SetCurSel(t);
					   ((CMainFrame*)AfxGetMainWnd())->m_HBTab.Invalidate();
					break;
				}
			}
		}
	}
}
