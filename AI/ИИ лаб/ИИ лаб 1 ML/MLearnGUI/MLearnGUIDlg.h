// MLearnGUIDlg.h : header file
//

#if !defined(AFX_MLEARNGUIDLG_H__297A18FA_74D2_4706_811C_E2277100449A__INCLUDED_)
#define AFX_MLEARNGUIDLG_H__297A18FA_74D2_4706_811C_E2277100449A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCtrl_src/GridCtrl.h"
#include "Anchor/AnchorMgr.h"

const int BufSize = 257;
const char chSep = '|';
/////////////////////////////////////////////////////////////////////////////
// CMLearnGUIDlg dialog

class CMLearnGUIDlg : public CDialog
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMLearnGUIDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CMLearnGUIDlg();

	CGridCtrl m_grdExamples;

// Dialog Data
	//{{AFX_DATA(CMLearnGUIDlg)
	enum { IDD = IDD_MLEARNGUI_DIALOG };
	//CListCtrl	m_lstExamples;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMLearnGUIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CAnchorMgr m_oAnchor;
	CToolTipCtrl m_tooltip;
	float m_arrWidthAspect[4];
	void OnOK();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMLearnGUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDelete();
	afx_msg void OnClear();
	afx_msg void OnAddExample();
	afx_msg void OnLoadData();
	afx_msg void OnSaveData();
	afx_msg void OnLearn();
	afx_msg void OnDisplay();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChangeFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLEARNGUIDLG_H__297A18FA_74D2_4706_811C_E2277100449A__INCLUDED_)
