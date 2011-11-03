#if !defined(AFX_NORMALSETTINGDLG_H__B8039FAB_B7A6_47E0_ADC7_CE64291B859D__INCLUDED_)
#define AFX_NORMALSETTINGDLG_H__B8039FAB_B7A6_47E0_ADC7_CE64291B859D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NormalSettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNormalSettingDlg dialog

class CNormalSettingDlg : public CDialog
{
// Construction
public:
	CNormalSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNormalSettingDlg)
	enum { IDD = IDD_NORMALSETTINGDLG };
	CIPAddressCtrl	m_ctlServIP;
	CComboBox	m_BaudRate_GM;
	CComboBox	m_PortName_GM;
	CComboBox	m_Parity_GM;
	CComboBox	m_Parity;
	CComboBox	m_BaudRate;
	CComboBox	m_PortName;
	UINT	m_nByteSize;
	UINT	m_nStopBits;
	int		m_nSharedMemory;
	BYTE	m_nIP0;
	BYTE	m_nIP1;
	BYTE	m_nIP2;
	BYTE	m_nIP3;
	UINT	m_nPort;
	CString	m_strArchivePath;
	BOOL	m_bCycleTest;
	BOOL	m_bRemoteCtrl;
	int		m_nPathBinary;
	UINT	m_nByteSize_GM;
	UINT	m_nStopBits_GM;
	BOOL	m_bSM_INUSE;
	BOOL	m_bGM_INUSE;
	UINT	m_nByteNumber_SM;
	UINT	m_nByteNumber_UPS;
	BOOL	m_bSM_HRD_CHECK;
	BOOL	m_bGM_HRD_CHECK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNormalSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CBrush m_bkBrush;
	// Generated message map functions
	//{{AFX_MSG(CNormalSettingDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTcpip();
	afx_msg void OnSharedmemory();
	afx_msg void OnUdp();
	afx_msg void OnPathbinary();
	afx_msg void OnPathnone();
	afx_msg void OnPathtext();
	afx_msg void OnOpen();
	afx_msg void OnSmInuse();
	afx_msg void OnGmInuse();
	afx_msg void OnSmHrdCheck();
	afx_msg void OnGmHrdCheck();
	afx_msg void OnChangeEditByteReadSm();
	afx_msg void OnChangeEditByteReadUps();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NORMALSETTINGDLG_H__B8039FAB_B7A6_47E0_ADC7_CE64291B859D__INCLUDED_)
