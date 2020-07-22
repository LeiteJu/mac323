CC = g++
FLAGS = -Wall -g -O0

main: main.cpp grafo.hpp
	${CC} ${FLAGS} $^ -o $@