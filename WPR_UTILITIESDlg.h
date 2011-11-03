// WPR_UTILITIESDlg.h : header file
//

#if !defined(AFX_WPR_UTILITIESDLG_H__1F6BE202_19AF_4A34_B8FD_CA184C642805__INCLUDED_)
#define AFX_WPR_UTILITIESDLG_H__1F6BE202_19AF_4A34_B8FD_CA184C642805__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoptestParamDlg.h"
#include "StatusMonitorTask.h"
#include "TestTask.h"
#include "UPSMonitorTask.h"
#include "digitalclock.h"
#include "ServerTask.h"
#include "ProductProcess.h"
#include "StaticCounter.h"

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITIESDlg dialog

enum{
	EAST,
	NORTH,
	VIRTICAL,
	WEST,
	SOUTH
};
class CDataView;
class CTotalSpecDlg;
class CWPR_UTILITY_SPECView;

class CWPR_UTILITIESDlg : public CDialog
{
// Construction
public:
	CWPR_UTILITIESDlg(CWnd* pParent = NULL);	// standard constructor
    void ShowData(UINT wParam, UINT lParam);
	void ShowSpecSingle(UINT wParam, UINT lParam);
	void ShowSpecAvg(UINT wParam, UINT lParam);
	void ShowSpecTotal(UINT wParam, UINT lParam);
	void ShowSysInfo();


	void SetCtrlWordsForEveryBeam();
	void SetCtrlWordsForTest(CDoptestParamDlg& DoptestParamdlg);
	void Scale();
	void RecordDataFromSM();
	void SetBeam(int id);

	//void ShowSpecTotal(UINT wParam, UINT lParam);

// Dialog Data
	//{{AFX_DATA(CWPR_UTILITIESDlg)
	enum { IDD = IDD_WPR_UTILITIES_DIALOG };
	CButton	m_sm_data_display;
	CStaticCounter	m_InterCount;
	CEdit	m_SysInfo;
	CListCtrl	m_alarmdisplist;
	CStatic	m_static_dsp_wiqclk;
	CStatic	m_static_dsp_wdvcc;
	CStatic	m_static_dsp_wavcc;
	CStatic	m_static_dsp_wadclk;
	CStatic	m_static_dsp_txbias;
	CStatic	m_static_dsp_lrb;
	CStatic	m_static_dsp_tramp;
	CStatic	m_static_dsp_t0;
	CStatic	m_static_dsp_stc;
	CStatic	m_static_dsp_rd;
	CStatic	m_static_tx_swr;
	CStatic	m_static_tx_rf_on;
	CStatic	m_static_txps;
	CStatic	m_static_overtemp;
	CStatic	m_static_tx_output;
	CStatic	m_static_tx_input;
	CDigitalClock	m_static_duty;
	CDigitalClock	m_static_output_pwr;
	CDigitalClock	m_static_input_pwr;
	CButton	m_button_east;
	CButton	m_button_north;
	CButton	m_button_south;
	CButton	m_button_virtical;
	CButton	m_button_west;
	CEdit	m_ups_status;
	CButton	m_button_ups;
	CButton	m_HPA0;
	CStatic	m_hpa0_status;
	CSliderCtrl	m_RTACSlider;
	CListCtrl	m_ListCtrl;
	CSliderCtrl	m_RFAttenSlider;
	BOOL	m_HPA0_ON;
	CString	m_str_ups_status;
	BOOL	m_b_west;
	BOOL	m_b_virtical;
	BOOL	m_b_south;
	BOOL	m_b_north;
	BOOL	m_b_east;
	CString	m_strSysInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWPR_UTILITIESDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CTestTask testtask;
	CStatusMonitorTask smtask;
	CUPSMonitorTask upstask;
	CServerTask servertask;
	CProductProcess producttask;

public:
	HICON m_hIcon;
    CBrush m_bkBrush;
	CToolBarCtrl m_ToolBar;
	CImageList m_ImageList;
	CImageList m_ImageListAlarm;
	CStatusBar m_StatusBar;
	CMap<CString, LPCTSTR, int, int&> reportTable;
	CWPR_UTILITY_SPECView* pSpecView;

    
	DWORD	m_nIpAddress;
	UINT	m_nPort;
	HICON m_hHPA[2];
	HICON m_hBeam[5];
	HICON m_hBeamSelected[5];

public:
    CDC* pHpaDC;
	CBrush   br_hpa_fault;
	CBrush   br_hpa_on;
	CBrush   br_hpa_off;
	CStatic* pStatusArray;

	CDataView* dataview;
	CTotalSpecDlg* specsview;

	BOOL bDataViewEnable;
	BOOL bSpectrasViewEnable;
	CRect  rect_screen;


	//FOR DISPLAY THE TX STATUS
	TX_FLOAT _f_tx_pwr_input;
	TX_FLOAT _f_tx_pwr_output;
	TX_FLOAT _f_tx_pwr_reflect;
	// Generated message map functions
	//{{AFX_MSG(CWPR_UTILITIESDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNortestSetting();
	afx_msg void OnSimulator();
	afx_msg void OnSm();
	afx_msg void OnBasicSetting();
	afx_msg void OnPha0();
	afx_msg void OnTestStop();
	afx_msg void OnTestandgetdata();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStartSm();
	afx_msg void OnStopSm();
	afx_msg void OnAdvancedSetting();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStartUps();
	afx_msg void OnStopUps();
	afx_msg void OnButtonUps();
	afx_msg void OnButtonStatus();
	afx_msg void OnCheckEast();
	afx_msg void OnCheckNorth();
	afx_msg void OnCheckSouth();
	afx_msg void OnCheckVirtical();
	afx_msg void OnCheckWest();
	afx_msg void OnDataview();
	afx_msg void OnUpdateStartSm(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStopSm(CCmdUI* pCmdUI);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnButtonDyntest();
	afx_msg void OnTotalspecView();
	afx_msg void OnButtonInclinometer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WPR_UTILITIESDLG_H__1F6BE202_19AF_4A34_B8FD_CA184C642805__INCLUDED_)
