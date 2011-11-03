// Global.cpp: implementation of the Global class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Global.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Global::Global()
{
     basic.SetFileName("BasicSetting.dat");
	 g_shutdown = false;
}

Global::~Global()
{
	g_shutdown = true;
}

Global global;
int g_test_strt;
int g_test_end ;    
int g_dop_freq_selected;
int	g_rf_freq_selected  ;
int	g_rf_lev_atten_sel;
int g_lo_phase_ctrl; 
int	g_bm_dir_change;
int g_coax_switch;
int g_dop_test_ctrl;  
int	g_noise_source;
int	g_sm_reset ;
int	g_trans_ctrl;
int	g_signal_source	;
int	g_signal_output;
int	g_RF_attenuation;
int g_RF_gate_moving;
int g_DIF_gate_moving;
int g_PC_code_moving;
int g_scalednumfftpts = 3;
int g_timedomainavg = 0;
int g_cur_prt[G_KMAXBEAMS] = {0};


float g_kpulse_rep_period[G_KMAXBEAMS] = {
(float)94.375,//154.514;//EH
(float)67.708,//100.694;//EL
(float)94.375,//154.514;//NH
(float)67.708,//100.694;//NL
(float)90.6,//148.333;  //VH
(float)65,//96.667;     //VL 
(float)94.375,          //WH
(float)67.708,          //WL
(float)94.375,          //SH
(float)67.708           //SL
};

int g_ktda_samples[G_KMAXBEAMS] = {
 70,//EH
 97,//EL
 70,//NH
 97,//NL
 80,//VH
112,//VL
 70,//WH
 97,//WL
 70,//SH
 97//SL

};

int g_knumber_of_spectra[G_KMAXBEAMS] = {
 34,//EH
 35,//EL
 34,//NH
 35,//NL
 30,//VH
 30,//VL
 34,//WH
 35,//WL
 34,//SH
 35//SL
};

char g_tac_values[16] = { 0,	//0 DB
					   1,		//-4 DB
					   2,		//-8 DB
					   3,		//-12 DB
					   4,		//-16 DB
					   5,		//-20 DB
					   6,		//-24 DB
					   7,		//-28 DB
					   8,		//-32 DB
					   9,		//-36 DB
					   0x0a,	//-40 DB
					   0x0b,	//-44 DB
					   0x0c,	//-48 DB
					   0x0d,	//-52 DB
					   0x0e,	//-56 DB
					   0x0f		//-60 DB
};


char* str_Beam[G_KMAXBEAMS] = {  "East (high)",   "East (low)",
						"North (high)",  "North (low)",
						"Vertical(high)","Vertical(low)",
						"West (high)",   "West (low)",
						"South (high)",  "South (low)"};
						

STATUS_DATA status_data;
char g_sm_data[SM_STATUS_BYTE_SIZE];

//{LIUChen add it for inquire the status of the ups.
UPS_STATUS g_ups_status;  
float g_ups_shutdown_time=1.0;//LIUChen add it for shut down the ups.
UPS_DATA g_ups_data;
//}

