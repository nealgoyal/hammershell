#!/bin/sh

../bin/rshell << 'EOF'

echo Testing single commands

echo hello
echo bye
git status

echo Testing multi commands

mkdir test && echo hello
echo bye && git status
touch file || echo hello

echo Testing comment commands

mkdir testfile && #echo hello; echo world; exit
#git status; mkdir file; echo hello; exit
echo a && #echo b || echo d; exit

echo Testing exit command

mkdir test && echo hello; exit
echo bye && git status; exit
touch file || echo hello; exit


EOF
