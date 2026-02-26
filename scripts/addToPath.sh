#!/bin/bash

SCRIPTS_DIR="$(cd "$(dirname "$0")" && pwd)"
TTE_DIR="$(cd $SCRIPTS_DIR && cd .. && pwd)"

if echo "$PATH" | grep -q "terminal_text_editor/bin"; 
then
    echo "It's already in the PATH"
else
    echo "export TTE_DIR=\"$TTE_DIR\"" >> ~/.bashrc
    echo 'export PATH="$PATH:$TTE_DIR/bin"' >> ~/.bashrc
    source ~/.bashrc
fi