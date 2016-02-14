#include "removeMonospace.h"
#include <fstream>
#include <iostream>

/******************************************************************************/
/*!
\brief - 
loading of width of each ASCII character into a vector

\param fileLocation - path name to the file's location
*/
/******************************************************************************/
void removeMonospace::loadSpace(const char* fileLocation) {
    std::ifstream fileStream(fileLocation,  std::ios::binary);
    eachCharSpace = { 0.f };
    if (!fileStream.is_open()) {
        std::cout << "Impossible to open " << fileLocation << ". Are you in the right directory ?\n";
    }
    else {
        while (!fileStream.eof()) {
            string data = "";
            getline(fileStream, data);
            int num = std::stoi(data);
            eachCharSpace.push_back(static_cast<float>(num));
        }
        fileStream.close();
    }
}