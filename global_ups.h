#ifndef _GLOBAL_UPS_H
#define _GLOBAL_UPS_H

#ifdef __cplusplus
extern "C" {
#endif

#define UPS_REQUEST_LEN 2
#define UPS_STATUS_LEN (47+1) //beause the sting have an end flag'/0'.
#define UPS_COMMAND_LEN 3
enum{
		IP_VOLTAGE,
		IP_FAULT_VOLTAGE,
		OP_VOLTAGE,
		OP_LOAD,
		IP_FREQ,
		BATTERY_VOLTAGE,
		TEMPERATURE,
		_STATUS
};
//STRUCT FOR STATUS INQUIRY 
typedef struct ups_request
{
	char r[UPS_REQUEST_LEN];
}UPS_REQUEST,*P_UPS_REQUEST;
#define UPS_REQUEST_SIZE (sizeof(UPS_REQUEST))

//STRUCT FOR STORE THE STATUS
typedef struct ups_status
{
	char s[UPS_STATUS_LEN];
}UPS_STATUS,*P_UPS_STATUS;
#define UPS_STATUS_SIZE (sizeof(UPS_STATUS))

//STRUCT FOR SHUTDOWN THE UPS
typedef struct ups_command
{
	char c[UPS_COMMAND_LEN];
}UPS_COMMAND,*P_UPS_COMMAND;
#define UPS_COMMAND_SIZE (sizeof(UPS_COMMAND))


//{LIUChen add it for ups 2009/12/11
typedef struct ups_data
{
	
	float ups_I_P_voltage;
	float ups_I_P_fault_voltage;
	float ups_O_P_voltage;
	float ups_O_P_load;
	float ups_I_P_frquence;
	float ups_Battery_voltage;
	float ups_Temperature;
	union {
		struct status_struct
		{
			unsigned char _received:1;
			unsigned char _shut_down_active:1;
			unsigned char _test_in_progress:1;
			unsigned char _standby:1; //0: online
			unsigned char _failed:1;
			unsigned char _bypass_boot_active:1;
			unsigned char _battery_low:1;
			unsigned char _utility_faild:1;   
		}status;
		unsigned char ch_status;
	}ups_status;
}UPS_DATA, *P_UPS_DATA;


#ifdef __cplusplus
}
#endif

#endif