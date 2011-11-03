#ifndef _GLOBAL_DATA_DEF
#define _GLOBAL_DATA_DEF


#ifdef __cplusplus
extern "C" {
#endif

/*
******************************************************
* GLOBAL SETTING
******************************************************
*/
#define  MAXFFTPOINTS	(1024)                                       
#define  PI             (3.1415926535) 
#define  COEF           (16777215.0)   // 2^24 -1
#define  HIGH_MODE_RANGEBIN   (82) 
#define  LOW_MODE_RANGEBIN    (82)
#define  MAX_RANGEBIN   (82)
#define  HIGHDMANUM     (HIGH_MODE_RANGEBIN*2)        
#define  LOWDMANUM      (LOW_MODE_RANGEBIN*2)     							        
#define  MAXSPECTRAAVGNUM (60)        
#define  ENDFLAG		(0xf0f0)
#define  LOW_MODE	    (100);
#define  HIGH_MODE		(101);
#define  MAXINVALID		-0x7FFFFFFF		
#define  MININVALID		0x7FFFFFFF 			

/*
******************************************************
* DEFINE THE  DATA MAX/MIN VALUE FOR DISPLAY
******************************************************
*/
typedef struct time_series_limit
{
	double i_max;
	double i_min;
	double q_max;
	double q_min;
	double i_scalor;
	double q_scalor;
}TS_LIMIT,*P_TS_LIMIT;

/*
******************************************************
* DEFINE THE  SPEC DATA MAX/MIN VALUE FOR DISPLAY
******************************************************
*/
typedef struct sp_limit
{
	double max;
	double min;
	int max_loc;
}SP_LIMIT,*P_SP_LIMIT;

/*
******************************************************
* DEFINE THE COMPLEX DATA TYPE
******************************************************
*/
typedef struct complex_data
{
	int iData;
	int qData;
}DATA,*P_DATA;

/*
******************************************************
* SINGLE SPECTRA FOR LOW MODE
******************************************************
*/
typedef struct data_single_l{
	DATA nTimeSeries[LOW_MODE_RANGEBIN * MAXFFTPOINTS];
}DATAPAGE_SINGLE_L;

/*
******************************************************
* SINGLE SPECTRA FOR HIGH MODE
******************************************************
*/
typedef struct data_single_h{
	DATA nTimeSeries[HIGH_MODE_RANGEBIN * MAXFFTPOINTS];
}DATAPAGE_SINGLE_H;

/*
******************************************************
* DEFINE THE HEADER FOR THE SPECTRA DATA
******************************************************
*/
typedef struct spec_header{
	int nFFTPoints;
	int nBeamNum;
	int nRangeBin;
	int nSpectraNum;
	int nTimeDomainAvg;
	long nPRT;
}SPECTRA_HEADER;

/*
******************************************************
* DEFINE THE TIME SERIES HEADER
******************************************************
*/
typedef struct time_series_header
{
	int nPackageLength;
	int nSpecCount; 
	int nMode;
}TS_HEADER;

typedef struct time_series_end
{
	int nEndFlag;
}TS_END;

/*
******************************************************
* DEFINE THE BODY FOR THE TIME SERIES DATA (LOW MODE)
******************************************************
*/
typedef struct datastruct_low{
	TS_HEADER data_header;
	DATAPAGE_SINGLE_L datapage_l;
	TS_END dataend;
}DATASTRUCT_LOW,*P_DATASTRUCT_LOW;
#define SIZE_DATA_STRUCT_LOW (sizeof(DATASTRUCT_LOW))

/* 
******************************************************
* DEFINE THE BODY FOR THE TIME SERIES DATA (HIGH MODE)
******************************************************
*/
typedef struct datastruct_high{
	TS_HEADER data_header;
	DATAPAGE_SINGLE_H datapage_h;
	TS_END dataend;
}DATASTRUCT_HIGH,*P_DATASTRUCT_HIGH;
#define SIZE_DATA_STRUCT_HIGH (sizeof(DATASTRUCT_HIGH))

/*
******************************************************
* DEFINE A STRUCT FOR STORE THE  SPEC
******************************************************
*/
typedef struct spec_struct{
	double spectra[MAX_RANGEBIN * MAXFFTPOINTS];
}SINGLE_SPEC,*P_SINGLE_SPECTRA;
#define SIZE_SINGLE_SPEC (sizeof(SINGLE_SPEC))

/*
******************************************************
* DEFINE A STRUCT FOR STORE ALL THE BEAMDATA
******************************************************
*/
typedef struct signal_struct
{
	double signal_power[MAX_RANGEBIN];
}SIGNAL_POWER,*P_SIGNAL_POWER;
#define SIZE_SIGNAL_POWER (sizeof(SIGNAL_POWER))

/*
******************************************************
* DEFINE A STRUCT FOR STORE ALL THE VELOCITY
******************************************************
*/
typedef struct velocity_struct
{
	double mean_velocity[MAX_RANGEBIN];
}MEAN_VELOCITY,*P_MEAN_VELOCITY;
#define SIZE_MEAN_VELOCITY (sizeof(MEAN_VELOCITY))

/*
******************************************************
* DEFINE A STRUCT FOR STORE ALL THE SPEC WIDTH
******************************************************
*/
typedef struct spec_width_struct
{
	double spec_width[MAX_RANGEBIN];
}SPEC_WIDTH,*P_SPEC_WIDTH;
#define SIZE_SPEC_WIDTH (sizeof(SPEC_WIDTH))

/*
******************************************************
* DEFINE A STRUCT FOR STORE THE NOISE LEVEL
******************************************************
*/
typedef struct noise_level_struct
{
	double noise_level[MAX_RANGEBIN];
}NOISE_LEVEL,*P_NOISE_LEVEL;
#define SIZE_NOISE_LEVEL (sizeof(NOISE_LEVEL))

/*
******************************************************
* DEFINE A STRUCT FOR STORE SNR
******************************************************
*/
typedef struct snr_struct
{
	double snr[MAX_RANGEBIN];
}SNR,*P_SNR;
#define SIZE_SNR (sizeof(SNR))

/*
******************************************************
* DEFINE A STRUCT FOR SINGLE SPEC LIMIT
******************************************************
*/
typedef struct spec_limit_struct
{
	SP_LIMIT limit[MAX_RANGEBIN];
}SPEC_SINGLE_LIMIT, *P_SPEC_SINGLE_LIMIT;

/*
******************************************************
* DEFINE A STRUCT FOR AVGED SPEC LIMIT 
*  (ADD MORE MEMBER LATTER)
******************************************************
*/
typedef struct spec_avg_limit_struct
{
	SP_LIMIT limit[MAX_RANGEBIN];
	int    peak_loc[MAX_RANGEBIN];
	double peak_val[MAX_RANGEBIN];
}SPEC_AVG_LIMIT, *P_SPEC_AVG_LIMIT;

#ifdef __cplusplus
}
#endif
#endif