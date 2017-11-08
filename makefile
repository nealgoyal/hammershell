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
