#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

int bank_balance = 1000;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void write_b(int new_amount);
int read_b();

/*
*	it lock with mutex1 first then mutex2 but withdraw lock with mutex2 first 
*	then mutex1 need wait for its unlock so it will be deadlock
*/
void deposit(void)
{
    int nb = 100;
    pthread_mutex_lock(&mutex1); //lock wiht mutex1 first
    usleep(100); // Simulate some work
    pthread_mutex_lock(&mutex2); //lock with mutex2 second

    int amount = read_b();
    printf("%sbefore deposit: %d%s\n", BLUE, amount, RESET);
    printf("%sdeposit: %d%s\n", BLUE, nb, RESET);
    amount += nb;
    write_b(amount);
    printf("%safter deposit: %d%s\n", BLUE, amount, RESET);

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
}

void withdraw(void)
{
    int nb = 200;
    pthread_mutex_lock(&mutex2); //lock with mutex2 first
    usleep(100000); // Simulate some work
    pthread_mutex_lock(&mutex1); //lock with mutex1 second

    int amount = read_b();
    printf("%sbefore withdraw: %d%s\n", GREEN, amount, RESET);
    printf("%swithdraw: %d%s\n", GREEN, nb, RESET);
    amount -= nb;
    write_b(amount);
    printf("%safter withdraw: %d%s\n", GREEN, amount, RESET);

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
}

void write_b(int new_amount) 
{
    bank_balance = new_amount;
}

int read_b()
{
    return bank_balance;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, (void *)deposit, NULL);
    pthread_create(&t2, NULL, (void *)withdraw, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}