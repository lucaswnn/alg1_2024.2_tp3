CC = g++
CXFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wformat-security -Werror
CXDEBUG = -g
CXVER = -std=c++20
SRC = src/*.cpp
INCLUDE = include/
TP = tp3

compile:
	$(CC) $(CXFLAGS) $(CXVER) -I$(INCLUDE) $(SRC) -o $(TP)

debug:
	$(CC) $(CXFLAGS) $(CXVER) $(CXDEBUG) -I$(INCLUDE) $(SRC) -o $(TP)

all:
	compile