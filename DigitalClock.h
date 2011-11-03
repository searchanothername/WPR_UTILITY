
/********************************************************************************

  File:    DigitalClock.h"
  Author:  Mt.Hu (hmt-abc@163.com)
  Date:    2008/4/28

  Note:    Please include the comment if you use the file in your project

********************************************************************************/

#if !defined(AFX_DIGITALCLOCK_H__6308EC19_76C9_4BE5_8F53_B4DBB7B11340__INCLUDED_)
#define AFX_DIGITALCLOCK_H__6308EC19_76C9_4BE5_8F53_B4DBB7B11340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ALIGN_LEFT    0;
#define ALIGN_CENTER  1;
#define ALIGN_RIGHT   2;


/////////////////////////////////////////////////////////////////////////////
// CDigitalClock window

class CDigitalClock : public CStatic
{
// Construction
public:
	CDigitalClock();

// Attributes
public:	
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDigitalClock)
	//}}AFX_VIRTUAL

// Implementation
public:	
	virtual ~CDigitalClock();
	
	COLORREF GetTextColor();
	COLORREF GetBkColor();
	int GetSpace();
	int GetAlign();

	void SetClock(int nHour,int nMinute,int nSecond);
	void SetData(int nInteger,int nDecimal);//LIUChen add it .
	void SetSpace(int nSpace);
	void SetTextColor(COLORREF crText);
	void SetBkColor(COLORREF crBk);
	void SetAlign(int nAlign);

	// Generated message map functions
protected:
	//{{AFX_MSG(CDigitalClock)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:	
	
	void DrawSection1(int nLeft);
	void DrawSection2(int nLeft);
	void DrawSection3(int nLeft);
	void DrawSection4(int nLeft);
	void DrawSection5(int nLeft);
	void DrawSection6(int nLeft);
	void DrawSection7(int nLeft);
	void Draw2Dot(int nLeft);
	void DrawSingleNumber(int nNum,int nLeft);
	void DrawHour();
	void DrawMinute();
	void DrawSecond();
	void DrawTimer();
	void DrawData();//LIUCHEN ADD IT
	void DrawInteger();
	void DrawDecimal();
	void DrawDot(int nLeft);

	COLORREF m_crText;
	COLORREF m_crBk;
	CRect m_rect;	
	CDC m_memDC;
	int m_nAlign;
	int m_nWidth;	
	int m_nHour;
	int m_nMinute;
	int m_nSecond;
	int m_nSpace;
	int m_nXmargin;
	int m_nYmargin;
	//{LIUCHEN ADD IT
	int m_nInteger;
	int m_nDecimal;
	//}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGITALCLOCK_H__6308EC19_76C9_4BE5_8F53_B4DBB7B11340__INCLUDED_)
