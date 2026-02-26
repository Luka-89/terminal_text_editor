#!/bin/bash

SCRIPTS_DIR="$(cd "$(dirname "$0")" && pwd)"
TTE_DIR="$(cd $SCRIPTS_DIR && cd .. && pwd)"

mkdir -p "$TTE_DIR/bin"
gcc "$TTE_DIR/src/main.c" -o "$TTE_DIR/bin/main"
if [ $? -gt 0 ]; 
then 
echo "Failed to build main program D:"
exit 1
else
echo -e "\e[32mMain built successfully\e[0m"
fi