
#include <iostream>
#include <vector>
#include "disjointSets.h"
#include "filereader.h"
#include "node.h"

using namespace std;


int main() {
    
    // Create disjoint set for classes
    DisjointSets dset;

    dset.addelements(5);

    FileReader fr;

    // Read the file to get the CS classes
    vector<Node> desired = fr.getClasses();   

    // Printing out the classes to check making sure we get duplicates (assuming different locations)
    for(Node n : fr.desiredClasses) {
        std::cout << n.name << std::endl;
        std::cout << n.location << std::endl;
    }

    // Store the locations of the classes into a map (value is the number of locations)
    std::map<std::string, int>& classLocs = fr.getLocations();
    
    // Helper vector for creating graph
    std::vector<std::string> relevantClasses = fr.targets;
    std::map<std::string, int> relevantClassLocs;

    // Taking the classes that don't correspond to a value of -1 to put in a separate list to create the force directed graph
    // -1 means class is NOT desired, if n >= 1, n being an integer, then that is the amount of occurences of a DESIRED class
    bool inDesired = false;
    for (auto pair: classLocs) {
        for (std::string toFind: relevantClasses) {
            if (pair.first == toFind) {
                inDesired = true;
            }
        }
        if (inDesired) {
            relevantClassLocs.insert(pair);
        }
        inDesired = false;
    }
    
    // Reprinting classes for testing purposes
    for (auto pair: relevantClassLocs) {
        std::cout << pair.first << std::endl;
        std::cout << pair.second << std::endl;
    }
    
    // Loop through each Node, while in each Node connect all relavant neighbors & set up weights O(n^2)
    for (unsigned nodeOneIndex = 0; nodeOneIndex < desired.size(); nodeOneIndex++) {
        Node nodeOne = desired[nodeOneIndex];
        for (unsigned nodeTwoIndex = nodeOneIndex + 1; nodeTwoIndex < desired.size(); nodeTwoIndex++) {
            Node nodeTwo = desired[nodeTwoIndex];
            // add nodeTwo to nodeOne's vector<Node> if they should be connected
            // add the weights according to the maps
        }
    }

    
    
}