#include <stdio.h>
#include <sys/time.h> // Include sys/time.h for gettimeofday()

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
