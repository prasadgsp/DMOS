// Authors : Gowrisankar Prasad M V ( ASU ID - 1207446028 )
//	      Rakesh Subramanian S ( ASU ID - 1207412319 )

#include "msgs.h"
#include<stdlib.h>
#include<time.h>

int clientid=0;
int serverid=0;

void client()
{
srand(time(NULL));
int r=(rand()%100);
int count1=0;
while(1){
P(p[99].full);
  int a[10];
  int i=0;  
 printf("\n---------------------------------------------------------------------------------\n");
  
  printf("\nCLIENT 1 SENDING DATA along with reply port\n\n");
  a[0]=r;
  for(i=1;i<10;i++) 
  { 
 	 a[i]=count1 +i;
 	 printf("%d\t", a[i]); 
  }
    printf("\n");
 send(&p[99], a);
  	count1+=10;

  sleep(1);
V(p[99].empty);

P(p[r].empty);
   printf("\nClient 1 Receiving Data from Server on Port %d\n",r);
   receive(&p[r],a);
   printf("\n???????????????????????????????????????????\n");
   for(i=1;i<10;i++) 
  { 
 	 printf("%d\t", a[i]); 
  }
   printf("\n???????????????????????????????????????????\n");	
 sleep(1);
V(p[r].full);
  }
}

void client1()
{
srand(time(NULL));
int r=(rand()%100);
int count1=100;
while(1){
P(p[99].full);
  int a[10];
  int i=0;  

 printf("\n---------------------------------------------------------------------------------\n");
  printf("\nCLIENT 2 SENDING DATA along with reply port\n\n");
  a[0]=r;
  for(i=1;i<10;i++) 
  { 
 	 a[i]=count1 +i;
 	 printf("%d\t", a[i]); 
  }
    printf("\n");
  send(&p[99], a);
  count1+=10;
  sleep(1);
V(p[99].empty);
P(p[r].empty);
   printf("\nClient 2 Receiving Data from Server on Port %d\n",r);
   receive(&p[r],a);
   printf("\n???????????????????????????????????????????\n");
   for(i=1;i<10;i++) 
  { 
 	 printf("%d\t", a[i]); 
  }
   printf("\n???????????????????????????????????????????\n");	
 sleep(1);
V(p[r].full);
  }

}


void server()
{
int count=0;
int replyport;
while(1){
  P(p[99].empty);
  count++;
  int a[10];
  receive(&p[99],a);
  printf("\n\nServer: Receive Success \n");
  int i=0; 
   	printf("\n-------------------------------------------\n");
  for(i=1;i<10;i++)
  printf("%d\t", a[i]);
   	printf("\n-------------------------------------------\n");
  replyport=a[0];
V(p[99].full);
  P(p[replyport].full);
  printf("\nServer Incrementing Data Value by 1 and sending it back via Reply Port %d\n",replyport);
  for(i=0;i<10;i++)
	a[i]=a[i]+1;
   send(&p[replyport],a);
  V(p[replyport].empty);
}
}

int main()
{   
    initports();
    printf("\nCreating a client\n");
    clientid++;
    start_thread(client);
    printf("\nCreating a client\n");
    clientid++;
    start_thread(client1);
   printf("\nCreating a server\n");
    start_thread(server);
    printf("\n\n");
    run();
    while (1) 
	{ sleep(1);}
}   



	
