
Q 1) Write a C program to implement Inter Process Communication using pipes to read and write at least two pair of child process.

Sol 1 )
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
/* Write COUNT copies of MESSAGE to STREAM, pausing for a second
between each. */
void writer (const char* message, int count, FILE* stream)
{
for (; count > 0; --count) {
/* Write the message to the stream, and send it off immediately. */
fprintf (stream, “%s\n”, message);
fflush (stream);
/* Snooze a while. */
sleep (1);
}
}
/* Read random strings from the stream as long as possible. */
void reader (FILE* stream)
{
char buffer[1024];
/* Read until we hit the end of the stream. fgets reads until
either a newline or the end-of-file. */
while (!feof (stream)
&& !ferror (stream)
&&fgets (buffer, sizeof (buffer), stream) != NULL)
fputs (buffer, stdout);
}
int main ()
{
intfds[2];
pid_tpid;
/* Create a pipe. File descriptors for the two ends of the pipe are
placed in fds. */
pipe (fds);
/* Fork a child process. */
for(int i=0 ;i <3;i++)
pid = fork ();
if (pid == (pid_t) 0) {
FILE* stream;
/* This is the child process. Close our copy of the write end of
the file descriptor. */
close (fds[1]);
/* Convert the read file descriptor to a FILE object, and read
from it. */
stream = fdopen (fds[0], “r”);
reader (stream);
close (fds[0]);
}
else {
/* This is the parent process. */
FILE* stream;
/* Close our copy of the read end of the file descriptor. */
close (fds[0]);
/* Convert the write file descriptor to a FILE object, and write
to it. */
stream = fdopen (fds[1], “w”);
writer (“Hello, world.”, 5, stream);
close (fds[1]);
}
return 0;
}

Q 2) Write a C program to implement Producer- Consumer problem in UNIX using shared memory.

Sol 2 )
/*PRODUCER CONSUMER  using shared memory*/
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#define N 5
struct buffer
{
int b[N];
sem_tempty,full;
intin,out;
}buf;
void *P()
{
int i=1;
while(1)
{
sem_wait(&(buf.empty));
buf.b[buf.in]=i;
buf.in=(buf.in+1)%N;
printf(“\nProduced :%d”,i++);
sleep(2);
sem_post(&(buf.full));
}
}
void *C()
{
int item;
while(1)
{
sem_wait(&(buf.full));
item=buf.b[buf.out];
buf.out=(buf.out+1)%N;
printf(“\nConsumed :%d”,item);
sem_post(&(buf.empty));
}
}
void main()
{
pthread_t t1,t2;
sem_init(&(buf.empty),0,N);
sem_init(&(buf.full),0,0);
buf.in=0;
buf.out=0;
pthread_create(&t1,NULL,P,NULL);
pthread_create(&t2,NULL,C,NULL);
pthread_join(t1,NULL);
pthread_join(t2,NULL);
}
Q 3) Write a thread program which demonstrates Pthreads condition variables. The main thread creates two threads. Both the threads should execute in interleaved manner and output should be as follows:
Thread 1 will print “I am in thread one”
Thread 2 will print “I am in thread 2”
Your output screen should be:
I am in thread one
I am in thread 2
I am in thread one
I am in thread 2
I am in thread one
I am in thread 2

Sol 3 )
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
	 
pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;
	 
void *functionCount1();
void *functionCount2();
int  count = 0;
#define COUNT_DONE  10
main()
	{
	   pthread_t thread1, thread2;
	 
	   pthread_create( &thread1, NULL, &functionCount1, NULL);
	   pthread_create( &thread2, NULL, &functionCount2, NULL);
	 
	   pthread_join( thread1, NULL);
	   pthread_join( thread2, NULL);
	 
	   printf("Final count: %d\n",count);
	 
	   exit(0);
	}
	 
	// Write numbers 1-3 and 8-10 as permitted by functionCount2()
	 
void *functionCount1()
	{
	   for(;;)
	   {
	      // Lock mutex and then wait for signal to relase mutex
	      pthread_mutex_lock( &count_mutex );
	 
	      // Wait while functionCount2() operates on count
	      // mutex unlocked if condition varialbe in functionCount2() signaled.
	      pthread_cond_wait( &condition_var, &count_mutex );
	      count++;
  //printf("Counter value functionCount1: %d\n",count);
	 printf("I m thread 1: %d\n",count);
             pthread_mutex_unlock( &count_mutex );
	 
	      if(count >= COUNT_DONE) return(NULL);
	    }
	}
	 
	// Write numbers 4-7
	 
	void *functionCount2()
	{
	    for(;;)
	    {
	       pthread_mutex_lock( &count_mutex );
	 
	       //if( count < COUNT_HALT1 || count > COUNT_HALT2 )
               if(count %2==0)
	       {
	          // Condition of if statement has been met.
	          // Signal to free waiting thread by freeing the mutex.
	          // Note: functionCount1() is now permitted to modify "count".
	          pthread_cond_signal( &condition_var );
	       }
	       else
	       {
	          count++;
                 printf("I m thread 2: %d\n",count);
	         // printf("Counter value functionCount2: %d\n",count);
	       }
	 
	       pthread_mutex_unlock( &count_mutex );
	 
	       if(count >= COUNT_DONE) return(NULL);
	    }
	 
	}










Q 4 ) Write a thread program that sorts array of 10 alphabets in a separate thread and returns an array containing the results. In the meantime the main thread should display any appropriate short message to the user and then display the results of the computation when they are ready.

Sol 4 )
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
	 
//pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;
	 
void *functionCount1();
//void *functionCount2();
int  count = 0;
#define COUNT_DONE  10
main()
{
   pthread_t thread1, thread2;
char iarray=new char[10];
iarray[0]='b';
iarray[1]='a';
iarray[2]='j';
iarray[3]='f';
iarray[4]='g';
iarray[5]='i';
iarray[6]='m';
iarray[7]='h';
iarray[8]='u';
iarray[9]='o';
pthread_create( &thread1, NULL, &functionCount1,iarray );
	   //pthread_create( &thread2, NULL, &functionCount2, NULL);
	 
	   pthread_join( thread1, NULL);
	   //pthread_join( thread2, NULL);
	 
	   printf("Waiting for the results from thread1:");
	 
	   exit(0);
	}
	 
 
	void *functionCount1()
	{
int i,j;
	   for(i=0;i<10-1;i++)
	   {
	      // Lock mutex and then wait for signal to relase mutex
	     // pthread_mutex_lock( &count_mutex );
	 for(j=0;j<10-1-i;j++)
	      {
                if(iarray[j]>iarray[j+1])
{
temp=iarray[i];
iarray[i]=iarray[j];
iarray[j]=temp;
} 
              }
}
	      //pthread_cond_wait( &condition_var, &count_mutex );
	      //count++;
 //printf("Counter value functionCount1: %d\n",count);
//	 printf("I m thread 1: %d\n",count);
  //           pthread_mutex_unlock( &count_mutex );
	 
	//      if(count >= COUNT_DONE) return(NULL);
	    }
	}

Q 5) Write a thread program using thread attribute, set it to detached, and then create a thread using the attribute. When the child has finished its execution it will terminates without synchronising with calling thread. After detaching it, also set scheduling policy of thread.

Sol 5)
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
void *thread_function(void *arg);
char message[] = "Hello World";
int thread_finished = 0;
int main()
 {
int res;
pthread_t a_thread;
pthread_attr_t thread_attr;
res = pthread_attr_init(&thread_attr);
  if (res != 0) 
{
  perror("Attribute creation failedâ€);
  exit(EXIT_FAILURE);
}
res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
if (res != 0) 
{
  perror("Setting detached attribute failedâ€);
  exit(EXIT_FAILURE);
}
res = pthread_create(&a_thread, &thread_attr,
thread_function, (void *)message);
if (res != 0)
{
   perror("Thread creation failedâ€);
   exit(EXIT_FAILURE);
}
(void)pthread_attr_destroy(&thread_attr);
while(!thread_finished)
{
  printf("Waiting for thread to say itâ€™s finished...\nâ€);
  sleep(1);
}
printf("Other thread finished, bye!\nâ€);
exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
 printf("thread_function is running. Argument was %s\nâ€, (char *)arg);
 sleep(4);
 printf("Second thread setting finished flag, and exiting now\n);
 thread_finished = 1;
 pthread_exit(NULL);
}













Q 6) Write a C program for Deadlock detection and avoidance using Banker's Algorithm.
Sol 6)
#include<stdio.h>
#include<stdlib.h>
int main()
{
intMax[10][10], need[10][10], alloc[10][10], avail[10], completed[10], safeSequence[10];
int p, r, i, j, process, count;
count = 0;
printf("Enter the no of processes : ");
scanf("%d", &p);
for(i = 0; i< p; i++)
completed[i] = 0;
printf("\n\nEnter the no of resources : ");
scanf("%d", &r);
printf("\n\nEnter the Max Matrix for each process : ");
for(i = 0; i < p; i++)
    {
printf("\nFor process %d : ", i + 1);
for(j = 0; j < r; j++)
scanf("%d", &Max[i][j]);
    }
printf("\n\nEnter the allocation for each process : ");
for(i = 0; i < p; i++)
    {
printf("\nFor process %d : ",i + 1);
for(j = 0; j < r; j++)
scanf("%d", &alloc[i][j]);
    }
printf("\n\nEnter the Available Resources : ");
for(i = 0; i < r; i++)
scanf("%d", &avail[i]);
for(i = 0; i < p; i++)
for(j = 0; j < r; j++)
need[i][j] = Max[i][j] - alloc[i][j];
do
        {
printf("\n Max matrix:\tAllocation matrix:\n");
for(i = 0; i < p; i++)
            {
for( j = 0; j < r; j++)
printf("%d ", Max[i][j]);
printf("\t\t");
for( j = 0; j < r; j++)
printf("%d ", alloc[i][j]);
printf("\n");
        }
process = -1;
for(i = 0; i < p; i++)
            {
if(completed[i] == 0)//if not completed
                {
process = i ;
for(j = 0; j < r; j++)
                    {
if(avail[j] < need[i][j])
                        {
process = -1;
break;
                        }
                    }
                }
if(process != -1)
break;
            }

if(process != -1)
            {
printf("\nProcess %d runs to completion!", process + 1);
safeSequence[count] = process + 1;
count++;
for(j = 0; j < r; j++)
                {
avail[j] += alloc[process][j];
alloc[process][j] = 0;
Max[process][j] = 0;
completed[process] = 1;
                }
            }
}
while(count != p && process != -1);
if(count == p)
        {
printf("\nThe system is in a safe state!!\n");
printf("Safe Sequence : < ");
for( i = 0; i < p; i++)
printf("%d ", safeSequence[i]);
printf(">\n");
        }
else
printf("\nThe system is in an unsafe state!!");
}
