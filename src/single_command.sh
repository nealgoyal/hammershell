#!/bin/sh

echo Testing single commands with no args

echo ls 
echo git status
echo git

echo Testing single commands with one arg

mkdir test && echo hello
echo cd && echo ls
touch file || echo hello

echo Testing single commands with two args or more

mkdir testfile && echo git; echo world
ls -a; mkdir file; echo hello
echo a && echo b || echo d
