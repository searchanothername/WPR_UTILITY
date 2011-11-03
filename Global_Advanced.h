// Global_Advanced.h: interface for the Global_Advanced class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBAL_ADVANCED_H__9724CCC2_0EE6_4057_AF8A_95A6CB60F517__INCLUDED_)
#define AFX_GLOBAL_ADVANCED_H__9724CCC2_0EE6_4057_AF8A_95A6CB60F517__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
*********************************************************
*FOR ALARM SETTING
*********************************************************
*/
#define TOTAL_ALARM_CLASS		(8) 
#define TOTAL_ALARNUM			(100) 

typedef struct alarmsetting{
	int   nLevel[TOTAL_ALARNUM];
	float min[TOTAL_ALARNUM];
	float max[TOTAL_ALARNUM];
}ALARMSETTING;

/*
*********************************************************
DEFINE ID OF ALARMS
*********************************************************
*/
#define LEVEL_HIGH   (2)
#define LEVEL_NORMAL (1)
#define LEVEL_NONE   (0)


#define ALARM_ID_START -1
//TX
#define ALARM_ID_TX_50V	(ALARM_ID_START+1)
#define ALARM_ID_TX_36V (ALARM_ID_TX_50V+1)
#define ALARM_ID_TX_28V (ALARM_ID_TX_36V+1)
#define ALARM_ID_TX_15V (ALARM_ID_TX_28V+1)

#define ALARM_ID_TX_NEG15V	(ALARM_ID_TX_15V+1)
#define ALARM_ID_TX_13V		(ALARM_ID_TX_NEG15V+1)
#define ALARM_ID_TX_5V		(ALARM_ID_TX_13V+1)
#define ALARM_ID_TX_INPUT	(ALARM_ID_TX_5V+1)

#define ALARM_ID_TX_OUTPUT		(ALARM_ID_TX_INPUT+1)
#define ALARM_ID_TX_TEMP		(ALARM_ID_TX_OUTPUT+1)
#define ALARM_ID_TX_REFLECT		(ALARM_ID_TX_TEMP+1)
//#define ALARM_ID_TX_DUTYCYCLE	(ALARM_ID_TX_REFLECT+1)

//CABIN
#define ALARM_ID_CABIN_28V	(ALARM_ID_TX_REFLECT+1)
#define ALARM_ID_CABIN_24V	(ALARM_ID_CABIN_28V+1)
#define ALARM_ID_CABIN_15V  (ALARM_ID_CABIN_24V+1)
#define ALARM_ID_CABIN_NEG15V (ALARM_ID_CABIN_15V+1)

#define ALARM_ID_CABIN_12V	(ALARM_ID_CABIN_NEG15V+1)
#define ALARM_ID_CABIN_9V	(ALARM_ID_CABIN_12V+1)
#define ALARM_ID_CABIN_6V1  (ALARM_ID_CABIN_9V+1)
#define ALARM_ID_CABIN_6V2  (ALARM_ID_CABIN_6V1+1)

#define ALARM_ID_CABIN_5V1	(ALARM_ID_CABIN_6V2+1)
#define ALARM_ID_CABIN_5V2	(ALARM_ID_CABIN_5V1+1)
#define ALARM_ID_CABIN_5V3  (ALARM_ID_CABIN_5V2+1)
#define ALARM_ID_CABIN_5V4  (ALARM_ID_CABIN_5V3+1)
#define ALARM_ID_CABIN_NEG5V  (ALARM_ID_CABIN_5V4+1)

#define ALARM_ID_CABIN_3_3V	(ALARM_ID_CABIN_NEG5V+1)
#define ALARM_ID_CABIN_ANT_POS_POW	(ALARM_ID_CABIN_3_3V+1)
#define ALARM_ID_CABIN_ANT_NEG_POW  (ALARM_ID_CABIN_ANT_POS_POW+1)
#define ALARM_ID_CABIN_TEMP_OUTSIDE  (ALARM_ID_CABIN_ANT_NEG_POW+1)
#define ALARM_ID_CABIN_TEMP_INSIDE  (ALARM_ID_CABIN_TEMP_OUTSIDE+1)

#define ALARM_ID_END (ALARM_ID_CABIN_TEMP_INSIDE+1)
#define ALARM_SIZE ALARM_ID_END


extern const CString alarm_table[TOTAL_ALARNUM];	

/*
*********************************************************
*FOR DMA SETTING
*********************************************************
*/
typedef struct dmasetting{
	unsigned int nDMA_Low;
	unsigned int nDMA_High;
}DMASETTING;

/*
*********************************************************
*FOR BEAM CTRL SETTING
*********************************************************
*/
typedef struct beamctrlsetting{
	int nBeamDirection[5];
}BEAMCTRLSETTING;

/*
*********************************************************
*FOR DSP AND ALGORISM SETTING
*********************************************************
*/
typedef struct dspsetting{
	unsigned long nCenterFreq;
	unsigned long nSampleRate;
	int nWindowType;
	int nRFGateMoveH;
	int nRFGateMoveL;
	int nPCCodeMove;
	int nBeginGateMoveH;
	int nBeginGateMoveL;
	BOOL nIQReverse;
	BOOL nRemoveDC;
}DSPSETTING;

/*
*********************************************************
*FOR GLOBAL ADVANCED SETTING
*********************************************************
*/
class Global_Advanced  
{
public:
	Global_Advanced();
	virtual ~Global_Advanced();
	void SetFileName(char* str_filename);
	void Load();
	void Save();

public:
	DMASETTING dmasetting;
	ALARMSETTING alarmsetting;
	BEAMCTRLSETTING beamctrlsetting;
	DSPSETTING dspsetting;

	CFile f;
	CFileException e;
	char* pFilename;
};


extern Global_Advanced global_advance;
extern const bool bQuantityTable[TOTAL_ALARNUM];
extern const bool bSeriousTable[TOTAL_ALARNUM];
extern const bool bDefaultAlarmTable[TOTAL_ALARNUM];

#endif // !defined(AFX_GLOBAL_ADVANCED_H__9724CCC2_0EE6_4057_AF8A_95A6CB60F517__INCLUDED_)
