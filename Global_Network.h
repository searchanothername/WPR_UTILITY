#ifndef _GLBOAL_NETWORK_H
#define _GLBOAL_NETWORK_H

#ifdef __cplusplus
extern "C" {
#endif

/*
*******************************************
* SIZE
*******************************************
*/
#define		HEADELEN			(sizeof(HDR))				
#define		OVERLAPPEDPLUSLEN	(sizeof(IO_OPERATION_DATA))	
#define		SERVERPORT			5555						
#define		RECV_BUFFER_SIZE	128	 	
#define		MAX_SUBTHREAD_SIZE	5	
#define     DATA_BUFFER_SIZE    1024

/*
********************************************
* IO OPERATION
********************************************
*/
#define		IOReadHead			10						
#define		IOReadBody			(IOReadHead+1)	
#define     IOWriteData         (IOReadBody+1)				
#define		IOEXIT				(IOWriteData+1)				 

/*
********************************************
* TYPE OF PACKAGE
********************************************
*/
#define		TYPE_HEARTBEAT			100						
#define		TYPE_STATUS				101					
#define		TYPE_DATA				102						

/*
********************************************		
* HEADER DEFINITION
********************************************
*/
typedef struct _header
{
	unsigned short		ustype;	//PACKAGE TYPE
	unsigned short		usLen;	//DATA LENGTH
}HDR, *PHDER;

/*
*********************************************			
* I/O OPERATION STRUCT
*********************************************
*/
typedef	struct _io_operation_data 
{
	OVERLAPPED	overlapped;					
	char		recvBuf[RECV_BUFFER_SIZE];		
	HDR			hdr;						
	byte		type;					
}IO_OPERATION_DATA, *PIO_OPERATION_DATA;

#ifdef __cplusplus
}
#endif
#endif