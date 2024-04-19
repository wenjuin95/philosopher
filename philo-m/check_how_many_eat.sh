#!/bin/bash

# Simulate the output from a command
output=$(cat <<EOF
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating       
200 1 is sleeping     
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating       
400 2 is sleeping
400 1 is thinking     
400 1 has taken a fork
400 1 has taken a fork
400 1 is eating       
600 1 is sleeping
600 2 is thinking     
600 2 has taken a fork
600 2 has taken a fork
600 2 is eating       
800 2 is sleeping
800 1 is thinking     
800 1 has taken a fork
800 1 has taken a fork
800 1 is eating       
1000 1 is sleeping
1000 2 is thinking     
1000 2 has taken a fork
1000 2 has taken a fork
1000 2 is eating       
1200 1 is thinking
1200 2 is sleeping
1200 1 has taken a fork
1200 1 has taken a fork
1200 1 is eating       
1400 2 is thinking
1400 1 is sleeping     
1400 2 has taken a fork
1400 2 has taken a fork
1400 2 is eating       
1600 2 is sleeping
1600 1 is thinking
1600 1 has taken a fork
1600 1 has taken a fork
1600 1 is eating
1800 1 is sleeping
1800 2 is thinking
1800 2 has taken a fork
1800 2 has taken a fork
1800 2 is eating
2000 2 is sleeping
2000 1 is thinking
2000 1 has taken a fork
2000 1 has taken a fork
2000 1 is eating
2200 2 is thinking
2200 1 is sleeping
2200 2 has taken a fork
2200 2 has taken a fork
2200 2 is eating
2400 1 is thinking
2400 2 is sleeping
2400 1 has taken a fork
2400 1 has taken a fork
2400 1 is eating
2600 2 is thinking
2600 1 is sleeping
2600 2 has taken a fork
2600 2 has taken a fork
2600 2 is eating
2800 1 is thinking
2800 2 is sleeping
2800 1 has taken a fork
2800 1 has taken a fork
2800 1 is eating
3000 1 is sleeping
3000 2 is thinking
3000 2 has taken a fork
3000 2 has taken a fork
3000 2 is eating
3200 2 is sleeping
3200 1 is thinking
3200 1 has taken a fork
3200 1 has taken a fork
3200 1 is eating
3400 1 is sleeping
3400 2 is thinking
3400 2 has taken a fork
3400 2 has taken a fork
3400 2 is eating
3600 1 is thinking
3600 2 is sleeping
3600 1 has taken a fork
3600 1 has taken a fork
3600 1 is eating
3800 2 is thinking
3800 2 has taken a fork
3800 2 has taken a fork
3800 2 is eating
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
