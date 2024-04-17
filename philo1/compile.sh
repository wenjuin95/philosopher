#!/bin/bash

output=$(./a.out)
echo "handle ./a.out:"
if [ -z "$output" ]; then
	echo -e "\033[0;32msuccess\033[0m"
else
	echo -e "\033[0;31mfail\033[0m"
fi

output=$(./a.out 1)
echo "handle ./a.out 1:"
if [ -z "$output" ]; then
	echo -e "\033[0;32msuccess\033[0m"
else
	echo -e "\033[0;31mfail\033[0m"
fi

output=$(./a.out 1 2)
echo "handle ./a.out 1 2:"
if [ -z "$output" ]; then
	echo -e "\033[0;32msuccess\033[0m"
else
	echo -e "\033[0;31mfail\033[0m"
fi

output=$(./a.out 1 2 3)
echo "handle ./a.out 1 2 3:"
if [ -z "$output" ]; then
	echo -e "\033[0;32msuccess\033[0m"
else
	echo -e "\033[0;31mfail\033[0m"
fi

output=$(./a.out 1 2 3 4)
echo "handle ./a.out 1 2 3 4:"
if [ -z "$output" ]; then
	echo -e "\033[0;32msuccess\033[0m"
else
	echo -e "\033[0;31mfail\033[0m"
fi

output=$(./a.out 1 2 3 4 5)
echo "handle ./a.out 1 2 3 4 5:"
if [ -z "$output" ]; then
	echo -e "\033[0;32msuccess\033[0m"
else
	echo -e "\033[0;31mfail\033[0m"
fi

output=$(./a.out 1 2 3 4 5 6)
echo "handle ./a.out 1 2 3 4 5 6:"
if [ -z "$output" ]; then
	echo -e "\033[0;32msuccess\033[0m"
else
	echo -e "\033[0;31mfail\033[0m"
fi

output=$(./a.out 1 2 3 4 5 6 7)
echo "handle ./a.out 1 2 3 4 5 6 7:"
if [ -z "$output" ]; then
	echo -e "\033[0;32msuccess\033[0m"
else
	echo -e "\033[0;31mfail\033[0m"
fi

output=$(./a.out 1 2 3 4 5 6 7 8)
echo "handle ./a.out 1 2 3 4 5 6 7 8:"
if [ -z "$output" ]; then
	echo -e "\033[0;32msuccess\033[0m"
else
	echo -e "\033[0;31mfail\033[0m"
fi