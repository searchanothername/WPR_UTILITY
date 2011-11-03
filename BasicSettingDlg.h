#if !defined(AFX_BASICSETTINGDLG_H__AEB87948_6DFE_456F_86AF_6621739F211E__INCLUDED_)
#define AFX_BASICSETTINGDLG_H__AEB87948_6DFE_456F_86AF_6621739F211E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BasicSettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBasicSettingDlg dialog

class CBasicSettingDlg : public CDialog
{
// Construction
public:
	CBasicSettingDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CBasicSettingDlg)
	enum { IDD = IDD_BASIC_SETTING_DLG };
	CComboBox	m_PSC_ComboBox;
	CComboBox	m_nFFT_ComboBox;
	CListBox	m_list_RangeBin;
	long	m_nPRT_ObliqueHigh;
	long	m_nPW_ObliqueHigh;
	UINT	m_nTAvg_ObliqueHigh;
	long	m_nPRT_ObliqueLow;
	long	m_nPW_ObliqueLow;
	UINT	m_nSAvg_ObliqueHigh;
	UINT	m_nSAvg_ObliqueLow;
	UINT	m_nTAvg_ObliqueLow;
	long	m_nPRT_VerticalHigh;
	long	m_nPW_VerticalHigh;
	UINT	m_nSAvg_VerticalHigh;
	UINT	m_nTAvg_VerticalHigh;
	long	m_nPRT_VerticalLow;
	long	m_nPW_VerticalLow;
	UINT	m_nSAvg_VerticalLow;
	UINT	m_nTAvg_VerticalLow;
	int		m_nSTC_East;
	int		m_nSTC_North;
	int		m_nSTC_Vertical;
	int		m_nSTC_South;
	int		m_nSTC_West;
	BOOL	m_bWholeRange;
	BOOL	m_bPulseCompress;
	BOOL	m_bHighModeSetting;
	BOOL	m_bHighMode240mGateRange;
	BOOL	m_b25MSigClose;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBasicSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CBrush m_bkBrush;
	// Generated message map functions
	//{{AFX_MSG(CBasicSettingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboFft();
	afx_msg void OnChangeEast();
	afx_msg void OnChangeNorth();
	afx_msg void OnChangeVertical();
	afx_msg void OnSelchangeRangbinList();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnChangeWest();
	afx_msg void OnChangeSouth();
	afx_msg void OnSelchangeComboPsc();
	afx_msg void OnWholerange();
	afx_msg void OnPulsecompress();
	afx_msg void OnHighmodetoggle();
	afx_msg void OnHighmode240();
	afx_msg void On25mSigClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASICSETTINGDLG_H__AEB87948_6DFE_456F_86AF_6621739F211E__INCLUDED_)
