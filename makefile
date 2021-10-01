all: clear output exec
output: main.cpp
	g++ main.cpp
exec: 
	./a.out
clear:
	rm -f *.out
