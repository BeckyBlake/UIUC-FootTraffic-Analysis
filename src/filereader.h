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
        * Reads the input from cc-sorted-locations.csv and creates nodes
        * for each unique location. Within each node is stored a vector
        * of the desired classes and all other classes also held at that
        * location.
        */
        FileReader(string targets_file);

        /**
        * FileReader destructor
        * Deletes all the memory allocated in allLocations
        */
        ~FileReader();

        /**
        * Initializes the isDesired map so that we can check whether or not
        * a class is desired
        */
        void initializeHelpers(string targets_file);

        /**
        * Adds the class to its place in the location node and adds the node to
        * the desiredClasses vector if necessary
        */
        void addClass(Node * node, string cName, int des);

        /**
        * Initializes the targets dset 
        */
        void initializeTargets();
        
        //Map used to check if a class is a desired class or not
        std::map<string, int> isDesired;
        
        //vector containing pointers to Nodes representing all locations
        //in the csv file
        vector<Node*> allLocations;
        
        //vector containing pointers to only Nodes representing locations with
        //desired classes
        vector<Node*> desiredLocations;

        // disjoint set that represents all the classes in the targets vector
        DisjointSets dset;
};