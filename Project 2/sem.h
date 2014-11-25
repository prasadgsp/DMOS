// Authors : Gowrisankar Prasad M V ( ASU ID - 1207446028 )
//	      Rakesh Subramanian S ( ASU ID - 1207412319 )

#include "threads.h"
#include<stdio.h>
#include<unistd.h>

typedef struct semaphore
{
int counter;
TCB_t *semQ;
}semaphore_t;

semaphore_t *CreateSem(int InputValue)
{
semaphore_t *sem=(semaphore_t *)malloc(sizeof(semaphore_t));
sem->counter=InputValue;
//InitQ(&(sem->semQ));
return sem;
}


void P(semaphore_t *sem)
{
sem->counter--;
if(sem->counter<0)
	{
	AddQ(&(sem->semQ),DelQ(&headerVal));
	swapcontext(&(sem->semQ->prev->context),&(headerVal->context));	
	}
}

void V(semaphore_t *sem)
{
sem->counter++;

if(sem->counter<=0)
	{
	AddQ(&headerVal,DelQ(&(sem->semQ)));
	
	}
yield();

}

