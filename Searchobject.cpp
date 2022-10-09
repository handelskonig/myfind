#include "Searchobject.h"


Searchobject::Searchobject(){
    Counter_R = 0;
    Counter_i = 0;
}

std::string Searchobject::getSearchpath(){
    return this->searchpath;
}

void Searchobject::setSearchpath(std::string path){
    this->searchpath = path;
}

void Searchobject::addfiles(std::string file){
    this->filenames.push_back(file);
}

std::vector<std::string> Searchobject::getFilenames(){
    return this->filenames;
}

unsigned short Searchobject::getR(){
    return this->Counter_R;
}
void Searchobject::setR(){
    if(this->Counter_R > 0){
        std::cout << "Error: -R can only be given once"; 
        exit(1);
    }
    else 
        Counter_R++;
}

void Searchobject::setI(){
    if(this->Counter_i > 0){
        std::cout << "Error: -i can only be given once"; 
        exit(1);
    }
    else
        Counter_i++;
}

unsigned short Searchobject::getI(){
    return this->Counter_i;
}
void Searchobject::printFiles(){
    for (auto &file : this->filenames)
        std::cout << file << " "; 
    std::cout << std::endl;
}

//TODO: einen weg finden die files mit dem suchparameter zu vergleichen
int Searchobject::searchFiles(std::string filename){
    if (this->searchpath == "./")                               // if ./ was given as path, use current path
        this->searchpath = std::filesystem::current_path(); 

    if (this->searchpath.back() != '/')
        this->searchpath = this->searchpath + "/";

    std::string file_w_path = this->searchpath + filename;

    std::cout << "filename " << file_w_path << std::endl;
    for (const auto & file : std::filesystem::directory_iterator(this->getSearchpath())){
        std::cout << std::filesystem::absolute(file.path()) << std::endl;;
        if (file_w_path == file.path().string()){
            std::cout << "\033[1;92mSuccess file was found under" << std::filesystem::absolute(file.path()) << "\033[0m" << std::endl;
            return 1;
        }
    }

    return 0;
}