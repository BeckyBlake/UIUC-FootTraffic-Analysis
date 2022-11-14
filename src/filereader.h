#pragma once

#include "node.h"
#include "disjointSets.h"
#include <vector>
#include <string>
#include <map>

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
        * Returns the desiredClasses vector which contains all nodes of the
        * classes we care about
        */
        vector<Node> & getClasses();

        /**
        * Returns a reference to the classLocs map which contains classes as
        * keys and their locations as values
        */
        std::map<std::string, int> & getLocations();

        /**
        * Initializes the classLocs map so that any class that we want is a key
        * and its value is its number of locations. Other classes will also be
        * included, but their values will be -1
        */
        void initializeLocs();


        /**
        * Initializes the targets dset 
        */
        void initializeTargets();
        
        vector<string> targets{"CS128", "CS124", "PHYS211", "MATH221", "RHET105", "MATH231"};
        std::map<std::string, int> classLocs;
        vector<Node> desiredClasses;
        vector<Node> theRest;

        // disjoint set that represents all the classes in the targets vector
        DisjointSets dset;
};