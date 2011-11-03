// DFVFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "DFVFrameWnd.h"
#include "DFVDocTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDFVFrameWnd

IMPLEMENT_DYNCREATE(CDFVFrameWnd, CFrameWnd)

CDFVFrameWnd::CDFVFrameWnd()
{
}

CDFVFrameWnd::~CDFVFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CDFVFrameWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CDFVFrameWnd)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDFVFrameWnd message handlers
BOOL CDFVFrameWnd::DFVLoadFrame(UINT nIDResource,
				DWORD dwDefaultStyle, CRect rect,
				CWnd* pParentWnd, DWORD dwDefaultStyleEx, 
				CCreateContext* pContext)
{
	// only do this once
//	ASSERT_VALID_IDR(nIDResource);
	ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

	m_nIDHelp = nIDResource;    // ID for help context (+HID_BASE_RESOURCE)

	CString strFullString;
	if (strFullString.LoadString(nIDResource))
		AfxExtractSubString(m_strTitle, strFullString, 0);    // first sub-string

//	VERIFY(AfxDeferRegisterClass(AFX_WNDFRAMEORVIEW_REG));

	// attempt to create the window
	LPCTSTR lpszClass = GetIconWndClass(dwDefaultStyle, nIDResource);
	LPCTSTR lpszTitle = m_strTitle;
	if (!Create(lpszClass, lpszTitle, dwDefaultStyle, rect,
	  pParentWnd, MAKEINTRESOURCE(nIDResource), dwDefaultStyleEx, pContext))
	{
		return FALSE;   // will self destruct on failure normally
	}

	// save the default menu handle
	ASSERT(m_hWnd != NULL);
	m_hMenuDefault = ::GetMenu(m_hWnd);

	// load accelerator resource
	LoadAccelTable(MAKEINTRESOURCE(nIDResource));

//	if (pContext == NULL)   // send initial update
//		SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);

	return TRUE;
}


void CDFVFrameWnd::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CString newName;
	CDFVDocTemplate * pTemplate = (CDFVDocTemplate *) GetActiveDocument()->GetDocTemplate();

	if (!pTemplate->DoPromptFileName(newName, AFX_IDS_OPENFILE,
	  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE))
		return; // open cancelled

	pTemplate->OpenDocumentFile(newName);
}

void CDFVFrameWnd::OnFileNew() 
{
	// TODO: Add your command handler code here
	CDFVDocTemplate * pTemplate = (CDFVDocTemplate *) GetActiveDocument()->GetDocTemplate();
	pTemplate->OpenDocumentFile(NULL);
}
