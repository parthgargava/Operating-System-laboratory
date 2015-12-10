
Q1) Write a C Program to demonstrate Race Condition in producer consumer problem using thread implementation
Sol 1)
# include <stdio.h>
# include <pthread.h>
#include<malloc.h>

int BufferSize=10;
int BufferIndex=0;
char *BUFFER;

pthread_cond_t Buffer_Not_Full = PTHREAD_COND_INITIALIZER;
pthread_cond_t Buffer_Not_Empty = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mVar = PTHREAD_MUTEX_INITIALIZER;

void *Producer()
{   int i=0; 
    for(;;)
    {
        pthread_mutex_lock(&mVar);
        if(BufferIndex==BufferSize)
        {                        
            pthread_cond_wait(&Buffer_Not_Full,&mVar);
	    sleep(3);
        }                        
        BUFFER[BufferIndex]='@';
	++BufferIndex;
	sleep(1);
        printf("Produce : %d \n",BufferIndex);
        pthread_mutex_unlock(&mVar);
        pthread_cond_signal(&Buffer_Not_Empty);  
	   ++i;
	if(i==(2*BufferSize)+2)
	break;

    }    
    
}

void *Consumer()
{ int i=0;	
    for(;;)
    {
        pthread_mutex_lock(&mVar);
        if(BufferIndex==-1)
        {            
            pthread_cond_wait(&Buffer_Not_Empty,&mVar);
	    sleep(3);
        }    
	 sleep(1);           
        printf("Consume : %d \n",BufferIndex);
	--BufferIndex;        
        pthread_mutex_unlock(&mVar);        
        pthread_cond_signal(&Buffer_Not_Full);  
	      ++i;
	if(i==(2*BufferSize)+3)
	break;     
    }    
}


int main()
{    
    pthread_t ptid,ctid;
    
    BUFFER=(char *) malloc(sizeof(char) * BufferSize);            
    
    pthread_create(&ptid,NULL,Producer,NULL);
    pthread_create(&ctid,NULL,Consumer,NULL);
    
    pthread_join(ptid,NULL);
    pthread_join(ctid,NULL);
        
    
    return 0;
}



Q 2) Write a C Program to implement producer consumer problem (Using POSIX semaphores).
Sol 2)
typedef int buffer_item;
#define BUFFER_SIZE 5

/* main.c */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define RAND_DIVISOR 100000000
#define TRUE 1

/* The mutex lock */
pthread_mutex_t mutex;

/* the semaphores */
sem_t full, empty;

/* the buffer */
buffer_item buffer[BUFFER_SIZE];

/* buffer counter */
int counter;

pthread_t tid;       //Thread ID
pthread_attr_t attr; //Set of thread attributes

void *producer(void *param); /* the producer thread */
void *consumer(void *param); /* the consumer thread */

void initializeData() {

   /* Create the mutex lock */
   pthread_mutex_init(&mutex, NULL);

   /* Create the full semaphore and initialize to 0 */
   sem_init(&full, 0, 0);

   /* Create the empty semaphore and initialize to BUFFER_SIZE */
   sem_init(&empty, 0, BUFFER_SIZE);

   /* Get the default attributes */
   pthread_attr_init(&attr);

   /* init buffer */
   counter = 0;
}

/* Producer Thread */
void *producer(void *param) {
   buffer_item item;

   while(TRUE) {
      /* sleep for a random period of time */
      int rNum = rand() / RAND_DIVISOR;
      sleep(rNum);

      /* generate a random number */
      item = rand();

      /* acquire the empty lock */
      sem_wait(&empty);
      /* acquire the mutex lock */
      pthread_mutex_lock(&mutex);

      if(insert_item(item)) {
         fprintf(stderr, " Producer report error condition\n");
      }
      else {
         printf("producer produced %d\n", item);
      }
      /* release the mutex lock */
      pthread_mutex_unlock(&mutex);
      /* signal full */
      sem_post(&full);
   }
}

/* Consumer Thread */
void *consumer(void *param) {
   buffer_item item;

   while(TRUE) {
      /* sleep for a random period of time */
      int rNum = rand() / RAND_DIVISOR;
      sleep(rNum);

      /* aquire the full lock */
      sem_wait(&full);
      /* aquire the mutex lock */
      pthread_mutex_lock(&mutex);
      if(remove_item(&item)) {
         fprintf(stderr, "Consumer report error condition\n");
      }
      else {
         printf("consumer consumed %d\n", item);
      }
      /* release the mutex lock */
      pthread_mutex_unlock(&mutex);
      /* signal empty */
      sem_post(&empty);
   }
}

/* Add an item to the buffer */
int insert_item(buffer_item item) {
   /* When the buffer is not full add the item
      and increment the counter*/
   if(counter < BUFFER_SIZE) {
      buffer[counter] = item;
      counter++;
      return 0;
   }
   else { /* Error the buffer is full */
      return -1;
   }
}

/* Remove an item from the buffer */
int remove_item(buffer_item *item) {
   /* When the buffer is not empty remove the item
      and decrement the counter */
   if(counter > 0) {
      *item = buffer[(counter-1)];
      counter--;
      return 0;
   }
   else { /* Error buffer empty */
      return -1;
   }
}

int main(int argc, char *argv[]) {
   /* Loop counter */
   int i;

   /* Verify the correct number of arguments were passed in */
   if(argc != 4) {
      fprintf(stderr, "USAGE:./main.out <INT> <INT> <INT>\n");
   }

   int mainSleepTime = atoi(argv[1]); /* Time in seconds for main to sleep */
   int numProd = atoi(argv[2]); /* Number of producer threads */
   int numCons = atoi(argv[3]); /* Number of consumer threads */

   /* Initialize the app */
   initializeData();

   /* Create the producer threads */
   for(i = 0; i < numProd; i++) {
      /* Create the thread */
      pthread_create(&tid,&attr,producer,NULL);
    }

   /* Create the consumer threads */
   for(i = 0; i < numCons; i++) {
      /* Create the thread */
      pthread_create(&tid,&attr,consumer,NULL);
   }

   /* Sleep for the specified amount of time in milliseconds */
  // sleep(mainSleepTime);
	pthread_join(tid,NULL);
   /* Exit the program */
   printf("Exit the program\n");
   exit(0);
}

Q 3) Write a C program to demonstrate Dining-Philosopher Problem and its solution using monitor.

Sol 3)
condition can_eat[NUM_PHILS];
enum states {THINKING, HUNGRY, EATING} state[NUM_PHILS-1];
int index;

for (index=0; index<NUM_PHILS; index++) {
	flags[index] = THINKING;
	}

	/* request the right to pickup chopsticks and eat */
	entry void pickup(int mynum) {

		/* announce that we're hungry */
		state[mynum] = HUNGRY;

		/* if neighbor's aren't eating, proceed */
		if ((state[mynum-1 mod NUM_PHILS] != EATING) &&
			(state [mynum+1 mod NUM_PHILS] != EATING)) {
			state[mynum] = EATING;
		}

		/* otherwise wait for them */
		else can_eat[mynum].wait;

		/* ready to eat now */
		state[mynum] = EATING;
	}

	/* announce that we're finished, give others a chance */
	entry void putdown(int mynum) {

		/* announce that we're done */
		state[mynum] = THINKING;

		/* give left (lower) neighbor a chance to eat */
		if ((state [mynum-1 mod NUM_PHILS] == HUNGRY) &&
		(state [mynum-2 mod NUM_PHILS] != EATING)) {
			can_eat[mynum-1 mod NUM_PHILS].signal;
		}

		/* give right (higher) neighbor a chance to eat */
		if ((state [mynum+1 mod NUM_PHILS] == HUNGRY) &&
		(state [mynum+2 mod NUM_PHILS] != EATING)) {
			can_eat[mynum+1 mod NUM_PHILS].signal;
		}
}

	me = get_my_id();
	while (TRUE) {

		/* think, wait, eat, do it all again ... */
		think();
		pickup(me);
		eat();
		putdown(me);

	}


Q 4) A system is defined to contain three cake processes and one agent process. Each baker continuously makes a cake and eats it. To make a cake, the baker needs three ingredients: sugar, egg and flour. One of the baker processes has egg, another has sugar and the third has flour. The agent has infinite supply of all the three materials. The agent places two of the ingredients on the table. The baker who has the remaining ingredient then makes and eats a cake, signalling the agent on completion. The agent then puts another two of the three ingredients, and the cycle repeats. Write a program to synchronize the agent and bakers.

Sol 4)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
enum Ingredients /* Enum representing the ingredients */
{
None,
sugar,
egg,
flour
};
/* Structure representing a Smoker & Agent process */
typedef struct baker
{ 
char bakerID[25];
int Item;
}BAKER;
typedef struct agent
{
char AgentID[25];
int Item1;
int Item2;
}AGENT;
char* GetIngredientName(int Item)
{
if(Item == sugar)
return "sugar";
else if(Item == egg)
return "egg";
else if(Item == flour)
return "flour";
}
void GetAgentIngredients(AGENT* agent)
{
/* Simulate random generation of ingredients*/
agent->Item1=random(3)+1;
while(1)
{
agent->Item2=random(3)+1;
if(agent->Item1 != agent->Item2)
break;
}
printf("\nAgent Provides Ingredients- %s,%s\n\n:,
GetIngredientName(agent->Item1),GetIngredientName(agent->Item2));
}
void GiveIngredientTobaker(AGENT*agent,BAKER* baker)
{
int index=0;
while(baker[index].Item !=NULL)
{
if((baker[index].Item !=agent->Item1)&&(baker[index].Item != 
agent->Item2));
{
printf("\nBaker - \%s\"-is baking his cake\n\n", baker[index].bakerID);
agent->Item1=None;
agent->Item2=None;
break;
}
index++;
}
}
void main()
{
/*Create the processes required -1 Agent, 3 bakers */
AGENT agent;
BAKER baker[4] = {{bakerWithsugar",sugar},
{"SmokerWithegg",egg},
{"SmokerWithflour",flour},{"\0",None}};
int userChoice=0;
strcpy(agent.AgentID,"Agent");
agent.Item1=None;
agent>item2=None;
while(1)
{
GetAgentIngredients(&agent);
GiveIngredientTobaker(&agent,baker);
printf("Press ESC to exit or any key to continue\n\n");
UserChoice=getch();
If(UserChoice ==27)
break;
}
}

