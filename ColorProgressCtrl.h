#pragma once
#include "MemDC.h"

// CColorProgressCtrl

class CColorProgressCtrl : public CProgressCtrl
{
	DECLARE_DYNAMIC(CColorProgressCtrl)

public:
	CColorProgressCtrl();
	virtual ~CColorProgressCtrl();

	void SetTextColor(COLORREF color)	{m_clrText = color;}
	void SetBkColor(COLORREF color)		{m_clrBkGround = color;}
	void SetBarColor(COLORREF color)    {m_clrBar = color;}

	COLORREF GetTextColor(COLORREF color)	{return m_clrText;}
	COLORREF GetBkColor(COLORREF color)		{return m_clrBkGround;}
	COLORREF GetBarColor(COLORREF color)    {return m_clrBar;}

	int SetPos(int nPos);
	void SetRange(int nLower,int nUpper);
	void DrawBar(CMemDCPointer* pDC,const CRect& rectClient,CRect& rectBar);
	
private:
	COLORREF	m_clrBar;
	COLORREF    m_clrBkGround;
	COLORREF    m_clrText;
	int			m_nLower;
	int         m_nUpper;
	int			m_nStep;
	int			m_nCurrentPosition;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


