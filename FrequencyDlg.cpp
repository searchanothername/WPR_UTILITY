// FrequencyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "FrequencyDlg.h"
#include "Global.h"
#include "DataView.h"
#include "DataHandlor.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrequencyDlg dialog

extern CDataHandlor data;
CFrequencyDlg::CFrequencyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFrequencyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrequencyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFrequencyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrequencyDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrequencyDlg, CDialog)
	//{{AFX_MSG_MAP(CFrequencyDlg)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_SHOW_SPEC_SINGLE_VIEW, ShowSpecSingle)
	ON_MESSAGE(WM_SHOW_SPEC_AVG_VIEW, ShowSpecAvg)
	ON_MESSAGE(WM_UPDAE_MARKER,ShowMarker)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrequencyDlg message handlers

BOOL CFrequencyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	color_grid = RGB(58,58,58);   
	color_single_spec = RGB(255,255,0);
	color_avg_spec = RGB(255,128,64);//(128,0,255);
	color_marker = RGB(128,128,255);//0,64,128);
	color_peak = RGB(255,0,0);//(0,64,128);
	color_noise = RGB(20,20,20);

	pn_grid.CreatePen(0,0,color_grid);
	pn_single.CreatePen(0,0,color_single_spec);
	pn_avg.CreatePen(0,0,color_avg_spec);
	pn_marker.CreatePen(0,0,color_marker);
	pn_peak.CreatePen(0,0,color_peak);
	pn_noise.CreatePen(0,0, color_noise);
	// TODO: Add extra initialization here

		
    XCAPSNUM = 16;
	YCAPSNUM = 16;

	m_nFocusRangeBin = 22;
	nSpecId = -1; 
	nBeamId = -1;
	m_nValue = 0;

	//Initialize the font
	font.CreateFont(15, 0, 0, 0, FW_REGULAR, 
		     0, 0, 0, 0, 0, 0, 0, 0, "Courier New");


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFrequencyDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	GetClientRect(&rect_screen);
	CMemDCPointer pMemDC(&dc);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetBkColor(RGB(0,0,0));

    DrawBackGround(pMemDC);
	if(m_bSingle)
		DrawSingleSpec(pMemDC);
	if(m_bAvg)
		DrawAvgSpec(pMemDC);


	//DrawMarker(pMemDC);
	// Do not call CDialog::OnPaint() for painting messages
}

void CFrequencyDlg::DrawBackGround(CMemDCPointer* pDC)
{
	CPen* oldPen = pDC->GetCurrentPen();
	CBrush* oldBrush = pDC->GetCurrentBrush();

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
	return;
}

void CFrequencyDlg::ShowSpecSingle(UINT wParam, UINT lParam)
{

	CString str;
	str.Format("SID: %d | BID: %d",wParam, lParam);
	g_DataView->GetDlgItem(IDC_EDIT_CHECKER)->SetWindowText(str);
	m_bSingle = g_DataView->m_bSingle;
	m_bAvg = g_DataView->m_bAvg;
	m_bShowNoiseLevel = g_DataView->m_bNoiseLevel;
	m_bShowPeakS = g_DataView->m_bPeakS;
	m_bShowPeakA = g_DataView->m_bPeakA;


	m_nFocusRangeBin = g_DataView->m_nFocusRangeBin;
	nSpecId = wParam;
	nBeamId = lParam;
	nFFT = data.nFFT;
	if(nSpecId == -1 || nBeamId == -1)
		return;
	else
		::InvalidateRect(m_hWnd,&rect_screen,FALSE);
	return;
}


void CFrequencyDlg::ShowSpecAvg(UINT wParam, UINT lParam)
{
	m_nFocusRangeBin = g_DataView->m_nFocusRangeBin;
	nSpecId = wParam;
	nBeamId = lParam;
	nFFT = data.nFFT;
	if(nSpecId == -1 || nBeamId == -1)
		return;
	else
		::InvalidateRect(m_hWnd,&rect_screen,FALSE);
	return;
}

void CFrequencyDlg::ShowMarker(UINT wParam, UINT lParam)
{
	m_nValue = wParam;
	nFFT = data.nFFT;
	::InvalidateRect(m_hWnd,&rect_screen,FALSE);
	return;
}

void CFrequencyDlg::DrawMarker(CMemDCPointer* pDC)
{
    CPen* oldPen = pDC->GetCurrentPen();
	CFont* oldFont = pDC->GetCurrentFont();
	
	pDC->SelectObject(&pn_marker);
	double w = rect_screen.Width();
	double h = rect_screen.Height();
	double xScalor = w/nFFT;

    pDC->MoveTo(rect_screen.left+m_nValue*xScalor,rect_screen.top);
	pDC->LineTo(rect_screen.left+m_nValue*xScalor,rect_screen.bottom);

	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldPen);

	return;
}

void CFrequencyDlg::DrawSingleSpec(CMemDCPointer* pDC)
{
    CPen* oldPen = pDC->GetCurrentPen();
	CFont* oldFont = pDC->GetCurrentFont();
	CPen newPen, peakPen;	
	CBrush br, br_peak;
	newPen.CreatePen(0,0,RGB(255,255,255));
	br.CreateSolidBrush(RGB(255,255,255));
	peakPen.CreatePen(0,0,RGB(255,0,255));
	br_peak.CreateSolidBrush(RGB(255,0,255));
	
	
	double w = rect_screen.Width();
	double h = rect_screen.Height();
	double fmax = global.spec_single_limit.limit[m_nFocusRangeBin].max;
	double fmin = global.spec_single_limit.limit[m_nFocusRangeBin].min;
	int loc = global.spec_single_limit.limit[m_nFocusRangeBin].max_loc;

    double yScalor =  (double)h*(0.6) / (fmax-fmin);
	double xScalor = w/nFFT;

    int rangebin = 0;
	int fftnum = data.nFFT;

	double* buffer;
	if(nBeamId%2==1){
		rangebin = data._RANGEBIN_LOW;
	}
	else{
		rangebin = data._RANGEBIN_HIGH;
	}
	buffer= data._spec_single->spectra;

	//FONT SETTING
    pDC->SelectObject(&font);


	//DRAW MAKER
	pDC->SelectObject(&newPen);
	pDC->SelectObject(&br);

	CPoint maker(rect_screen.left+m_nValue*xScalor, 
		h*0.8- (*(buffer+MAXFFTPOINTS*m_nFocusRangeBin+m_nValue)-fmin)*yScalor); 
    //DRAW INFORMATION
	CString str;
	str.Format("Loc: %d Val: %6.2f", m_nValue, 
		*(buffer+MAXFFTPOINTS*m_nFocusRangeBin+m_nValue));
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	if(m_nValue<fftnum/2)
		pDC->TextOut(maker.x, maker.y-30, str);
	else
		pDC->TextOut(maker.x-150, maker.y-30, str);

	CPoint point[3] = {CPoint(maker.x-10/2, maker.y-10*0.866),
					   CPoint(maker.x+10/2, maker.y-10*0.866),
					   maker};

	pDC->Polygon(point, 3);

    //DRAW PEAKER
	if(m_bShowPeakS)
	{
		pDC->SelectObject(&peakPen);
		pDC->SelectObject(&br_peak);
		CPoint maker(rect_screen.left+loc*xScalor, 
			h*0.8- (fmax-fmin)*yScalor);

		CString str;
		str.Format("Loc: %d Val: %6.2f", loc, fmax);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,0,255));
		if(m_nValue<fftnum/2)
			pDC->TextOut(maker.x, maker.y-30, str);
		else
			pDC->TextOut(maker.x-150, maker.y-30, str);
		
		CPoint point[3] = {CPoint(maker.x-10/2, maker.y-10*0.866),
			CPoint(maker.x+10/2, maker.y-10*0.866),
			maker};
		
		pDC->Polygon(point, 3);

	}



    //DRAW SPECTRUM
	pDC->SelectObject(&pn_single);
	SS_Point[0].x = rect_screen.left;
	SS_Point[0].y = h*0.8- (*(buffer+MAXFFTPOINTS*m_nFocusRangeBin)-fmin) *yScalor;
	pDC->MoveTo(SS_Point[0]);
	for(int i=0;i<fftnum; i++)
	{
		SS_Point[i].x = rect_screen.left+(int)(i*xScalor);
		SS_Point[i].y = h*0.8- (*(buffer+MAXFFTPOINTS*m_nFocusRangeBin+i)-fmin)*yScalor;
		pDC->LineTo(SS_Point[i]);
	}

	
	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldPen);


	return;
}

void CFrequencyDlg::DrawAvgSpec(CMemDCPointer* pDC)
{

	CPen* oldPen = pDC->GetCurrentPen();
	CFont* oldFont = pDC->GetCurrentFont();
	CPen newPen, noiseTextPen;
	CBrush br,br_peak;
	newPen.CreatePen(0,0,RGB(0,255,0));
	br.CreateSolidBrush(RGB(0,255,0));
	br_peak.CreateSolidBrush(color_peak);
	noiseTextPen.CreatePen(0,0,RGB(255,255,255));


	double w = rect_screen.Width();
	double h = rect_screen.Height();

	double fmax = global.spec_avg_limit.limit[m_nFocusRangeBin].max;
	double fmin = global.spec_avg_limit.limit[m_nFocusRangeBin].min;
	int loc = global.spec_avg_limit.limit[m_nFocusRangeBin].max_loc;

    double yScalor =  (double)h*(0.6) / (fmax-fmin);
	double xScalor = w/nFFT;

    int rangebin = 0;
	int fftnum = data.nFFT;

	double* buffer;
	if(nBeamId%2==1){
		rangebin = data._RANGEBIN_LOW;
	}
	else{
		rangebin = data._RANGEBIN_HIGH;
	}
	buffer= data._spec_avged_cpy->spectra;

	//FONT SETTING
    pDC->SelectObject(&font);

	//DRAW MAKER
	pDC->SelectObject(&newPen);
	pDC->SelectObject(&br);

	CPoint maker(rect_screen.left+m_nValue*xScalor, 
		h*0.8- (*(buffer+MAXFFTPOINTS*m_nFocusRangeBin+m_nValue)-fmin)*yScalor);

	//DRAW INFORMATION
	CString str;
	str.Format("Loc: %d Val: %6.2f", m_nValue, 
		*(buffer+MAXFFTPOINTS*m_nFocusRangeBin+m_nValue));
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,255,0));
	if(m_nValue<fftnum/2)
		pDC->TextOut(maker.x, maker.y-30, str);
	else
		pDC->TextOut(maker.x-150, maker.y-30, str);


	CPoint point[3] = {CPoint(maker.x-10/2, maker.y-10*0.866),
					   CPoint(maker.x+10/2, maker.y-10*0.866),
					   maker};

	pDC->Polygon(point, 3);


	//DRAW NOISE
	if(m_bShowNoiseLevel){
	
		
		if(fabs(data._noise_level->noise_level[m_nFocusRangeBin])> 1e-11){
			CRect r(rect_screen.left, h*0.8 - (data._noise_level->noise_level[m_nFocusRangeBin]-fmin)*yScalor,
				rect_screen.right,rect_screen.bottom);
		
			pDC->SelectObject(&noiseTextPen);
			CBrush brNoise;
			brNoise.CreateHatchBrush( HS_DIAGCROSS, color_noise );
			pDC->SelectObject(&brNoise);
			pDC->Rectangle( &r);


			CString strNoise;
			strNoise.Format("Noise Level: %6.2f",data._noise_level->noise_level[m_nFocusRangeBin]);
			pDC->SetBkMode(TRANSPARENT);
	        pDC->SetTextColor(RGB(255,255,255));
			pDC->TextOut(r.CenterPoint().x-20,
					r.CenterPoint().y,
					strNoise);
		}	
	}

	//DRAW PEAK 
	if(m_bShowPeakA)
	{
		pDC->SelectObject(&pn_peak);
		pDC->SelectObject(&br_peak);
		CPoint maker(rect_screen.left+loc*xScalor, 
			h*0.8- (fmax-fmin)*yScalor);

		CString str;
		str.Format("Loc: %d Val: %6.2f", loc, fmax);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(color_peak);
		if(m_nValue<fftnum/2)
			pDC->TextOut(maker.x, maker.y-30, str);
		else
			pDC->TextOut(maker.x-150, maker.y-30, str);

		
		CPoint point[3] = {CPoint(maker.x-10/2, maker.y-10*0.866),
			CPoint(maker.x+10/2, maker.y-10*0.866),
			maker};
		
		pDC->Polygon(point, 3);

	}



	//DRAW SPECTRUM 
	pDC->SelectObject(&pn_avg);
	SA_Point[0].x = rect_screen.left;
	SA_Point[0].y = h*0.8- (*(buffer+MAXFFTPOINTS*m_nFocusRangeBin)-fmin) *yScalor;
	pDC->MoveTo(SS_Point[0]);
	for(int i=0;i<fftnum; i++)
	{
		SA_Point[i].x = rect_screen.left+(int)(i*xScalor);
		SA_Point[i].y = h*0.8- (*(buffer+MAXFFTPOINTS*m_nFocusRangeBin+i)-fmin)*yScalor;
		pDC->LineTo(SA_Point[i]);
	}

	//pDC->SelectObject(&pn_peak);
    //pDC->MoveTo(rect_screen.left,h*0.8-(global.spec_avg_limit.limit[m_nFocusRangeBin].max-fmin)*yScalor);
	//pDC->LineTo(rect_screen.right,h*0.8-(global.spec_avg_limit.limit[m_nFocusRangeBin].max-fmin)*yScalor);


	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldPen);

	return;
}


HBRUSH CFrequencyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return m_bkBrush;
}
