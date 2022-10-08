all: myfind
myfind: myfind.o Searchobject.o 
	g++ -g -Wall -o myfind  myfind.o Searchobject.o
myfind.o: myfind.cpp Searchobject.h
	g++ -g -Wall -c myfind.cpp
Searchobject.o: Searchobject.h
clean:
	rm –f myfind
