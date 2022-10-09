all: myfind
myfind: myfind.o Searchobject.o 
	g++ -g -Wall -std=c++17  -o myfind  myfind.o Searchobject.o
myfind.o: myfind.cpp Searchobject.h
	g++ -g -Wall -std=c++17  -c myfind.cpp
Searchobject.o: Searchobject.h
clean:
	rm –f myfind
