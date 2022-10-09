#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>


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
        bool searchFiles(std::string filename);
        bool iterateDirectory(std::string file_w_path, std::filesystem::path searchpath, std::string filename);
};

