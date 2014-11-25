// Authors : Gowrisankar Prasad M V ( ASU ID - 1207446028 )
//	      Rakesh Subramanian S ( ASU ID - 1207412319 )

#include<stdio.h>
#include "threads.h"

int global = 0;

void functionA()
{
int local=0;

printf("\n");

while(1)
{
printf("<--------------------------------------------->");
printf("\n\nFunction A Running\n");

printf("Local variable of FunctionA = %d\n",++local);
printf("Global variable incremented to= %d\n",++global);
yield();
printf("Resuming Function A\n\n");
}

}

void functionB()
{
int local=0;

printf("\n");
while(1)
{
printf("<--------------------------------------------->");
printf("\n\nFunction B Running\n");
printf("Local variable of FunctionB = %d\n",++local);
printf("Global variable incremented to= %d\n",++global);
yield();
printf("Resuming Function B\n\n");
}

}

void functionC()
{
int local=0;

printf("\n");
while(1)
{
printf("<--------------------------------------------->");
printf("\n\nFunction C Running\n");
printf("Local variable of FunctionC = %d\n",++local);
printf("Global variable incremented to= %d\n",++global);
yield();
printf("Resuming Function C\n\n");
}

}

int main()
{
//start the threads
printf("\n");
start_thread(&functionA);
start_thread(&functionB);
start_thread(&functionC);
run();
return 0;
}

