// Authors : Gowrisankar Prasad M V ( ASU ID - 1207446028 )
//	      Rakesh Subramanian S ( ASU ID - 1207412319 )

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sem.h"

semaphore_t *r_sem, *w_sem, *mutex;
int rc=0,wc=0,rwc=0,wwc=0;
int global_ID=1;

void reader_entry(int val)
{
	printf("Reader No.%d entering\n", val);
	P(mutex);
	if (wwc > 0 || wc > 0) {
	    printf("Reader No.%d is Blocking For Writer\n", val);
	    rwc++;		
	    V(mutex);		
	    P(r_sem);		
	    rwc--;		

	}
	rc++;
	if (rwc > 0)
	    V(r_sem);
	else
	    V(mutex);		
}

void reader_exit(int val)
{
	P(mutex);
	rc--;			
	if (rc == 0 && wwc > 0) {
	    
	    V(w_sem);
	} else
	    V(mutex);

}

void writer_entry(int val)
{
	printf("\t\t\t\t\tWriter No.%d entering\n", val);
	P(mutex);
	if (rc > 0 || wc > 0) {
	    printf("\t\t\t\t\tWriter No.%d is blocking for others\n",val);
	    wwc++;		
	    V(mutex);		
	   
	    P(w_sem);		
	    wwc--;		
	}
	wc++;			
	V(mutex);		
}

void writer_exit(int val)
{
	P(mutex);
	wc--;
	if (rwc > 0) {		
	    V(r_sem);
	} else if (wwc > 0) {	
	    V(w_sem);
	} else {		
	    V(mutex);
	}
}



void reader(void)
{ 
  int val;
  P(mutex); val = global_ID++; V(mutex);
  while(1){
	reader_entry(val);
	printf
	    ("--- Reader: No.%d ---Reading---\n", val);
	sleep(1);
	reader_exit(val);
  };
}

void writer(void)
{
  int val;
  P(mutex); val = global_ID++; V(mutex);
  while(1){
 	writer_entry(val);
	printf
	    ("\t\t\t\t\tWriter: No.%d ---Writing---\n", val);
	sleep(1);
	writer_exit(val);
  };
}

int main()
{
    mutex=CreateSem(1);
    r_sem=CreateSem(0);
    w_sem=CreateSem(0);
    start_thread(reader);
    start_thread(reader);
    start_thread(reader);
    start_thread(reader);
    start_thread(writer);
    start_thread(writer);
    
    
    run();
    //while (1) sleep(1);
}   




