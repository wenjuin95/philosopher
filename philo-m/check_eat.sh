#!/bin/bash

# Simulate the output from a command
output=$(cat ./philo.txt)

# Initialize the counter
eating1=0
eating2=0
eating3=0
eating4=0
eating5=0

# Loop through the output
while read line; # Read the output assign to line
do 
    if [[ "$line" == *"1 [0;32mis eating[0m"* ]]; then # Check if the line contains " * is eating"
        ((eating1++)) 
    elif [[ "$line" == *"2 [0;32mis eating[0m"* ]]; then
		((eating2++))
	elif [[ "$line" == *"3 [0;32mis eating[0m"* ]]; then
		((eating3++))
	elif [[ "$line" == *"4 [0;32mis eating[0m"* ]]; then
		((eating4++))
	elif [[ "$line" == *"5 [0;32mis eating[0m"* ]]; then
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
