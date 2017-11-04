#!/bin/sh

../bin/rshell << 'EOF'

echo Testing exit command

mkdir test && echo hello; exit
echo bye && git status; exit
touch file || echo hello; exit

EOF
