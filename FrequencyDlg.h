#if !defined(AFX_FREQUENCYDLG_H__AA456E57_4D2C_47C5_B2F4_5DCC0302D9F7__INCLUDED_)
#define AFX_FREQUENCYDLG_H__AA456E57_4D2C_47C5_B2F4_5DCC0302D9F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrequencyDlg.h : header file
//
#include "MemDC.h"
#include "Global_DataDef.h"
/////////////////////////////////////////////////////////////////////////////
// CFrequencyDlg dialog
class CDataView;
class CFrequencyDlg : public CDialog
{
// Construction
public:
	CFrequencyDlg(CWnd* pParent = NULL);   // standard constructor
    void setParent(CDataView* pParent){g_DataView = pParent;}
	void ShowSpecSingle(UINT wParam, UINT lParam);
	void ShowSpecAvg(UINT wParam, UINT lParam);
	void ShowMarker(UINT wParam, UINT lParam);
// Dialog Data
	//{{AFX_DATA(CFrequencyDlg)
	enum { IDD = IDD_DIALOG_FREQ };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrequencyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDataView* g_DataView;
	CRect rect_screen;
	void DrawBackGround(CMemDCPointer* pDC);
	void DrawSingleSpec(CMemDCPointer* pDC);
	void DrawAvgSpec(CMemDCPointer* pDC);
	void DrawMarker(CMemDCPointer* pDC);
private:
	UINT  m_nFocusRangeBin;
	int nSpecId;
	int nBeamId;
	int nFFT;
	BOOL	m_bSingle;
	BOOL	m_bAvg;
	BOOL    m_bShowNoiseLevel;
	BOOL    m_bShowPeakS;
	BOOL	m_bShowPeakA;
	int     m_nValue;


	COLORREF color_grid;   
	COLORREF color_single_spec;
	COLORREF color_avg_spec;
	COLORREF color_marker;
	COLORREF color_peak;
	COLORREF color_noise;

	CBrush m_bkBrush;
	CPen   pn_grid;
	CPen   pn_single;
	CPen   pn_avg;
	CPen   pn_marker;
	CPen   pn_peak;
	CPen   pn_noise;

    int XCAPSNUM;
	int YCAPSNUM;
	LOGFONT logfont;
	CFont font;

	CPoint SS_Point[MAXFFTPOINTS];
	CPoint SA_Point[MAXFFTPOINTS];
	// Generated message map functions
	//{{AFX_MSG(CFrequencyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FREQUENCYDLG_H__AA456E57_4D2C_47C5_B2F4_5DCC0302D9F7__INCLUDED_)
