#ifndef _MEM_DC_H
#define _MEM_DC_H
/////////////////////////////////////////////////////
//I create this class for draw image in the memory 
//and copy it from memory to memory
//liuchen 2006/2/16
//////////////////////////////////////////////////////
class CMemDCPointer : public CDC 
{	
public:
	CMemDCPointer(CDC* pDC) : CDC(), m_oldBitmap(NULL), m_pDC(pDC)
	{
		if(!m_pDC)
		{
			AfxMessageBox("Pointer of DC is NULL.");
			return;
		}
		CreateCompatibleDC(pDC);
		pDC->GetClipBox(&m_rect);
		m_newbitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
		m_oldBitmap = SelectObject(&m_newbitmap);
		SetWindowOrg(m_rect.left, m_rect.top);
	}
	
	~CMemDCPointer() 
	{
			m_pDC->BitBlt(m_rect.left, 
				          m_rect.top, 
						  m_rect.Width(), 
						  m_rect.Height(), 
				          this, 
						  m_rect.left, 
						  m_rect.top, 
						  SRCCOPY);

			SelectObject(m_oldBitmap);
	}

	CMemDCPointer* operator->() {return this;}
	operator CMemDCPointer*() {return this;}

private:
	CBitmap		m_newbitmap;		
	CBitmap*	m_oldBitmap;	
	CDC*		m_pDC;			
	CRect		m_rect;			
	BOOL		m_bMemDC;	
};

#endif