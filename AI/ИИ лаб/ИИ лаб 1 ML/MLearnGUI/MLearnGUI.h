// MLearnGUI.h : main header file for the MLEARNGUI application
//

#if !defined(AFX_MLEARNGUI_H__66F16ED6_57F6_4B28_9BE7_7138133FB00A__INCLUDED_)
#define AFX_MLEARNGUI_H__66F16ED6_57F6_4B28_9BE7_7138133FB00A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMLearnGUIApp:
// See MLearnGUI.cpp for the implementation of this class
//

class CMLearnGUIApp : public CWinApp
{
public:
	CMLearnGUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMLearnGUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMLearnGUIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLEARNGUI_H__66F16ED6_57F6_4B28_9BE7_7138133FB00A__INCLUDED_)
