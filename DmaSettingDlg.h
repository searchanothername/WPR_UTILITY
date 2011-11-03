#if !defined(AFX_DMASETTINGDLG_H__D49AE339_48A7_419B_B956_C9D61027C9B5__INCLUDED_)
#define AFX_DMASETTINGDLG_H__D49AE339_48A7_419B_B956_C9D61027C9B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DmaSettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDmaSettingDlg dialog

class CDmaSettingDlg : public CDialog
{
// Construction
public:
	CDmaSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDmaSettingDlg)
	enum { IDD = IDD_DMA_SETTING };
	CSliderCtrl	m_DMA_slider_low;
	CSliderCtrl	m_DMA_slider_high;
	int		m_nDMA_Low;
	int		m_nDMA_High;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDmaSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CBrush m_bkBrush;
	// Generated message map functions
	//{{AFX_MSG(CDmaSettingDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOutofmemoryLowmodedmaSlider(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMASETTINGDLG_H__D49AE339_48A7_419B_B956_C9D61027C9B5__INCLUDED_)
