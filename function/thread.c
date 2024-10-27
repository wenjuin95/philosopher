#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m" 

void mult_function(void);
void sum_function(void);
void thread(void);
void thread2(void);

/*  visualize thread
*	sum                        mult
*	| int i = 1                | 
*	| int j = 2                |
*	| int sum = j+i            |
*	|                          | int a = 2
*	|                          | int b = 2
*	|                          | int mult = a*b
*	| printf("load sum...\n"); |
*	|                          | printf("load mult...\n");
*	| sleep(1);		           |
*	|                          | sleep(1);
*	| printf(sum);             |
*	|                          | printf(mult);
*/
/*=========================================================*/
int main() //thread
{
	pthread_t t1;
	pthread_t t2;

	//create thread
	//       thread id, attribute, function, argument
	pthread_create(&t1, NULL, (void *)thread, NULL); 
	pthread_create(&t2, NULL, (void *)thread2, NULL);

	//wait for thread to finish. 
	//if you don't put this, the program will end before the thread finish
	pthread_join(t1, NULL); 
	pthread_join(t2, NULL);

	return 0;
}

/*  visualize no thread
*	sum                        mult
*	| int i = 1                | 
*	| int j = 2                |
*	| int sum = j+i            |
*	| printf("load sum...\n"); |
*	| sleep(1);		           |
*	| printf(sum);             |
*	|                          | int a = 2
*	|                          | int b = 2
*	|                          | int mult = a*b
*	|                          | printf("load mult...\n");
*	|                          | sleep(1);
*	|                          | printf(mult);
*/
/*=========================================================*/
// int main() //no thread
// {
// 	sum_function();
// 	mult_function();
// 	return 0;
// }

////////////////////////////////////////////////////////////////////////

void thread(void)
{
	int i = 1;
	int j = 2;
	int sum = j+i;
	printf("%sload sum...%s\n", BLUE, RESET);
	sleep(1);
	printf("%ssum: %d%s\n", BLUE, sum, RESET);
}

void thread2(void)
{
	int a = 2;
	int b = 2;
	int mult = a*b;
	printf("%sload mult...%s\n", GREEN, RESET);
	sleep(1);
	printf("%smult: %d%s\n", GREEN, mult, RESET);
}

void sum_function(void)
{
	int i = 1;
	int j = 2;
	int sum = j+i;
	printf("%sload sum...\n%s", BLUE, RESET);
	sleep(1);
	printf("%ssum: %d%s\n", BLUE, sum, RESET);
}

void mult_function(void)
{
	int a = 2;
	int b = 2;
	int mult = a*b;
	printf("%sload mult...%s\n", GREEN, RESET);
	sleep(1);
	printf("%smult: %d%s\n", GREEN, mult, RESET);
}
