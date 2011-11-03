// Performance.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Performance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPerformance

IMPLEMENT_DYNAMIC(CPerformance, CPropertySheet)

CPerformance::CPerformance(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CPerformance::CPerformance(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));
/*	AddPage(&pf_sys_pa_page);
	AddPage(&pf_power_supply_page);
	AddPage(&pf_drv_and_fans_page);
	AddPage(&pf_hpa_and_pa_temp_page);
	AddPage(&pf_sundries_1_page);
	AddPage(&pf_sundries_2_page);
	*/
}

CPerformance::~CPerformance()
{
}


BEGIN_MESSAGE_MAP(CPerformance, CPropertySheet)
	//{{AFX_MSG_MAP(CPerformance)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPerformance message handlers

HBRUSH CPerformance::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertySheet::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	return m_bkBrush;
	// TODO: Return a different brush if the default is not desired
	//return hbr;
}
