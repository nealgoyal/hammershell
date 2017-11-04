#!/bin/sh

../bin/rshell << 'EOF'

echo Testing multi commands

mkdir test && echo hello
echo bye && git status
touch file || echo hello

EOF
