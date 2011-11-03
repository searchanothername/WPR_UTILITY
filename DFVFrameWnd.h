#if !defined(AFX_DFVFRAMEWND_H__04EC151F_9E30_11D5_8F75_0048546F01E7__INCLUDED_)
#define AFX_DFVFRAMEWND_H__04EC151F_9E30_11D5_8F75_0048546F01E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DFVFrameWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDFVFrameWnd frame

class CDFVFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CDFVFrameWnd)
protected:
	CDFVFrameWnd();           // protected constructor used by dynamic creation

// Attributes
public:


// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDFVFrameWnd)
	//}}AFX_VIRTUAL
	virtual BOOL DFVLoadFrame(UINT nIDResource,
				DWORD dwDefaultStyle, CRect rect,
				CWnd* pParentWnd, DWORD dwDefaultStyleEx, 
				CCreateContext* pContext);

// Implementation
protected:
	virtual ~CDFVFrameWnd();

	// Generated message map functions
	//{{AFX_MSG(CDFVFrameWnd)
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DFVFRAMEWND_H__04EC151F_9E30_11D5_8F75_0048546F01E7__INCLUDED_)
