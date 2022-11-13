#pragma once

#include "node.h"
#include <vector>
#include <string>

using namespace std;

class FileReader {
    public:
        /**
        * Reads the input from course-catalog.csv and stores it in two
        * vectors: desiredClasses, which we will be using further, and
        * theRest, which we will still store, but not use. It will also
        * store how many locations any class will be in in a dictionary
        * named classLocs, where the key is classname (ie MACS100) and 
        * value is how many locations it has
        * 
        */
        FileReader();

        /**
        * Returns the desiredClasses vector
        */
        vector<Node> getClasses();

        void initializeLocs();
        
        vector<string> targets{"CS128", "CS124", "PHYS211", "MATH221", "RHET105", "MATH231"};
        std::map<std::string, int> classLocs;
        vector<Node> desiredClasses;
        vector<Node> theRest;
};