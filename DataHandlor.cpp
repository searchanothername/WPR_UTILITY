#include "stdafx.h"
#include "DataHandlor.h"
#include "Global.h"
#include "math.h"
#include "Global_SM.h"
#include "Global_Advanced.h"

CDataHandlor::CDataHandlor()
{

}

CDataHandlor::~CDataHandlor()
{
	UnmapViewOfFile(_spec_avged);
	UnmapViewOfFile(_spec_single);
	UnmapViewOfFile(_signal_power);
	UnmapViewOfFile(_mean_velocity);
	UnmapViewOfFile(_spec_width);
	UnmapViewOfFile(_noise_level);
	UnmapViewOfFile(_snr);
	UnmapViewOfFile(_spec_avged_cpy);
	UnmapViewOfFile(_spec_avged_comp);

	CloseHandle(h_spec_avged);
	CloseHandle(h_spec_single);
	CloseHandle(h_signal_power);
	CloseHandle(h_mean_velocity);
	CloseHandle(h_spec_width);
	CloseHandle(h_noise_level);
	CloseHandle(h_snr);
	CloseHandle(h_spec_avged_cpy);
	CloseHandle(h_spec_avged_comp);

	_spec_avged = 0;
	_spec_single = 0;
	_signal_power = 0;
	_mean_velocity = 0;
	_spec_width = 0;
	_noise_level = 0;
	_snr = 0;
	_spec_avged = 0;
	_spec_avged_cpy =0;
	_spec_avged_comp = 0;
}

BOOL CDataHandlor::init()
{
	_data_low = (P_DATASTRUCT_LOW) VirtualAlloc(NULL,
								SIZE_DATA_STRUCT_LOW * MAXSPECTRAAVGNUM, 
								MEM_TOP_DOWN|MEM_RESERVE,
								PAGE_READWRITE);


	_data_high = (P_DATASTRUCT_HIGH) VirtualAlloc(NULL,
								SIZE_DATA_STRUCT_HIGH * MAXSPECTRAAVGNUM,
								MEM_TOP_DOWN|MEM_RESERVE,
								PAGE_READWRITE);	

	nFFT = global.basic.basicinfo.nfft;

    
	h_spec_avged = CreateFileMapping((HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE_SINGLE_SPEC,
		NULL);
	_spec_avged = (P_SINGLE_SPECTRA)MapViewOfFile(h_spec_avged,FILE_MAP_ALL_ACCESS,0,0,0);
    ZeroMemory(_spec_avged,SIZE_SINGLE_SPEC);

	h_spec_avged_cpy = CreateFileMapping((HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE_SINGLE_SPEC,
		NULL);
	_spec_avged_cpy = (P_SINGLE_SPECTRA)MapViewOfFile(h_spec_avged_cpy,FILE_MAP_ALL_ACCESS,0,0,0);
    ZeroMemory(_spec_avged_cpy,SIZE_SINGLE_SPEC);
	
	h_spec_avged_comp = CreateFileMapping((HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE_SINGLE_SPEC,
		NULL);
	_spec_avged_comp = (P_SINGLE_SPECTRA)MapViewOfFile(h_spec_avged_comp,FILE_MAP_ALL_ACCESS,0,0,0);
    ZeroMemory(_spec_avged_comp,SIZE_SINGLE_SPEC);

	h_spec_single = CreateFileMapping((HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE_SINGLE_SPEC,
		NULL);
	_spec_single = (P_SINGLE_SPECTRA)MapViewOfFile(h_spec_single,FILE_MAP_ALL_ACCESS,0,0,0);
	ZeroMemory(_spec_single, SIZE_SINGLE_SPEC);

	h_signal_power = CreateFileMapping((HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE_SIGNAL_POWER,
		NULL);
	_signal_power = (P_SIGNAL_POWER)MapViewOfFile(h_signal_power,FILE_MAP_ALL_ACCESS,0,0,0);
	ZeroMemory(_signal_power, SIZE_SIGNAL_POWER);

	h_mean_velocity = CreateFileMapping((HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE_MEAN_VELOCITY,
		NULL);
	_mean_velocity = (P_MEAN_VELOCITY)MapViewOfFile(h_mean_velocity,FILE_MAP_ALL_ACCESS,0,0,0);
	ZeroMemory(_mean_velocity,SIZE_MEAN_VELOCITY);
	
	h_spec_width = CreateFileMapping((HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE_SPEC_WIDTH,
		NULL);
	_spec_width = (P_SPEC_WIDTH)MapViewOfFile(h_spec_width,FILE_MAP_ALL_ACCESS,0,0,0);
    ZeroMemory(_spec_width,SIZE_SPEC_WIDTH);

	h_noise_level = CreateFileMapping((HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE_NOISE_LEVEL,
		NULL);
	_noise_level = (P_NOISE_LEVEL)MapViewOfFile(h_noise_level,FILE_MAP_ALL_ACCESS,0,0,0);
	ZeroMemory(_noise_level, SIZE_NOISE_LEVEL);


	h_snr = CreateFileMapping((HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE_SNR,
		NULL);
	_snr = (P_SNR)MapViewOfFile(h_snr,FILE_MAP_ALL_ACCESS,0,0,0);
	ZeroMemory(_snr,SIZE_SNR);


	return ((_data_high && _data_low)?TRUE:FALSE);

}

P_DATASTRUCT_LOW CDataHandlor::getDataLow(const int index){
	if(index<MAXSPECTRAAVGNUM)
		return _data_low+index;
	else 
		return 0;
}

P_DATASTRUCT_HIGH CDataHandlor::getDataHigh(const int index){
	if(index<MAXSPECTRAAVGNUM)
		return _data_high+index;
	else 
		return 0;
}

BOOL CDataHandlor::setDataLow(const fft_index, const int spec_index, int* buf)
{

	unsigned int DATA_BLOCK_COUNT = \
		global.basic.basicinfo.bHighModeRange240m\
		?1:16;
	unsigned int DATA_BLOCK_SIZE = SIZE_DATA_STRUCT_LOW*DATA_BLOCK_COUNT;

	VirtualAlloc(_data_low+spec_index,DATA_BLOCK_SIZE,MEM_COMMIT,PAGE_READWRITE);
	if(buf){
		(_data_low + spec_index)->data_header.nPackageLength = SIZE_DATA_STRUCT_LOW;
		(_data_low + spec_index)->data_header.nSpecCount = spec_index;
		(_data_low + spec_index)->data_header.nMode = LOW_MODE;
		(_data_low + spec_index)->dataend.nEndFlag = ENDFLAG;

		const int offset = global_advance.dspsetting.nBeginGateMoveL;
		memcpy((_data_low+spec_index)->datapage_l.nTimeSeries\
			+fft_index*DATA_BLOCK_COUNT*(_RANGEBIN_LOW-offset),
			buf+offset*2,DATA_BLOCK_COUNT*(_RANGEBIN_LOW-offset)*2*sizeof(int));
		
		//RECORD THE DATA ON LOCAL MACHINE
		saveData(LOMODE_ID, fft_index, spec_index);
	}
	else{
		return FALSE;
	}
	
	return TRUE;
	
}

BOOL CDataHandlor::setDataHigh(const int fft_index, const int spec_index, int* buf)
{
	unsigned int DATA_BLOCK_COUNT = \
		global.basic.basicinfo.bHighModeRange240m\
		?1:16;
	unsigned int DATA_BLOCK_SIZE = SIZE_DATA_STRUCT_HIGH*DATA_BLOCK_COUNT;

	VirtualAlloc(_data_high+spec_index,SIZE_DATA_STRUCT_HIGH,MEM_COMMIT,PAGE_READWRITE);
	if(buf){
		(_data_high + spec_index)->data_header.nPackageLength = SIZE_DATA_STRUCT_HIGH;
		(_data_high + spec_index)->data_header.nSpecCount = spec_index;
		(_data_high + spec_index)->data_header.nMode = HIGH_MODE;
		(_data_high + spec_index)->dataend.nEndFlag = ENDFLAG;

		const int offset = global_advance.dspsetting.nBeginGateMoveH;
		memcpy((_data_high+spec_index)->datapage_h.nTimeSeries+fft_index*DATA_BLOCK_COUNT*(_RANGEBIN_HIGH-offset),
			buf+offset*2,DATA_BLOCK_COUNT*(_RANGEBIN_HIGH-offset)*2*sizeof(int));
		
		//RECORD THE DATA ON LOCAL MACHINE
		saveData(HIMODE_ID, fft_index, spec_index);
		
	}
	else{
		return FALSE;
	}
	
	return TRUE;
}

void CDataHandlor::saveData(const int mode , const int index, const int spec_index)
{


	const int rangebin[2] = {_RANGEBIN_HIGH,_RANGEBIN_LOW};
    P_DATA buffer[2]  = {
				(_data_high)->datapage_h.nTimeSeries,
				(_data_low)->datapage_l.nTimeSeries
				};

	char* path = g_ctrl_config.str_archive_path;
	if(SAVE_TEXT == g_ctrl_config.selection){
		char filename[200] ={0};
		sprintf(filename, "%s\\raw.txt",path);
		FILE* fp = fopen(filename,"a+");
		if(!fp)
			return;
		
		fprintf(fp, "====================================\n");
		fprintf(fp, "SPEC ID: %d, SWEEP ID: %d\n",spec_index, index);
		fprintf(fp, "====================================\n");
		for(int i=0; i<rangebin[mode]; i++)
		{
			int idata = (buffer[mode]+index*rangebin[mode]+i)->iData;
			int qdata = (buffer[mode]+index*rangebin[mode]+i)->qData;
			fprintf(fp, "I: %d\t Q: %d\t Power: %6.2f\t Anagle: %6.2f \n",\
					idata, qdata, 
					10*log10(pow(idata,2.0)+pow(qdata,2.0)),
					atan2(idata,qdata)*180.0/PI);
		}
		fclose(fp);
	}
	else if( SAVE_BINARY ==  g_ctrl_config.selection){
		char filename[200] ={0};
		sprintf(filename, "%s\\raw.dat",path);
		FILE* fp = fopen(filename, "a+b");
		if(!fp)
			return;
		for(int i=0; i<rangebin[mode]; i++)
		{
			int idata = (buffer[mode]+index*rangebin[mode]+i)->iData;
			int qdata = (buffer[mode]+index*rangebin[mode]+i)->qData;
			int g[2] = {idata, qdata};
			fwrite(g,sizeof(int),2,fp);
		}
		fclose(fp);
	}



	
	return;
}