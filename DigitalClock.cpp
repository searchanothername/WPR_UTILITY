
/********************************************************************************

  File:    DigitalClock.h"
  Author:  Mt.Hu (hmt-abc@163.com)
  Date:    2008/4/28

  Note:    Please include the comment if you use the file in your project

********************************************************************************/

// DigitalClock.cpp : implementation file
//

#include "stdafx.h"
#include "DigitalClock.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDigitalClock

CDigitalClock::CDigitalClock()
{	
	m_crBk = ::GetSysColor(COLOR_BTNFACE);
	m_crText = ::GetSysColor(COLOR_BTNTEXT);
	m_nAlign = 1;
	m_nWidth = 0;	
	m_nHour = 0;
	m_nMinute = 0;
	m_nSecond = 0;
	m_nSpace = 5;
	m_nXmargin = 10;
	m_nYmargin = 4;	
}

CDigitalClock::~CDigitalClock()
{
}


BEGIN_MESSAGE_MAP(CDigitalClock, CStatic)
	//{{AFX_MSG_MAP(CDigitalClock)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDigitalClock message handlers


void CDigitalClock::DrawSection1(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[4];
		point[0].x=nLeft+(int)(0.1*m_nWidth);
		point[0].y=m_nYmargin;

		point[1].x=nLeft+(int)(0.9*m_nWidth);
		point[1].y=m_nYmargin;

		point[2].x=nLeft+(int)(0.7*m_nWidth);
		point[2].y=(int)(0.2*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.3*m_nWidth);
		point[3].y=(int)(0.2*m_nWidth)+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,4,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();
		
		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[0]);			
	}	
}

void CDigitalClock::DrawSection2(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[5];
		point[0].x=nLeft+m_nWidth;
		point[0].y=(int)(0.1*m_nWidth)+m_nYmargin;

		point[1].x=nLeft+m_nWidth;
		point[1].y=(int)(0.8*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.9*m_nWidth);
		point[2].y=(int)(0.9*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.8*m_nWidth);
		point[3].y=(int)(0.8*m_nWidth)+m_nYmargin;

		point[4].x=nLeft+(int)(0.8*m_nWidth);
		point[4].y=(int)(0.3*m_nWidth)+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,5,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[4]);
		
		m_memDC.MoveTo(point[4]);
		m_memDC.LineTo(point[0]);
	}

	
}

void CDigitalClock::DrawSection3(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[5];
		point[0].x=nLeft+m_nWidth;
		point[0].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[1].x=nLeft+m_nWidth;
		point[1].y=(int)(1.8*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.8*m_nWidth);
		point[2].y=(int)(1.6*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.8*m_nWidth);
		point[3].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[4].x=nLeft+(int)(0.9*m_nWidth);
		point[4].y=m_nWidth+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,5,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[4]);
		
		m_memDC.MoveTo(point[4]);
		m_memDC.LineTo(point[0]);
	}
		
}

void CDigitalClock::DrawSection4(int nLeft)
{	
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[4];
		point[0].x=nLeft+(int)(0.1*m_nWidth);
		point[0].y=(int)(1.9*m_nWidth)+m_nYmargin;

		point[1].x=nLeft+(int)(0.9*m_nWidth);
		point[1].y=(int)(1.9*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.7*m_nWidth);
		point[2].y=(int)(1.7*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.3*m_nWidth);
		point[3].y=(int)(1.7*m_nWidth)+m_nYmargin;		

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,4,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[0]);		
	
	}

}

void CDigitalClock::DrawSection5(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[5];
		point[0].x=nLeft;
		point[0].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[1].x=nLeft;
		point[1].y=(int)(1.8*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.2*m_nWidth);
		point[2].y=(int)(1.6*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.2*m_nWidth);
		point[3].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[4].x=nLeft+(int)(0.1*m_nWidth);
		point[4].y=m_nWidth+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,5,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[4]);
		
		m_memDC.MoveTo(point[4]);
		m_memDC.LineTo(point[0]);
	}


}

void CDigitalClock::DrawSection6(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[5];
		point[0].x=nLeft;
		point[0].y=(int)(0.1*m_nWidth)+m_nYmargin;

		point[1].x=nLeft;
		point[1].y=(int)(0.8*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.1*m_nWidth);
		point[2].y=(int)(0.9*m_nWidth)+m_nYmargin;

		point[3].x=nLeft+(int)(0.2*m_nWidth);
		point[3].y=(int)(0.8*m_nWidth)+m_nYmargin;

		point[4].x=nLeft+(int)(0.2*m_nWidth);
		point[4].y=(int)(0.3*m_nWidth)+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,5,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[4]);
		
		m_memDC.MoveTo(point[4]);
		m_memDC.LineTo(point[0]);
	}

}

void CDigitalClock::DrawSection7(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CPoint point[6];
		point[0].x=nLeft+(int)(0.3*m_nWidth);
		point[0].y=(int)(0.9*m_nWidth)+m_nYmargin;

		point[1].x=nLeft+(int)(0.7*m_nWidth);
		point[1].y=(int)(0.9*m_nWidth)+m_nYmargin;

		point[2].x=nLeft+(int)(0.8*m_nWidth);
		point[2].y=m_nWidth+m_nYmargin;

		point[3].x=nLeft+(int)(0.7*m_nWidth);
		point[3].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[4].x=nLeft+(int)(0.3*m_nWidth);
		point[4].y=(int)(1.1*m_nWidth)+m_nYmargin;

		point[5].x=nLeft+(int)(0.2*m_nWidth);
		point[5].y=m_nWidth+m_nYmargin;

		CBrush br(m_crText);
		CRgn rgn;
		rgn.CreatePolygonRgn(point,6,ALTERNATE);
		m_memDC.FillRgn(&rgn,&br);

		br.DeleteObject();
		rgn.DeleteObject();

		m_memDC.MoveTo(point[0]);
		m_memDC.LineTo(point[1]);
		
		m_memDC.MoveTo(point[1]);
		m_memDC.LineTo(point[2]);
		
		m_memDC.MoveTo(point[2]);
		m_memDC.LineTo(point[3]);
		
		m_memDC.MoveTo(point[3]);
		m_memDC.LineTo(point[4]);
		
		m_memDC.MoveTo(point[4]);
		m_memDC.LineTo(point[5]);
		
		m_memDC.MoveTo(point[5]);
		m_memDC.LineTo(point[0]);
	}

}

void CDigitalClock::Draw2Dot(int nLeft)
{
	if (m_memDC.m_hDC!=NULL)
	{
		CBrush br(m_crText);				

		CRect rect;
		rect.SetRect(nLeft+(int)(0.3*m_nWidth),(int)(0.4*m_nWidth)+m_nYmargin,
			nLeft+(int)(0.6*m_nWidth),(int)(0.7*m_nWidth)+m_nYmargin);
		m_memDC.Ellipse(rect);
		CRgn rgn1;
		rgn1.CreateEllipticRgn(rect.left,rect.top,rect.right,rect.bottom);
		m_memDC.FillRgn(&rgn1,&br);

		rect.OffsetRect(0,(int)(0.8*m_nWidth)+m_nYmargin);
		m_memDC.Ellipse(rect);
		CRgn rgn2;
		rgn2.CreateEllipticRgn(rect.left,rect.top,rect.right,rect.bottom);
		m_memDC.FillRgn(&rgn2,&br);

		br.DeleteObject();
		rgn1.DeleteObject();
		rgn2.DeleteObject();
	}
}

void CDigitalClock::SetBkColor(COLORREF crBk)
{
	m_crBk = crBk;	

	DrawTimer();
}

void CDigitalClock::SetTextColor(COLORREF crText)
{
	m_crText = crText;
	
	DrawTimer();
}

void CDigitalClock::SetAlign(int nAlign)
{
	m_nAlign = nAlign;
	
	DrawTimer();
}

COLORREF CDigitalClock::GetBkColor()
{
	return m_crBk;
}

COLORREF CDigitalClock::GetTextColor()
{
	return m_crText;
}

int CDigitalClock::GetAlign()
{
	return m_nAlign;
}

void CDigitalClock::SetClock(int nHour, int nMinute, int nSecond)
{
	m_nHour = nHour;
	m_nMinute = nMinute;
	m_nSecond = nSecond;

	DrawTimer();	
}


void CDigitalClock::SetData(int i,int d)
{
    m_nInteger = i;
	m_nDecimal = d;
	DrawData();

	return;
}

void CDigitalClock::DrawHour()
{
	int nLeft=m_nXmargin;
	if (m_nHour<10)
	{
		DrawSingleNumber(0,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(m_nHour,nLeft);
	}
	else
	{
		TCHAR *c=new TCHAR[10];
		_itoa(m_nHour,c,10);
		int num1=c[0]-48;
		int num2=c[1]-48;
		DrawSingleNumber(num1,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(num2,nLeft);
	}
	nLeft+=m_nWidth;
	Draw2Dot(nLeft);	
}

void CDigitalClock::DrawMinute()
{
	int nLeft=m_nXmargin+3*m_nWidth+m_nSpace;
	if (m_nMinute<10)
	{
		DrawSingleNumber(0,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(m_nMinute,nLeft);
	}
	else
	{
		TCHAR c[10]={0};		
		_itoa(m_nMinute,c,10);		
		int num1=c[0]-48;
		int num2=c[1]-48;
		DrawSingleNumber(num1,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(num2,nLeft);		
	}
}

void CDigitalClock::DrawSecond()
{
	int nLeft=m_nXmargin+6*m_nWidth+2*m_nSpace;
	if (m_nSecond<10)
	{
		DrawSingleNumber(0,nLeft);
		nLeft+=(int)(1.4*m_nWidth);
		DrawSingleNumber(m_nSecond,nLeft);
	}
	else
	{
		TCHAR *c=new TCHAR[10];
		_itoa(m_nSecond,c,10);
		int num1=c[0]-48;
		int num2=c[1]-48;
		DrawSingleNumber(num1,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(num2,nLeft);	
	}
}

void CDigitalClock::DrawTimer()
{	
	if (m_memDC.m_hDC!=NULL)
	{	
		
		GetClientRect(&m_rect);		
		
		m_nWidth = (int)(m_rect.Height()-2*m_nYmargin)/2;
		if (0 == m_nAlign)
		{			
			m_nXmargin = m_nYmargin;
		}
		else if (2 == m_nAlign)
		{			
			m_nXmargin = m_rect.Width()-8*m_nWidth-3*m_nSpace-m_nYmargin;
		}
		else
		{
			m_nXmargin = (int)(m_rect.Width()-8*m_nWidth-3*m_nSpace)/2;
		}
		

		m_memDC.FillSolidRect(m_rect,m_crBk);

		CPen pen(PS_SOLID,1,m_crText);
		CPen* pOldPen=m_memDC.SelectObject(&pen);

		DrawHour();
		DrawMinute();
		DrawSecond();

		Invalidate();
		
		m_memDC.SelectObject(pOldPen);
		pen.DeleteObject();
	}
}


void CDigitalClock::DrawData()
{
	if (m_memDC.m_hDC!=NULL)
	{	
		
		GetClientRect(&m_rect);		
		
		m_nWidth = (int)(m_rect.Height()-2*m_nYmargin)/2;
		if (0 == m_nAlign)
		{			
			m_nXmargin = m_nYmargin;
		}
		else if (2 == m_nAlign)
		{			
			m_nXmargin = m_rect.Width()-8*m_nWidth-3*m_nSpace-m_nYmargin;
		}
		else
		{
			m_nXmargin = (int)(m_rect.Width()-8*m_nWidth-3*m_nSpace)/2;
		}
		

		m_memDC.FillSolidRect(m_rect,m_crBk);

		CPen pen(PS_SOLID,1,m_crText);
		CPen* pOldPen=m_memDC.SelectObject(&pen);

		DrawInteger();
		DrawDecimal();

		Invalidate();
		
		m_memDC.SelectObject(pOldPen);
		pen.DeleteObject();
	}
	return;
}


void CDigitalClock::DrawInteger()
{
    int nLeft=m_nXmargin;
	if (m_nInteger<10)
	{
		DrawSingleNumber(0,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(m_nInteger,nLeft);
	}
	else
	{
		TCHAR *c=new TCHAR[10];
		_itoa(m_nInteger,c,10);
		int num1=c[0]-48;
		int num2=c[1]-48;
		DrawSingleNumber(num1,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(num2,nLeft);
	}
	nLeft+=m_nWidth;
	DrawDot(nLeft);
	return;
}

void CDigitalClock::DrawDecimal()
{
	int nLeft=m_nXmargin+3*m_nWidth+m_nSpace;
	if (m_nDecimal<10)
	{
		DrawSingleNumber(0,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(m_nDecimal,nLeft);
	}
	else
	{
		TCHAR c[10]={0};		
		_itoa(m_nDecimal,c,10);		
		int num1=c[0]-48;
		int num2=c[1]-48;
		DrawSingleNumber(num1,nLeft);
		nLeft+=m_nWidth+m_nSpace;
		DrawSingleNumber(num2,nLeft);		
	}
	return;
}

void CDigitalClock::DrawDot(int nLeft)
{
  if (m_memDC.m_hDC!=NULL)
	{
		CBrush br(m_crText);				

		CRect rect;
		rect.SetRect(nLeft+(int)(0.3*m_nWidth),(int)(0.4*m_nWidth)+m_nYmargin,
			nLeft+(int)(0.6*m_nWidth),(int)(0.7*m_nWidth)+m_nYmargin);
	/*	m_memDC.Ellipse(rect);
		CRgn rgn1;
		rgn1.CreateEllipticRgn(rect.left,rect.top,rect.right,rect.bottom);
		m_memDC.FillRgn(&rgn1,&br);
*/
		rect.OffsetRect(0,(int)(0.8*m_nWidth)+m_nYmargin);
		m_memDC.Ellipse(rect);
		CRgn rgn2;
		rgn2.CreateEllipticRgn(rect.left,rect.top,rect.right,rect.bottom);
		m_memDC.FillRgn(&rgn2,&br);

		br.DeleteObject();
		rgn2.DeleteObject();
	}
}



void CDigitalClock::DrawSingleNumber(int nNum,int nLeft)
{
	switch (nNum)
	{
	case 0:
		DrawSection1(nLeft);
		DrawSection2(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);
		DrawSection5(nLeft);
		DrawSection6(nLeft);
		break;
	case 1:		
		DrawSection2(nLeft);
		DrawSection3(nLeft);		
		break;
	case 2:
		DrawSection1(nLeft);
		DrawSection2(nLeft);
		DrawSection4(nLeft);
		DrawSection5(nLeft);
		DrawSection7(nLeft);
		break;
	case 3:
		DrawSection1(nLeft);
		DrawSection2(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);		
		DrawSection7(nLeft);
		break;
	case 4:		
		DrawSection2(nLeft);
		DrawSection3(nLeft);		
		DrawSection6(nLeft);
		DrawSection7(nLeft);
		break;
	case 5:
		DrawSection1(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);
		DrawSection6(nLeft);
		DrawSection7(nLeft);
		break;
	case 6:
		DrawSection1(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);
		DrawSection5(nLeft);
		DrawSection6(nLeft);
		DrawSection7(nLeft);
		break;
	case 7:
		DrawSection1(nLeft);
		DrawSection2(nLeft);
		DrawSection3(nLeft);		
		break;
	case 8:
		DrawSection1(nLeft);
		DrawSection2(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);
		DrawSection5(nLeft);
		DrawSection6(nLeft);
		DrawSection7(nLeft);
		break;
	case 9:
		DrawSection1(nLeft);
		DrawSection3(nLeft);
		DrawSection4(nLeft);
		DrawSection2(nLeft);
		DrawSection6(nLeft);
		DrawSection7(nLeft);
		break;
	default:
		;
	}

}

void CDigitalClock::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	GetClientRect(&m_rect);		
	
	if (m_memDC.m_hDC==NULL)
	{
		m_nYmargin = (int)(0.1*m_rect.Height());
		CBitmap bmp;
		CBitmap* pOldBmp;

		m_memDC.CreateCompatibleDC(&dc);
		bmp.CreateCompatibleBitmap(&dc,m_rect.Width(),m_rect.Height());
		pOldBmp=m_memDC.SelectObject(&bmp);		
	}	
			
	dc.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&m_memDC,0,0,SRCCOPY);	
	
}

void CDigitalClock::SetSpace(int nSpace)
{
	m_nSpace = nSpace;

	DrawTimer();
}

int CDigitalClock::GetSpace()
{
	return m_nSpace;
}






