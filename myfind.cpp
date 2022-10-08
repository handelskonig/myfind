#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <vector>
#include "Searchobject.h"

//TODO: rausfinden wie das mit den extra argumenten funktioniert (optarg)


/* Entry Point */
int main(int argc, char *argv[])
{
    int c;
    Searchobject *search = new Searchobject();

    while ((c = getopt(argc, argv, "Ri")) != EOF)
    {
        switch (c)
        {
        case '?':
            std::cerr << "Error Unknown option";
            exit(1);
            break;

        case 'R':
            search->setR();
            break;

        case 'i':
            search->getI();
            break;

        default:
            assert(0);
        }
    }

    //Todo: logik für wenn -R oder oder -i eingegeben wird
    if ((search->getR() < 1) || (search->getI() < 1))
    {
        std::string test = "test";
        search->setSearchpath(argv[1]);
        for(int i = 2; i < argc; i++)
            search->addfiles(argv[i]);
    }

    /* if ( optind >= argc ) {
        fprintf(stderr, "Fehler: Es wurden Optionen, die Argumente erwarten, ohne Argument angegeben.\n");
        exit(EXIT_FAILURE);
    } */

    std::cout << argc << " arguments were given." << std::endl << "Path: " << search->getSearchpath()<< std::endl << "Looking for files: ";
    search->printFiles();

    return 0;
}

