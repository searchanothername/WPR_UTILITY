// WPR_UTILITIES.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "WPR_UTILITIESDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "Global.h"
#include "Global_SM.h"
#include "Global_Advanced.h"
/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITIESApp

BEGIN_MESSAGE_MAP(CWPR_UTILITIESApp, CWinApp)
	//{{AFX_MSG_MAP(CWPR_UTILITIESApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITIESApp construction

CWPR_UTILITIESApp::CWPR_UTILITIESApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWPR_UTILITIESApp object

CWPR_UTILITIESApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITIESApp initialization

BOOL CWPR_UTILITIESApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
    
	/////////////////////////////
	//LOAD THE ADAPTOR
	global.basic.Load();
	global.sm_descriptor.Load();

    //////////////////////////////
	//LOAD PORT ADAPTOR
	LoadPortAdaptor();

	//////////////////////////////
	//LOAD ADVANCED SETTING
	global_advance.Load();


	CWPR_UTILITIESDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
