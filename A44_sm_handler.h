#ifndef _A44_SM_HANDLER_H
#define _A44_SM_HANDLER_H

//FOR STATUS MONITOR
void a442_sm_command (char* sm_com, unsigned short sm_com_params, unsigned int & sm_rc);
void dhv_status_monitor_xmit(unsigned short command, unsigned int & result);
void dhv_status_monitor_xmit_RSS(unsigned int & result);

//FOR NEW FREQ GENERATOR
void dhv_signal_generator_acquair_status(unsigned int & result);
void dhv_signal_generator_beamsel(BOOL bObliqueSel, unsigned int& result);
void dhv_signal_generator_25M(BOOL bOpen, unsigned int& result);

//FOR UPS 
void a422_ups_command(char* ups_com, unsigned int& ups_rc); 
void dhv_ups_xmit_RSS(unsigned int & result);
void dhv_ups_shutdown(); 

union cmdparam
{
	unsigned short param;
	char cparam[2];
};
extern cmdparam cmparam;
extern cmdparam HPA_PARAM[10];

#endif