// AnchorMgr.h: interface for the CAnchorMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANCHORMGR_H__C98F8005_34B1_4FA7_8BA4_8254D5549D5A__INCLUDED_)
#define AFX_ANCHORMGR_H__C98F8005_34B1_4FA7_8BA4_8254D5549D5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
	Delphi-kind anchors class.
	(C) Copyright 2004 by Baksheyev T.
*/
#include <vector>
#include <windows.h>

const UCHAR Anchor_None   = 0;
const UCHAR Anchor_Left   = 1;
const UCHAR Anchor_Top    = 2;
const UCHAR Anchor_Right  = 4;
const UCHAR Anchor_Bottom = 8;
const UCHAR Anchor_Horiz = Anchor_Left | Anchor_Right;
const UCHAR Anchor_Vert = Anchor_Top | Anchor_Bottom;
const UCHAR Anchor_All = 15;

class CAnchorMgr  
{
public:
	// construction/destruction ///////////////////////////////////
	CAnchorMgr();
	CAnchorMgr(CWnd *p_ptrParentWnd);
	virtual ~CAnchorMgr();

	// attributes /////////////////////////////////////////////////
	// setting parent
	void SetParent(CWnd *p_ptrParentWnd);
	/* adding control to the vector of controls which should be
		repositioned when parent window resized */
	void AddControl(HWND p_hCtrlWnd, UCHAR p_Anchors = Anchor_All);
	// when control is moved its distances must be recalculated
	void MovedControl(HWND p_hCtrlWnd);

	// this function should be called when parent window resized
	void OnParentResize(int p_iNewWidth, int p_iNewHeight);

protected:
	// controls' parent window
	CWnd *m_ptrParentWnd;
	// size of the parent window
	int m_cyParent; // height
	int m_cxParent; // width
	// anchor for any control
	struct TAnchor{		
		HWND m_hCtrlWnd; // window handler of the control
		UCHAR m_Anchors; // set of the anchors
		RECT m_Distance; // distances
		float m_ScaleX, // ratio betweeen parent width & control's centerX
				m_ScaleY; // ratio betweeen parent height & control's centerY
	};
	// anchor vector type
	typedef std::vector <TAnchor> TAnchorVec;
	// vector of anchors
	TAnchorVec m_vecAnchors;
};

#endif // !defined(AFX_ANCHORMGR_H__C98F8005_34B1_4FA7_8BA4_8254D5549D5A__INCLUDED_)
