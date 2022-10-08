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
    std::string file = "\"" + this->searchpath + filename + "\"";
    std::cout << "filename" << file;
    for (const auto & file : std::filesystem::directory_iterator(this->getSearchpath())){
        std::cout << file << std::endl;
        if (strcmp(file, filename)){
            std::cout <<"Test";
            return 1;
        }
    }
    return 0;
}