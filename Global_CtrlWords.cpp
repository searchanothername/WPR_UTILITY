// Global_CtrlWords.cpp: implementation of the CGlobal_CtrlWords class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Global_CtrlWords.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int pccodemoving;//liuchen add it 2006/12/13
control_word_0_6 g_submode_ctrlwrds[G_BEAMNUMBERS];
control_word_0_6 g_nomal_ctrlwrds;
control_word_0_6 g_last;
BOOL b_nochanged = TRUE;
BOOL b_firstdownload;
float g_duty_cycle[G_BEAMNUMBERS] ;
float g_transmitter_pulsewidth[G_BEAMNUMBERS];


UINT Data0 = 0;
UINT Data1 = 1;
UINT Data2 = 2;
UINT Data4 = 4;
UINT Data8 = 8;


int g_curbeamnum = 0;

