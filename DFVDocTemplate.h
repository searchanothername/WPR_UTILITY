#if !defined(AFX_DFVDOCTEMPLATE_H__04EC1524_9E30_11D5_8F75_0048546F01E7__INCLUDED_)
#define AFX_DFVDOCTEMPLATE_H__04EC1524_9E30_11D5_8F75_0048546F01E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DFVDocTemplate.h : header file
//

#include "DFVDocument.h"

#define baseCDFVDocTemplate CSingleDocTemplate

/////////////////////////////////////////////////////////////////////////////
// CDFVDocTemplate command target

class CDFVDocTemplate : public baseCDFVDocTemplate
{
	DECLARE_DYNAMIC(CDFVDocTemplate)

	CDFVDocTemplate(UINT nIDResource,
		CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass,
		CRuntimeClass* pViewClass);

// Attributes
public:
	CWnd * m_pParent;
	CRect m_Rect;
	DWORD m_Style;
	DWORD m_StyleEx;

	CFrameWnd * m_pFrame;

// Operations
public:
	virtual CFrameWnd* CreateNewFrame(CDocument* pDoc, CFrameWnd* pOther);
	virtual BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog);
	void _AfxAppendFilterSuffix(CString& filter, OPENFILENAME& ofn,
	CDocTemplate* pTemplate, CString* pstrDefaultExt);
	virtual CDocument* OpenDocumentFile(
		LPCTSTR lpszPathName, BOOL bMakeVisible = TRUE);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDFVDocTemplate)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDFVDocTemplate();

	// Generated message map functions
	//{{AFX_MSG(CDFVDocTemplate)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DFVDOCTEMPLATE_H__04EC1524_9E30_11D5_8F75_0048546F01E7__INCLUDED_)
