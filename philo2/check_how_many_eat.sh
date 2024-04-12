#!/bin/bash

# Simulate the output from a command
output=$(cat <<EOF
0 2 has taken a fork
0 2 has taken a fork
0 2 is eating
200 2 is sleeping
200 1 has taken a fork
200 1 has taken a fork
200 1 is eating
400 1 is sleeping
400 2 is thinking
400 2 has taken a fork
400 2 has taken a fork
400 2 is eating
600 2 is sleeping
600 1 is thinking
600 1 has taken a fork
600 1 has taken a fork
600 1 is eating
800 1 is sleeping
800 2 is thinking
800 2 has taken a fork
800 2 has taken a fork
800 2 is eating
1000 1 is thinking
1000 2 is sleeping
1000 1 has taken a fork
1000 1 has taken a fork
1000 1 is eating
EOF
)

#input number of philo
read -p "Enter the number of philosophers: " num_philo

# Initialize the counter
eating=0

# Count the occurrences of "is eating"
while read line; # Read the output assign to line
do 
    if [[ "$line" == *"is eating"* ]]; then # Check if the line contains "is eating"
        ((eating++)) 
    fi
done <<< "$output" # Pass the output to the while loop

# Calculate half the count
half_eating=$(($eating / num_philo))

# Output the result
echo "Total philo 'is eating': $eating"
echo "each philo of 'is eating': $half_eating"
