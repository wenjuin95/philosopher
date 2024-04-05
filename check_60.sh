#!/bin/bash

output=$(./a.out 2 200 200 200)
echo $output
if [ -z "$output" ]; then
	echo -e "\033[0;32msuccess\033[0m"
else
	echo -e "\033[0;31mfail\033[0m"
fi