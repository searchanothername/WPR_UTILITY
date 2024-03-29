// ColoredListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ColoredListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColoredListCtrl

CColoredListCtrl::CColoredListCtrl()
{
	//m_colRow1 = RGB(220,220,220);
	//m_colRow2 = RGB(247,247,247);

	m_colRow1 = RGB(240,247,249);
	m_colRow2 = RGB(229,232,239);

	//m_colRow1 = RGB(40,40,40);
	//m_colRow2 = RGB(70,70,70);
}

CColoredListCtrl::~CColoredListCtrl()
{
}


BEGIN_MESSAGE_MAP(CColoredListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CColoredListCtrl)
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColoredListCtrl message handlers

void CColoredListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
  *pResult = 0;

  LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;
  int iRow = lplvcd->nmcd.dwItemSpec;

  switch(lplvcd->nmcd.dwDrawStage)
  {
    case CDDS_PREPAINT :
    {
      *pResult = CDRF_NOTIFYITEMDRAW;
      return;
    }

    // Modify item text and or background
    case CDDS_ITEMPREPAINT:
    {
      lplvcd->clrText = RGB(0,0,0);
      // If you want the sub items the same as the item,
      // set *pResult to CDRF_NEWFONT
      *pResult = CDRF_NOTIFYSUBITEMDRAW;
      return;
    }

    // Modify sub item text and/or background
    case CDDS_SUBITEM | CDDS_PREPAINT | CDDS_ITEM:
    {
		
        if(iRow %2){
         lplvcd->clrTextBk = m_colRow2;
        }
        else{
          lplvcd->clrTextBk = m_colRow1;
        }
		

        *pResult = CDRF_DODEFAULT;
        return;
    }
  }
   



}

BOOL CColoredListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
  CRect rect;
  CColoredListCtrl::GetClientRect(rect);


  POINT mypoint;  
  
  CBrush brush0(m_colRow1);
  CBrush brush1(m_colRow2);


 
 int chunk_height=GetCountPerPage();
 pDC->FillRect(&rect,&brush1);

 for (int i=0;i<=chunk_height;i++)
 {
		
	
	GetItemPosition(i,&mypoint);
	rect.top=mypoint.y ;
	GetItemPosition(i+1,&mypoint);
	rect.bottom =mypoint.y;
	pDC->FillRect(&rect,i %2 ? &brush1 : &brush0);


 }

  brush0.DeleteObject();
  brush1.DeleteObject();

  return FALSE;
}
