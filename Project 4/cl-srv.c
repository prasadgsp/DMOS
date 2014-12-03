// Authors : Gowrisankar Prasad M V ( ASU ID - 1207446028 )
//	      Rakesh Subramanian S ( ASU ID - 1207412319 )

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "msgs.h"
int flag=0;
char newExtmsg[10];
void client_print()
{
int i=0;
int j=0;
char msg[10];
char table[10][10];
int count=0;
while(1)
{
sleep(1);
if(count%2==0)
	yield();

P(p[0].full);
//printf("\nEntering Print Client\n");
strcpy(msg,"PRINT");
send(&p[0],msg);
printf("\nPrint Client --- Sent 'Print' Command\n");
sleep(2);
V(p[0].empty);

P(p[55].empty);
printf("\nPrint Client --- Receiving Table Entries from Server\n");
for(i=0;i<10;i++)
{
receive(&p[55+i],table[i]);
}
printf("\nPrint Client --- Printing Table\n\n");
for(i=0;i<10;i++)
{
	printf("%d - %s\t",i,table[i]);
}
printf("\n\n");
count++;
sleep(1);
V(p[55].full);

}

}

void client_AddDel()
{


char flag[10];
char msg[10];
char msg7[10];
char addDel[3][20];
char table[10][10];
strcpy(addDel[0],"ADD_String_>_102");
strcpy(addDel[1],"ADD1");
strcpy(addDel[2],"ADD2");

while(1)
{
strcpy(flag,"NO");
int randAddDel;
srand(time(NULL));
randAddDel=rand()%2;

if(randAddDel==0)
{
printf("\nAdd/Modify Client decided to perform ADD Operation\n");
int rand1;
int rand2;
P(p[0].full);
sleep(1);
strcpy(msg,"ADD");
send(&p[0],msg);
printf("\nAdd Client --- Sent 'ADD' Command\n");
srand(time(NULL));
rand1=rand()%10;
msg7[0]=(char)(((int)'0')+rand1);
rand2=rand()%3;
//------------------------------------
int receivelength = strlen(addDel[rand2]);
int counter=0;
int i=0;
if((receivelength>10))
{
strcpy(flag,"YES");
char newmsg[10];
printf("\nAdd Client --- Decided to add at position %s with String %s\n",msg7,addDel[rand2]);
printf("\nServer --- String length of '%s' greater than 10: SPLITTING STRING \n",addDel[rand2]); 


int x=0;
int jj;
strncpy(newmsg,addDel[rand2],10);
printf("\n First half of the string is %s:\n",newmsg);
for(jj=10;jj<receivelength;jj++)
{
newExtmsg[jj-10]=addDel[rand2][jj];
}
newExtmsg[receivelength]='\0';


int randomnew;
char pos[20];
srand(time(NULL));
randomnew=rand()%10;
pos[0]=(char)(((int)'0')+randomnew);
send(&p[74],flag);
send(&p[74],pos);
send(&p[74],newmsg);
send(&p[74],newExtmsg);

printf("\n Add Client --- First half of msg is %s\n",newmsg);
printf("\n Add Client --- Second half of the string is %s:\n",newExtmsg);

V(p[0].empty);
P(p[74].empty);

sleep(1);
V(p[74].full);


}

else{
send(&p[74],flag);
printf("\nAdd Client --- Decided to add at position %s with String %s\n",msg7,addDel[rand2]);
send(&p[74],msg7);
send(&p[74],addDel[rand2]);
V(p[0].empty);
P(p[74].empty);

sleep(1);
V(p[74].full);
}


}
else  {
printf("\nAdd/Delete Client decided to perform DELETE Operation\n");
int randx;
P(p[0].full);
sleep(1);
strcpy(msg,"DELETE");
send(&p[0],msg);
printf("\nDelete Client --- Sent 'DELETE' Command\n");

srand(time(NULL));
randx=rand()%10;
if(randx-1==0)
{
randx+1;
}
else
{
randx-1;
}
msg7[0]=(char)(((int)'0')+randx);
printf("\nDelete Client --- Decided to delete at position %s\n",msg7);
send(&p[21],msg7);
V(p[0].empty);
P(p[21].empty);

sleep(1);
V(p[21].full);

}
}
}

void client_modify()
{
int i=0;
int j=0;
char reply[10];
int rand1,rand2;
char msg2[10];
strcpy(msg2,"");
char msg[10];
char table[10][10];
char mod[3][10];
strcpy(mod[0],"M1");
strcpy(mod[1],"M2");
strcpy(mod[2],"M3");
char temp[10];
while(1)
{
P(p[0].full);
sleep(2);
//printf("\nEntering Modify Client\n");
strcpy(msg,"MODIFY");
send(&p[0],msg);
printf("\nModify Client --- Sent 'Modify' Command\n");
srand(time(NULL));
rand1=rand()%10;
msg2[0]=(char)(((int)'0')+rand1);
rand2=rand()%3;
printf("\nModify Client --- Decided to modify position %d with String %s\n",rand1,mod[rand2]);
send(&p[25],msg2);
send(&p[25],mod[rand2]);
printf("\n\n");
sleep(1);
V(p[0].empty);
P(p[25].empty);
sleep(1);
V(p[25].full);
}
}


void server()
{
int i;
char flag[10];
char table[10][40];
char msg[10];
char msg1[10];
char msg2[10];
char msg14[10];
char msg16[20];
char msg15[300];

int m1,m2;
int m3;
char replym[10];
strcpy(replym,"Completed");
while(1)
{
P(p[0].empty);
sleep(1);
printf("\nServer --- Entering Server\n");
receive(&p[0],msg);
if(strcmp(msg,"PRINT")==0)
{
V(p[0].full);
P(p[55].full);
printf("\n Server --- Server received command from Print Client \n");
printf("\n Server --- Sending Table to Print Client\n");
for(i=0;i<10;i++)
{
send(&p[55+i],table[i]);
}
printf("\n Server --- Sent \n");
V(p[55].empty);
}
else if(strcmp(msg,"ADD")==0)
{

V(p[0].full);
P(p[74].full);

receive(&p[74],flag);
printf("\n Server --- Server received command from ADD Client %s\n",flag);
receive(&p[74],msg14);
m3=atoi(msg14);
receive(&p[74],msg15);

if(strlen(flag)==3)
{
receive(&p[74],msg16);
}

printf("\n Server --- Trying to perform Received ADD command at position %d with string %s \n",m3,msg15);
int length = strlen (table[m3]);
if(length==0)
{
if(strlen(flag)==3)
{
int m4;

if(m3==8 || m3==9)
{
m4=0;
}
else
{
 m4=m3+2;
}

while(strlen(table[m4])!=0)
{

if(m4==9)
{
m4==0;
}
else
{
m4=m4+1;
}
}
printf("\nServer --- Copying 2nd String at position %d\n",m4);
strcpy(table[m4],msg16);
}

strcpy(table[m3],msg15);
printf("\nServer --- String added successfully at position %d\n",m3);
}
else
{
	printf("\nServer --- Position %d already has a String existing...Cannot Add\n",m3);
}
V(p[74].empty);
}
else if(strcmp(msg,"MODIFY")==0)
{
printf("\n Server --- Server received command from Modify Client \n");
V(p[0].full);
P(p[25].full);
receive(&p[25],msg1);
m1=atoi(msg1);
receive(&p[25],msg2);
int length = strlen (table[m1]);
if(length==0)
{
printf("\nServer --- Position %s does not have any string. Cannot modify\n",msg1);
}
else
{
char temporary[10];
strcpy(temporary,msg2);
printf("\n Server --- Sending Received command to modify position %d with string %s \n",m1,msg2);
strcat(table[m1],temporary);
printf("\nServer --- Modified Successfully\n");
}
V(p[25].empty);
}
else if(strcmp(msg,"DELETE")==0)
{
char msg10[10];
int m5;
V(p[0].full);
P(p[21].full);
printf("\n Server --- Server received command from DELETE Client\n");
receive(&p[21],msg10);
m5 = atoi(msg10);
strcpy(table[m5],"");
printf("\nServer --- Deleted at position %d Successfully\n",m5);
V(p[21].empty);
}
}
}


int main()
{ 
  printf("\nDocumentation\n---------------\n\nIntroduction:\n*************\n\n The system has THREE clients and ONE server. The client functionalities are as follows:\n\n 1. Client 1: Print Client \n---------\nThe client one prints the contents of the table after each request to the server. Only one  request is sent at a time. The print client  has a yield() function in it for manual switching of threads to make sure other clients run more often than the print as they are of more significance.\n\n 2. Client 2: ADD/DELETE Client \nThe client performs addition and deletion operation on the table. \n\n ADD:\n------\nThe addition function looks for an empty position in the table and if there is one, it adds the string to it. The general lenght of string is defined to be of 10 characters. However,  if sometimes the string is of higher length, then the string is split into strings of length10 characters each.\n\n DELETE:\n---------\nThe delete operation randomly looks for positions in the table to empty them, this operation is primarily used to maintain balance to make sure the table does not overflow with more  strings than it can handle.\n\n 3. Client 3: MODIFY Client\n----------------- \n The client performs modification operations on the table\n The modify function randomly looks for a position in the table and if the contents of that position are not empty, it modifies the same by concantenating with some random precoded string \n\n  4. SERVER:\n---------\n The server is the thread which does all the work listed above. It receives the various commands and any inputs such as position and precoded string if necessary for print/add/delete/modify operations \n ");
sleep(3);
    initports();	
    printf("\nCreating a SERVER\n");
   start_thread(server);
printf("\nCreating Print client\n");
    start_thread(client_print);
      printf("\nCreating Modify client\n");
    start_thread(client_modify);
printf("\nCreating Add/Del client\n");
  start_thread(client_AddDel);
  
  
    printf("\n\n");
    run();
    while (1) 
	{ sleep(1);}
return 0;
} 
