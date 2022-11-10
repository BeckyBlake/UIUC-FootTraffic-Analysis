#pragma once

#include "node.h"
#include <vector>
#include <string>

using namespace std;

class FileReader {
    public:
        FileReader();
        vector<Node> getClasses();
        
        std::map<std::string, int> classLocs;
        vector<Node> classNodes;
};