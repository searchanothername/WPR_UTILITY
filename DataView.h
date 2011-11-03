#if !defined(AFX_DATAVIEW_H__824E75CD_0A33_4F86_ADB7_21E443672B65__INCLUDED_)
#define AFX_DATAVIEW_H__824E75CD_0A33_4F86_ADB7_21E443672B65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataView dialog
#include "TimeSeriesDlg.h"
#include "FrequencyDlg.h"
#include "RawdataDlg.h"
#include "ColorProgressCtrl.h"

class CWPR_UTILITIESDlg;
class CDataView : public CDialog
{
// Construction
public:
	CDataView(CWnd* pParent = NULL);   // standard constructor
    
// Dialog Data
	//{{AFX_DATA(CDataView)
	enum { IDD = IDD_DIALOG_DATAVIEW };
	CSliderCtrl	m_MarkerCtrl;
	CComboBox	m_cobo_Window;
	CColorProgressCtrl	m_progress;
	CTabCtrl	m_DataViewTab;
	CString	m_str_MarkerPower;
	BOOL	m_bIData;
	BOOL	m_bQData;
	BOOL	m_bNum;
	BOOL	m_bSamp;
	BOOL	m_bSingle;
	BOOL	m_bAvg;
	int		m_nMarkerValue;
	int		m_nValue;
	CString	m_str_MarkerPeak;
	CString	m_str_SweepNum;
	CString	m_str_SweepStart;
	CString	m_str_FocusRange;
	double	m_velocity;
	BOOL	m_bNoiseLevel;
	BOOL	m_bPeakS;
	BOOL	m_bPeakA;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:	
	int m_nSweepStart;
	int m_nSweepNum;
	int m_nFocusRangeBin;
	int m_nBeamId;

private:
	CTimeSeriesDlg time_series_dlg;
	CFrequencyDlg freq_dlg;
	CRawdataDlg raw_dlg;
	CRect rect;
	BOOL bDataComming;
	CWPR_UTILITIESDlg* _utility;
	void ShowData(UINT wParam, UINT lParam);
	void ShowSpecSingle(UINT wParam, UINT lParam);
	void ShowSpecAvg(UINT wParam, UINT lParam);

public:
	void setParent(CWPR_UTILITIESDlg* pParent);
// Implementation
protected:
	CBrush m_bkBrush;
	// Generated message map functions
	//{{AFX_MSG(CDataView)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnCheckIdata();
	afx_msg void OnCheckQdata();
	afx_msg void OnCheckSamp();
	afx_msg void OnCheckNum();
	virtual void OnOK();
	afx_msg void OnCheckSpecAvg();
	afx_msg void OnCheckSpecSingle();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckNoiselevel();
	afx_msg void OnCheckPeakA();
	afx_msg void OnCheckPeakS();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAVIEW_H__824E75CD_0A33_4F86_ADB7_21E443672B65__INCLUDED_)
