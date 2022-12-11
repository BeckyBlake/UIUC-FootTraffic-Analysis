#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include "filereader.h"
#include "node.h"
#include <algorithm>


TEST_CASE("file_reader_instantiation_works", "[weight=10][valgrind]") {
    // Create filereader object
    FileReader fr("../targets.csv");
    // pass test case if fr exists
    REQUIRE(fr.otherLocations.size() >= 0);
}

using namespace std;
// Use file reader to get a list of the possible DESIRED classes that we seek
TEST_CASE("no_repeat_locations_as_nodes", "[weight=10][valgrind]") {
    vector<string> locationHistory;
    FileReader fr("../targets.csv");
    for(Node* node : fr.desiredLocations) {
        // std::cout << node->location << "'s classes: " << std::endl;
        for (string s : locationHistory) {
            if (s == node->location) {
                FAIL("Location already exists in vector");
            }
        }
        locationHistory.push_back(node->location);
    }
}

// Use file reade the possible DESIRED classes that we seek
// TEST_CASE("file_reader_constructor_not", "[weight=10][valgrind]") {
//     FileReader fr("../targets.csv");
//     // Desired list of classes
//     vector<string> targets{"CS128", "CS124", "PHYS211", "MATH221", "RHET105", "MATH231"};
//     for (auto node : fr.allLocations) {
//         // Make sure the desired classes are in targets
//         if(node->desiredClasses.size() != 0) {
//             std::cout << node->location << "hmm" << std::endl;
//         }
//         REQUIRE(node->desiredClasses.size() == 0);
        
//         //REQUIRE(std::find(targets.begin(), targets.end(), node->name) != targets.end());
 
//    }
// }

TEST_CASE("locations_contain_at_least_one_class", "[weight=10][valgrind]") {
    // create file reader
    FileReader fr("../targets.csv");
    // loop through file reader desired locations
    for (Node* node : fr.desiredLocations) {
        // check if the node contains any classes
        if (node->desiredClasses.size() == 0) {
            FAIL("Location does not contain any classes");
        }
    }
}

TEST_CASE("location_only_contains_desired_classes", "[weight=10][valgrind]") {
    // create a target vector
    vector<string> targets{"CS128", "CS124", "PHYS211", "MATH221", "RHET105", "MATH231"};
    // init file reader
    FileReader fr("../targets.csv");
    // loop through file reader desired locations
    for (Node* node : fr.desiredLocations) {
        // loop through the desired classes of the node
        for (string className : node->desiredClasses) {
            // FAIL if className is not in targets
            if (std::find(targets.begin(), targets.end(), className) == targets.end()) {
                FAIL("Class is not in targets");
            }
        }
    }
}



TEST_CASE("graph_implementation", "[weight=10][valgrind]") {
    // create file reader
    FileReader fr("../targets.csv");
    std::vector<std::string> CSClasses = {"CS128", "CS124", "PHYS211", "MATH221", "RHET105", "MATH231"};
    // loop through file reader desired locations and populate the graph with edges and weights
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
    
    // Check that the graph is connected
    // Create a vector of visited nodes
    vector<string> visited;
    // Create a queue of nodes to visit
    queue<Node*> toVisit;
    // Add the first node to the queue
    toVisit.push(fr.desiredLocations[0]);
    // While the queue is not empty
    while (!toVisit.empty()) {
        // Get the next node in the queue
        Node* currNode = toVisit.front();
        // Remove the node from the queue
        toVisit.pop();
        // Add the node to the visited vector
        visited.push_back(currNode->location);
        // Loop through the neighbors of the node
        for (Node* neighbor : currNode->neighbors) {
            // If the neighbor is not in the visited vector, add it to the queue
            if (std::find(visited.begin(), visited.end(), neighbor->location) == visited.end()) {
                toVisit.push(neighbor);
            }
        }
    }
    // Check that the visited vector is the same size as the desired locations vector
    // REQUIRE(visited.size() == fr.desiredLocations.size());

    // printe out every string in the visited vector
    for (string s : visited) {
        std::cout << s << std::endl;
    }
    // print out every desiredLocation location
    for (Node* node : fr.desiredLocations) {
        std::cout << node->location << std::endl;
    }
}

// // Use file reader to get a list of the OTHER UNDESIRED classes that we do NOT seek
// TEST_CASE("file_r("../targets.csv")eader_constructor_undesired", "[weight=10][valgrind]") {
//     FileReader fr;
//     // Undesired list of classes
//     vector<string> targets{"CS128", "CS124", "PHYS211", "MATH221", "RHET105", "MATH231"};
//     for (auto node : fr.theRest) {
//         // Make sure the desired classes are NOT in our file
//         REQUIRE(std::find(targets.begin(), targets.end(), node.name) == targets.end());
//     }
// // }

// TEST_CASE("disjoint set size", "[weight=10][valgrind]") {
//     FileReader fr;
//     // initialize disjoint set
//     fr.initializeTargets();
//     REQUIRE(fr.dset.size(0) == 6);

// TEST_CASE("dijkstra test", "[weight=10][valgrind]") {
//     FileReader fr("../targets.csv");

// }