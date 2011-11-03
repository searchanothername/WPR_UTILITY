// WPR_UTILITY_SPECDoc.h : interface of the CWPR_UTILITY_SPECDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WPR_UTILITY_SPECDOC_H__43F22245_E736_4B8D_87D0_62389C9E45BC__INCLUDED_)
#define AFX_WPR_UTILITY_SPECDOC_H__43F22245_E736_4B8D_87D0_62389C9E45BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DFVDocument.h"
class CWPR_UTILITY_SPECDoc : public CDFVDocument
{
protected: // create from serialization only
	CWPR_UTILITY_SPECDoc();
	DECLARE_DYNCREATE(CWPR_UTILITY_SPECDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWPR_UTILITY_SPECDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWPR_UTILITY_SPECDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWPR_UTILITY_SPECDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WPR_UTILITY_SPECDOC_H__43F22245_E736_4B8D_87D0_62389C9E45BC__INCLUDED_)
