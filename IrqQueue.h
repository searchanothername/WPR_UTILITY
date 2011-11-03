#ifndef _IRQ_QUEUE_H
#define _IRQ_QUEUE_H

typedef struct irq{
	int spec_id;
	int beam_id;
	int rangebin;
	int fftnum;
}IRQ,*P_IRQ;
#define SIZE_IRQ (sizeof(IRQ))

#define MAX_SIZE (20)
class IRQQueue
{
public:
	
	IRQQueue();
	virtual ~IRQQueue();

public:
	BOOL append(IRQ i);
	BOOL remove_head(P_IRQ pq);
	int length(){return nSize;}
	void clear(){nSize = 0;}
	
private:
	IRQ irq_array[MAX_SIZE];
	HANDLE h_e[2];
	HANDLE& h_mutex;
	HANDLE& h_sem;
	int nSize;
};
#endif