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
    std::string searchpath;
    std::vector<std::string> filenames;
    unsigned short Counter_R = 0;
    unsigned short Counter_i = 0;

    while ((c = getopt(argc, argv, "Ri")) != EOF)
    {
        switch (c)
        {
        case '?':
            std::cerr << "Error Unknown option";
            exit(1);
            break;

        case 'R':
            Counter_R++;
            break;

        case 'i':
            Counter_i++;
            break;

        default:
            assert(0);
        }
    }
    if ((Counter_R < 1) || (Counter_i < 1))
    {
        searchpath = argv[1];
        for(int i = 2; i < argc; i++)
            filenames.push_back(argv[i]);
    }

    /* if ( optind >= argc ) {
        fprintf(stderr, "Fehler: Es wurden Optionen, die Argumente erwarten, ohne Argument angegeben.\n");
        exit(EXIT_FAILURE);
    } */

    std::cout << argc << " arguments were given." << std::endl << "Path: " << searchpath << std::endl << "Looking for files: ";
    for (auto &file : filenames)
        std::cout << file << " ";    

    return 0;
}

