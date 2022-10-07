#include <iostream>
#include <unistd.h>
#include <assert.h>

//TODO: rausfinden wie das mit den extra argumenten funktioniert (optarg)


/* Entry Point */
int main(int argc, char *argv[])
{
    int c;
    //char *dateiname;
    //char *programm_name;
    unsigned short Counter_R = 0;
    unsigned short Counter_i = 0;

    //programm_name = argv[0];

    while ((c = getopt(argc, argv, "Ri:")) != EOF)
    {
        switch (c)
        {
        case '?':
            std::cerr << "Error Unknown option";
            exit(1);
            break;

        case 'R':
            Counter_R++;
            //dateiname = optarg;
            break;

        case 'v':
            Counter_i++;
            break;

        default:
            assert(0);
        }
    }
    if ((Counter_R > 1) || (Counter_i > 1))
    {
        std::cerr << "Too many arguments!";
        exit(1);
    }

    if (optind < argc)
    {
        printf("ARGV Elemente ohne Optionen: ");
        while (optind < argc)
        {
            printf("%s ", argv[optind++]);
        }
        printf("\n");
    }

    /* if ( optind >= argc ) {
        fprintf(stderr, "Fehler: Es wurden Optionen, die Argumente erwarten, ohne Argument angegeben.\n");
        exit(EXIT_FAILURE);
    } */

    std::cout << argc << " arguments were given." << std::endl;


    if (Counter_R > 0){
        std::cout << "looking for " << ; 
    }

/*int main(int argc, char *argv[]){
    
    int c;
    char* program_name = optarg;
    int counter_R = 0;
    int counter_i = 0;
    //program_name = argv[0];



    while ((c = getopt(argc, argv, "Ri:")) != EOF){
        switch (c){
        
        case '?':
            fprintf(stderr, "Error: Unknown option.\n");
            exit(1);
            break;

        case 'R':
            counter_R++;
            exit(0);
            break;

        case 'i':
            counter_i++;
            exit(0);
            break;
        }
    }*/
    
    return 0;
}