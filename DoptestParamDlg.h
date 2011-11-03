#if !defined(AFX_DOPTESTPARAMDLG_H__FC9E8540_D556_4502_87E7_A85E0386235C__INCLUDED_)
#define AFX_DOPTESTPARAMDLG_H__FC9E8540_D556_4502_87E7_A85E0386235C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoptestParamDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoptestParamDlg dialog

class CDoptestParamDlg : public CDialog
{
// Construction
public:
	CDoptestParamDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDoptestParamDlg)
	enum { IDD = IDD_DOPTEST_PARAM };
	CComboBox	m_TST_BEAM_NUM_COMB;
	int		m_TST_DOP_PHASE;
	int		m_TST_BEAM_NUM;
	int		m_TST_RF_FREQ;
	int		m_TST_COAX_SWITCH;
	int		m_TST_BM_DIRCHANGE;
	int		m_TST_LO_PHASE;
	int		m_TST_NOISE_SOURCE;
	int		m_TST_SIGNAL_AMP;
	int		m_TST_SIGNAL_OUTPUT;
	int		m_TST_SIGNAL_SOURCE;
	int		m_TST_SM_RESET;
	int		m_TST_TRANSMITTER;
	int		m_TST_RF_ATTEN;
	int		m_TST_DOP_TST_CTRL;
	int		m_TST_RF_GATEMOVING;
	int		m_TST_DIF_GATEMOVING;
	int		m_TST_PCCODE_MOVING;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoptestParamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CBrush m_bkBrush;
	// Generated message map functions
	//{{AFX_MSG(CDoptestParamDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOPTESTPARAMDLG_H__FC9E8540_D556_4502_87E7_A85E0386235C__INCLUDED_)
