all: myfind
myfind: myfind.cpp
	g++ -g -Wall -o myfind myfind.cpp
clean:
	rm –f myfind
