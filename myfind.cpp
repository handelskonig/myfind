#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <vector>
#include <string.h>
#include "Searchobject.h"

//help function
void print_usage(){
    std::cout << " Usage: ./myfind [-R] [-i] searchpath filename1 [filename2] ...[filenameN]\nTo search in current directory enter ./ as searchpath\n Path has to end with /" << std::endl;
}

//TODO: einen Weg finden, dass egal is wo -R und -i gesetzt ist
//extracting data from arguments 
void extractData(Searchobject* search, int argc, char *argv[]){
    int flags = 0;  //determines if -R or -i was set

    if (search->getR() && search->getI()){
        if(strcmp(argv[1], "-Ri"))              //checks if flags were set as -Ri or as -R -i
            flags = 2;                       
        else 
            flags = 1;
    }

    else if (search->getR() || search->getI())
        flags = 1;


    search->setSearchpath(argv[flags + 1]);    //searchpath is next to flags in array
    for (int i = 2 + flags; i < argc; i++) {   //files to look for are next to searchpath
        search->addfiles(argv[i]);
    }
}


/* Entry Point */
int main(int argc, char *argv[])
{
    int c;
    Searchobject *search = new Searchobject();

    while ((c = getopt(argc, argv, "Rih")) != EOF)
    {
        switch (c)
        {
        case '?':
            std::cerr << "Error Unknown option\nUse ./myfind -h for help";
            exit(1);

        case 'h':
            print_usage();
            exit(1);

        case 'R':
            search->setR();
            break;

        case 'i':
            search->setI();
            break;

        default:
            assert(0);
        }
    }

    extractData(search, argc, argv);

    std::cout << optind << " arguments were given." << std::endl << "Path: " << search->getSearchpath()<< std::endl << "Looking for files: ";
    search->printFiles(); 
    if (!search->searchFiles(search->getFilenames()[0]))
        std::cerr << "\033[1;31mError: " << search->getFilenames()[0] << " was not found in " << search->getSearchpath() << "\033[0m" << std::endl;

    return 0;
}

