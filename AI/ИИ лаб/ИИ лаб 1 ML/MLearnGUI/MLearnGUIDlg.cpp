// MLearnGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MLearnGUI.h"
#include "MLearnGUIDlg.h"
#include "NewCellType/GridCellCheck.h"
#include "ML.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
char szBuf[BufSize]; // lines read buffer
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMLearnGUIDlg dialog

CMLearnGUIDlg::CMLearnGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMLearnGUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMLearnGUIDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMLearnGUIDlg::~CMLearnGUIDlg()
{
	if (must)
		delete []must;
	if (may)
		delete []may;
}

void CMLearnGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMLearnGUIDlg)
	DDX_Control(pDX, IDC_GRID, m_grdExamples);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMLearnGUIDlg, CDialog)
	//{{AFX_MSG_MAP(CMLearnGUIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_ADD, OnAddExample)
	ON_BN_CLICKED(IDC_LOAD_DATA, OnLoadData)
	ON_BN_CLICKED(IDC_SAVE_DATA, OnSaveData)
	ON_BN_CLICKED(IDC_LEARN, OnLearn)
	ON_BN_CLICKED(IDC_DISPLAY, OnDisplay)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHANGE_FONT, OnChangeFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMLearnGUIDlg message handlers

BOOL CMLearnGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	MAX = 100;
	may = NULL;
	must = NULL;
	/*may = new attr[MAX];
	must = new attr[MAX];*/
	
	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), "<text>");
		m_tooltip.AddTool(GetDlgItem(IDCANCEL), "quit from the application");
		m_tooltip.AddTool(GetDlgItem(IDC_ADD), "add new example");
		m_tooltip.AddTool(GetDlgItem(IDC_DELETE), "delete selected example");
		m_tooltip.AddTool(GetDlgItem(IDC_CLEAR), "clear example list");
		m_tooltip.AddTool(GetDlgItem(IDC_LOAD_DATA), "load examples from file");
		m_tooltip.AddTool(GetDlgItem(IDC_SAVE_DATA), "save examples to file");
	}

	// examples grid initialization
	m_grdExamples.SetColumnCount(4);
	m_grdExamples.SetRowCount(1);
	m_grdExamples.SetFixedRowCount();
	m_grdExamples.SetFixedColumnCount(0);
	m_grdExamples.SetColumnResize(FALSE);
	m_grdExamples.SetRowResize(FALSE);
	m_grdExamples.SetSingleColSelection();
	m_grdExamples.SetColumnWidth(0, 25);
	m_grdExamples.SetColumnWidth(1, 85);
	m_grdExamples.SetColumnWidth(2, 120);
	m_grdExamples.SetColumnWidth(3, 90);
	RECT rct;
	m_grdExamples.GetClientRect(&rct);
	float fltWidth = rct.right - 25;
	m_arrWidthAspect[1] = 85.f/fltWidth;
	m_arrWidthAspect[2] = 120.f/fltWidth;
	m_arrWidthAspect[3] = 90.f/fltWidth;
	m_grdExamples.GetCell(0, 0)->SetText("Hit");
	m_grdExamples.GetCell(0, 1)->SetText("Subject");
	m_grdExamples.GetCell(0, 2)->SetText("Verb");
	m_grdExamples.GetCell(0, 3)->SetText("Object");
	//m_grdExamples.SetCellType(1, 0, RUNTIME_CLASS(CGridCellCheck));
	// anchors
	m_oAnchor.SetParent(this);
	m_oAnchor.AddControl(GetDlgItem(IDC_GRID)->m_hWnd);
	m_oAnchor.AddControl(GetDlgItem(IDC_DISPLAY)->m_hWnd, Anchor_Right|Anchor_Top);
	m_oAnchor.AddControl(GetDlgItem(IDC_LEARN)->m_hWnd, Anchor_Right|Anchor_Top);
	m_oAnchor.AddControl(GetDlgItem(IDCANCEL)->m_hWnd, Anchor_Right|Anchor_Bottom);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMLearnGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMLearnGUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMLearnGUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMLearnGUIDlg::OnOK()
{
}

BOOL CMLearnGUIDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

void CMLearnGUIDlg::OnDelete() 
{
	CCellRange &sel = m_grdExamples.GetSelectedCellRange();
		
	int iRowLow = sel.GetMinRow(),
		iRowHigh = sel.GetMaxRow();
	
	for (int i=iRowLow; i<=iRowHigh; i++)
		m_grdExamples.DeleteRow(iRowLow);
	// automatic redrawing isn't performed
	m_grdExamples.Invalidate(FALSE);
	// updating interface state
	if (m_grdExamples.GetRowCount()<=1){
		GetDlgItem(IDC_LEARN)->EnableWindow(FALSE);
		GetDlgItem(IDC_DISPLAY)->EnableWindow(FALSE);
	}
}

void CMLearnGUIDlg::OnClear() 
{
	//m_lstExamples.DeleteAllItems();
	m_grdExamples.SetRowCount(1);
	// updating interface state
	GetDlgItem(IDC_LEARN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISPLAY)->EnableWindow(FALSE);
}

void CMLearnGUIDlg::OnAddExample() 
{
	int iRow = m_grdExamples.InsertRow(NULL);
	m_grdExamples.SetCellType(iRow, 0, RUNTIME_CLASS(CGridCellCheck));
	m_grdExamples.Invalidate(FALSE);

	GetDlgItem(IDC_LEARN)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISPLAY)->EnableWindow(FALSE);
}

void CMLearnGUIDlg::OnLoadData() 
{
	CFileDialog dlg(TRUE, "lxm", NULL, OFN_ENABLESIZING|OFN_PATHMUSTEXIST,
			"Learning example files (*.lxm)|*.lxm|All files (*.*)|*.*||");

	char szTitle[]="Select file to load the data";
	dlg.m_ofn.lpstrTitle = szTitle;
	if (dlg.DoModal()!=IDOK)
		return;

	// opening the file
	FILE *f = fopen(LPCSTR(dlg.GetFileName()), "r+t");
	if (f==NULL){
		MessageBox("Cannot open learning example file.", NULL,
				MB_OK|MB_ICONSTOP);
		return;
	}

	BeginWaitCursor();

	// clearing examples list
	m_grdExamples.SetRowCount(1);
	
	int iBufActualSize, // size of the data which was read
			iStart, // begin of the current field in record
			iRow, iCol,
			i;	
	// loading data from file	
	while (!feof(f)){
		if(!fgets(szBuf, BufSize-2, f))
			break;
		iBufActualSize = strlen((const char*)szBuf);
		if (!iBufActualSize || szBuf[0]=='\n')
			continue;
		
		if (szBuf[iBufActualSize-1]=='\n')
			szBuf[iBufActualSize-1] = chSep;
		else{
			szBuf[iBufActualSize] = chSep;
			szBuf[iBufActualSize+1] = '\0';
			iBufActualSize++;
		}

		iRow = m_grdExamples.InsertRow(NULL);
		m_grdExamples.SetCellType(iRow, 0, RUNTIME_CLASS(CGridCellCheck));
		
		// determining example type
		for (i=0; i<iBufActualSize; i++)
			if (szBuf[i]=='1' || szBuf[i]=='Y' || szBuf[i]=='y'){ // Hit
				((CGridCellCheck*)
					(m_grdExamples.GetCell(iRow, 0)))->SetCheck();
				break;
			}
			else if (szBuf[i]=='0' || szBuf[i]=='N' || szBuf[i]=='n'){ // Near-miss
				((CGridCellCheck*)
					(m_grdExamples.GetCell(iRow, 0)))->SetCheck(FALSE);
				break;
			}
		iCol = 1;
		while (szBuf[i++]!='|');			
		iStart = i;
		// subject, verb & object...		
		for (; i<iBufActualSize && iCol<4; i++)
			if (szBuf[i]==chSep){
				szBuf[i] = '\0';
				m_grdExamples.GetCell(iRow, iCol)->SetText((szBuf+iStart));
				iStart = i+1;
				iCol++;
				szBuf[i] = chSep;
			}
	}

	fclose(f);

	// updating interface state
	if (m_grdExamples.GetRowCount()>1){
		GetDlgItem(IDC_LEARN)->EnableWindow(TRUE);
		GetDlgItem(IDC_DISPLAY)->EnableWindow(FALSE);
	}

	EndWaitCursor();
	m_grdExamples.Invalidate(FALSE);
}

void CMLearnGUIDlg::OnSaveData() 
{
	CFileDialog dlg(FALSE, "lxm", NULL, OFN_ENABLESIZING|OFN_OVERWRITEPROMPT,
			"Learning example files (*.lxm)|*.lxm|All files (*.*)|*.*||");

	char szTitle[]="Select file to save the data";
	dlg.m_ofn.lpstrTitle = szTitle;
	if (dlg.DoModal()!=IDOK)
		return;

	// opening the file
	FILE *f = fopen(LPCSTR(dlg.GetFileName()), "w+t");
	if (f==NULL){
		MessageBox("Cannot open learning example file.", NULL,
				MB_OK|MB_ICONSTOP);
		return;
	}

	int i,		
		nExamples = m_grdExamples.GetRowCount()-1;
	
	BeginWaitCursor();
	
	for (i=1; i<=nExamples; i++){
		// example type
		fprintf(f, "%i|", ((CGridCellCheck*)
					(m_grdExamples.GetCell(i, 0)))->GetCheck());
		// subject
		fprintf(f, "%s|", m_grdExamples.GetCell(i, 1)->GetText());
		// verb
		fprintf(f, "%s|", m_grdExamples.GetCell(i, 2)->GetText());
		// object
		fprintf(f, "%s\n", m_grdExamples.GetCell(i, 3)->GetText());
	}

	EndWaitCursor();
}

void CMLearnGUIDlg::OnLearn() 
{
	if (may)
		delete []may;
	if (must)
		delete []must;
	MAX = m_grdExamples.GetRowCount()-1;
	if (MAX==0)
		return;
	may = new attr[MAX];
	must = new attr[MAX];
	may_pos = 0; must_pos = 0;

	int i;
	//char sub[80], verb[80], obj[80];
	char *sub, *verb, *obj;

	for (i=1; i<=MAX; i++){
		BOOL bHit = ((CGridCellCheck*)
				(m_grdExamples.GetCell(i, 0)))->GetCheck();		
		sub = (char*)m_grdExamples.GetCell(i, 1)->GetText();
		verb = (char*)m_grdExamples.GetCell(i, 2)->GetText();
		obj = (char*)m_grdExamples.GetCell(i, 3)->GetText();
		if (bHit){// Hit
			if (find_may(sub,verb,obj)==-1){
				assert_may (sub,verb,obj);
				generalize (sub,verb,obj);
			}
		}
		else{ // Near-miss
			restrict(sub,verb,obj);
		}
	}
	GetDlgItem(IDC_DISPLAY)->EnableWindow(TRUE);
}

void CMLearnGUIDlg::OnDisplay() 
{
	CListBox* pList = (CListBox*)GetDlgItem(IDC_KNOWLEDGE_LIST);

	if (pList->IsWindowVisible()){
		GetDlgItem(IDC_ADD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CLEAR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DELETE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LOAD_DATA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SAVE_DATA)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_DISPLAY, "&Display");
		pList->ShowWindow(SW_HIDE);
		//pList->MoveWindow(1, 1, 10, 10, FALSE);
		::MoveWindow(pList->m_hWnd, 1, 1, 10, 10, FALSE);
		GetDlgItem(IDC_LEARN)->EnableWindow(TRUE);
		m_grdExamples.ShowWindow(SW_SHOW);
		return;
	}
	SetDlgItemText(IDC_DISPLAY, "&Hide");

	BeginWaitCursor();
	
	CString sBuffer;
	int i;

	pList->ResetContent();

	pList->InsertString(-1, "----------May have :----------");
	for (i=0; i < may_pos; i++)
		if (may[i].active)
		{
			sBuffer.Format(" %s %s %s", may[i].subject,		
					may[i].verb,may[i].object);
			pList->InsertString(-1, sBuffer);
		};

	//printf("\n\n Must have :");
	pList->InsertString(-1, "----------Must have :----------");

	for (i=0; i<must_pos; i++)
	{
		/*printf("\n %s %s %s", must[i].subject,must[i].verb,
				must[i].object);*/
		sBuffer.Format(" %s %s %s", must[i].subject,must[i].verb,
				must[i].object);
		pList->InsertString(-1, sBuffer);
	};

	// updating interface
	m_grdExamples.ShowWindow(SW_HIDE);
	CRect rect;	
	m_grdExamples.GetWindowRect(LPRECT(rect));		
	ScreenToClient(LPRECT(rect));
	pList->MoveWindow(&rect, FALSE);	
	pList->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LEARN)->EnableWindow(FALSE);

	GetDlgItem(IDC_ADD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CLEAR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DELETE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LOAD_DATA)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_SAVE_DATA)->ShowWindow(SW_HIDE);

	EndWaitCursor();
}

void CMLearnGUIDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	m_oAnchor.OnParentResize(cx, cy);

	if (!m_grdExamples.GetSafeHwnd())
		return;
	RECT rct;
	m_grdExamples.GetClientRect(&rct);
	rct.right -= 25;
	int i, iWidth;
	for (i=1; i<=3; i++){
		iWidth = m_arrWidthAspect[i]*float(rct.right)+.5f;
		if (iWidth>3)
			m_grdExamples.SetColumnWidth(i, iWidth);
	}
}

void CMLearnGUIDlg::OnChangeFont() 
{
	LOGFONT lf;
	m_grdExamples.GetFont()->GetLogFont(&lf);

	CFontDialog dlg(&lf);
	if (dlg.DoModal() == IDOK) {
		dlg.GetCurrentFont(&lf);

		CFont Font;
		Font.CreateFontIndirect(&lf);
		m_grdExamples.SetFont(&Font);
		/*OnItalics();	
		m_Grid.AutoSize();*/
		//m_grdExamples.AutoSize();
		Font.DeleteObject();	
	}
}
