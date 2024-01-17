#ifndef DOWNLOADMANAGER_UTILITY_H
#define DOWNLOADMANAGER_UTILITY_H

#include <string>
#include <fstream>
#include <streambuf>


//a support function to open a file and read the contents into a string buffer
std::string FromFileIntoStringBuffer(const char* const filename){
    std::ifstream file(filename);   //open file

    file.seekg(0, std::ios::end);   //go to the end of file
    size_t size = file.tellg();     //return the size from start to end of file
    std::string buffer(size, ' ');  //allocate a buffer upfront
    file.seekg(0);                  //return to the start of the file

    file.read(buffer.data(), size); //read contents of a file into the string buffer

    return buffer;
}



#endif //DOWNLOADMANAGER_UTILITY_H
