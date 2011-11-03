#if !defined(AFX_RAWDATADLG_H__7CEEB27D_CD94_43A8_8917_AEA114923201__INCLUDED_)
#define AFX_RAWDATADLG_H__7CEEB27D_CD94_43A8_8917_AEA114923201__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RawdataDlg.h : header file
//

#include "Global_DataDef.h"
/////////////////////////////////////////////////////////////////////////////
// CRawdataDlg dialog
class CDataView;
class CRawdataDlg : public CDialog
{
// Construction
public:
	CRawdataDlg(CWnd* pParent = NULL);   // standard constructor
	void setParent(CDataView* pParent){g_DataView = pParent;}
	void ShowData(UINT wParam, UINT lParam);
	void calculate(double* phase, 
					double* power,
					int length);
// Dialog Data
	//{{AFX_DATA(CRawdataDlg)
	enum { IDD = IDD_DIALOG_RAW };
	CButton	m_btn_Pause;
	CListCtrl	m_ListCtrl_DataInfo;
	BOOL	m_bSaveDetails;
	BOOL	m_bSaveResults;
	BOOL	m_bPause;
	double	m_fPhaseNoiseDB;
	double	m_fPhaseNoiseDeg;
	double	m_fPwrAvg;
	double	m_fPwrMM;
	double	m_fPhaseMM;
	double	m_fPhaseAvg;
	double	m_fPwrSum;
	double	m_fPwrVariance;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRawdataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDataView* g_DataView;
	CBrush m_bkBrush;
	UINT  m_nFocusRangeBin;
	int nSpecId;
	int nBeamId;
	double fPwrMax;
	double fPwrMin;
	double fPhaseMax;
	double fPhaseMin;
	double fPwrMean;
	double fPwrSum;
	double fPhaseMean;
	double fPhaseNoise_dB;
	double fPhaseNoise_deg;

	double fIData[MAXFFTPOINTS];
	double fQData[MAXFFTPOINTS];
	double fPower[MAXFFTPOINTS];
	double fPhase[MAXFFTPOINTS];
	// Generated message map functions
	//{{AFX_MSG(CRawdataDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCheckRawControl();
	afx_msg void OnCheckSaveDetails();
	afx_msg void OnCheckSaveResults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAWDATADLG_H__7CEEB27D_CD94_43A8_8917_AEA114923201__INCLUDED_)
