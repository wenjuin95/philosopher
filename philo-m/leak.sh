#!/bin/bash

# Check if the number of arguments is 5 or 6
echo -e "argument is it 4 or 5 ?:"
if [[ $# -eq 5 || $# -eq 6 ]]; then
	echo -e "\033[0;32myes\033[0m"
else
	echo -e "\033[0;31mno\033[0m"
fi

# Check if memory leak is Mac or Linux
if [[ $# -eq 5 || $# -eq 6 ]]; then
	echo -e "Any memory leak?:"
	if [ "$(uname)" = "Darwin" ]; then
		leaks -atExit -- "$@" > /dev/null 2>&1
		if [ $? -eq 0 ]; then
			echo -e "\033[0;32mno leak\033[0m"
		else
			leaks -atExit -- "$@"
		fi
	elif [ "$(uname)" = "Linux" ]; then
		# 2>&1 is used to redirect stderr to stdout so that we can grep on it
		if valgrind "$@" 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible"; then
			echo -e "\033[0;32mno leak\033[0m"
		else
			valgrind "$@"
		fi
	fi
fi