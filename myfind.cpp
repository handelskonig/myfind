#include <assert.h>
#include "Searchobject.h"
#include <sys/wait.h>
#include <string.h>

//help function
void print_usage(){
    std::cout << " Usage: ./myfind [-R] [-i] searchpath filename1 [filename2] ...[filenameN]\nTo search in current directory enter ./ as searchpath" << std::endl;
}

//TODO: einen Weg finden, dass egal is wo -R und -i gesetzt ist
//extracting data from arguments 
int extractData(Searchobject* search, int argc, char *argv[]){
    int flags = 0;  //determines if -R or -i was set

    if (search->getR() && search->getI()){
        if(strcmp(argv[1], "-Ri"))              //checks if flags were set as -Ri or as -R -i
            flags = 2;                       
        else 
            flags = 1;
    }

    else if (search->getR() || search->getI())
        flags = 1;

    if(!std::filesystem::exists(argv[flags +1])){ //Check to see if give path is valid
        std::cerr << "Error! Invalid path!";
        exit(-3);
    }

    search->setSearchpath(argv[flags + 1]);    //searchpath is next to flags in array
    for (int i = 2 + flags; i < argc; i++) {   //files to look for are next to searchpath
        search->addfiles(argv[i]);
    }

    return flags;
}

void iterateFiles(Searchobject *search, int filecounter){

    /* for every single file in the filename vector: fork -> if the fork fails exit the program, if the process is a parent process it looks for the
       give file(s) starting with the first one, if it's a child process first it checks if there's a uneven number of files to look for, if so check if
       the file is the last one to execute. e.g. 5 is uneven but it will still create a child process with uneven file idexes like 1 and 3 until it gets to
       index 5. Then child progress looks for the file next to the index where parent process is looking and breaks out of for loop so that child process
       doesn't also create more children. At the end of the forloop index is being incremented again so that parent process doesnt look in the same place
       where the child process looked before him. Another for loop at the end makes sure that the parent process waits for every single child to terminate */

    for (int i = 0; i < filecounter; i++) {
        int pid = fork();

        if(pid == -1){
            std::cerr << "Error: Splitting processes failed!";
            exit(-1);
        }

        else if(pid == 0){
            if(filecounter % 2 != 0 && i == filecounter)
                break;

            if (!search->searchFiles(search->getFilenames()[i + 1])){
                std::cerr << "\033[1;31m" << getpid() << ": " << search->getFilenames()[i] << " was not found\033[0m" << std::endl;
            }
            break;
        }

        else{
            if (!search->searchFiles(search->getFilenames()[i]))
                std::cerr << "\033[1;31m" << getpid() << ": " << search->getFilenames()[i] << " was not found\033[0m" << std::endl;
        }
        i++;
    }

    for(int i = 0; i < filecounter; i++)
        wait(NULL);
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

    int flags = extractData(search, argc, argv);
    int filecounter = 0;
    filecounter = argc - flags - 2; //getting the number of files that are being searched.
                                    //total argument counter minus -r and -i (if given) minus searchpath minus - program name
    std::cout << "Looking for " << filecounter << " file(s). " << std::endl << "Path: " << search->getSearchpath()<< std::endl << "Looking for files: ";
    search->printFiles(); 

    iterateFiles(search, filecounter);
    
    delete search;

    return 0;
}

