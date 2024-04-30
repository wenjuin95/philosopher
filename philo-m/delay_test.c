#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av)
{
	(void)ac;
    struct timespec start, end;
    long long totalNanos = 0;

	int sleep = atoi(av[1]);

	clock_gettime(CLOCK_MONOTONIC, &start); // Get start time
    usleep(sleep * 1000); // Convert milliseconds to microseconds
    clock_gettime(CLOCK_MONOTONIC, &end); // Get end time

    //Calculate elapsed time in nanoseconds
	/*
	* 1. end.tv_sec - start.tv_sec = total second
	* 2. total second * 1000000000 = total nanoseconds
	* 3. end.tv_nsec - start.tv_nsec = total nanoseconds
	*/
    totalNanos = (end.tv_sec - start.tv_sec) * 1000000000LL +
                 (end.tv_nsec - start.tv_nsec);


    // Convert total nanoseconds to microseconds for readability
    long long totalMicros = totalNanos / 1000;

    // Print the total usleep time in microseconds
    //printf("Total usleep time: %lld microseconds\n", totalMicros);

    // Convert total nanoseconds to milliseconds with decimal
    double totalMillis = (double)totalNanos / (1000 * 1000);

    // Print the total usleep time in milliseconds with decimal
    printf("Total usleep time: %.3f milliseconds\n", totalMillis);

	//Printf the delay in microseconds
	printf("the delay in microsecond: %lld\n", totalMicros - sleep * 1000);
    return 0;
}

// void print_info(t_table *table)
// {
// 	int i = -1;
// 	while (++i < table->num_philo)
// 	{
// 		printf("id: %d\n", table->philo[i].philo_id);
// 		if (table->philo[i].eating == 0)
// 			printf("eating: flag off\n");
// 		if (table->done_or_die == 0)
// 			printf("done_or_die: flag off\n");
// 		printf("num_meal: %d\n", table->philo[i].num_meal);
// 		printf("time_start_eat: %ld\n", table->philo[i].time_start_eat);
// 		printf("last_meal: %ld\n", table->philo[i].last_meal);
// 		printf("time_to_die: %ld\n", table->philo[i].time_to_die);
// 		printf("time_to_eat: %ld\n", table->philo[i].time_to_eat);
// 		printf("time_to_sleep: %ld\n", table->philo[i].time_to_sleep);
// 		printf("num_for_philo_eat: %d\n", table->philo[i].num_for_philo_eat);
// 		printf("num_philo: %d\n", table->philo[i].num_philo);
// 		printf("\n");
// 	}
// }

// printf("===========================\n");
// printf("\nid            : %d\n", id);
// printf("time          : %ld\n", get_time());
// printf("start_eat_time: %ld\n", philo->time_start_eat);
// printf("===========================\n");