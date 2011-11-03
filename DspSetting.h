#if !defined(AFX_DSPSETTING_H__BEA809E0_AA79_4850_AAA8_94086DD6CF4D__INCLUDED_)
#define AFX_DSPSETTING_H__BEA809E0_AA79_4850_AAA8_94086DD6CF4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DspSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDspSetting dialog

class CDspSetting : public CDialog
{
// Construction
public:
	CDspSetting(CWnd* pParent = NULL);   // standard constructor

	int windowSel;
// Dialog Data
	//{{AFX_DATA(CDspSetting)
	enum { IDD = IDD_DIALOG_DSP };
	CSliderCtrl	m_slider_rfgate_l;
	CSpinButtonCtrl	m_spin_begingate_h;
	CSliderCtrl	m_slider_begingate_l;
	CSliderCtrl	m_slider_beginggate_h;
	CSpinButtonCtrl	m_spin_pccode;
	CSliderCtrl	m_slider_pccode;
	CSpinButtonCtrl	m_spin_rfgate;
	CSliderCtrl	m_slider_rfgate;
	CComboBox	m_Combo_Window;
	long	m_nCenterFreq;
	long	m_nSampleClock;
	BOOL	m_bIQReverse;
	BOOL	m_bDCRemoval;
	int		m_nslider_rfgate;
	int		m_nRFGate;
	int		m_nslider_pccode;
	int		m_nPCCode;
	int		m_nslider_beginggate_h;
	int		m_nslider_begingate_l;
	int		m_nBeginGateH;
	int		m_nBeginGateL;
	int		m_nslider_rfgate_l;
	int		m_nRFGateL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDspSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
    CBrush m_bkBrush;
	
	// Generated message map functions
	//{{AFX_MSG(CDspSetting)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboWindow();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDeltaposSpinRfgate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinPccode(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinBegingateH(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinBegingateL(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinRfgateL(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPSETTING_H__BEA809E0_AA79_4850_AAA8_94086DD6CF4D__INCLUDED_)
