
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
    //vector<Node> desired = fr.getClasses();   

    // Printing out the classes to check making sure we get duplicates (assuming different locations)
    for(Node* n : fr.desiredLocations) {
        std::cout << n->location << "'s classes: " << std::endl;
        for(string s : n->desiredClasses) {
            std::cout << s << " ";
        }
        std::cout << '\n';
    }

    // Create a vector of classes that a cs major takes
    std::vector<std::string> CSClasses = {"CS128", "CS124", "PHYS211", "MATH221", "RHET105", "MATH231"};

    // Loop through all the desired locations and make edges for each class they do NOT share
    for (unsigned int i = 0; i < fr.desiredLocations.size(); i++) {
        for (unsigned int j = i + 1; j < fr.desiredLocations.size(); j++) {
            // count the number of classes for each location that are in the CSclasses vector
            int nodeOneClassCount = 0;
            int nodeTwoClassCount = 0;
            int sameClassCount = 0;
            Node* nodeOne = fr.desiredLocations[i];
            Node* nodeTwo = fr.desiredLocations[j];
            
            // Count number of classes in our first location
            for (std::string className : nodeOne.desiredClasses) {
                if (std::find(CSClasses.begin(), CSClasses.end(), className) != CSClasses.end()) {
                    nodeOneClassCount++;
                }
            }
            
            // Count number of classes in our second location
            for (std::string className : nodeTwo.desiredClasses) {
                if (std::find(CSClasses.begin(), CSClasses.end(), className) != CSClasses.end()) {
                    nodeTwoClassCount++;
                }
            }
            // Count the number of same classes into sameClassCount 
            for (std::string className : nodeOne.desiredClasses) {
                if (std::find(nodeTwo.desiredClasses.begin(), nodeTwo.desiredClasses.end(), className) != nodeTwo.desiredClasses.end()) {
                    sameClassCount++;
                }
            }

            // Connect the two nodes with weight = nodeOneClassCount * nodeTwoClassCount - sameClassCount
            int weight = nodeOneClassCount * nodeTwoClassCount - sameClassCount;
            // Create a new connection and set weight
            nodeOne -> neighbors.push_back(nodeTwo);
            nodeOne -> weights.push_back(weight);
            nodeTwo -> neighbors.push_back(nodeOne);
            nodeTwo -> weights.push_back(weight);
        }
    }

    // Loop through the CSClasses vector and loop through each node in the desiredLocations vector if the class is in the node's desiredClasses vector, then 

    // // Store the locations of the classes into a map (value is the number of locations)
    // std::map<std::string, int>& classLocs = fr.getLocations();
    
    // // Helper vector for creating graph
    // std::vector<std::string> relevantClasses = fr.targets;
    // std::map<std::string, int> relevantClassLocs;

    // // Taking the classes that don't correspond to a value of -1 to put in a separate list to create the force directed graph
    // // -1 means class is NOT desired, if n >= 1, n being an integer, then that is the amount of occurences of a DESIRED class
    // bool inDesired = false;
    // for (auto pair: classLocs) {
    //     for (std::string toFind: relevantClasses) {
    //         if (pair.first == toFind) {
    //             inDesired = true;
    //         }
    //     }
    //     if (inDesired) {
    //         relevantClassLocs.insert(pair);
    //     }
    //     inDesired = false;
    // }
    
    // // Reprinting classes for testing purposes
    // for (auto pair: relevantClassLocs) {
    //     std::cout << pair.first << std::endl;
    //     std::cout << pair.second << std::endl;
    // }
    
    // // Loop through each Node, while in each Node connect all relavant neighbors & set up weights O(n^2)
    // for (unsigned nodeOneIndex = 0; nodeOneIndex < desired.size(); nodeOneIndex++) {
    //     Node nodeOne = desired[nodeOneIndex];
    //     for (unsigned nodeTwoIndex = nodeOneIndex + 1; nodeTwoIndex < desired.size(); nodeTwoIndex++) {
    //         Node nodeTwo = desired[nodeTwoIndex];
    //         // add nodeTwo to nodeOne's vector<Node> if they should be connected
    //         // add the weights according to the maps
    //     }
    // }


}