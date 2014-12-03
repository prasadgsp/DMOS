// Authors : Gowrisankar Prasad M V ( ASU ID - 1207446028 )
//	      Rakesh Subramanian S ( ASU ID - 1207412319 )

#include "sem.h"
#include<string.h>
	
	typedef struct port
	{
	char msg[10][10];
	int in, out;
	semaphore_t *mutex, *full, *empty;
	}PORT;
	
	PORT p[100];
	
	
	void initports()
	{
	int i=0;
	for(i=0;i<100;i++)
	{
	p[i].in=0;
	p[i].out=0;
	p[i].mutex=CreateSem(1);
	p[i].full=CreateSem(10);
	p[i].empty=CreateSem(0);
	}
	}
	
	
	void send(PORT *p, char msg[])
	{
	//P(p->full);
	P(p->mutex);
	
	strcpy(p->msg[p->in],msg);

	p->in = ((p->in)+1)%10;
	V(p->mutex);
	//V(p->empty);
	}
	
	void receive(PORT *p, char msg[])
	{
	//P(p->empty);
	P(p->mutex);
	int i=0;
	strcpy(msg,p->msg[p->out]);	
	
	p->out = ((p->out)+1)%10;
	
	V(p->mutex);
	//V(p->full);
	
	}

