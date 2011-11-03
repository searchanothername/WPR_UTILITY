#ifndef _DATA_HANDLOR_H
#define _DATA_HANDLOR_H

#include "Global_DataDef.h"
enum
{
	HIMODE_ID=0,
	LOMODE_ID=1
};

class CDataHandlor
{
public:
	CDataHandlor();
	virtual ~CDataHandlor();

	BOOL init();

	P_DATASTRUCT_LOW getDataLow(const int index = 0);
	P_DATASTRUCT_HIGH getDataHigh(const int index = 0);
	BOOL setDataLow(const int fft_index = 0,const int spec_index = 0, int* buf=0);
	BOOL setDataHigh(const int fft_index = 0,const int spec_index = 0, int* buf=0);
	void setRangeBin( int rangebin_low=0, int rangebin_high=0)
	{
		_RANGEBIN_LOW = rangebin_low;
		_RANGEBIN_HIGH = rangebin_high;
		return;
	}

protected:
	void saveData(const int mode = LOMODE_ID, 
		          const int index = 0, 
				  const int spec_index = 0);

public:
	int nMode;
	P_DATASTRUCT_LOW _data_low;
	P_DATASTRUCT_HIGH _data_high;

	P_SINGLE_SPECTRA _spec_avged;
	P_SINGLE_SPECTRA _spec_avged_cpy;
	P_SINGLE_SPECTRA _spec_avged_comp;
	P_SINGLE_SPECTRA _spec_single;
	P_SIGNAL_POWER _signal_power;
	P_MEAN_VELOCITY _mean_velocity;
	P_SPEC_WIDTH _spec_width;
	P_NOISE_LEVEL _noise_level;
	P_SNR _snr;

	HANDLE h_spec_avged;
	HANDLE h_spec_avged_cpy;
	HANDLE h_spec_avged_comp;
	HANDLE h_spec_single;
	HANDLE h_signal_power;
	HANDLE h_mean_velocity;
	HANDLE h_spec_width;
	HANDLE h_noise_level;
	HANDLE h_snr;
	
	int _RANGEBIN_LOW;
	int _RANGEBIN_HIGH;
	int nFFT;
};

#endif
