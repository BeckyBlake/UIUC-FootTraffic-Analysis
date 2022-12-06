
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "disjointSets.h"
#include "filereader.h"
#include "forceDirectedGraph.h"
#include "node.h"

using namespace std;


std::vector<Node*> dijkstra(int starting_index, FileReader& fr) {
    //Dijkstra's algorithm
    // distance vector
    std::vector<int> distances(fr.desiredLocations.size());
    // predecessor vector
    std::vector<Node*> predecessors(fr.desiredLocations.size());

    // initialize all distances from starting to infinity and all predecessors to null
    for (unsigned i = 0; i < fr.desiredLocations.size(); i++) {
        //big
        distances[i] = 100000;
        predecessors[i] = NULL;
    }

    // the distance from the start to the start is 0 
    distances[starting_index] = 0;

    std::vector<Node*> heap = fr.desiredLocations;
    //used to keep track of nodes that are done
    std::vector<Node*> discovered;
    for (unsigned i = 0; i < heap.size(); i++) {
        // find cheapest neighbor of current node
        Node* current = heap[i];
        //initialize min to contain the first weight
        // std::cout << "current->weight size " << current->weights.size() << std::endl;
        int min = current->weights[0];
        int min_idx = 0;
        for (unsigned j = 0; j < current->weights.size(); j++) {
            if (current->weights[j] < min && current->weights[j] != 0) {
                min = current->weights[j];
                min_idx = j;
            }
        }
        //initialize closest neighbor
        Node* smallest_neighbor = current->neighbors[min_idx];
        discovered.push_back(smallest_neighbor);

        for (unsigned j = 0; j < current->neighbors.size(); j++) {
            // if it is already discovered, continue
            if (std::find(discovered.begin(), discovered.end(), current->neighbors[j]) != discovered.end()) { 
                continue;
            }
            // std::cout << "made it here" << std::endl;
            if (current->weights[j] + distances[i] < distances[j]) {
                // std::cout << "made it here" << std::endl;
                distances[j] = current->weights[j] + distances[i];
                predecessors[j] = current;
            }
        }
    }
    return predecessors;
    // return std::vector<Node*>();
}

// Result of Dijksra's ----> you have a vector predecessors. The starting node is whatever is in desiredLocations[starting_index] and say you want to find the 
// shortest path to the node at desiredLocations[3] from desiredLocations[starting_index], predecessors[3] will tell you predecessor, so you look at the
// predecessor of that and keep following the predecessors until you arrive at the starting node, that is your shortest path


int main() {
    
    // Create disjoint set for classes
    DisjointSets dset;

    dset.addelements(5);

    FileReader fr("../test_classes.csv");

    // Read the file to get the CS classes
    // Vector<Node> desired = fr.getClasses();   

    // Printing out the classes to check making sure we get duplicates (assuming different locations)
    for(Node* n : fr.desiredLocations) {
        std::cout << n->location << "'s classes: " << std::endl;
        for(string s : n->desiredClasses) {
            std::cout << s << " ";
        }
        std::cout << '\n';
    }

    std::cout << "Size of locations " << fr.allLocations.size() << std::endl;
    std::cout << "Size of desired " << fr.desiredLocations.size() << std::endl;

    // Create a vector of classes that is contained in the desired csv file
    std::vector<std::string> CSClasses = fr.dclasses;

    for (unsigned int i = 0; i < fr.desiredLocations.size(); i++) {
        for (unsigned int j = i + 1; j < fr.desiredLocations.size(); j++) {
            // count the number of classes for each location that are in the CSclasses vector
            int nodeOneClassCount = 0;
            int nodeTwoClassCount = 0;
            int sameClassCount = 0;
            Node* nodeOne = fr.desiredLocations[i];
            Node* nodeTwo = fr.desiredLocations[j];
            
            // Count number of classes in our first location
            for (std::string className : nodeOne->desiredClasses) {
                if (std::find(CSClasses.begin(), CSClasses.end(), className) != CSClasses.end()) {
                    nodeOneClassCount++;
                }
            }
            
            // Count number of classes in our second location
            for (std::string className : nodeTwo->desiredClasses) {
                if (std::find(CSClasses.begin(), CSClasses.end(), className) != CSClasses.end()) {
                    nodeTwoClassCount++;
                }
            }
            // Count the number of same classes into sameClassCount 
            for (std::string className : nodeOne->desiredClasses) {
                if (std::find(nodeTwo->desiredClasses.begin(), nodeTwo->desiredClasses.end(), className) != nodeTwo->desiredClasses.end()) {
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


    // // Print out the neighbors and weights for each node
    // for (Node* node : fr.desiredLocations) {
    //     std::cout << node->location << "'s neighbors: " << std::endl;
    //     for (Node* neighbor : node->neighbors) {
    //         std::cout << neighbor->location << " | ";
    //     }
    //     std::cout << std::endl;
    //     for (int weight : node->weights) {
    //         std::cout << weight << " ";
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << "starting index is 0 which is location " << fr.desiredLocations[0]->location << std::endl;
    std::cout << "let's say end target is 3 which is location " << fr.desiredLocations[3]->location << std::endl;
    std::vector<Node*> path = dijkstra(0, fr);

    
    std::cout << path.size() << std::endl;
    std::cout << path[1] << std::endl;
    for (unsigned i = 1; i < path.size(); i++) {
        // std::cout << path[i]
        std::cout << fr.desiredLocations[i]->location << "'s predecessor is " << path[i]->location << std::endl;
    }
    Node* starting = fr.desiredLocations[0];
    Node* current_predecessor = path[3];
    // while (current_predecessor->location != starting->location) {
    //     std::cout << current_predecessor->location << std::endl;
    //     // find index of current predecessor
    //     unsigned i;
    //     for (i = 0; i < fr.desiredLocations.size(); i++) {
    //         if (fr.desiredLocations[i]->location == current_predecessor->location) {
    //             break;
    //         }
    //     }
    //     current_predecessor = path[i];
    // }


    //////// Force directed graph ////////
    // ForceDirectedGraph fdg = ForceDirectedGraph(fr.desiredLocations);

    return 0;
/////////////////////

    // Loop through the CSClasses vector and loop through each node in the desiredLocations vector if the class is in the node's desiredClasses vector, then 

    // // Store the locations of the classes into a map (value is the number of locations)
    // std::map<std::string, int>& classLocs = fr.getLocations();
    
    // // Helper vector for creating graph
    // std::vector<std::string> relevantClasses = fr.;
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


