#include "stdafx.h"
#include "Global_SM.h"
#include "A44_sm_handler.h"

cmdparam cmparam;
cmdparam HPA_PARAM[10];

/*
******************************************************************************
* SEND COMMAND TO THE STATUS MONITOR
* THEY ARE 2 KINDS : STATUS ACQUIRE AND COMMAND (CONTROL THE HPA AND DRIVER)
******************************************************************************
*/
void a442_sm_command (char* sm_com, unsigned short sm_com_params, unsigned int & sm_rc)
{
   
    if(strcmp(sm_com, "RSS") != 0)
	{
	    dhv_status_monitor_xmit(sm_com_params, sm_rc);
	}
	else
	{
        dhv_status_monitor_xmit_RSS(sm_rc);
		dhv_signal_generator_acquair_status(sm_rc);//acquire the infomation of frequence generator
	}
	return;
}

/*
******************************************************************************
* SEND COMMAND TO THE UPS
******************************************************************************
*/
void a422_ups_command(char* ups_com, unsigned int& ups_rc)
{
	if(strcmp(ups_com, "RSS") == 0)
	{
	    dhv_ups_xmit_RSS(ups_rc);
	}
	return;
}

/*
******************************************************************************
* READ STATUS FROM UPS
******************************************************************************
*/
void dhv_ups_xmit_RSS(unsigned int & result)
{
	if(g_sg_port.isconfiged())
	{
		result = read_ups_status(&g_sg_port);
	}
	return;
}

/*
******************************************************************************
* READ STATUS FROM UPS
******************************************************************************
*/
void dhv_ups_shutdown()
{
	writecomm_ups(&g_sg_port);
	return;
}



/*
******************************************************************************
* SEND COMMAND TO THE STATUS MONITOR
* CONTROL THE HPA AND DRIVER SWITCH
******************************************************************************
*/
void dhv_status_monitor_xmit(unsigned short command, unsigned int & result)
{
	//pack the command information.
	cmparam.param = command;
	
	g_sm_command[1] = cmparam.cparam[0];
	g_sm_command[2] = cmparam.cparam[1];

	//write to serial port.
	if(g_sm_port.isconfiged())
	{
		result = writecomm(&g_sm_port);
	}
}


/*
******************************************************************************
* SEND COMMAND TO THE STATUS MONITOR TO ACQUIRE THE STATUS
******************************************************************************
*/
void dhv_status_monitor_xmit_RSS(unsigned int & result)
{
	if(g_sm_port.isconfiged())
	{
		result = writecomm_rss(&g_sm_port);
	}
}

/*
******************************************************************************
* SEND COMMAND TO SIGNAL GENERATOR TO OPEN 25MHZ
******************************************************************************
*/
void dhv_signal_generator_25M(BOOL bOpen, unsigned int& result)
{
    if(bOpen) 
		memcpy(g_sg_command, OPEN25M, sizeof(char)*4);
	else
		memcpy(g_sg_command, CLOSE25M, sizeof(char)*4);

	if(g_sg_port.isconfiged())
	{
		result = writecomm_sg(&g_sg_port);
	}
}

/*
******************************************************************************
* SEND COMMAND FOR BEAM PARAMETER WHICH WILL BE SENT TO SIGNAL GENERATOR
******************************************************************************
*/
void dhv_signal_generator_beamsel(BOOL bObliqueSel, unsigned int& result)
{
    if(bObliqueSel) 
		memcpy(g_sg_command, OBLIQUE, sizeof(char)*4);
	else
		memcpy(g_sg_command, VERTICAL, sizeof(char)*4);

	if(g_sg_port.isconfiged())
	{
		result = writecomm_sg(&g_sg_port);
	}
}

/*
******************************************************************************
*SEND COMMAND TO SIGNAL GENERATOR TO ACQUIRE THE STATUS
******************************************************************************
*/
void dhv_signal_generator_acquair_status(unsigned int & result)
{
	if(g_sg_port.isconfiged())
	{
		result = read_alarm_of_signalgenerator(&g_sg_port);
	}
}