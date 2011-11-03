#if !defined(AFX_BEAMCODEDLG_H__5C1B068B_9676_4471_8A5F_BD1CD248C1B5__INCLUDED_)
#define AFX_BEAMCODEDLG_H__5C1B068B_9676_4471_8A5F_BD1CD248C1B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BeamCodeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBeamCodeDlg dialog

class CBeamCodeDlg : public CDialog
{
// Construction
public:
	CBeamCodeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBeamCodeDlg)
	enum { IDD = IDD_DIALOG_BEAMSETTING };
	int		m_nSouth;
	int		m_nVirtical;
	int		m_nWest;
	int		m_nNorth;
	int		m_nEast;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBeamCodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_bkBrush;
	// Generated message map functions
	//{{AFX_MSG(CBeamCodeDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEAMCODEDLG_H__5C1B068B_9676_4471_8A5F_BD1CD248C1B5__INCLUDED_)
