// WPR_UTILITIES.h : main header file for the WPR_UTILITIES application
//

#if !defined(AFX_WPR_UTILITIES_H__C4BE46D9_61D6_4357_9378_FFFF1B663C34__INCLUDED_)
#define AFX_WPR_UTILITIES_H__C4BE46D9_61D6_4357_9378_FFFF1B663C34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITIESApp:
// See WPR_UTILITIES.cpp for the implementation of this class
//

class CWPR_UTILITIESApp : public CWinApp
{
public:
	CWPR_UTILITIESApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWPR_UTILITIESApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWPR_UTILITIESApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WPR_UTILITIES_H__C4BE46D9_61D6_4357_9378_FFFF1B663C34__INCLUDED_)
