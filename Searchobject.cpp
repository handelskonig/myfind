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

bool Searchobject::iterateDirectory(std::string file_w_path, std::filesystem::path searchpath, std::string filename){


    for (const auto & file : std::filesystem::directory_iterator(searchpath)){  //iterating over files

        std::string temp = file.path().string();  //temp variable turning filepath to string for convinience

        if(this->getR()){
            if(std::filesystem::is_directory(file.path())){  //check to see if file is a directory
                this->searchpath = file.path();    //searchpath is being changed to subdirectory path
                std::cout << "Looking in: " << file.path() << std::endl;    
                if(searchFiles(filename))     // the searchfiles funct is called again to create new file_with path and do search again in subdirectory
                    return true;
            }
        }

        if(getI()){                  // if -i flag is set turn the whole path to lowercase letters
            std::for_each(temp.begin(), temp.end(), [](char & c) {
                c = ::tolower(c);
            });
        }

        if (file_w_path == temp){   // comparing file to look for with every file in directory, returning 1 if successful
            std::cout << "\033[1;92mSuccess file was found under" << std::filesystem::absolute(file.path()) << "\033[0m" << std::endl;
            return true;
        }
    }
    return false;
}

bool Searchobject::searchFiles(std::string filename){


    //#####TODO: relativer Pfad muss auch gehen######
    if (this->searchpath == "./")                               // if ./ was given as path, use current path
        this->searchpath = std::filesystem::current_path(); 

    if (this->searchpath.back() != '/')                  //if searchpath was given without / at the end add /
        this->searchpath = this->searchpath + "/";

    std::string file_w_path = this->searchpath + filename; //adding searchpath to filename 
    
    //###TODO: pfad muss auch case insensitive angegeben werden können####
    if(this->getI()){  //if -i flag is set turn the file with whole path string to all lowercase
        std::for_each(file_w_path.begin(), file_w_path.end(), [](char & c) {
            c = ::tolower(c);
        });
    }    

    std::filesystem::path searchpath(this->searchpath); //creating a searchpath object
    if(iterateDirectory(file_w_path, searchpath, filename))       //iterating current directory using filename and searchpath
        return true;
    else
        return false;
}

