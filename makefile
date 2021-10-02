all: clear output exec
output: main.cpp toosh.cpp
	g++ main.cpp toosh.cpp
exec: 
	./a.out
clear:
	rm -f *.out
