#!/bin/bash

# Simulate the output from a command
output=$(cat <<EOF

0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 5 has taken a fork
200 4 has taken a fork
200 1 is sleeping
200 2 has taken a fork
200 5 has taken a fork
200 5 is eating
200 2 has taken a fork
200 2 is eating
200 3 is sleeping
400 2 is sleeping
400 4 has taken a fork
400 4 is eating
400 1 is thinking
400 1 has taken a fork
400 1 has taken a fork
400 1 is eating
400 5 is sleeping
400 3 is thinking
400 3 has taken a fork
600 1 is sleeping
600 4 is sleeping
600 5 is thinking
600 5 has taken a fork
600 5 has taken a fork
600 5 is eating
600 2 is thinking
600 3 has taken a fork
600 3 is eating
600 2 has taken a fork
800 1 is thinking
800 4 is thinking
800 4 has taken a fork
800 3 is sleeping
800 5 is sleeping
800 1 has taken a fork
800 2 has taken a fork
800 2 is eating
800 4 has taken a fork
800 4 is eating
1000 2 is sleeping
1000 4 is sleeping
1000 3 is thinking
1000 3 has taken a fork
1000 3 has taken a fork
1000 3 is eating
1000 1 has taken a fork
1000 5 is thinking
1000 5 has taken a fork
1000 1 is eating
1200 4 is thinking
1200 4 has taken a fork
1200 3 is sleeping
1200 5 has taken a fork
1200 5 is eating
1200 1 is sleeping
1200 2 is thinking
1200 2 has taken a fork
1200 2 has taken a fork
1200 2 is eating
1400 3 is thinking
1400 3 has taken a fork
1400 1 is thinking
1400 4 has taken a fork
1400 4 is eating
1400 1 has taken a fork
1400 1 has taken a fork
1400 1 is eating
1400 2 is sleeping
1400 5 is sleeping
1600 1 is sleeping
1600 5 is thinking
1600 5 has taken a fork
1600 5 has taken a fork
1600 5 is eating
1600 4 is sleeping
1600 2 is thinking
1600 2 has taken a fork
1600 3 has taken a fork
1600 3 is eating
1800 5 is sleeping
1800 4 is thinking
1800 1 is thinking
1800 1 has taken a fork
1800 3 is sleeping
1800 4 has taken a fork
1800 4 has taken a fork
1800 4 is eating
1800 2 has taken a fork
1800 2 is eating
2000 5 is thinking
2000 5 has taken a fork
2000 3 is thinking
2000 3 has taken a fork
2000 2 is sleeping
2000 4 is sleeping
2000 3 has taken a fork
2000 3 is eating
2000 1 has taken a fork
2000 1 is eating
2200 4 is thinking
2200 1 is sleeping
2200 3 is sleeping
2200 2 is thinking
2200 2 has taken a fork
2200 2 has taken a fork
2200 2 is eating
2200 4 has taken a fork
2200 5 has taken a fork
2200 5 is eating
2400 1 is thinking
2400 3 is thinking
2400 3 has taken a fork
2400 2 is sleeping
2400 1 has taken a fork
2400 1 has taken a fork
2400 1 is eating
2400 5 is sleeping
2400 4 has taken a fork
2400 4 is eating
2600 4 is sleeping
2600 2 is thinking
2600 1 is sleeping
2600 5 is thinking
2600 5 has taken a fork
2600 5 has taken a fork
2600 5 is eating
2600 3 has taken a fork
2600 3 is eating
2600 2 has taken a fork
2800 5 is sleeping
2800 4 is thinking
2800 1 is thinking
2800 1 has taken a fork
2800 3 is sleeping
2800 2 has taken a fork
2800 2 is eating
2800 4 has taken a fork
2800 4 has taken a fork
2800 4 is eating
3000 3 is thinking
3000 3 has taken a fork
3000 3 has taken a fork
3000 3 is eating
3000 5 is thinking
3000 5 has taken a fork
3000 4 is sleeping
3000 2 is sleeping
3000 1 has taken a fork
3000 1 is eating
3200 3 is sleeping
3200 2 is thinking
3200 1 is sleeping
3200 4 is thinking
3200 4 has taken a fork
3200 2 has taken a fork
3200 2 has taken a fork
3200 2 is eating
3200 5 has taken a fork
3200 5 is eating
3400 3 is thinking
3400 3 has taken a fork
3400 5 is sleeping
3400 1 is thinking
3400 1 has taken a fork
3400 1 has taken a fork
3400 1 is eating
3400 2 is sleeping
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
