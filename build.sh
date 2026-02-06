#!/bin/bash

gcc src/main.c -o bin/main
if [ $? -gt 0 ]; 
then 
echo "Failed to build main program D:"
else
echo -e "\e[32mFatal Error:\e[0m Operation finished successfully"
bin/main
fi