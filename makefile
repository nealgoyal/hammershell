COMPILE = g++
FLAGS = -Wall -Werror --ansi -pedantic -std=c++11
EXEC = bin/rshell
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(shell mkdir -p bin)

$(EXEC): $(OBJECTS)
	$(COMPILE) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(COMPILE) -c $(FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)
	#
	# CC = g++
	# CC_FLAGS = -Wall -ansi
	# EXEC = test.out
	# SOURCES = $(wildcard *.cpp)
	# OBJECTS = $(SOURCES:.cpp=.o)
	#
	# $(EXEC): $(OBJECTS)
	# 	$(CC) $(OBJECTS) -o $(EXEC)
	#
	# %.o: %.cpp
	# 	$(CC) -c $(CC_FLAGS) $< -o $@
	#
	# clean:
	# 	rm -f $(EXEC) $(OBJECTS)
