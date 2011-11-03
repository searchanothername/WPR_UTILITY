#include "stdafx.h"
#include "IrqQueue.h"


IRQQueue::IRQQueue()
:h_mutex(h_e[0]),h_sem(h_e[1]),nSize(0)
{
	h_mutex = ::CreateMutex(0,0,0);
	h_sem = ::CreateSemaphore(0,0,MAX_SIZE,0);
}

IRQQueue::~IRQQueue()
{
	::CloseHandle(h_mutex);
	::CloseHandle(h_sem);
}


BOOL IRQQueue::append(IRQ i)
{
	BOOL bStat;
	DWORD dw = ::WaitForSingleObject(h_mutex, 1000);
	if(dw == WAIT_OBJECT_0){
		long lPrev = 0;
		bStat = ::ReleaseSemaphore(h_sem,1,&lPrev);
		if(bStat){
			memcpy(&(irq_array[lPrev]),&i,SIZE_IRQ);
			++nSize;
		}else{
			//ERROR REPORT
		}
		::ReleaseMutex(h_mutex);
		return TRUE;
	}
	else
	{
		//ERROR REPORT
		return TRUE;
	}
	return FALSE;
}


BOOL IRQQueue::remove_head(P_IRQ pq)
{
	DWORD dw = ::WaitForMultipleObjects(2,h_e,TRUE,2000);
	if(dw == WAIT_OBJECT_0)
	{//PULL IT OUT
		*pq = irq_array[0];
		::MoveMemory(&(irq_array[0]), &(irq_array[1]), SIZE_IRQ*(MAX_SIZE-1));
	
		--nSize;
		::ReleaseMutex(h_mutex);
		return TRUE;
	}else
	{
		return FALSE;
	}
	return FALSE;
}
