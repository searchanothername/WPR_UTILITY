// TimeSeriesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "TimeSeriesDlg.h"
#include "Global.h"
#include "DataHandlor.h"
#include "DataView.h"
#include "Global_Advanced.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesDlg dialog

extern CDataHandlor data;
CTimeSeriesDlg::CTimeSeriesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeSeriesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeSeriesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	nSpecId = -1;
	nBeamId = -1;
	NUMTOSHOW_END = 0;
	NUMTOSHOW_START = 0;
	m_nSweepNum = 0;
}


void CTimeSeriesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeSeriesDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeSeriesDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeSeriesDlg)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_MESSAGE(WM_SHOW_TIMESERIES,ShowData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesDlg message handlers

BOOL CTimeSeriesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bkBrush.CreateSolidBrush(RGB(0,0,0));
	color_background	= RGB(0,0,0);
    color_screen        = RGB(0,0,0);
	color_grid          = RGB(58,58,58);    

	color_line_i		= RGB(255,0,0);
	color_line_q        = RGB(0,255,255);
	color_line_power    = RGB(0,255,0);

	color_point_i       = RGB(255,255,0);
	color_point_q		= RGB(255,0,255);
	color_point_power   = RGB(128,128,0);
	
	br_background.CreateSolidBrush(color_background);
	br_screen.CreateSolidBrush(color_grid);
	pn_grid.CreatePen(0,0,color_grid);

    pn_line_i.CreatePen(0,0,color_line_i);
	pn_line_q.CreatePen(0,0,color_line_q);
	pn_line_power.CreatePen(0,0,color_line_power);

	pn_point_i.CreatePen(0,4,color_point_i);
	pn_point_q.CreatePen(0,4,color_point_q);
	pn_point_power.CreatePen(0,4,color_point_power);

    font_index.CreateFont(15, 0, 0, 0, FW_REGULAR, 
		     0, 0, 0, 0, 0, 0, 0, 0, "Courier New");

	XCAPSNUM = 16;
	YCAPSNUM = 16;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CTimeSeriesDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return m_bkBrush;
}

void CTimeSeriesDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	GetClientRect(&rect_screen);
	CMemDCPointer pMemDC(&dc);
    DrawBackGround(pMemDC);
	if(m_bIData)
		DrawIData(pMemDC);
	if(m_bQData)
		DrawQData(pMemDC);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CTimeSeriesDlg::ShowData(UINT wParam, UINT lParam)
{
	nSpecId = wParam;
	nBeamId = lParam;
	m_nSweepStart = g_DataView->m_nSweepStart;
	m_nSweepNum = g_DataView->m_nSweepNum;

	m_bIData = g_DataView->m_bIData;
    m_bQData = g_DataView->m_bQData;
	m_bNum = g_DataView->m_bNum;
	m_bSamp = g_DataView->m_bSamp;
	::InvalidateRect(m_hWnd,&rect_screen,FALSE);
	return;
}

void CTimeSeriesDlg::DrawBackGround(CMemDCPointer* pDC)
{
	CPen* oldPen = pDC->GetCurrentPen();
	CBrush* oldBrush = pDC->GetCurrentBrush();

	//Fill the back ground
	//pDC->SelectObject(&color_screen);
	//pDC->Rectangle(&rect_screen);

	//Draw the grids
	pDC->SelectObject(&pn_grid);
    double xScale = (double)rect_screen.Width()/XCAPSNUM;
	double yScale = (double)rect_screen.Height()/YCAPSNUM;

	//Y
	for(int i = 1; i<XCAPSNUM; i++){
		pDC->MoveTo(rect_screen.left+i*xScale,rect_screen.top);
		pDC->LineTo(rect_screen.left+i*xScale,rect_screen.bottom);
	}

	//X
	for( i = 1; i<YCAPSNUM; i++){
		pDC->MoveTo(rect_screen.left, rect_screen.top+i*yScale);
		pDC->LineTo(rect_screen.right,rect_screen.top+i*yScale);
	}
	
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}

void CTimeSeriesDlg::DrawIData(CMemDCPointer* pDC)
{

	if(nSpecId == -1 || nBeamId == -1)
		return;

	CPen* oldPen = pDC->GetCurrentPen();
	CFont* oldFont = pDC->SelectObject(&font_index);
	pDC->SelectObject(&pn_line_i);
    
	//GET WINDOW SIZE
	int w = rect_screen.Width();
	int h = rect_screen.Height();
	int rangebin = 0;
	int fftnum = data.nFFT;

	P_DATA buffer;
	if(nBeamId%2==1){
		rangebin = data._RANGEBIN_LOW-global_advance.dspsetting.nBeginGateMoveL;
		buffer	= (data._data_low+nSpecId)->datapage_l.nTimeSeries+0;
	}
	else{
		rangebin = data._RANGEBIN_HIGH-global_advance.dspsetting.nBeginGateMoveH;
		buffer	= (data._data_high+nSpecId)->datapage_h.nTimeSeries+0;
	}

	NUMTOSHOW_START = rangebin*m_nSweepStart;
	NUMTOSHOW_END = NUMTOSHOW_START + rangebin*m_nSweepNum;

	double y_scalor = (double)h/2 /global.ts_limit[nSpecId].i_scalor;
    double x_scalor = (double) w/(double)(NUMTOSHOW_END-NUMTOSHOW_START);

	IPoints[0].x = rect_screen.left;
	IPoints[0].y = h/2 - ((buffer+0)->iData) *y_scalor;
	pDC->MoveTo(IPoints[0]);
	for(int i=0;i<NUMTOSHOW_END-NUMTOSHOW_START; i++)
	{
		IPoints[i].x = rect_screen.left+(int)(i*x_scalor);
		IPoints[i].y = h/2 - (buffer+NUMTOSHOW_START+i)->iData*y_scalor;
		pDC->LineTo(IPoints[i]);
	}

	//FOR SHOW SAMPLE
	if(m_bSamp){
		pDC->SelectObject(&pn_point_i);
		for(i=0; i<NUMTOSHOW_END-NUMTOSHOW_START; i++){	
			pDC->MoveTo(IPoints[i]);
			pDC->LineTo(IPoints[i]);
			}
	}

	//FOR SHOW INDEX
	if(m_bNum){
		CString str_IdOfPoint;
	    pDC->SetBkColor(RGB(0,0,0));
	    pDC->SetTextColor(color_point_i);
		for(i=0; i<NUMTOSHOW_END-NUMTOSHOW_START; i++){
		str_IdOfPoint.Format("%d",i%rangebin);
		pDC->TextOut(IPoints[i].x+5, 
						 IPoints[i].y-5,
					     str_IdOfPoint);
		}
	}


	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldFont);
}

void CTimeSeriesDlg::DrawQData(CMemDCPointer* pDC)
{
	
	if(nSpecId == -1 || nBeamId == -1)
		return;

	CPen* oldPen = pDC->GetCurrentPen();
	CFont* oldFont = pDC->SelectObject(&font_index);
	pDC->SelectObject(&pn_line_q);
    
	//GET WINDOW SIZE
	int w = rect_screen.Width();
	int h = rect_screen.Height();
	int rangebin = 0;
	int fftnum = data.nFFT;

	P_DATA buffer;
	if(nBeamId%2==1){
		rangebin = data._RANGEBIN_LOW-global_advance.dspsetting.nBeginGateMoveL;
		buffer	= (data._data_low+nSpecId)->datapage_l.nTimeSeries+0;
	}
	else{
		rangebin = data._RANGEBIN_HIGH-global_advance.dspsetting.nBeginGateMoveH;
		buffer	= (data._data_high+nSpecId)->datapage_h.nTimeSeries+0;
	}

	NUMTOSHOW_START = rangebin*m_nSweepStart;
	NUMTOSHOW_END = NUMTOSHOW_START + rangebin*m_nSweepNum;

	double y_scalor = (double)h/2 /global.ts_limit[nSpecId].q_scalor;
    double x_scalor = (double) w/(double)(NUMTOSHOW_END-NUMTOSHOW_START);

	QPoints[0].x = rect_screen.left;
	QPoints[0].y = h/2 - ((buffer+0)->qData) *y_scalor;
	pDC->MoveTo(QPoints[0]);
	for(int i=0;i<NUMTOSHOW_END-NUMTOSHOW_START; i++)
	{
		QPoints[i].x = rect_screen.left+(int)(i*x_scalor);
		QPoints[i].y = h/2 - (buffer+NUMTOSHOW_START+i)->qData*y_scalor;
		pDC->LineTo(QPoints[i]);
	}

		//FOR SHOW SAMPLE
	if(m_bSamp){
		pDC->SelectObject(&pn_point_q);
		for(i=0; i<NUMTOSHOW_END-NUMTOSHOW_START; i++){	
			pDC->MoveTo(QPoints[i]);
			pDC->LineTo(QPoints[i]);
			}
	}

	//FOR SHOW INDEX
	if(m_bNum){
		CString str_IdOfPoint;
	    pDC->SetBkColor(RGB(0,0,0));
	    pDC->SetTextColor(color_point_q);
		for(i=0; i<NUMTOSHOW_END-NUMTOSHOW_START; i++){
			str_IdOfPoint.Format("%d",i%rangebin);
			pDC->TextOut(QPoints[i].x+5, 
						 QPoints[i].y-5,
					     str_IdOfPoint);
		}
	}
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldFont);
}
