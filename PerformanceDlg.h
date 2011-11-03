#if !defined(AFX_PERFORMANCEDLG_H__4CFA7510_EC14_46B7_9409_9C7403869391__INCLUDED_)
#define AFX_PERFORMANCEDLG_H__4CFA7510_EC14_46B7_9409_9C7403869391__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PerformanceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPerformanceDlg dialog

class CPerformanceDlg : public CDialog
{
// Construction
public:
	CPerformanceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPerformanceDlg)
	enum { IDD = IDD_DIALOG_SM };
	CStatic	m_static_txm15v;
	CStatic	m_static_tx5v;
	CStatic	m_static_tx50v;
	CStatic	m_static_tx36v;
	CStatic	m_static_tx28v;
	CStatic	m_static_tx15v;
	CStatic	m_static_tx13v;
	CStatic	m_static_sw;
	CStatic	m_static_sp;
	CStatic	m_static_rf_fault;
	CStatic	m_static_rf;
	CStatic	m_static_psm5v;
	CStatic	m_static_psm15v;
	CStatic	m_static_ps9v;
	CStatic	m_static_ps6v;
	CStatic	m_static_ps5v4;
	CStatic	m_static_ps5v3;
	CStatic	m_static_ps5v2;
	CStatic	m_static_ps5v1;
	CStatic	m_static_ps24v;
	CStatic	m_static_ps3_3v;
	CStatic	m_static_ps15v;
	CStatic	m_static_ps12v;
	CStatic	m_static_overtemp;
	CStatic	m_static_output;
	float	m_Tx5v;
	float	m_Tx50v;
	float	m_Tx36v;
	float	m_Tx28v;
	float	m_Tx15v;
	float	m_Tx13v;
	float	m_Tx_Temp;
	float	m_Tx_Reflect;
	float	m_Tx_Output;
	float	m_Tx_Input;
	float	m_Psm15v;
	float	m_Ps9v;
	float	m_Ps6v;
	float	m_Ps5v4;
	float	m_Ps5v3;
	float	m_Ps5v2;
	float	m_Ps5v1;
	float	m_Ps3_3v;
	float	m_Ps24v;
	float	m_Ps15v;
	float	m_Ps12v;
	float	m_Txm15v;
	float	m_Psm5v;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPerformanceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	 CBrush m_bkBrush;
	 void show_status(CStatic& st,const int index);

	// Generated message map functions
	//{{AFX_MSG(CPerformanceDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERFORMANCEDLG_H__4CFA7510_EC14_46B7_9409_9C7403869391__INCLUDED_)
