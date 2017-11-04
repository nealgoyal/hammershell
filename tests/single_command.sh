#!/bin/sh

../bin/rshell << 'EOF'

echo Testing single commands

echo hello
echo bye
git status


EOF
