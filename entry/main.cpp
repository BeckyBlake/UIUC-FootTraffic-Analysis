
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "filereader.h"
#include "forceDirectedGraph.h"
#include "node.h"
#include "heap.h"

using namespace std;

// Runs Dijkstra's algorithm to find shortest path between a selected location and all other locations
// Input: starting index is the location that we'll find shortest path to all other nodes
// Input: fr is a filereader object that contains the vector of locations
// Output: a vector of node pointers. Each index corresponds with the nodes in fr.desiredLocations and the node at that index represents that predecessor 
std::vector<Node*> dijkstra(int starting_index, FileReader& fr) {
    // distance vector
    std::vector<int> distances(fr.desiredLocations.size());
    // predecessor vector
    std::vector<Node*> predecessors(fr.desiredLocations.size());

    // initialize all distances from starting to infinity and all predecessors to null
    for (unsigned i = 0; i < fr.desiredLocations.size(); i++) {
        //big
        distances[i] = 1000000;
        predecessors[i] = NULL;
    }

    // the distance from the start to the start is 0 
    distances[starting_index] = 0;

    // declare heap
    heap pqueue;

    //used to keep track of nodes that are done
    std::vector<std::string> discovered;
    
    // place starting node into "heap"
    pqueue.push({distances[starting_index], fr.desiredLocations[starting_index]});
    

    while (!pqueue.empty()) {
        // find current node

        Node* current = pqueue.peek().second;
        pqueue.pop();
        // std::cout << "discovering " << current->location << std::endl;
        discovered.push_back(current->location);
        for (unsigned j = 0; j < current->neighbors.size(); j++) {
            // if it is already discovered, continue
            if (std::find(discovered.begin(), discovered.end(), current->neighbors[j]->location) != discovered.end()) { 

                continue;
            }
            //find index of current node in distances vector
            unsigned i;
            for (i = 0; i < fr.desiredLocations.size(); i++) {
                if (fr.desiredLocations.at(i) == current) {
                    break;
                }
            }
            unsigned neighbor_idx;
            for (neighbor_idx = 0; neighbor_idx < fr.desiredLocations.size(); neighbor_idx++) {
                if (fr.desiredLocations.at(neighbor_idx) == current->neighbors[j]) {
                    break;
                }
            }
            if (current->weights[j] + distances[i] < distances[neighbor_idx] && (current->weights[j]) != 0) {

                distances[neighbor_idx] = current->weights[j] + distances[i];
                predecessors[neighbor_idx] = current;
                
                // insert into heap
                
                std::pair<int, Node*> pair = {distances[neighbor_idx], fr.desiredLocations[neighbor_idx]};
                pqueue.push(pair);

            }
        }
    }
    return predecessors;
}

// Result of Dijksra's ----> you have a vector predecessors. The starting node is whatever is in desiredLocations[starting_index] and say you want to find the 
// shortest path to the node at desiredLocations[3] from desiredLocations[starting_index], predecessors[3] will tell you predecessor, so you look at the
// predecessor of that and keep following the predecessors until you arrive at the starting node, that is your shortest path


int main() {

    FileReader fr("../targets.csv");

    // Read the file to get the CS classes
    // Vector<Node> desired = fr.getClasses();   

    // Printing out the classes to check making sure we get duplicates (assuming different locations)
    fr.desiredLocations.pop_back();
    for(Node* n : fr.desiredLocations) {
        std::cout << n->location << "'s classes: " << std::endl;
        for(string s : n->desiredClasses) {
            std::cout << s << " ";
        }
        std::cout << '\n';
    }

    // Create a vector of classes that is contained in the desired txt file
    std::vector<std::string> CSClasses = fr.dclasses;

    //iterate through every location
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


    // Print out the neighbors and weights for each node
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

    // Path = path of least foot traffic
    std::vector<Node*> path = dijkstra(0, fr);

    
    //////// Force directed graph ////////
    ForceDirectedGraph fdg = ForceDirectedGraph(fr.desiredLocations);
    fdg.drawGraph("graph.png", "coords.txt");

    return 0;
}


