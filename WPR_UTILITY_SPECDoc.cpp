// WPR_UTILITY_SPECDoc.cpp : implementation of the CWPR_UTILITY_SPECDoc class
//

#include "stdafx.h"
//#include "WPR_UTILITY_SPEC.h"

#include "WPR_UTILITY_SPECDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITY_SPECDoc

IMPLEMENT_DYNCREATE(CWPR_UTILITY_SPECDoc, CDocument)

BEGIN_MESSAGE_MAP(CWPR_UTILITY_SPECDoc, CDocument)
	//{{AFX_MSG_MAP(CWPR_UTILITY_SPECDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITY_SPECDoc construction/destruction

CWPR_UTILITY_SPECDoc::CWPR_UTILITY_SPECDoc()
{
	// TODO: add one-time construction code here

}

CWPR_UTILITY_SPECDoc::~CWPR_UTILITY_SPECDoc()
{
}

BOOL CWPR_UTILITY_SPECDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITY_SPECDoc serialization

void CWPR_UTILITY_SPECDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITY_SPECDoc diagnostics

#ifdef _DEBUG
void CWPR_UTILITY_SPECDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWPR_UTILITY_SPECDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITY_SPECDoc commands
