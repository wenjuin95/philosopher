#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m" 

/*	with thread you have data race but the time is faster
*	deposit                  withdraw
*	| bank_balance = 1000	 |
*	|                        | bank_balance = 1000
*	| bank_balance = +100	 |
*	|                        | bank_balance = -200
*	| bank_balance = 1100	 |
*	|						 | bank_balance = 800
*	result: 800 / 1100
*/
int bank_balance = 1000;

void write_b(int new_amount) 
{
	usleep(100000);
	bank_balance = new_amount;
}

int read_b()
{
	usleep(100000);
	return bank_balance;
}

void *deposit(void)
{
	int nb = 100;
	int amount = read_b();
	printf("%sbefore deposit: %d%s\n", BLUE, amount, RESET);
	printf("%sdeposit: %d%s\n", BLUE, nb, RESET);
	amount += nb;
	write_b(amount);
	printf("%safter deposit: %d%s\n", BLUE, amount, RESET);
	return NULL;
}

void *withdraw(void)
{
	int nb = 200;
	int amount = read_b();
	printf("%sbefore withdraw: %d%s\n", GREEN, amount, RESET);
	printf("%swithdraw: %d%s\n", GREEN, nb, RESET);
	amount -= nb;
	write_b(amount);
	printf("%safter withdraw: %d%s\n", GREEN, amount, RESET);
	return NULL;
}

int main()
{
	// pthread_t t1, t2;
	// pthread_create(&t1, NULL, (void *)deposit, NULL);
	// pthread_create(&t2, NULL, (void *)withdraw, NULL);
	// pthread_join(t1, NULL);
	// pthread_join(t2, NULL);

	//without thread you won't see data race but the time is slower
	deposit();
	withdraw();
	printf("latest bank balance: %d\n", bank_balance);
	return 0;
}
