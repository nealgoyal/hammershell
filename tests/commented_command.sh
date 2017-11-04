#!/bin/sh

../bin/rshell << 'EOF'

echo Testing comment commands

mkdir testfile && #echo hello; echo world; exit
#git status; mkdir file; echo hello; exit
echo a && #echo b || echo d; exit


EOF
