// Global.h: interface for the Global class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBAL_H__207A6452_9BBB_48FE_8CC5_E959966CC865__INCLUDED_)
#define AFX_GLOBAL_H__207A6452_9BBB_48FE_8CC5_E959966CC865__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "global_ups.h"
#include "IrqQueue.h"
#include "Global_DataDef.h"
#include "Global_SM_NewTx.h"

#define OK					(1)
#define FAIL				(0)
#define TOTAL_SWITCH_NUM	(8)
#define TOTAL_SUB_TASK_NUM  (8)

#define DP_TASK_ID          (0)
#define SM_TASK_ID          (DP_TASK_ID+1)
#define TEST_TASK_ID        (SM_TASK_ID+1)
#define ALARM_TASK_ID       (TEST_TASK+ID+1)
#define UPS_TASK_ID			(ALARM_TASK_ID+1)
#define NETWORK_TASK_ID		(UPS_TASK_ID+1)
#define PRODUCT_TASK_ID	    (NETWORK_TASK_ID+1)


#define WM_MYSHOW			(WM_USER+1000)
#define WM_SHOW_DATA		(WM_MYSHOW+1)
#define WM_SHOW_TIMESERIES	(WM_SHOW_DATA+1)
#define WM_UPDATE_PROGRESS	(WM_SHOW_TIMESERIES+1)
#define WM_SHOW_DATAINFO	(WM_UPDATE_PROGRESS+1)
#define WM_SHOW_SPEC_SINGLE (WM_SHOW_DATAINFO+1)
#define WM_SHOW_SPEC_AVG	(WM_SHOW_SPEC_SINGLE+1)
#define WM_SHOW_SPEC_SINGLE_VIEW (WM_SHOW_DATAINFO+1)
#define WM_SHOW_SPEC_AVG_VIEW	(WM_SHOW_SPEC_SINGLE+1)
#define WM_UPDAE_MARKER     (WM_SHOW_SPEC_AVG_VIEW+1)
#define WM_SHOW_SPEC_TOTAL  (WM_UPDAE_MARKER+1)


#define G_KMAXBEAMS  (10)
extern int  g_cur_prt[G_KMAXBEAMS];//For show current PRF
extern float g_kpulse_rep_period[G_KMAXBEAMS];
extern int   g_ktda_samples[G_KMAXBEAMS];
extern int   g_knumber_of_spectra[G_KMAXBEAMS];


enum
{
	COMM_SHAREDMEM = 0,
	COMM_NETWORK = 1,
	COMM_NONE = 2
};

typedef struct{
	int		m_nAlarm_Level;
	BOOL	m_bSingleByte;
	BOOL    m_bSingleBit;
	CString	m_strName;
	float	m_fLimitMin;
	float	m_fLimitMax;
	UINT	m_nHighByte;
	UINT	m_nLowByte;
	UINT	m_nHighBit;
	UINT	m_nLowBit;
	float   m_fFactor;
	BOOL    m_bNot;
}STATUS_ITEM_INFO, *P_STATUS_ITEM_INFO;


typedef struct{
	int		m_nAlarm_Level;
	char	m_strName[100];
	int		m_integer;
	int		m_decimal;
}STATUS_ITEM_INFO_BIN, *P_STATUS_ITEM_INFO_BIN;


typedef enum{
	EVL_RIGHT,
	EVL_FALSE,
	EVL_WARNNING
}STATUS_EVL;
/*
************************************************************
* THIS CLASS IS TO CONTROL A GLOBAL VARIBLE B_SWITCH
************************************************************
*/
class CSwitch{
public:
	CSwitch(){}
	virtual ~CSwitch(){};
public:
	BOOL TurnOn(){
		CSingleLock sl(&mutex);
		BOOL n_StatLockSuccess = sl.Lock();
		b_switch = TRUE;
		BOOL n_StatUnlockSuccess = sl.Unlock();

		return (n_StatLockSuccess && n_StatUnlockSuccess);
	}
	
	BOOL TurnOff(){
		CSingleLock sl(&mutex);
		BOOL n_StatLockSuccess = sl.Lock();
		b_switch = FALSE;
		BOOL n_StatUnlockSuccess = sl.Unlock();

		return (n_StatLockSuccess && n_StatUnlockSuccess);
	}

	BOOL IsOn(){return b_switch;}
private:
	CMutex mutex;
	BOOL b_switch;

};

/*
************************************************************
*  FOR OBLIQUE BEAM SETTING
************************************************************
*/
typedef struct oblique_setting_struct{
	//setting for oblique
	unsigned int time_domain_avg_low;
	unsigned int spec_domain_avg_low;
	long prt_low;
	long pulse_width_low;

	unsigned int time_domain_avg_high;
	unsigned int spec_domain_avg_high;
	long prt_high;
	long pulse_width_high;

}OBLIQUESTRUCT;

/*
************************************************************
* FOR VERTICAL BEAM SETTING
************************************************************
*/
typedef struct vertical_setting_struct{
	//setting for oblique
	unsigned int time_domain_avg_low;
	unsigned int spec_domain_avg_low;
	long prt_low;
	long pulse_width_low;

	unsigned int time_domain_avg_high;
	unsigned int spec_domain_avg_high;
	long prt_high;
	long pulse_width_high;

}VERTICALSTRUCT;

typedef struct stc{
	int ch_stc[24][5];
}STCSTRUCT;

/*
************************************************************
* FOR STATUS DESCRIPTION
************************************************************
*/
class CStatusInfo:public CObject
{
public:
	CStatusInfo(){};
	virtual ~CStatusInfo(){};

public:
	STATUS_ITEM_INFO _info;
};

class CStatusMonitorDescriptior
{
public:
	CStatusMonitorDescriptior(){_component_size = 0;}
	~CStatusMonitorDescriptior(){
		while(_list.GetHeadPosition())
		{
			delete _list.RemoveHead();
		}
	}

	int getDecimalData(CString& str)
	{
		int id = str.Find("=")+1;
		char* p = str.GetBuffer(str.GetLength())+id;
		int k = atoi(p);
		return k;

	}

	float getFloatData(CString& str)
	{
		int id = str.Find("=")+1;
		char* p = str.GetBuffer(str.GetLength())+id;
		float k = atof(p);
		return k;

	}

	CString getStringData(CString& str)
	{
		int id = str.Find("=")+1;
		char* p = str.GetBuffer(str.GetLength())+id;
	    CString s(p);
		return s;
	}

	CObList& getList(){return _list;}
    
    void Load()
	{
		CStdioFile _file("biteformt.dat", CFile::modeRead | CFile::typeText);
		CString str_cp_num;
		CString str_cp_spliter;
		CString str_bytes_num;

		_file.ReadString(str_bytes_num);
		_file.ReadString(str_cp_num);
		_file.ReadString(str_cp_spliter);
	
		const int nbyte = getDecimalData(str_bytes_num);
		const int ndata = getDecimalData(str_cp_num);
		
		for(int i=0; i<ndata; ++i)
		{
			CStatusInfo* pObj = new CStatusInfo;
			CString str_content;

			//NAME
			_file.ReadString(str_content);
			pObj->_info.m_strName = getStringData(str_content);
			
			//ALARM LEVEL
			_file.ReadString(str_content);
			pObj->_info.m_nAlarm_Level = getDecimalData(str_content);

			//SIGNAL BYTE
			_file.ReadString(str_content);
			pObj->_info.m_bSingleByte = getDecimalData(str_content);

			//SIGNAL BIT
			_file.ReadString(str_content);
			pObj->_info.m_bSingleBit = getDecimalData(str_content);

			//LIMIT MIN
			_file.ReadString(str_content);
			pObj->_info.m_fLimitMin = getFloatData(str_content);

			//LIMIT MAX
			_file.ReadString(str_content);
			pObj->_info.m_fLimitMax = getFloatData(str_content);

			//HIGH BYTE
			_file.ReadString(str_content);
			pObj->_info.m_nHighByte = getDecimalData(str_content);

			//LOW BYTE
			_file.ReadString(str_content);
			pObj->_info.m_nLowByte = getDecimalData(str_content);

			//HIGH BIT
			_file.ReadString(str_content);
			pObj->_info.m_nHighBit = getDecimalData(str_content);

			//LOW BIT
			_file.ReadString(str_content);
			pObj->_info.m_nLowBit = getDecimalData(str_content);

			//FACTOR
			_file.ReadString(str_content);
			pObj->_info.m_fFactor = getFloatData(str_content);

			//NOT FLAG
			_file.ReadString(str_content);
			pObj->_info.m_bNot = getDecimalData(str_content);

		
			_file.ReadString(str_cp_spliter);
			_list.AddTail(pObj);
		}
		
	};
	

private:
	CObList _list;
	unsigned int _component_size;

};


/*
************************************************************
* FOR BASIC SETTING
************************************************************
*/
typedef struct basicsettingstruct{
	unsigned int nfft;
	OBLIQUESTRUCT oblique_struct;
	VERTICALSTRUCT vertical_struct;
	STCSTRUCT stc_struct;
	BOOL bWholeRangeAddSTC;
	BOOL bPulseCompress;
	unsigned int nPSCModeSel;
	STCSTRUCT stc_sturct_high;//I THINK IT IS NECESSARY TO SET STC FOR HIGH MODE
	BOOL bHighModeSetting;
	BOOL bHighModeRange240m;
	BOOL b25MCLOSE;
}BASICSTRUCT;


class CBasicSetting{
public:
	CBasicSetting(){}
	~CBasicSetting(){}

	void SetFileName(char* str_filename){
		pFilename = str_filename;
	}

    void Load(){		
		f.Open(pFilename,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead,&e);
		f.Read(&basicinfo,sizeof(BASICSTRUCT));
		f.Close();
		g_cur_prt[0] = basicinfo.oblique_struct.prt_high;
		g_cur_prt[1] = basicinfo.oblique_struct.prt_low;
		g_cur_prt[2] = basicinfo.oblique_struct.prt_high;
		g_cur_prt[3] = basicinfo.oblique_struct.prt_low;
		g_cur_prt[4] = basicinfo.vertical_struct.prt_high;
		g_cur_prt[5] = basicinfo.vertical_struct.prt_low;
		g_cur_prt[6] = basicinfo.oblique_struct.prt_high;
		g_cur_prt[7] = basicinfo.oblique_struct.prt_low;
		g_cur_prt[8] = basicinfo.oblique_struct.prt_high;
		g_cur_prt[9] = basicinfo.oblique_struct.prt_low;
		for(int i=0; i<10; i++){
			if(i<4 || i>5){//oblique beam
				if(i%2 == 0){//high mode
                     g_cur_prt[i] = basicinfo.oblique_struct.prt_high;
					 g_ktda_samples[i] = basicinfo.oblique_struct.time_domain_avg_high;
				     g_knumber_of_spectra[i] = basicinfo.oblique_struct.spec_domain_avg_high;
				}
				else{//low mode
                     g_cur_prt[i] = basicinfo.oblique_struct.prt_low;
					 g_ktda_samples[i] = basicinfo.oblique_struct.time_domain_avg_low;
				     g_knumber_of_spectra[i] = basicinfo.oblique_struct.spec_domain_avg_low;
				}
			}
			else{//vertical beam
				if(i%2 == 0){//high mode
					 g_cur_prt[i] = basicinfo.vertical_struct.prt_high;
					 g_ktda_samples[i] = basicinfo.vertical_struct.time_domain_avg_high;
				     g_knumber_of_spectra[i] = basicinfo.vertical_struct.spec_domain_avg_high;

				}
				else{//low mode
					 g_cur_prt[i] = basicinfo.vertical_struct.prt_low;
					 g_ktda_samples[i] = basicinfo.vertical_struct.time_domain_avg_low;
				     g_knumber_of_spectra[i] = basicinfo.vertical_struct.spec_domain_avg_low;

				}
			}
		}
        

		return;
	}

	void Save(){
		f.Open(pFilename,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite,&e);
		f.Write(&basicinfo,sizeof(BASICSTRUCT));
		f.Close();
		return;
	}

	void SetDefaultValue(){
		basicinfo.nfft = 256;

		//OBLIQUE MODE
		basicinfo.oblique_struct.time_domain_avg_low = 97;
		basicinfo.oblique_struct.spec_domain_avg_low = 35;
		basicinfo.oblique_struct.prt_low = 67708;
		basicinfo.oblique_struct.pulse_width_low = 830;

		basicinfo.oblique_struct.time_domain_avg_high = 70;
		basicinfo.oblique_struct.spec_domain_avg_high = 34;
		basicinfo.oblique_struct.prt_high = 94375;
		basicinfo.oblique_struct.pulse_width_high= 6640;

		//VERTICAL MODE
		basicinfo.vertical_struct.time_domain_avg_low = 112;
		basicinfo.vertical_struct.spec_domain_avg_low = 30;
		basicinfo.vertical_struct.prt_low = 65000;
		basicinfo.vertical_struct.pulse_width_low = 800;

		basicinfo.vertical_struct.time_domain_avg_high = 80;
		basicinfo.vertical_struct.spec_domain_avg_high = 30;
		basicinfo.vertical_struct.prt_high = 90600;
		basicinfo.vertical_struct.pulse_width_high= 6400;

		//STC 
		for(int i=0;i<24; i++){
			basicinfo.stc_struct.ch_stc[i][0] = 0;
			basicinfo.stc_struct.ch_stc[i][1] = 0;
			basicinfo.stc_struct.ch_stc[i][2] = 0;
			basicinfo.stc_struct.ch_stc[i][3] = 0;
			basicinfo.stc_struct.ch_stc[i][4] = 0;

			basicinfo.stc_sturct_high.ch_stc[i][0] = 0;
			basicinfo.stc_sturct_high.ch_stc[i][1] = 0;
			basicinfo.stc_sturct_high.ch_stc[i][2] = 0;
			basicinfo.stc_sturct_high.ch_stc[i][3] = 0;
			basicinfo.stc_sturct_high.ch_stc[i][4] = 0;
		}
	}
public:
	BASICSTRUCT basicinfo;
	CFile f;
	CFileException e;
	char* pFilename;

};

/////////////////////////////////////////////////////////
//This class group all the global varible we need.

typedef struct _tx_data
{
	float tx_50v;
	float tx_36v;	
	float tx_28v;
	float tx_15v;

	float tx_m15v;
	float tx_13v;
	float tx_5v;
	float input_power;

	float output_power;
	float temperature;
	float reflect_power;
	float duty_cycle;
}TX_DATA,*P_TX_DATA;

typedef struct _cabin_data
{
	float cab_28v;
	float cab_24v;
	float cab_15v;
	float cab_m15v;

	float cab_12v;
	float cab_9v;
	float cab_6v1;
	float cab_6v2;

	float cab_5v1;
	float cab_5v2;
	float cab_5v3;
	float cab_5v4;

	float cab_neg5v;
	float cab_3_3v;
	float ant_pos_pwr;
	float ant_neg_pwr;

	float temp_outside;
	float temp_inside;
}CABIN_DATA,*P_CABIN_DATA;

typedef struct _dsp_fault{
	unsigned char lrb;
	unsigned char rd;
	unsigned char tx_bias_gate;
	unsigned char stc;

	unsigned char tr_amp;
	unsigned char t0;
	unsigned char av_cc;
	unsigned char iq_clock;

	unsigned char dv_cc;
	unsigned char ad_clock;
}DSP_FAULT,*P_DSP_FAULT;


typedef struct _tx_fault
{
    unsigned char spare:1;
	unsigned char rf_shut:1;
	unsigned char rf_fault:1;
	unsigned char over_temp:1;
	unsigned char tx_output:1;
	unsigned char sw:1;
	unsigned char ps:1;
	unsigned char spare1:1;
}TX_FAULT,*P_TX_FAULT;

typedef union tx_fault_union
{
	TX_FAULT fault;
	unsigned char ch_fault;
}TX_FAULT_UNION,*P_TX_FAULT_UNION;


typedef struct _status_data
{
	TX_DATA tx_data;
	CABIN_DATA cab_data;
	TX_FAULT_UNION tx_fault_union;
	DSP_FAULT dsp_fault;
}STATUS_DATA,*P_STATUS_DATA;
#define STATUS_DATA_SIZE (sizeof(STATUS_DATA))

class Global  
{
public:
	Global();
	virtual ~Global();
public:
	CSwitch cs_test;
	CSwitch cs_sm;
	CSwitch cs_ups;
	CSwitch cs_dataprocess;
	CSwitch cs_alarmprocess;
	CSwitch cs_network;
	CSwitch cs_product;
	IRQQueue series_fifo;
	SPEC_SINGLE_LIMIT spec_single_limit;
	SPEC_AVG_LIMIT    spec_avg_limit;

    CBasicSetting basic;
	CStatusMonitorDescriptior  sm_descriptor;
    int g_shutdown;
	int g_Data[41];
	TS_LIMIT ts_limit[MAXSPECTRAAVGNUM];

};

extern Global global;
extern int  g_test_strt;
extern int  g_test_end ;    
extern int  g_dop_freq_selected;
extern int  g_rf_freq_selected;
extern int  g_rf_lev_atten_sel;
extern int  g_lo_phase_ctrl; 
extern int  g_bm_dir_change;
extern int  g_coax_switch;
extern int  g_dop_test_ctrl;  
extern int  g_noise_source;
extern int	g_sm_reset ;
extern int	g_trans_ctrl;
extern int	g_signal_source;
extern int	g_signal_output;
extern int	g_RF_attenuation;
extern int  g_RF_gate_moving;
extern int  g_DIF_gate_moving;
extern int  g_PC_code_moving;
extern int  g_timedomainavg;
extern int  g_scalednumfftpts;
extern char g_tac_values[16];
extern char* str_Beam[10]; 
extern STATUS_DATA status_data;

/*
#define SM_STATUS_START -1
#define SM_STATUS_TXM15V  (SM_STATUS_START+1)
#define SM_STATUS_TX5V  (SM_STATUS_TXM15V+1)
#define SM_STATUS_TX50V (SM_STATUS_TX5V+1)
#define SM_STATUS_TX36V (SM_STATUS_TX50V+1)
#define SM_STATUS_TX28V (SM_STATUS_TX36V+1)
#define SM_STATUS_TX15V (SM_STATUS_TX28V+1)
#define SM_STATUS_TX13V (SM_STATUS_TX15V+1)
#define SM_STATUS_SW (SM_STATUS_TX13V+1)
#define SM_STATUS_SP (SM_STATUS_SW+1)
#define SM_STATUS_RF_FAULT (SM_STATUS_SP+1)
#define SM_STATUS_RF (SM_STATUS_RF_FAULT+1)
#define SM_STATUS_PSM5V (SM_STATUS_RF+1)
#define SM_STATUS_PSM15V (SM_STATUS_PSM5V+1)
#define SM_STATUS_PS9V (SM_STATUS_PSM15V+1)
#define SM_STATUS_PS6V (SM_STATUS_PS9V+1)
#define SM_STATUS_PS5V4 (SM_STATUS_PS6V+1)
#define SM_STATUS_PS5V3 (SM_STATUS_PS5V4+1)
#define SM_STATUS_PS5V2 (SM_STATUS_PS5V3+1)
#define SM_STATUS_PS5V1 (SM_STATUS_PS5V2+1)
#define SM_STATUS_PS24V (SM_STATUS_PS5V1+1)
#define SM_STATUS_PS3_3V (SM_STATUS_PS24V+1)
#define SM_STATUS_PS15V (SM_STATUS_PS3_3V+1)
#define SM_STATUS_PS12V (SM_STATUS_PS15V+1)
#define SM_STATUS_OVERTEMP (SM_STATUS_PS12V+1)
#define SM_STATUS_OUTPUT (SM_STATUS_OVERTEMP+1)

#define SM_SP_BSU_FLT (SM_STATUS_OUTPUT+1)
#define SM_W_ADCLK (SM_SP_BSU_FLT+1)
#define RD (SM_W_ADCLK+1)
#define LRB (RD+1)
#define T0 (LRB+1)
#define W_IQCLK (T0+1)
#define W_DVCC (W_IQCLK+1)
#define W_AVCC (W_DVCC+1)

#define SM_STATUS_END (W_AVCC+1)
#define SM_STATUS_SIZE SM_STATUS_END
*/
extern char g_sm_data[SM_STATUS_BYTE_SIZE];

//{LIUChen add it for inquire the status of the ups.
extern UPS_STATUS g_ups_status;  
extern float g_ups_shutdown_time;//LIUChen add it for shut down the ups.
extern UPS_DATA g_ups_data;
//}


#endif // !defined(AFX_GLOBAL_H__207A6452_9BBB_48FE_8CC5_E959966CC865__INCLUDED_)
