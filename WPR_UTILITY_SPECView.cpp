// WPR_UTILITY_SPECView.cpp : implementation of the CWPR_UTILITY_SPECView class
//

#include "stdafx.h"
#include "resource.h"
//#include "WPR_UTILITY_SPEC.h"
#include <time.h>
#include "WPR_UTILITY_SPECDoc.h"
#include "WPR_UTILITY_SPECView.h"
#include "DataHandlor.h"
#include "Global_CtrlWords.h"
#include "Global_Advanced.h"
#include "Global.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITY_SPECView
DWORD WINAPI Listener(LPVOID lpParameter);
extern CDataHandlor data;
extern HANDLE g_hSpecsFinished;
extern volatile bool bProductProcessing;
//extern volatile BOOL bSpectrasViewEnable;
//extern CCriticalSection cs;

IMPLEMENT_DYNCREATE(CWPR_UTILITY_SPECView, CZoomView)

BEGIN_MESSAGE_MAP(CWPR_UTILITY_SPECView, CZoomView)
	//{{AFX_MSG_MAP(CWPR_UTILITY_SPECView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CZoomView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CZoomView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CZoomView::OnFilePrintPreview)
	ON_COMMAND(ID_ZERO, OnZero)
	ON_COMMAND(ID_ZOOMOUT, OnZoomOut)
	ON_COMMAND(ID_ZOOMIN, OnZoomIn)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITY_SPECView construction/destruction
CWPR_UTILITY_SPECView* pSpecView = 0;
CWPR_UTILITY_SPECView::CWPR_UTILITY_SPECView()
{
	// TODO: add construction code here
    bProductProcessing = false;
	color_grid = RGB(58,58,58);   
	color_spec = RGB(0,0,0);
	color_marker = RGB(128,128,255);//0,64,128);
	color_peak = RGB(255,255,255);//(0,64,128);

	pn_grid.CreatePen(0,0,color_grid);
	pn_spec.CreatePen(0,0,color_spec);
	pn_marker.CreatePen(0,0,color_marker);
	pn_peak.CreatePen(0,0,color_peak);
	// TODO: Add extra initialization here
    XCAPSNUM = 16;
	YCAPSNUM = 16;

	font_height.CreateFont(2, 0, 0, 0, FW_REGULAR, 
		     0, 0, 0, 0, 0, 0, 0, 0, "Courier New");
	m_bSelectMode = FALSE;

/*
	
	bRun = TRUE;
	DWORD nThreadId;
	hThread = CreateThread(0,0,Listener, this,0,&nThreadId);
	CloseHandle(hThread);
	*/
}


CWPR_UTILITY_SPECView::~CWPR_UTILITY_SPECView()
{
	/*
	cs.Lock();
		bSpectrasViewEnable = FALSE;
	cs.Unlock();
	bRun = FALSE;
	DWORD dwExitCode = STILL_ACTIVE;
	BOOL  bStat = TRUE;
	while((dwExitCode == STILL_ACTIVE) && bStat){
		bStat =  GetExitCodeThread(hThread, &dwExitCode);
	}
	*/
	pSpecView = 0;
	return;
}

BOOL CWPR_UTILITY_SPECView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    pSpecView = this;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITY_SPECView drawing

void CWPR_UTILITY_SPECView::OnDraw(CDC* pDC)
{
	CWPR_UTILITY_SPECDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	GetClientRect(&rect_screen);
	//CMemDCPointer pMemDC(pDC);

	DrawSpectras(pDC);
	//DrawMarker(pDC);
    if (m_bSelectMode == TRUE) 
	{
		CPen* pPen = pDC->GetCurrentPen();
		LOGPEN logPen;
		pPen->GetLogPen(&logPen);
		logPen.lopnColor = RGB(128,128,255);
		logPen.lopnStyle = PS_SOLID;

		LOGBRUSH logBrush;
		::ZeroMemory(&logBrush,sizeof(logBrush));
		logBrush.lbStyle = BS_HOLLOW;
		
		CPen newPen;
		newPen.CreatePenIndirect(&logPen);
		CBrush newBrush;
		newBrush.CreateBrushIndirect(&logBrush);
		CPen* oldPen = pDC->SelectObject(&newPen);
		CBrush* oldBrush = pDC->SelectObject(&newBrush);

		pDC->Rectangle(m_rubberBand);

		pDC->SelectObject(oldBrush);
		pDC->SelectObject(oldPen);
	}

}

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITY_SPECView printing

BOOL CWPR_UTILITY_SPECView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWPR_UTILITY_SPECView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWPR_UTILITY_SPECView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITY_SPECView diagnostics

#ifdef _DEBUG
void CWPR_UTILITY_SPECView::AssertValid() const
{
	CView::AssertValid();
}

void CWPR_UTILITY_SPECView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWPR_UTILITY_SPECDoc* CWPR_UTILITY_SPECView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWPR_UTILITY_SPECDoc)));
	return (CWPR_UTILITY_SPECDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITY_SPECView message handlers
void CWPR_UTILITY_SPECView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bSelectMode == FALSE) 
	{
		m_bSelectMode = TRUE;
		m_ptStart = point;
		DPtoLP(&m_ptStart);
		m_rubberBand.SetRect(m_ptStart, m_ptStart);
		Invalidate(FALSE);
	}
	CView::OnLButtonDown(nFlags, point);
}

void CWPR_UTILITY_SPECView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bSelectMode != FALSE) 
	{
		DPtoLP(&point);
		m_rubberBand.SetRect(m_ptStart, point);
		m_rubberBand.NormalizeRect();
	}
	
	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}

void CWPR_UTILITY_SPECView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bSelectMode = FALSE;
	Invalidate(FALSE);

	SetZoomArea(m_rubberBand);
	CView::OnLButtonUp(nFlags, point);
}


void CWPR_UTILITY_SPECView::DrawSpectras(CDC* pDC)
{
	/*
	srand(time(0));
	int width = rect_screen.Width();
	int height = rect_screen.Height()/10;
	int i = 0;

	CPen* oldPen = pDC->GetCurrentPen();
	pDC->SelectObject(pn_spec);

	
	for (i = 0; i < 10; i++)
	{
		pDC->FillSolidRect(CRect(0, i * height, \
		width, i * height + height), RGB(rand() % 255, rand() % 255, rand() % 255));
		//pDC->MoveTo(0,i*height);
		//pDC->LineTo(width,(i+1)*height);
	}
	pDC->SelectObject(oldPen);
	*/
	if(!bProductProcessing)
		return;

	nFFT = data.nFFT;
	nBeamId = g_curbeamnum;
	if(g_curbeamnum %2 == LOMODE_ID)
	{
		nRangebin =  global_advance.dmasetting.nDMA_Low/2\
						-global_advance.dspsetting.nBeginGateMoveL;
	}
	else if(g_curbeamnum %2 == HIMODE_ID)
	{
		nRangebin =  global_advance.dmasetting.nDMA_High/2\
						-global_advance.dspsetting.nBeginGateMoveH;
	}

    CPen* oldPen = pDC->GetCurrentPen();
	CFont* oldFont = pDC->GetCurrentFont();
	double w = rect_screen.Width();
	double h = (double)rect_screen.Height()/(double)nRangebin;
	double* buffer= data._spec_avged_cpy->spectra;
	
	pDC->SelectObject(&font_height);
	for(int i = 0; i<nRangebin; i++)
	{
		pDC->SelectObject(&pn_spec);
		double fmax = global.spec_avg_limit.limit[i].max;
		double fmin = global.spec_avg_limit.limit[i].min;
		double y_offset = (i-1)*h+h*0.8;
		double yScalor =  (double)h*(0.6) / (fmax-fmin);
	    double xScalor = w/nFFT;
		
		SS_Point.x = rect_screen.left;
		SS_Point.y = rect_screen.bottom-5-y_offset- (*(buffer+MAXFFTPOINTS*i)-fmin) *yScalor;
		pDC->MoveTo(SS_Point);
		
		for(int j=0;j<nFFT; j++)
		{
			SS_Point.x = rect_screen.left+(int)(j*xScalor);
			SS_Point.y = rect_screen.bottom-5-y_offset- (*(buffer+MAXFFTPOINTS*i+j)-fmin)*yScalor;
			pDC->LineTo(SS_Point);
		}
		pDC->SelectObject(oldPen);

		int loc = global.spec_avg_limit.peak_loc[i];
		int val = global.spec_avg_limit.peak_val[i];
		int sp = rect_screen.bottom-5-y_offset - (val-fmin)*yScalor;

		pDC->SelectObject(&pn_peak);
		pDC->MoveTo(rect_screen.left+loc*xScalor-2,
					sp);
		pDC->LineTo(rect_screen.left+loc*xScalor+2,
					sp);

		pDC->MoveTo(rect_screen.left+loc*xScalor,
					sp-2);
		pDC->LineTo(rect_screen.left+loc*xScalor,
					sp+2);
		pDC->SelectObject(oldPen);

		CString strHeight;
		strHeight.Format("%6.2fkm",i*global.basic.basicinfo.oblique_struct.pulse_width_low*0.15/1000.0);

		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(rect_screen.left+loc*xScalor-5,
			        sp+2,strHeight);
		
	}

	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldPen);
}

void CWPR_UTILITY_SPECView::DrawMarker(CDC* pDC)
{
}

void CWPR_UTILITY_SPECView::OnZero()
{
	m_zoomFactor = 1.0;
	SetZoomScale(m_zoomFactor);
	SetZoomArea(rect_screen);
}

void CWPR_UTILITY_SPECView::OnZoomIn()
{
	SetZoomScale(m_zoomFactor + 1.0f);
	return;
}

void CWPR_UTILITY_SPECView::OnZoomOut()
{
	if(m_zoomFactor>1.0f)
	SetZoomScale(m_zoomFactor - 1.0f);
	return;
}

/*
DWORD WINAPI Listener(LPVOID lpParameter)
{	
	CWPR_UTILITY_SPECView* pView = (CWPR_UTILITY_SPECView*) lpParameter;
	if(pView){
		while(pView->bRun)
		{
			cs.Lock();
			DWORD stat = ::WaitForSingleObject(g_hSpecsFinished, 100);
			if(stat == WAIT_OBJECT_0){
				pView->nFFT = data.nFFT;
				pView->nBeamId = g_curbeamnum;
				if(g_curbeamnum %2 == LOMODE_ID)
				{
					pView->nRangebin =  global_advance.dmasetting.nDMA_Low/2\
						-global_advance.dspsetting.nBeginGateMoveL;
				}
				else if(g_curbeamnum %2 == HIMODE_ID)
				{
					pView->nRangebin =  global_advance.dmasetting.nDMA_High/2\
						-global_advance.dspsetting.nBeginGateMoveH;
				}

				
				if(bSpectrasViewEnable)
				   pView->Invalidate(FALSE);
				else{
					cs.Unlock();
					return 0;
				}
			}
			cs.Unlock();
		};
	}

	return 0;
}
*/

