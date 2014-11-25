// Authors : Gowrisankar Prasad M V ( ASU ID - 1207446028 )
//			 Rakesh Subramanian S ( ASU ID - 1207412319 )

#include<unistd.h>
#include "tcb.h"

void InitQ(TCB_t**); 
void AddQ(TCB_t**,TCB_t*);
TCB_t* DelQ(TCB_t**);
void RotateQ(TCB_t**);

void InitQ(TCB_t **Q)
{	
	(*Q)->prev = *Q ;
	(*Q)->next = *Q;
	printf("\nQueue Initialized\n");
}

void AddQ(TCB_t **Q, TCB_t *addnode) 
{
 
    if (*Q== '\0')
    {
	//printf("1st thread added");
	
	InitQ(&addnode);
	*Q= addnode;
	
    }
    else
    {
	//printf("Adding subsequent threads");
    	(*Q)->prev->next=addnode;	
	addnode->next = *Q;
	addnode->prev= (*Q)->prev;
	(*Q)->prev=addnode;
    }
}


TCB_t* DelQ(TCB_t **Q)
{

TCB_t *delQ = '\0';

if((*Q) == '\0')
{
	//printf("Empty Queue\n");
}
else
{
	delQ=(*Q);

	if((*Q)->prev==(*Q))
	{
	(*Q) = '\0';
	//printf("Deleted only element from Q\n");
	}
	else
	{
	(*Q)->prev->next=(*Q)->next;
	(*Q)->next->prev=(*Q)->prev;
	(*Q)=(*Q)->next;
	}
delQ->prev='\0';
delQ->next='\0';
return delQ;
}

}


void rotateQ(TCB_t **Q)
{
TCB_t *rotate;
if((*Q)=='\0')
{
	printf("Empty Queue\n");
}
else
{	printf("\nContext Switch to next thread\n");
	rotate=DelQ(Q);
	AddQ(Q,rotate);
	//(*Q)=(*Q)->next; 
	sleep(1);
}
}
