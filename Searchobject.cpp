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
}