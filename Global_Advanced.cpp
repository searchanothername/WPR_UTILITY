// Global_Advanced.cpp: implementation of the Global_Advanced class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Global_Advanced.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const CString alarm_table[TOTAL_ALARNUM]= {
	//TX 
		_T("TX 50V"), _T("TX 36V"),_T("TX 28V"),_T("TX 15V"),
		_T("TX -15V"),_T("TX 13V"),_T("TX 5V"),
		_T("TX INPUT"),_T("TX OUTPUT"),_T("TX TEMP"),_T("TX REFLECT"),
		//_T("DUTY CYCLE"),

	//CABIN
		_T("CABIN 28V"),_T("CABIN 24V"),_T("CABIN 15V"),_T("CABIN -15V"),
		_T("CABIN 12V"),_T("CABIN 9V"),_T("CABIN 6V1"),_T("CABIN 6V2"),
		_T("CABIN 5V1"),_T("CABIN 5V2"),_T("CABIN 5V3"),_T("CABIN 5V4"),
		_T("CABIN -5V"),
		_T("CABIN 3.3V"),
		_T("ANT POS POWER"),_T("ANT NEG POWER"),
		_T("TEMPERATURE OUTSIDE"), _T("TEMPERATURE INSIDE")

	//RASS (NO RASS FOR THIS SYSTEM)
		//_T("RASS STAT")
};


const bool bQuantityTable[TOTAL_ALARNUM] = {
	//  --------------------------------
	//  0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
	//  --------------------------------
	    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//00 - 15
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//16 - 31
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//32 - 47
		1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,//48 - 63
		0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,//64 - 79
		1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,//80 - 96
		0,0,0,0							//97 - 100
};

const bool bSeriousTable[TOTAL_ALARNUM] = {
	//  --------------------------------
	//  0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
	//  --------------------------------
	    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//00 - 15
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//16 - 31
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//32 - 47
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//48 - 63
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//64 - 79
		0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,//80 - 96
		1,1,0,0                         //97 - 100
};

const bool bDefaultAlarmTable[TOTAL_ALARNUM] = {
	//  --------------------------------
	//  0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
	//  --------------------------------
	    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//00 - 15
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//16 - 31
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//32 - 47
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//48 - 63
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//64 - 79
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//80 - 96
		0,0,0,0                         //97 - 100
};


Global_Advanced::Global_Advanced()
{
   SetFileName("AdvancedSetting.dat");
}

Global_Advanced::~Global_Advanced()
{
}

void Global_Advanced::SetFileName(char* str_filename){
		pFilename = str_filename;
}

void Global_Advanced::Load(){
		f.Open(pFilename,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead,&e);
		f.Read(&dmasetting,sizeof(DMASETTING));
		f.Read(&alarmsetting,sizeof(ALARMSETTING));
		for(int i=0; i<TOTAL_ALARNUM; i++){
			if(bSeriousTable[i])
			   alarmsetting.nLevel[i] = LEVEL_HIGH;
		}
		f.Read(&beamctrlsetting,sizeof(BEAMCTRLSETTING));
		f.Read(&dspsetting,sizeof(DSPSETTING));
		f.Close();
}

void Global_Advanced::Save(){
		f.Open(pFilename,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite,&e);
		f.Write(&dmasetting,sizeof(DMASETTING));
		f.Write(&alarmsetting,sizeof(ALARMSETTING));
		f.Write(&beamctrlsetting,sizeof(BEAMCTRLSETTING));
		f.Write(&dspsetting, sizeof(DSPSETTING));
		f.Close();
}

Global_Advanced global_advance;

