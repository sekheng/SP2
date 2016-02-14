/******************************************************************************/
/*!
\file       removeMonospace.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
To create a factory that can remove monospace between the words
*/
/******************************************************************************/
#ifndef REMOVEMONOSPACE_H_
#define REMOVEMONOSPACE_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

/******************************************************************************/
/*!
struct removeMonospace:
\brief
removing of monospace by storing each of the character into the vector storage
*/
/******************************************************************************/
struct removeMonospace {
    vector<float> eachCharSpace;
    void loadSpace(const char* fileLocation);
};

#endif