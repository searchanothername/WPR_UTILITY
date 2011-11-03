#ifndef _SM_NEW_TX_H
#define _SM_NEW_TX_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct float_type
{
	unsigned char integer;
	unsigned char decimal;
}TX_FLOAT;

typedef struct status_byte
{
	unsigned char spare1		:1;
	unsigned char b_rf_open		:1;
	unsigned char b_rf_false	:1;
	unsigned char b_over_temp	:1;
	unsigned char b_rf_output	:1;
	unsigned char b_sw_false	:1;
	unsigned char b_power_false	:1;
	unsigned char spare2		:1;

}STATUS_BYTE;

typedef struct status_psp
{
	unsigned char _sp_bsu_flt	:1;
	unsigned char _w_adclk		:1;
	unsigned char _rd			:1;
	unsigned char _lrb			:1;
	unsigned char _t0			:1;
	unsigned char _w_iqclk		:1;
	unsigned char _w_dvcc		:1;
	unsigned char _w_avcc		:1;
}STATUS_PSP;
/*
typedef struct sm_status
{
	unsigned char sm_hrd;				//B0 
	TX_FLOAT sm_pwr_input;				//B1 B2
	TX_FLOAT sm_5_V;					//B3 B4
	TX_FLOAT sm_pwr_output;				//B5 B6
	TX_FLOAT sm_pwr_reflect;			//B7 B8
	TX_FLOAT sm_temperature;			//B9 B10
	TX_FLOAT sm_13_V;					//B11 B12
	TX_FLOAT sm_50_V;					//B13 B14
	TX_FLOAT sm_28_V;					//B15 B16
	TX_FLOAT sm_36_V;					//B17 B18
	TX_FLOAT sm_15_V;					//B19 B20
	TX_FLOAT sm_neg_15_V;				//B21 B22
	STATUS_BYTE sm_status_byte;			//B23 

	//{ADD IT FOR RECORD THE DUTY 2010/3/30
	unsigned char sm_pos_pulse_width_h;	 //B24
	unsigned char sm_pos_pulse_width_l;  //B25
	unsigned char sm_neg_pulse_width_h;  //B26
	unsigned char sm_neg_pulse_width_l;  //B27
	unsigned char sm_tx_spare[6];        //B28 ~ B33
	//}
	unsigned char sm_end;				//B34

	unsigned char sm_spare_byte[3];		//B35 B36 B37
	unsigned char sm_15_v;				//B38
	unsigned char sm_pos_voltage_spare;	//B39
	unsigned char sm_9_v;				//B40
	unsigned char sm_pos_voltage_spare1;//B41
	unsigned char sm_neg_15_v;			//B42
	unsigned char sm_neg_voltage_spare1;//B43
	unsigned char sm_neg_5_v;			//B44
	unsigned char sm_5_v3;				//B45
	unsigned char sm_24_v;				//B46
	unsigned char sm_5_v4;				//B47
	unsigned char sm_12_v;				//B48
	unsigned char sm_6_v;				//B49
	unsigned char sm_5_v1;				//B50
	unsigned char sm_3_3_v;				//B51
	unsigned char sm_5_v2;				//B52
	unsigned char sm_InDoor_Temperature;//B53
	unsigned char sm_Spare_B44;         //B54
	unsigned char sm_Pos_Ant_Power;		//B55
	unsigned char sm_Spare_B46;			//B56
	unsigned char sm_Neg_Ant_Power;		//B57
	unsigned char sm_Spare_B48;			//B58
	unsigned char sm_OutDoor_Temperature;//B59
	unsigned char sm_voltage_spare;		//B60
	unsigned char sm_B51;				//B61		
	STATUS_PSP	  sm_psp_status;		//B62
	unsigned char sm_B53;				//B63
}SM_STATUS,*P_SM_STATUS;
*/
/*
typedef struct sm_status
{
	//TX PART TOTAL 35 BYTES
	unsigned char sm_hrd;				//B0 
	TX_FLOAT sm_pwr_input;				//B1 B2
	TX_FLOAT sm_5_V;					//B3 B4
	TX_FLOAT sm_pwr_output;				//B5 B6
	TX_FLOAT sm_pwr_reflect;			//B7 B8
	TX_FLOAT sm_temperature;			//B9 B10
	TX_FLOAT sm_13_V;					//B11 B12
	TX_FLOAT sm_50_V;					//B13 B14
	TX_FLOAT sm_28_V;					//B15 B16
	TX_FLOAT sm_36_V;					//B17 B18
	TX_FLOAT sm_15_V;					//B19 B20
	TX_FLOAT sm_neg_15_V;				//B21 B22
	STATUS_BYTE sm_status_byte;			//B23 
	//{ADD IT FOR RECORD THE DUTY 2010/3/30
	unsigned char sm_pos_pulse_width_h;	 //B24
	unsigned char sm_pos_pulse_width_l;  //B25
	unsigned char sm_neg_pulse_width_h;  //B26
	unsigned char sm_neg_pulse_width_l;  //B27
	unsigned char sm_tx_spare[6];        //B28 ~ B33
	//}
	unsigned char sm_end;				 //B34

	//SPARE
    unsigned char sm_spare_byte[5];			 //B35 ~ B39

	//CABIN PART TOTAL 60 BYTES
	unsigned char sm_12_v;				 //B40
	unsigned char sm_spare_byte_0[3];	 //B41 ~ B43
	unsigned char sm_5_v1;					//B44
	unsigned char sm_15_v;					//B45
	unsigned char sm_6_v1;					//B46
	unsigned char sm_9_v;					//B47
	unsigned char sm_Pos_Ant_Power;			//B48
	unsigned char sm_spare_byte_1[3];		//B49 ~ B51
	unsigned char sm_OutDoor_Temperature;	//B52
	unsigned char sm_spare_byte_a;			//B53
	unsigned char sm_InDoor_Temperature;	//B54
	unsigned char sm_Neg_Ant_Power;			//B55
	unsigned char sm_spare_byte_2[4];		//B56 ~ B59
	unsigned char sm_5_v3;					//B60
	unsigned char sm_neg_15_v;				//B61
	unsigned char sm_5_v2;					//B62
	unsigned char sm_3_3_v;					//B63
	unsigned char sm_spare_byte_3[2];		//B64 ~ B65
	unsigned char sm_24_v;					//B66
	unsigned char sm_28_v;					//B67
	unsigned char sm_neg_5_v;				//B68
	unsigned char sm_spare_byte_b;			//B69
	unsigned char sm_6_v2;					//B70
	unsigned char sm_5_v4;					//B71
	unsigned char sm_spare_byte_4[8];		//B72 ~ B79

	union{									//B80
		struct BYTE_80{
			unsigned char lrb:1;
			unsigned char spare1:3;
			unsigned char rd:1;
			unsigned char spare2:3;
		}sm_byte_80_field;
		unsigned char sm_byte_80;
	};

	
	unsigned char sm_byte_81;				//B81
	unsigned char sm_byte_82;				//B82

	union{									//B83
		struct BYTE_83{
			unsigned char spare1:4;
			unsigned char tx_bias_gate:1;
			unsigned char stc:1;
			unsigned char tr_amp:1;
			unsigned char t0:1;
		}sm_byte_83_field;
		unsigned char sm_byte_83;
	};

	union{									//B84
		struct BYTE_84{
			unsigned char spare1:5;
			unsigned char av_cc:1;
			unsigned char spare2:2;	
		}sm_byte_84_field;
		unsigned char sm_byte_84;
	};

	union{									//B85
		struct BYTE_85{
			unsigned char spare1:2;
			unsigned char iqclock:1;
			unsigned char dv_cc:1;
			unsigned char adclock:1;
			unsigned char spare2:3;	
		}sm_byte_85_field;
		unsigned char sm_byte_85;
	};

	unsigned char sm_byte_86;				 //B86
	unsigned char sm_byte_87_selftest;	     //B87	
	unsigned char sm_byte_88_selftest;	     //B88	
	unsigned char sm_byte_89_selftest;	     //B89	
	unsigned char sm_byte_90_selftest;	     //B90	
	unsigned char sm_byte_91_selftest;	     //B91	
	unsigned char sm_byte_92_selftest;	     //B92	
	unsigned char sm_rass_stat;				 //B93	
	unsigned char sm_byte_94_selftest;	     //B94	
	unsigned char sm_byte_95_selftest;	     //B95	
	unsigned char sm_byte_96_selftest;	     //B96	
	unsigned char sm_byte_97_selftest;	     //B97	
	unsigned char sm_byte_98_selftest;	     //B98	
	unsigned char sm_byte_99_selftest;	     //B99	

}SM_STATUS,*P_SM_STATUS;
*/

/*
******************************************
* DESCRIPTION:
*	DIFINITION FOR STATUS MONITOR
******************************************
*/
#define MAX_SM_BYTE 100
typedef struct sm_status
{
	unsigned char sm_byte[MAX_SM_BYTE];
}SM_STATUS,*P_SM_STATUS;
#define SM_STATUS_BYTE_SIZE (sizeof(SM_STATUS))

/*
******************************************
* DESCRIPTION:
*	DIFINITION FOR PSP STATUS
******************************************
*/
typedef struct sp_status
{
	bool	lrb;
	bool	rd;
	bool	tx_bias_gate;
	bool	stc;
	bool	tr_amp;
	bool	t0;
	bool	av_cc;
	bool	iqclock;
	bool	dv_cc;
	bool	adclock;
}SP_STATUS,*P_SP_STATUS;
#define SP_STATUS_SIZE (sizeof(SP_STATUS))

/*
******************************************
* DESCRIPTION:
*	DIFINITION FOR TX STATUS
******************************************
*/
typedef struct tx_status
{
	bool tx_input;
	bool tx_output;
	bool tx_swr;
	bool tx_over_temp;
	bool tx_power_supply;
	bool tx_power_on;
}TX_STATUS,*P_TX_STATUS;
#define TX_STATUS_SIZE (sizeof(TX_STATUS))


#ifdef __cplusplus
}
#endif
#endif