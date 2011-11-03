// ColorProgressCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ColorProgressCtrl.h"


// CColorProgressCtrl

IMPLEMENT_DYNAMIC(CColorProgressCtrl, CProgressCtrl)

CColorProgressCtrl::CColorProgressCtrl()
{
	m_nLower=0;
	m_nUpper=100;
	m_nCurrentPosition=0;
	m_nStep=10;
	m_clrBkGround=::GetSysColor(COLOR_3DFACE);
	m_clrText=COLORREF(RGB(255,255,255));
}

CColorProgressCtrl::~CColorProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(CColorProgressCtrl, CProgressCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CColorProgressCtrl message handlers
void CColorProgressCtrl::SetRange(int nLower,int nUpper)
{
	//This Function is to Set Range of the progress 
	m_nLower=nLower;
	m_nUpper=nUpper;
	m_nCurrentPosition=nLower;
	
	CProgressCtrl::SetRange(nLower,nUpper);
}

int CColorProgressCtrl::SetPos(int nPos)
{
	//Set the Position of the Progress
	m_nCurrentPosition=nPos;
	return (CProgressCtrl::SetPos(nPos));
}

void CColorProgressCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CProgressCtrl::OnPaint() for painting messages
	CMemDCPointer pMemDC(&dc);

	CRect rectClient;
	CRect rectBar;
	GetClientRect(rectClient);
	rectBar = rectClient;
	float right = (float)m_nCurrentPosition / (float)(m_nUpper) * (float)rectClient.right;
	rectBar.right = right ;
	DrawBar(pMemDC,rectClient,rectBar);
	
}


void CColorProgressCtrl::DrawBar(CMemDCPointer* pDC,const CRect& rectClient,CRect& rectBar)
{
   
	CBrush bk_brush;
	CBrush bar_brush;
	bk_brush.CreateSolidBrush(RGB(58,58,58));
		bar_brush.CreateSolidBrush(RGB(0,0,255));//(128,0,255));

	//Draw back ground
	if(m_nCurrentPosition<=m_nLower||m_nCurrentPosition>m_nUpper)
	{
		pDC->FillRect(&rectClient,&bk_brush);
		bk_brush.DeleteObject();
		bar_brush.DeleteObject();
		return;
	}
	
	//Draw bar
	pDC->FillRect(&rectClient,&bk_brush);
	pDC->FillRect(&rectBar,&bar_brush);
	bk_brush.DeleteObject();
	bar_brush.DeleteObject();
	
	//Draw text
	CString percent;
	percent.Format(_T("%d%%"),(int)(100*(float)m_nCurrentPosition/m_nUpper));
	pDC->SetTextColor(m_clrText);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(percent,(LPRECT)&rectClient,DT_VCENTER|DT_CENTER|DT_SINGLELINE);


	return;
}

BOOL CColorProgressCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;// CProgressCtrl::OnEraseBkgnd(pDC);
}
