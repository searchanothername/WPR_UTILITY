// StatusMonitorTask.cpp: implementation of the CStatusMonitorTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "StatusMonitorTask.h"
#include "WPR_UTILITIESDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "Global.h"
#include "Global_SM.h"
#include "A44_sm_handler.h"
#include <math.h>
#include "Global_Advanced.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CStatusMonitorTask::CStatusMonitorTask()
{
	
	HANDLE h_bite;
	h_bite = CreateFileMapping((HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		sizeof(unsigned char)*MAX_MESSAGE_SIZE,
		"SHAREDMEM");
	_bytes = (unsigned char* )MapViewOfFile(h_bite,FILE_MAP_ALL_ACCESS,0,0,0);
	ZeroMemory(_bytes, 	sizeof(unsigned char)*MAX_MESSAGE_SIZE);

}

CStatusMonitorTask::~CStatusMonitorTask()
{
    this->Stop(NULL);
	UnmapViewOfFile(_bytes);
	CloseHandle(h_bite);
	_bytes = 0;
}

void CStatusMonitorTask::SetParent(CWPR_UTILITIESDlg* pWindow)
{
	g_utility = pWindow;
}

DWORD CStatusMonitorTask::Run(void* pParam){
	
	//Initialize the SM port when task started.
	if(g_sm_port_config.bInUse)
	{
		g_sm_port.configcomm( g_sm_port_config.str_portname,
			g_sm_port_config.baudrate,
			g_sm_port_config.parity,
			g_sm_port_config.byte_num); 
		if(!g_sm_port.isconfiged()){
			AfxMessageBox("Port config fail");
			return 0;
		}
	}

	g_utility->m_hpa0_status.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON14));
	
	//Clear the global status.
	memset(&status_data, 0 ,SM_STATUS_BYTE_SIZE);
	while(global.cs_sm.IsOn()){
		UINT sm_retcd = 0;
		a442_sm_command ("RSS", 0, sm_retcd);
		if(g_sm_port_config.bHRDCheck)
		{
			if(g_sm_status.sm_byte[0]==0x7e)
			{
				SendDataToMainDlg();
				SendDataToBITEX();
			}
		}
		else
		{
			SendDataToMainDlg();
			SendDataToBITEX();
		}
		Sleep(1000);
	};
	return 1;
}

/*
***********************************************************
* DESCRIPTION:
*		SEND DATA TO BITEX SHOW THE STATUS BY BITEX.
***********************************************************
*/
CEvent g_eSendBITE(FALSE,FALSE,"SEND BITE",NULL);
void CStatusMonitorTask::SendDataToBITEX()
{
	memcpy(_bytes, &g_sm_status, g_sm_port_config.byte_num);
	_bytes[MAX_MESSAGE_SIZE-1]= g_sm_port_config.byte_num;
	g_eSendBITE.SetEvent();
	return;
}

/*
***********************************************************
* DESCRIPTION:
*		STOP THE MONITORING STATUS
***********************************************************
*/
DWORD CStatusMonitorTask::Stop(void* pParam){	
	CRect rect;
	g_utility->pStatusArray->GetClientRect(&rect);
	g_utility->pHpaDC->FillRect(&rect,&(g_utility->m_bkBrush));

	if(global.cs_sm.IsOn()){
		global.cs_sm.TurnOff();
	}

	if(g_sm_port.isconfiged()){
		g_sm_port.closecomm();
	}

	g_utility->m_hpa0_status.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON16));
	g_utility->m_HPA0.SetCheck(FALSE);

	this->Exit();
	return 1;
}


/*
***********************************************************
* DESCRIPTION:
*	  SEND THE STATUS TO THE MAIN DIALOG
***********************************************************
*/
unsigned char smByte[SM_STATUS_BYTE_SIZE] = {0};
unsigned char smByteOld[SM_STATUS_BYTE_SIZE] = {0};
void CStatusMonitorTask::SendDataToMainDlg()
{
	memcpy(smByte,&g_sm_status, sizeof(unsigned char)*g_sm_port_config.byte_num);
	//SearchStatus(&g_sm_status);
	for(int i=0; i<g_sm_port_config.byte_num; ++i)
	{
		if(smByte[i] != smByteOld[i])
		{
			CString str_Id;
			CString str_Data;
			str_Id.Format("%d",i);
			str_Data.Format("%0x",smByte[i]);
			
			g_utility->m_ListCtrl.DeleteItem(i);
			g_utility->m_ListCtrl.InsertItem(i,str_Id);
			g_utility->m_ListCtrl.SetItemText(i,1,str_Data);
		}
	}
	memcpy(smByteOld,smByte,sizeof(unsigned char)*g_sm_port_config.byte_num);

	
	//FOR SHOW THE STATUS ON THE MAIN DIALOG
	CStatic* st[16] = {
		    &g_utility->m_static_dsp_lrb,
			&g_utility->m_static_dsp_rd,
			&g_utility->m_static_dsp_txbias,
			&g_utility->m_static_dsp_stc,

			&g_utility->m_static_dsp_tramp,
			&g_utility->m_static_dsp_t0,
			&g_utility->m_static_dsp_wavcc,
			&g_utility->m_static_dsp_wiqclk,

			&g_utility->m_static_dsp_wdvcc,
			&g_utility->m_static_dsp_wadclk,
		    &g_utility->m_static_overtemp,
			&g_utility->m_static_tx_output,

			&g_utility->m_static_tx_swr,
			&g_utility->m_static_txps,
			&g_utility->m_static_tx_input,	
			&g_utility->m_static_tx_rf_on	
	};

	CString st_name[16]= {
		"LRB\r",     "RD\r",           "TX BIAS GATE\r", "STC\r",
		"T/R AMP\r", "T0\r",           "W_AVCC\r",       "W_IQCLK\r",
		"W_DVCC\r",  "W_ADCLK\r",      "OVER TEMP\r",    "OUTPUT\r",
		"SWR\r",     "POWER SUPPLY\r", "INPUT\r",        "RF ON\r"
	};

	CString tx_st_name[3] = {
		"TX INPUT\r", "TX OUTPUT\r", "TX REFLECT\r"
	};



	//CHECK THE BYTES
	CObList& list = global.sm_descriptor.getList();
	POSITION pos = list.GetHeadPosition();
	while (pos != NULL)
	{
		STATUS_EVL level;
		CStatusInfo* pObj = (CStatusInfo*)list.GetAt(pos);
		P_STATUS_ITEM_INFO pInfo = &(pObj->_info);
		CString name = pInfo->m_strName;
		
		//CHCK SINGLE BYTE SINGLE BIT
		if(pInfo->m_bSingleByte && pInfo->m_bSingleBit)
		{
			level = checkSingleBit(*pInfo, pInfo->m_nLowByte, pInfo->m_nLowBit);

			//SHOW THE STATUS DIRECTLY ON THE MAIN DIALOG
			for(int i=0; i<16; ++i)
			{
				if(st_name[i].Compare(name) ==0)
				{
					switch (level)
					{
					case EVL_RIGHT:
						st[i]->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON15));
						break;
					case EVL_FALSE:
						st[i]->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON16));
						break;
					case EVL_WARNNING:
						st[i]->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON14));
						break;
					default:
						break;
					};	
				}
			}

		}
		//CHCK SINGLE BYTE
		else if(pInfo->m_bSingleByte && !pInfo->m_bSingleBit)
		{
			level = checkMultiBit(*pInfo,pInfo->m_nLowByte, pInfo->m_nHighBit,pInfo->m_nLowBit);
		}

		//CHECK MULTIBYTE
		if(!pInfo->m_bSingleByte)
		{
			level = checkDualByte(*pInfo, pInfo->m_nHighByte, pInfo->m_nLowByte);
			//SHOW THE DIGITAL VARIABLE
			//DISPLAY THE 
			TX_FLOAT data;
			data.integer = g_sm_status.sm_byte[pInfo->m_nHighByte];
			data.decimal = g_sm_status.sm_byte[pInfo->m_nLowByte];

			if(name.Compare(tx_st_name[0])==0) //TX INPUT
			{
				memcpy(&g_utility->_f_tx_pwr_input, &data, sizeof(TX_FLOAT));
			}
			else if(name.Compare(tx_st_name[1]) ==0) //TX OUTPUT
			{
				memcpy(&g_utility->_f_tx_pwr_output, &data, sizeof(TX_FLOAT));
			}
			else if(name.Compare(tx_st_name[2]) == 0) //TX REFLECT
			{
				memcpy(&g_utility->_f_tx_pwr_reflect, &data, sizeof(TX_FLOAT));
			}
		}

		//SEND ALARAM 
		if(level != EVL_RIGHT)
		{
			_status_info_send.m_nAlarm_Level = level;
			_status_info_send.m_integer = _integer;
			_status_info_send.m_decimal = _decimal;
			char* p= pInfo->m_strName.GetBuffer(pInfo->m_strName.GetLength()+1);	
			*(p+pInfo->m_strName.GetLength()) = NULL;
			memcpy(_status_info_send.m_strName,p, pInfo->m_strName.GetLength()+1);
			
			
			//SEND THE INFORMATION TO THE WPR_UTILITY BY MESSAGE.
			COPYDATASTRUCT   cpd; 
			cpd.cbData   =   sizeof(STATUS_ITEM_INFO_BIN);
			cpd.lpData   =   (void*)(&_status_info_send); 
			HWND  h = ::FindWindow(NULL, "WPR UTILITY");
			if(h)
				::SendMessage(h, WM_COPYDATA, NULL, (LPARAM)&cpd);
		}
	

		list.GetNext(pos);
	}

}	


//////////////////////////////////////////////////////////////////////////////
//LOOK UP THE STATUS AND REPORT ALARM  TO ALARM PROCESSER.
//////////////////////////////////////////////////////////////////////////////
void CStatusMonitorTask::SearchStatus(void* ps){

	//memset(g_sm_data,0,sizeof(char)*SM_STATUS_BYTE_SIZE);

/*
	sm_status* status = (sm_status*) ps;
	memset(g_sm_data,0,sizeof(char)*SM_STATUS_BYTE_SIZE);

	//CHECK THE TX
	status_data.tx_fault_union.fault.rf_shut = status->sm_status_byte.b_rf_open;

	status_data.tx_fault_union.fault.rf_fault = status->sm_status_byte.b_rf_false;
	CheckStat(status->sm_status_byte.b_rf_false,1,CString("RF INPUT FAULT"));

	status_data.tx_fault_union.fault.over_temp = status->sm_status_byte.b_over_temp;
	CheckStat(status->sm_status_byte.b_over_temp,1,CString("TX OVER TEMPERATURE"));

	status_data.tx_fault_union.fault.tx_output = status->sm_status_byte.b_rf_output;
	CheckStat(status->sm_status_byte.b_rf_output,1,CString("TX OUTPUT FAULT"));

	status_data.tx_fault_union.fault.sw = status->sm_status_byte.b_sw_false;
	CheckStat(status->sm_status_byte.b_sw_false,1,CString("TX SW FAULT"));

	status_data.tx_fault_union.fault.ps = status->sm_status_byte.b_power_false;
	CheckStat(status->sm_status_byte.b_power_false,1,CString("TX PS FAULT"));

	//CHECK THE POWER SUPPLAY
	double integer = status->sm_pwr_input.integer;
	double decimal = (double)status->sm_pwr_input.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	if(integer>127) {
		integer =255-integer;
		status_data.tx_data.input_power = -integer + decimal;
	}
	else
	{
		status_data.tx_data.input_power = integer + decimal;
	}

	integer = status->sm_pwr_output.integer;
	decimal = (double)status->sm_pwr_output.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	if(integer>127) {
		integer =255-integer;
		status_data.tx_data.output_power = -integer + decimal;
	}
	else
	{
		status_data.tx_data.output_power = integer + decimal;
	}

	integer = status->sm_pwr_reflect.integer;
	decimal = (double)status->sm_pwr_reflect.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	if(integer>127) {
		integer =255-integer;
		status_data.tx_data.reflect_power = -integer + decimal;
	}
	else
	{
		status_data.tx_data.reflect_power = integer + decimal;
	}

	integer = status->sm_temperature.integer;
	decimal = (double)status->sm_temperature.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	if(integer>127) {
		integer =255-integer;
		status_data.tx_data.temperature = -integer + decimal;
	}
	else
	{
		status_data.tx_data.temperature = integer + decimal;
	}


	integer = status->sm_5_V.integer;
	decimal = (double)status->sm_5_V.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	status_data.tx_data.tx_5v = integer + decimal;
	CheckVal(status_data.tx_data.tx_5v,ALARM_ID_TX_5V);

	integer = status->sm_pwr_input.integer;
	decimal = (double)status->sm_pwr_input.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	status_data.tx_data.input_power = integer + decimal;
	CheckVal(status_data.tx_data.input_power,ALARM_ID_TX_INPUT);
	
	integer = status->sm_pwr_output.integer;
	decimal = (double)status->sm_pwr_output.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	status_data.tx_data.output_power = integer + decimal;
	CheckVal(status_data.tx_data.output_power,ALARM_ID_TX_OUTPUT);
	
	integer = status->sm_pwr_reflect.integer;
	decimal = (double)status->sm_pwr_reflect.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	status_data.tx_data.reflect_power = integer + decimal;
	CheckVal(status_data.tx_data.reflect_power,ALARM_ID_TX_REFLECT);
	
	integer = status->sm_temperature.integer;
	decimal = (double)status->sm_temperature.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	status_data.tx_data.temperature = integer + decimal;
	CheckVal(status_data.tx_data.temperature,ALARM_ID_TX_TEMP);
	
	integer = status->sm_13_V.integer;
	decimal = (double)status->sm_13_V.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	status_data.tx_data.tx_13v = integer + decimal;
	CheckVal(status_data.tx_data.tx_13v,ALARM_ID_TX_13V);
	
	
	integer = status->sm_50_V.integer;
	decimal = (double)status->sm_50_V.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	status_data.tx_data.tx_50v = integer + decimal;
	CheckVal(status_data.tx_data.tx_50v,ALARM_ID_TX_50V);
	
	integer = status->sm_28_V.integer;
	decimal = (double)status->sm_28_V.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	status_data.tx_data.tx_28v = integer + decimal;
	CheckVal(status_data.tx_data.tx_28v,ALARM_ID_TX_28V);
	
	integer = status->sm_36_V.integer;
	decimal = (double)status->sm_36_V.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	status_data.tx_data.tx_36v = integer + decimal;
	CheckVal(status_data.tx_data.tx_36v,ALARM_ID_TX_36V);
	
	integer = status->sm_15_V.integer;
	decimal = (double)status->sm_15_V.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	status_data.tx_data.tx_15v = integer + decimal;
	CheckVal(status_data.tx_data.tx_15v,ALARM_ID_TX_15V);
	
	
	integer = status->sm_neg_15_V.integer;
	decimal = (double)status->sm_neg_15_V.decimal;
	decimal = decimal / pow(10,(int)(log10(decimal)+0.5));
	status_data.tx_data.tx_m15v = -(integer + decimal);
	CheckVal(status_data.tx_data.tx_m15v,ALARM_ID_TX_NEG15V);


    status_data.cab_data.cab_28v = (double) status->sm_28_v * 0.125;
	CheckVal(status_data.cab_data.cab_28v,ALARM_ID_CABIN_28V);

	status_data.cab_data.cab_24v = (double) status->sm_24_v * 0.107;
	CheckVal(status_data.cab_data.cab_24v,ALARM_ID_CABIN_24V);

	status_data.cab_data.cab_15v = (double) status->sm_15_v * 0.067;
	CheckVal(status_data.cab_data.cab_15v,ALARM_ID_CABIN_15V);

	status_data.cab_data.cab_m15v = -(double) status->sm_neg_15_v * 0.067;
	CheckVal(status_data.cab_data.cab_m15v,ALARM_ID_CABIN_NEG15V);

	status_data.cab_data.cab_12v = (double) status->sm_12_v * 0.0536;
	CheckVal(status_data.cab_data.cab_12v,ALARM_ID_CABIN_12V);

    status_data.cab_data.cab_9v = (double) status->sm_9_v * 0.0402;
	CheckVal(status_data.cab_data.cab_9v,ALARM_ID_CABIN_9V);

	status_data.cab_data.cab_6v1 = (double)  status->sm_6_v1 * 0.0268;
	CheckVal(status_data.cab_data.cab_6v1,ALARM_ID_CABIN_6V1);

	status_data.cab_data.cab_6v2 = (double)  status->sm_6_v2 * 0.0268;
	CheckVal(status_data.cab_data.cab_6v2,ALARM_ID_CABIN_6V2);

	status_data.cab_data.cab_5v1 = (double) status->sm_5_v1 * 0.0223;
	CheckVal(status_data.cab_data.cab_5v1,ALARM_ID_CABIN_5V1);

	status_data.cab_data.cab_5v2 = (double) status->sm_5_v2 * 0.0223;
	CheckVal(status_data.cab_data.cab_5v2,ALARM_ID_CABIN_5V2);

	status_data.cab_data.cab_5v3 = (double) status->sm_5_v3 * 0.0223;
	CheckVal(status_data.cab_data.cab_5v3,ALARM_ID_CABIN_5V3);

	status_data.cab_data.cab_5v4 = (double) status->sm_5_v4 * 0.0223;
	CheckVal(status_data.cab_data.cab_5v4,ALARM_ID_CABIN_5V4);

	status_data.cab_data.cab_neg5v = -(double) status->sm_neg_5_v * 0.0223;
	CheckVal(status_data.cab_data.cab_neg5v,ALARM_ID_CABIN_NEG5V);

	status_data.cab_data.cab_3_3v = (double) status->sm_3_3_v * 0.0147;
	CheckVal(status_data.cab_data.cab_3_3v,ALARM_ID_CABIN_3_3V);

	status_data.cab_data.ant_pos_pwr = (double) status->sm_Pos_Ant_Power;
	CheckVal(status_data.cab_data.ant_pos_pwr,ALARM_ID_CABIN_ANT_POS_POW);

	status_data.cab_data.ant_neg_pwr = (double) status->sm_Neg_Ant_Power;
	CheckVal(status_data.cab_data.ant_neg_pwr,ALARM_ID_CABIN_ANT_NEG_POW);

	status_data.cab_data.temp_outside = (double) status->sm_OutDoor_Temperature;
	CheckVal(status_data.cab_data.temp_outside,ALARM_ID_CABIN_TEMP_OUTSIDE);

	status_data.cab_data.temp_inside = (double) status->sm_InDoor_Temperature;
	CheckVal(status_data.cab_data.temp_inside,ALARM_ID_CABIN_TEMP_INSIDE);


*/
	return;
}

/*
***********************************************************
* DESCRIPTION:
*	CHECK THE VALUE FOR ALARM DISPLAY.
***********************************************************
*/
void CStatusMonitorTask::CheckVal(float val, int id)
{

	COPYDATASTRUCT   cpd; 

	if(val>global_advance.alarmsetting.min[id] && 
		val<global_advance.alarmsetting.max[id]){
		cpd.dwData = 2;
		//return;	
	}
	else{
	
		if(global_advance.alarmsetting.nLevel[id] == LEVEL_NORMAL){
			cpd.dwData   =   0; 
		}else if(global_advance.alarmsetting.nLevel[id] == LEVEL_HIGH){
			cpd.dwData   =   1; 
		}
		else if(global_advance.alarmsetting.nLevel[id] == LEVEL_NONE){
			cpd.dwData   =   -1; 
		}
	}

	CString info = alarm_table[id];
	cpd.cbData   =   info.GetLength()+1;
	cpd.lpData   =   (void*)(info.GetBufferSetLength(cpd.cbData)); 
	::SendMessage(g_utility->m_hWnd,WM_COPYDATA,NULL,(LPARAM)&cpd);

	return;
}

/*
***********************************************************
* DESCRIPTION:
*	CHECK THE BOOL STATUS FOR ALARM DISPLAY.
***********************************************************
*/
void CStatusMonitorTask::CheckStat(bool bError,int level,CString strInfo)
{
	if(bError){
		COPYDATASTRUCT   cpd; 
		cpd.dwData   =   level; 
		cpd.cbData   =   strInfo.GetLength()+1;
		cpd.lpData   =   (void*)(strInfo.GetBufferSetLength(cpd.cbData)); 
		::SendMessage(g_utility->m_hWnd,WM_COPYDATA,NULL,(LPARAM)&cpd);
	}
	return;
}


//////////////////////////////////////////////////////////////////////////////
//SCALE THE VALUE.
//////////////////////////////////////////////////////////////////////////////
void CStatusMonitorTask::Scale()
{
	return;
}

//////////////////////////////////////////////////////////////////////////////
//CREATE HAP PARAMS FOR EACH BEAM
//////////////////////////////////////////////////////////////////////////////
void CStatusMonitorTask::MakeHPAParamForEachBeam()
{
	return;
}

//////////////////////////////////////////////////////////////////////////////
//TURN ON HPA FOR EACH BEAM AND THE SETTING IS IN ADAPTOR
//////////////////////////////////////////////////////////////////////////////
void CStatusMonitorTask::TurnOnHPAForEachBeam(const int nCurrentBeam)
{
	UINT ret = 0;
	a442_sm_command("HPA",HPA_PARAM[nCurrentBeam].param,ret);
	return;
}

//////////////////////////////////////////////////////////////////////////////
//TURN ON HPA BY ITS NUM.
//////////////////////////////////////////////////////////////////////////////
void CStatusMonitorTask::SetSingleHPA(const int HPANUM, const BOOL bOpen)
{
	UINT ret = 0;
	if(bOpen)
		cmparam.cparam[0] &= HPA_START_MASK;
	else
		cmparam.cparam[0] |= HPA_SHUT_MASK;
	
	a442_sm_command("HPA",cmparam.param,ret);
	return;
}

/*
***********************************************************
* DESCRIPTION:
*		CHECK THE SINGLE BYTE
*		2011/5/17
***********************************************************
*/
STATUS_EVL CStatusMonitorTask::checkSingleBit(STATUS_ITEM_INFO&_status_info, unsigned char ByteID, unsigned char lBitID)
{
	 unsigned char data = (g_sm_status.sm_byte[ByteID]>>lBitID) & 0x0001;
	 if(_status_info.m_bNot)
		 data = !data;

	 _integer = data;
	 _decimal = 0;

	if(data)
	{
		if(	_status_info.m_nAlarm_Level ==0)
		{	
			return EVL_RIGHT;
		}
		else if(_status_info.m_nAlarm_Level ==1)
		{
			return EVL_WARNNING;
		}else if(_status_info.m_nAlarm_Level ==2)
		{
			return EVL_FALSE;
		}
	}
	else
	{
		return EVL_RIGHT;
	}

	return EVL_RIGHT;

}

/*
***********************************************************
* DESCRIPTION:
*		CHECK THE DUAL BYTES
*		2011/5/17
***********************************************************
*/
STATUS_EVL CStatusMonitorTask::checkDualByte(STATUS_ITEM_INFO&_status_info, unsigned char hByteID, unsigned char lByteID)
{
    int m_nInteger = _integer = g_sm_status.sm_byte[hByteID];
	int m_nDecimal = _decimal = g_sm_status.sm_byte[lByteID];

	float decimal = (double)m_nDecimal/ pow(10,(int)(log10(m_nDecimal)+0.5));
	float data = m_nInteger + decimal;
		if(data>_status_info.m_fLimitMax || data<_status_info.m_fLimitMin)
	{
		if(	_status_info.m_nAlarm_Level ==0)
		{
			 return EVL_RIGHT;
		}
		else if(_status_info.m_nAlarm_Level ==1)
		{
		
			return EVL_WARNNING;
		}else if(_status_info.m_nAlarm_Level ==2)
		{
		
			return EVL_FALSE;
		}
	}
	else
	{
		return EVL_RIGHT;
	}

	return EVL_RIGHT;
}

/*
***********************************************************
* DESCRIPTION:
*		CHECK THE MULTIBYTES 
*		2011/5/17
***********************************************************
*/
STATUS_EVL CStatusMonitorTask::checkMultiBit(STATUS_ITEM_INFO&_status_info, unsigned char ByteID, unsigned char hBitID, unsigned char lBitID)
{
	unsigned int mask = 0;
	for(int i=hBitID; i>=lBitID; --i)
	{
		mask+=pow(2,i);
	}

	float data = (float)((g_sm_status.sm_byte[ByteID] & mask)>>lBitID) * _status_info.m_fFactor;
	int m_nInteger = _integer = (float)data*100/100;
	int m_nDecimal = _decimal = ((float)data - m_nInteger)*100;
	
	if(data>_status_info.m_fLimitMax || data<_status_info.m_fLimitMin)
	{
		if(	_status_info.m_nAlarm_Level ==0)
		{
			return EVL_RIGHT;
		}
		else if(_status_info.m_nAlarm_Level ==1)
		{
			return EVL_WARNNING;
		}else if(_status_info.m_nAlarm_Level ==2)
		{
			return EVL_FALSE;
		}
	}
	else
	{
		return EVL_RIGHT;
	}
	return EVL_RIGHT;
}