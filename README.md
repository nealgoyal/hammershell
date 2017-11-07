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
## Requirements
Need to install the boost library to run the program. To get instructions on how to install, follow the website here: https://www.pyimagesearch.com/2015/04/27/installing-boost-and-boost-python-on-osx-with-homebrew/. Also, you need to compile using C++11. In order to compile, you can either run our makefile or use the command
```c++
  $ g++ *.cpp -std=c++11
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
- We currently cannot account for non bin items, such as commands like "cd".
- Issues with shell scripts running accordingly to each test.
- Cannot account for quotations within the commands
- Will run with a connector at the end of the program
