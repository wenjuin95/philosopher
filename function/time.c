#include <stdio.h>
#include <sys/time.h> // Include sys/time.h for gettimeofday()

/*
*	struct timeval :: a struct that contains two members
*	1. tv_sec is the number of seconds
*	2. tv_usec is the number of microseconds
*	&time :: the address of the struct timeval time

*/
int main() {
    struct timeval time;

    gettimeofday(&time, NULL);
    // Calculate milliseconds
	long long microseconds = time.tv_usec + time.tv_sec * 1000000;
	printf("microseconds: %llx\n", microseconds);
    long milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    printf("Milliseconds: %ld\n", milliseconds);
	long sec = milliseconds / 1000;
	printf("sec: %ld\n", sec);
	long min = sec / 60;
	printf("minutes: %ld\n", min);
	long hour = min / 60;
	printf("hours: %ld\n", hour);
	long day = hour / 24;
	printf("days: %ld\n", day);
	long year = day / 365;
	printf("years: %ld\n", year);

    return 0;
}

//show how the ft_usleep function works
// long get_time(void)
// {
// 	struct timeval time;
// 	long milisec;

// 	gettimeofday(&time, NULL);
// 	milisec = time.tv_sec * 1000 + time.tv_usec / 1000;
// 	return milisec;
// }

// int main()
// {
//     long start_time = get_time();
//     long time_diff;
//     while (1)
//     {
//         time_diff = get_time() - start_time;
//         printf("%ld - %ld = %ld\n", get_time(), start_time, time_diff);
//         usleep(200 * 999);
//         if (time_diff > 1000)
//             break;
//     }
// }
