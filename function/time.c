#include <stdio.h>
#include <unistd.h> // Include unistd.h for usleep()
#include <sys/time.h> // Include sys/time.h for gettimeofday()
#include <math.h>

#define BLUE "\033[0;34m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

/*
*	struct timeval :: a struct that contains two members
*	1. tv_sec is the number of seconds
*	2. tv_usec is the number of microseconds
*	&time :: the address of the struct timeval time

*/
// int main() {
//     struct timeval time;

//     gettimeofday(&time, NULL);
//     // Calculate milliseconds
// 	long long microseconds = time.tv_usec + time.tv_sec * 1000000;
// 	printf("microseconds: %llx\n", microseconds);
//     long milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
//     printf("Milliseconds: %ld\n", milliseconds);
// 	long sec = milliseconds / 1000;
// 	printf("sec: %ld\n", sec);
// 	long min = sec / 60;
// 	printf("minutes: %ld\n", min);
// 	long hour = min / 60;
// 	printf("hours: %ld\n", hour);
// 	long day = hour / 24;
// 	printf("days: %ld\n", day);
// 	long year = day / 365;
// 	printf("years: %ld\n", year);

//     return 0;
// }


/*******************************************************/
/*      show how the ft_usleep function works          */
/*******************************************************/

#define TIME 200 //milisec
#define SLEEP_TIME 500 //microsec if milisec is 0.5
#define INCREASE SLEEP_TIME / 1000.0
#define TIME_DIFF SLEEP_TIME / 1000.0

double get_time(void)
{
	struct timeval time;
	double milisec;

	gettimeofday(&time, NULL);
	milisec = time.tv_sec * 1000.0 + time.tv_usec / 1000.0;
	return milisec;
}

int main()
{
    double start_time = get_time();
    double time_diff;
    double increase = 0.0;
    double iteration_start_time, iteration_end_time, iteration_time_diff;
	int position = 0;

    while ((get_time() - start_time) < TIME)
    {

        iteration_start_time = get_time();
        time_diff = get_time() - start_time;
		position++;
        printf("%s%d. Expected: %.1fms%s | %sActual: %.1fms%s\n", BLUE, position, increase, RESET, YELLOW, time_diff, RESET);
        increase += INCREASE;
        usleep(SLEEP_TIME);
        iteration_end_time = get_time();
        iteration_time_diff = iteration_end_time - iteration_start_time;
		if (fabs(iteration_time_diff - TIME_DIFF) < 0.05) // Check if the absolute difference is smaller than 0.01
            printf("%stime: %.1f                time: %.1fms%s\n\n", GREEN, TIME_DIFF, iteration_time_diff, RESET);
		else
        	printf("%stime: %.1f                time: %.1fms%s\n\n", RED, TIME_DIFF, iteration_time_diff, RESET);
    }
    return 0;
}
