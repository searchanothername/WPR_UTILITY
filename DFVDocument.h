#if !defined(AFX_DFVDOCUMENT_H__04EC1525_9E30_11D5_8F75_0048546F01E7__INCLUDED_)
#define AFX_DFVDOCUMENT_H__04EC1525_9E30_11D5_8F75_0048546F01E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DFVDocument.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDFVDocument document

#define DELETE_EXCEPTION(e) do { e->Delete(); } while (0)

class CDFVDocument : public CDocument
{
protected:
	CDFVDocument();           // protected constructor used by dynamic creation
	DECLARE_DYNAMIC(CDFVDocument)

// Attributes
public:

// Operations
public:
	virtual BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace = TRUE);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDFVDocument)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDFVDocument();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDFVDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DFVDOCUMENT_H__04EC1525_9E30_11D5_8F75_0048546F01E7__INCLUDED_)
