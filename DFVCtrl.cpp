// DFVCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DFVCtrl.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDFVCtrl

CDFVCtrl::CDFVCtrl()
{
	m_pDocTemplate = NULL;
	m_pParent = NULL;
}

CDFVCtrl::~CDFVCtrl()
{
}


BEGIN_MESSAGE_MAP(CDFVCtrl, CWnd)
	//{{AFX_MSG_MAP(CDFVCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDFVCtrl message handlers

BOOL CDFVCtrl::Create(CWnd *pParent, DWORD ctrlId,
		UINT nIDResource,
		CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass,
		CRuntimeClass* pViewClass,
		DWORD Style, DWORD StyleEx)
{

	m_pParent = pParent;

    SubclassWindow(m_pParent->GetDlgItem(ctrlId)->GetSafeHwnd());

	m_pDocTemplate = new CDFVDocTemplate(
		nIDResource,
		pDocClass,
		pFrameClass,       // main SDI frame window
		pViewClass);

	m_pDocTemplate->m_pParent = pParent;
	
	CRect clientRect;
	GetWindowRect(clientRect);
    m_pParent->ScreenToClient(&clientRect);
	m_pDocTemplate->m_Rect = clientRect;
	
	m_pDocTemplate->m_Style = Style;
	m_pDocTemplate->m_StyleEx = StyleEx;

	m_pDocTemplate->OpenDocumentFile(NULL);
	return TRUE;
}
