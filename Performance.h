#if !defined(AFX_PERFORMANCE_H__6535C64B_C26B_4006_9D94_24C88E82BF49__INCLUDED_)
#define AFX_PERFORMANCE_H__6535C64B_C26B_4006_9D94_24C88E82BF49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Performance.h : header file
//
#include "pf_power_supply_page.h"
#include "pf_sys_pa_page.h"
#include "pf_drv_and_fans.h"
#include "pf_hpa_and_pa_temp.h"
#include "pf_sundries_1.h"
#include "pf_sundries_2.h"
/////////////////////////////////////////////////////////////////////////////
// CPerformance

class CPerformance : public CPropertySheet
{
	DECLARE_DYNAMIC(CPerformance)

// Construction
public:
	CPerformance(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPerformance(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
  /*CPf_power_supply_page pf_power_supply_page;
   CPf_sys_pa_page pf_sys_pa_page;
   CPf_drv_and_fans pf_drv_and_fans_page;
   CPf_hpa_and_pa_temp pf_hpa_and_pa_temp_page;
   CPf_sundries_1 pf_sundries_1_page;
   CPf_sundries_2 pf_sundries_2_page;
   */
// Operations
public:
    CBrush m_bkBrush;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPerformance)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPerformance();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPerformance)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERFORMANCE_H__6535C64B_C26B_4006_9D94_24C88E82BF49__INCLUDED_)
