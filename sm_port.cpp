#include "stdafx.h"
#include "SM_port.h"
#include "Global_SM.h"
#include "Global.h"
#include "global_ups.h"
static UPS_REQUEST req = {'Q','1'};
static UPS_COMMAND command = {'S','0','1'};


/*
******************************************************************************
* WRITE COMMAND TO THE STATUS MONITOR
******************************************************************************
*/
UINT  writecomm(LPVOID lpParam)
{
	int stat = 0;
	COMSTAT comstat;
	DWORD n = 0;
	UINT result;

	result =0;
	DWORD err = CE_RXOVER;
	CSM_Port* pCom = (CSM_Port*)lpParam;
	if(!pCom->isconfiged()){
		AfxMessageBox("PORT CONFIG IS NOT FINISHED");
		return 1;
	}

	CSingleLock sLock(&(pCom->sMutex));
	
	ClearCommError(pCom->m_hCom, &err, &comstat);
	if(sLock.Lock()){
		if(pCom->m_hCom){
		    if( comstat.cbInQue > 0 ) {
			    stat = ReadFile(pCom->m_hCom, &g_sm_status,comstat.cbInQue, &err, NULL);
			}

		    stat = WriteFile(pCom->m_hCom,g_sm_command,sizeof(unsigned char)*4,&n,NULL);
			if(stat){
				if(n<4){
					result = 2;  // Write time out occured 
				}
			}
			else{   // Communication error
				result = 3;
			}
		}
	    sLock.Unlock();
	}	
	return result;
}

/*
******************************************************************************
* WRITE RQUEST TO THE STATUS MONITOR 
******************************************************************************
*/
UINT  writecomm_rss(LPVOID lpParam)
{
	int stat = 0;
	//char RSS = 10;
	UINT result;
	DWORD n = 0;
	COMSTAT comstat;
	DWORD err = CE_RXOVER;
	result =0;

	CSM_Port* pCom = (CSM_Port*)lpParam;
	if(!pCom->isconfiged()){
		AfxMessageBox("PORT CONFIG IS NOT FINISHED");
		return 1;
	}
    
    CSingleLock sLock(&(pCom->sMutex));

    ClearCommError(pCom->m_hCom, &err, &comstat);
    if(sLock.Lock()){
		if(pCom->m_hCom){
			if( comstat.cbInQue > 0 ) {
			    stat = ReadFile(pCom->m_hCom, &g_sm_temp,comstat.cbInQue, &err, NULL);
			}
            g_sm_rss[1]= g_sm_command[1];
			stat = WriteFile(pCom->m_hCom,g_sm_rss,sizeof(unsigned char)*4,&n,NULL);
			if(stat){
				if(n<4){
					result = 2;  // Write time out occured
				}
				else{
					Sleep(100);
					DWORD length = min(pCom->m_nByteNum,comstat.cbInQue);
					//stat = ReadFile(pCom->m_hCom,&g_sm_status,sizeof(sm_status),&n,NULL);
					stat = ReadFile(pCom->m_hCom,&g_sm_status,pCom->m_nByteNum,&n,NULL);
					if(stat){
						if(n < sizeof(pCom->m_nByteNum))
							result = 4; //read time out occured
					}
					else{
						result = 5;   //Communication error
					}
				}
			}
			else{
				result = 3; // Communication error
			}		
		}
		sLock.Unlock();
	}
	return result;
}

/*
******************************************************************************
* WRITE COMMAND TO THE FREQUENCY GENERATOR
******************************************************************************
*/
UINT  writecomm_sg(LPVOID lpParam)
{
	int stat = 0;
	COMSTAT comstat;
	DWORD n = 0;
	UINT result;

	result =0;
	DWORD err = CE_RXOVER;
	CSM_Port* pCom = (CSM_Port*)lpParam;
	if(!pCom->isconfiged()){
		AfxMessageBox("PORT CONFIG IS NOT FINISHED");
		return 1;
	}

	CSingleLock sLock(&(pCom->sMutex));
	ClearCommError(pCom->m_hCom, &err, &comstat);

	if(sLock.Lock()){
		if(pCom->m_hCom){

		    if( comstat.cbInQue > 0 ) {
			    stat = ReadFile(pCom->m_hCom, &g_sg_status, comstat.cbInQue, &err, NULL);
			}

		    stat = WriteFile(pCom->m_hCom,g_sg_command,sizeof(char)*4,&n,NULL);
			if(stat){
				if(n<4){
					result = 2;  // Write time out occured 
				}
			}
			else{   // Communication error
				result = 3;
			}
		}
	    sLock.Unlock();
	}	
   return 0;
}

/*
******************************************************************************
* DESCRIPTION: READ THE ALARM FROM FREQUENCY GENERATOR
******************************************************************************
*/
UINT  read_alarm_of_signalgenerator(LPVOID lpParam)
{
	int stat = 0;
	UINT result;
	DWORD n = 0;
	COMSTAT comstat;
	DWORD err = CE_RXOVER;
	result =0;

	CSM_Port* pCom = (CSM_Port*)lpParam;
	if(!pCom->isconfiged()){
		AfxMessageBox("PORT CONFIG IS NOT FINISHED");
		return 1;
	}
    
    CSingleLock sLock(&(pCom->sMutex));

    ClearCommError(pCom->m_hCom, &err, &comstat);
    if(sLock.Lock()){
		if(pCom->m_hCom){
			Sleep(100);
			stat = ReadFile(pCom->m_hCom,&g_sg_status,sizeof(char)*4,&n,NULL);
			if(stat){
				if(n < sizeof(g_sg_status))
					result = 4; //read time out occured
			}
			else{
				result = 5;   //Communication error
			}
		}
		sLock.Unlock();
	}
	return result;
}

/*
******************************************************************************
* DESCRIPTION: WRITE COMMAND TO THE UPS FOR SHUT DOWN.
******************************************************************************
*/
UINT writecomm_ups(LPVOID lpParam)
{
	int stat = 0;
	COMSTAT comstat;
	DWORD n = 0;
	UINT result;
	UPS_STATUS temp;

	result =0;
	DWORD err = CE_RXOVER;

	//Get the serial port.
	CSM_Port* pCom = (CSM_Port*)lpParam;
	if(!pCom->isconfiged()){
		AfxMessageBox("PORT CONFIG IS NOT FINISHED");
		return 1;
	}

	if(g_ups_shutdown_time>=1 && g_ups_shutdown_time<=10)
	{
		command.c[1] = '0';
		command.c[2] = (int)g_ups_shutdown_time+'0';
	}
	else if(g_ups_shutdown_time>0 && g_ups_shutdown_time<1)
	{
		command.c[1] = '.';
		command.c[2] = (int)(g_ups_shutdown_time*10)+'0';
	}
	else{
		return 1;
	}

	CSingleLock sLock(&(pCom->sMutex));
	ClearCommError(pCom->m_hCom, &err, &comstat);

	if(sLock.Lock()){
		if(pCom->m_hCom!=INVALID_HANDLE_VALUE){

		    if( comstat.cbInQue > 0 ) {
			    stat = ReadFile(pCom->m_hCom, &temp, comstat.cbInQue, &err, NULL);
			}

		    stat = WriteFile(pCom->m_hCom,&command,UPS_COMMAND_SIZE,&n,NULL);
			if(stat){
				if(n<UPS_COMMAND_SIZE){
					result = 2;  // Write time out occured 
				}
			}
			else{   // Communication error
				result = 3;
			}
		}
	    sLock.Unlock();
	}	
	return result;
	
	return 0;
}

/*
******************************************************************************
* DESCRIPTION: READ THE STATUS FROM UPS.
******************************************************************************
*/
UINT read_ups_status(LPVOID lpParam)
{
	int stat = 0;
	UINT result;
	DWORD n = 0;
	COMSTAT comstat;
	DWORD err = CE_RXOVER;
	result =0;
	UPS_STATUS temp;

	//Fist get the serial port and check if it was configured.
	CSM_Port* pCom = (CSM_Port*)lpParam;
	if(!pCom->isconfiged()){
		AfxMessageBox("PORT CONFIG IS NOT FINISHED");
		return 1;
	}
    
    CSingleLock sLock(&(pCom->sMutex));
    ClearCommError(pCom->m_hCom, &err, &comstat);

    if(sLock.Lock()){//Lock the resource.
		if(pCom->m_hCom!=INVALID_HANDLE_VALUE){
			if( comstat.cbInQue > 0 ) {//Read out the remains in the memmory.
			    stat = ReadFile(pCom->m_hCom, &temp,comstat.cbInQue, &err, NULL);
			}
          
		    //Status inquiry
			stat = WriteFile(pCom->m_hCom,&req,UPS_REQUEST_SIZE,&n,NULL);
			if(stat){
				if(n<UPS_REQUEST_SIZE){
					result = 2;  // Write time out occured
				}
				else{
					Sleep(500);
				    stat = ReadFile(pCom->m_hCom,&g_ups_status,UPS_STATUS_SIZE,&n,NULL);
					if(stat){
						if(n < UPS_STATUS_SIZE){
							result = 4; //read time out occured
						}
					}
					else{
						result = 5;//Communication error
					}
				}
			}
			else{
				result = 3;//Communication error
			}		
		}
		sLock.Unlock();
	}
	return result;

	return 0;
}