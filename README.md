# RShell Program
## Author: Justin Schopick and Neal Goyal

## Project Description
This program will mimic a linux or unix terminal. The program will run by allowing the user to take in a command. The program will parse each command into different vectors based on commands and connectors. Then, we use system calls to give each command functionality.
**For example:**
```c++
 $ ls -a
 $ echo hello
 $ mkdir test
```
**Is Equal To**
```c++
 $ ls -a; echo hello; mkdir test
```

## Scripts
In this lab, we used scripts to thoroughly test all the commands.
```c++
  single_command.sh        #tests single commands
  multi_command.sh         #tests commands with ;, &&, or ||
  commented_command.sh     #tests commands with comments
  exit.sh
```

## Running RShell
```c++
$ git clone  https://github.com/cs100/rshell-just-kneel.git
$ cd rshell-just-kneel
$ git checkout assn2
$ make
$ bin/rshell
```

## Known Bugs
