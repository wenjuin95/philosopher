#!/bin/bash

read -p "" output

# Check for memory leaks on the process
leaks --atExit -- $output
