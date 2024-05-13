#!/bin/bash

# Simulate the output from a command
output=$(cat <<EOF

0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
1 5 has taken a fork
200 2 has taken a fork
200 5 has taken a fork
200 5 is eating
200 1 is sleeping
201 4 has taken a fork
201 2 has taken a fork
201 2 is eating
201 3 is sleeping
400 1 is thinking
400 1 has taken a fork
400 4 has taken a fork
400 4 is eating
400 5 is sleeping
401 3 is thinking
401 3 has taken a fork
401 1 has taken a fork
401 1 is eating
401 2 is sleeping
600 5 is thinking
600 5 has taken a fork
600 3 has taken a fork
600 3 is eating
600 4 is sleeping
601 2 is thinking
601 1 is sleeping
601 2 has taken a fork
601 5 has taken a fork
601 5 is eating
800 3 is sleeping
800 2 has taken a fork
800 2 is eating
800 4 is thinking
800 4 has taken a fork
801 1 is thinking
801 4 has taken a fork
801 1 has taken a fork
801 4 is eating
801 5 is sleeping
1000 3 is thinking
1000 3 has taken a fork
1000 1 has taken a fork
1000 1 is eating
1000 2 is sleeping
1001 5 is thinking
1001 4 is sleeping
1001 5 has taken a fork
1001 3 has taken a fork
1001 3 is eating
1200 1 is sleeping
1200 5 has taken a fork
1200 5 is eating
1200 2 is thinking
1200 2 has taken a fork
1201 4 is thinking
1201 4 has taken a fork
1201 3 is sleeping
1201 2 has taken a fork
1201 2 is eating
1400 1 is thinking
1400 5 is sleeping
1400 1 has taken a fork
1400 4 has taken a fork
1400 4 is eating
1401 2 is sleeping
1401 1 has taken a fork
1401 1 is eating
1401 3 is thinking
1401 3 has taken a fork
1600 5 is thinking
1600 4 is sleeping
1600 5 has taken a fork
1600 3 has taken a fork
1600 3 is eating
1601 2 is thinking
1601 2 has taken a fork
1601 1 is sleeping
1601 5 has taken a fork
1601 5 is eating
1800 4 is thinking
1800 3 is sleeping
1800 4 has taken a fork
1800 2 has taken a fork
1800 2 is eating
1801 5 is sleeping
1801 4 has taken a fork
1801 4 is eating
1801 1 is thinking
1801 1 has taken a fork
2000 2 is sleeping
2000 1 has taken a fork
2000 1 is eating
2000 3 is thinking
2000 3 has taken a fork
2001 5 is thinking
2001 5 has taken a fork
2001 4 is sleeping
2001 3 has taken a fork
2001 3 is eating
2200 1 is sleeping
2200 5 has taken a fork
2200 5 is eating
2200 2 is thinking
2200 2 has taken a fork
2201 4 is thinking
2201 4 has taken a fork
2201 3 is sleeping
2201 2 has taken a fork
2201 2 is eating
2400 1 is thinking
2400 4 has taken a fork
2400 4 is eating
2400 1 has taken a fork
2400 5 is sleeping
2401 3 is thinking
2401 3 has taken a fork
2401 2 is sleeping
2401 1 has taken a fork
2401 1 is eating
2600 4 is sleeping
2600 5 is thinking
2600 5 has taken a fork
2600 3 has taken a fork
2600 3 is eating
2601 1 is sleeping
2601 5 has taken a fork
2601 5 is eating
2601 2 is thinking
2601 2 has taken a fork
2800 4 is thinking
2800 4 has taken a fork
2800 3 is sleeping
2800 2 has taken a fork
2800 2 is eating
2801 5 is sleeping
2801 4 has taken a fork
2801 4 is eating
2801 1 is thinking
2801 1 has taken a fork
3000 2 is sleeping
3000 1 has taken a fork
3000 1 is eating
3000 3 is thinking
3000 3 has taken a fork
3001 5 is thinking
3001 5 has taken a fork
3001 4 is sleeping
3001 3 has taken a fork
3001 3 is eating
3200 1 is sleeping
3200 5 has taken a fork
3200 2 is thinking
3200 2 has taken a fork
3200 5 is eating
3201 4 is thinking
3201 4 has taken a fork
3201 3 is sleeping
3201 2 has taken a fork
3201 2 is eating
3400 5 is sleeping
3400 4 has taken a fork
3400 4 is eating

EOF
)

# Initialize the counter
eating1=0
eating2=0
eating3=0
eating4=0
eating5=0

# Loop through the output
while read line; # Read the output assign to line
do 
    if [[ "$line" == *" 1 is eating"* ]]; then # Check if the line contains " * is eating"
        ((eating1++)) 
    elif [[ "$line" == *" 2 is eating"* ]]; then
		((eating2++))
	elif [[ "$line" == *" 3 is eating"* ]]; then
		((eating3++))
	elif [[ "$line" == *" 4 is eating"* ]]; then
		((eating4++))
	elif [[ "$line" == *" 5 is eating"* ]]; then
		((eating5++))
	fi
done <<< "$output" # Pass the output to the while loop

total_eating=$(($eating1 + $eating2 + $eating3 + $eating4 + $eating5))

#total philo had eat
echo "Total philo eat: $total_eating"

#philo 1
if [ $eating1 -ne 0 ]; then # -ne: not equal
	echo "philo 1 eat: $eating1"
fi

#philo 2
if [ $eating2 -ne 0 ]; then
	echo "philo 2 eat: $eating2"
fi

#philo 3
if [ $eating3 -ne 0 ]; then
	echo "philo 3 eat: $eating3"
fi

#philo 4
if [ $eating4 -ne 0 ]; then
	echo "philo 4 eat: $eating4"
fi

#philo 5
if [ $eating5 -ne 0 ]; then
	echo "philo 5 eat: $eating5"
fi
