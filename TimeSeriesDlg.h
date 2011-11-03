#if !defined(AFX_TIMESERIESDLG_H__B06EDB6F_EEF7_4C54_82D6_3B6D48BB2B72__INCLUDED_)
#define AFX_TIMESERIESDLG_H__B06EDB6F_EEF7_4C54_82D6_3B6D48BB2B72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeSeriesDlg.h : header file
//
#include "MemDC.h"
#include "Global_DataDef.h"
/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesDlg dialog
class CDataView;
class CTimeSeriesDlg : public CDialog
{
// Construction
public:
	CTimeSeriesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeSeriesDlg)
	enum { IDD = IDD_DIALOG_TIME_SERIES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeSeriesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	void ShowData(UINT wParam, UINT lParam);
	void setParent(CDataView* parent){g_DataView = parent;}

// Implementation
private:
	CDataView* g_DataView;
	CBrush m_bkBrush;
	int nSpecId;
	int nBeamId;
	CRect rect_screen;

    COLORREF color_background; 
	COLORREF color_screen;
	COLORREF color_grid;   
	COLORREF color_line_i;
	COLORREF color_line_q;
	COLORREF color_line_power;
	COLORREF color_point_i;
	COLORREF color_point_q;
	COLORREF color_point_power;

	CBrush br_background;
	CBrush br_screen;
	CPen   pn_grid;
	CPen   pn_line_i;
	CPen   pn_line_q;
	CPen   pn_line_power;
	CPen   pn_point_i;
	CPen   pn_point_q;
	CPen   pn_point_power;
	CFont  font_index;

	
    int XCAPSNUM;
	int YCAPSNUM;
	int NUMTOSHOW_END;
	int NUMTOSHOW_START;

	CPoint IPoints[MAX_RANGEBIN*MAXFFTPOINTS];
    CPoint QPoints[MAX_RANGEBIN*MAXFFTPOINTS];

protected:
	void DrawBackGround(CMemDCPointer* pDC);
	void DrawIData(CMemDCPointer* pDC);
	void DrawQData(CMemDCPointer* pDC);

	UINT	m_nSweepStart;
	UINT	m_nSweepNum;
	BOOL	m_bIData;
	BOOL	m_bQData;
	BOOL	m_bNum;
	BOOL	m_bSamp;

	// Generated message map functions
	//{{AFX_MSG(CTimeSeriesDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMESERIESDLG_H__B06EDB6F_EEF7_4C54_82D6_3B6D48BB2B72__INCLUDED_)
