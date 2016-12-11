// AnchorMgr.cpp: implementation of the CAnchorMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AnchorMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnchorMgr::CAnchorMgr()
	:m_ptrParentWnd(0)
{
}

CAnchorMgr::CAnchorMgr(CWnd *p_ptrParentWnd)
{
	SetParent(p_ptrParentWnd);
}

CAnchorMgr::~CAnchorMgr()
{
}

//////////////////////////////////////////////////////////////////////

void CAnchorMgr::SetParent(CWnd *p_ptrParentWnd)
{
	m_ptrParentWnd = p_ptrParentWnd;
	CRect rct;
	m_ptrParentWnd->GetClientRect(LPRECT(rct));
	m_cxParent = rct.Width();
	m_cyParent = rct.Height();
}

void CAnchorMgr::AddControl(HWND p_hCtrlWnd,
		unsigned char p_Anchors/* = Anchor_None*/)
{
	if (IsWindow(p_hCtrlWnd) &&
			p_Anchors!=3 /* this anchors (left and top) are already
			supported by windows */){
		TAnchor anc;
		RECT rct;
		GetWindowRect(p_hCtrlWnd, &rct);
		m_ptrParentWnd->ScreenToClient(&rct);
		anc.m_Anchors = p_Anchors;
		anc.m_hCtrlWnd = p_hCtrlWnd;
		anc.m_Distance.left = rct.left;
		anc.m_Distance.top = rct.top;
		anc.m_Distance.right = m_cxParent-rct.right;
		anc.m_Distance.bottom = m_cyParent-rct.bottom;
		anc.m_ScaleX = float(rct.left+rct.right)/2.f/float(m_cxParent);
		anc.m_ScaleY = float(rct.top+rct.bottom)/2.f/float(m_cyParent);
		m_vecAnchors.push_back(anc);
	}
}

void CAnchorMgr::MovedControl(HWND p_hCtrlWnd)
{
	int i=0, iSize = m_vecAnchors.size();
	for (; i<iSize; i++)
		if (m_vecAnchors[i].m_hCtrlWnd==p_hCtrlWnd){
			RECT rct;
			GetWindowRect(p_hCtrlWnd, &rct);
			m_ptrParentWnd->ScreenToClient(&rct);
			m_vecAnchors[i].m_Distance.left = rct.left;
			m_vecAnchors[i].m_Distance.top = rct.top;
			m_vecAnchors[i].m_Distance.right = m_cxParent-rct.right;
			m_vecAnchors[i].m_Distance.bottom = m_cyParent-rct.bottom;
			m_vecAnchors[i].m_ScaleX =
					float(rct.left+rct.right)/2.f/float(m_cxParent);
			m_vecAnchors[i].m_ScaleY =
					float(rct.top+rct.bottom)/2.f/float(m_cyParent);
			break;
		}
	
}

//////////////////////////////////////////////////////////////////////

void CAnchorMgr::OnParentResize(int p_iNewWidth, int p_iNewHeight)
{
	if (!IsWindow(m_ptrParentWnd->GetSafeHwnd()))
		return;

	int i,
			iSize = m_vecAnchors.size(),
			iDeltaX = p_iNewWidth - m_cxParent,
			iDeltaY = p_iNewHeight - m_cyParent;	
	
	TAnchor *pAnchor;	
	CRect rctCtrl(0,0,0,0);
	//POINT point;

//	CString s;
	for (i=0; i<iSize; i++){
		pAnchor = &(m_vecAnchors[i]);
		GetWindowRect(pAnchor->m_hCtrlWnd, LPRECT(rctCtrl));
		m_ptrParentWnd->ScreenToClient(LPRECT(rctCtrl));
		int cxControl = rctCtrl.Width(),
				cyControl = rctCtrl.Height();
		// distance moving
		if ((pAnchor->m_Anchors & Anchor_Horiz)!=0){
			if (pAnchor->m_Anchors & Anchor_Right)
				rctCtrl.right = p_iNewWidth-pAnchor->m_Distance.right;			
			if ((pAnchor->m_Anchors & Anchor_Left)==0)
				rctCtrl.left = rctCtrl.right - cxControl;
			else
				rctCtrl.left = pAnchor->m_Distance.left;			
		}
		else{ // propotional moving
			int iCenterX = float(p_iNewWidth) * pAnchor->m_ScaleX + .5f;
			rctCtrl.left = iCenterX - (cxControl/2);
			rctCtrl.right = rctCtrl.left + cxControl;
		}
		// distance moving
		if ((pAnchor->m_Anchors & Anchor_Vert)!=0){
			if (pAnchor->m_Anchors & Anchor_Bottom)
				rctCtrl.bottom = p_iNewHeight-pAnchor->m_Distance.bottom;
			if ((pAnchor->m_Anchors & Anchor_Top)==0)
				rctCtrl.top = rctCtrl.bottom - cyControl;
			else
				rctCtrl.top = pAnchor->m_Distance.top;
		}
		else{ // propotional moving
			int iCenterY = float(p_iNewHeight) * pAnchor->m_ScaleY + .5f;
			rctCtrl.top = iCenterY - (cyControl/2);
			rctCtrl.bottom = rctCtrl.top + cyControl;
		}

		MoveWindow(pAnchor->m_hCtrlWnd, rctCtrl.left, rctCtrl.top,
				rctCtrl.Width(), rctCtrl.Height(), TRUE);
	}

	m_cxParent = p_iNewWidth;
	m_cyParent = p_iNewHeight;
	m_ptrParentWnd->Invalidate(FALSE);
}