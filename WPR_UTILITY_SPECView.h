// WPR_UTILITY_SPECView.h : interface of the CWPR_UTILITY_SPECView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WPR_UTILITY_SPECVIEW_H__438ADA32_B303_4704_B7E4_5D7E8F737880__INCLUDED_)
#define AFX_WPR_UTILITY_SPECVIEW_H__438ADA32_B303_4704_B7E4_5D7E8F737880__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZoomView.h"
#include "MemDC.h"

class CWPR_UTILITY_SPECDoc;


class CWPR_UTILITY_SPECView : public CZoomView
{
	friend DWORD WINAPI Listener(LPVOID lpParameter);
protected: // create from serialization only
	CWPR_UTILITY_SPECView();
	DECLARE_DYNCREATE(CWPR_UTILITY_SPECView)

// Attributes
public:
	CWPR_UTILITY_SPECDoc* GetDocument();

// Operations
public:
	CRect rect_screen;
	void DrawSpectras(CDC* pDC);
	void DrawMarker(CDC* pDC);

private:
	HANDLE hThread;
	BOOL bRun;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWPR_UTILITY_SPECView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWPR_UTILITY_SPECView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRect m_rubberBand;
	CPoint m_ptStart;
	BOOL m_bSelectMode;


private:
	COLORREF color_grid;   
	COLORREF color_spec;
	COLORREF color_marker;
	COLORREF color_peak;


	CPen   pn_grid;
	CPen   pn_spec;
	CPen   pn_marker;
	CPen   pn_peak;
	CFont  font_height;

    int nFFT;
	int nBeamId;
	int nRangebin;

    int XCAPSNUM;
	int YCAPSNUM;

	CPoint SS_Point;
	CPoint SP_Point;

// Generated message map functions
protected:
	//{{AFX_MSG(CWPR_UTILITY_SPECView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnZero();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WPR_UTILITY_SPECView.cpp
inline CWPR_UTILITY_SPECDoc* CWPR_UTILITY_SPECView::GetDocument()
   { return (CWPR_UTILITY_SPECDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WPR_UTILITY_SPECVIEW_H__438ADA32_B303_4704_B7E4_5D7E8F737880__INCLUDED_)
