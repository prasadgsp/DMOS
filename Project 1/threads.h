// Authors : Gowrisankar Prasad M V ( ASU ID - 1207446028 )
//			 Rakesh Subramanian S ( ASU ID - 1207412319 )

#include "q.h"
	
	//header value to be sent to Q 
	TCB_t *headerVal = '\0';
	
	static int count = 0; //to be added to the 

void start_thread(void *runFunction) //function is passed as parameter?
{

	void *stackAlloc =  (void*)malloc (8192);//allocate a stack (via malloc) of a 		certain size (choose 8192)
	//allocate a tcb via malloc
	TCB_t *tcbAlloc = (TCB_t*) malloc (sizeof(TCB_t));
	//call init_TCB	
	init_TCB(tcbAlloc, runFunction, stackAlloc, 8192);
	//call addQ
	count++;
	tcbAlloc->counter = count;//should add counter in TCB structure
	AddQ(&headerVal,tcbAlloc); 
}

void run()
{
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(headerVal->context));
}

void yield()
{	//get the previous thread context
	TCB_t *prevContext = '\0';
	prevContext = headerVal;
	
	//store current context 
	rotateQ(&headerVal);
	
	swapcontext(&(prevContext->context),&(headerVal->context)); 
	//swap the context, from previous thread to the thread pointed to by runQ	
}
	


