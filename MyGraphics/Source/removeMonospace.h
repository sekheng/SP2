#ifndef REMOVEMONOSPACE_H_
#define REMOVEMONOSPACE_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

struct removeMonospace {
    vector<float> eachCharSpace;
    void loadSpace(const char* fileLocation);
};

#endif