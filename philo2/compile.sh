#!/bin/bash

if [[ "$#" -eq 5 || "$#" -eq 6 ]]; then
	echo -e "\033[0;32msuccess\033[0m"
else
	echo -e "\033[0;31mfail\033[0m"
fi