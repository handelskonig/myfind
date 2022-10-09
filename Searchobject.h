#include <iostream>
#include <vector>
#include <string.h>
#include <filesystem>
#include <dirent.h>

class Searchobject{
    private:
        std::string searchpath;
        std::vector<std::string> filenames;
        unsigned short Counter_R;
        unsigned short Counter_i;
    public:
        Searchobject();
        ~Searchobject();
        std::string getSearchpath();
        void setSearchpath(std::string path);
        std::vector<std::string> getFilenames();
        void addfiles(std::string file);
        unsigned short getR();
        void setR();
        void setI();
        unsigned short getI();
        void printFiles();
        int searchFiles(std::string filename);
};

