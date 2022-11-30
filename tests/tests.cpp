#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "filereader.h"
#include "node.h"
#include <algorithm>


using namespace std;
// Use file reader to get a list of the possible DESIRED classes that we seek
TEST_CASE("file_reader_constructor_desired", "[weight=10][valgrind]") {
    FileReader fr("../targets.csv");
    // Desired list of classes
    vector<string> targets{"CS128", "CS124", "PHYS211", "MATH221", "RHET105", "MATH231"};
    for (auto node : fr.desiredLocations) {
        // Make sure the desired classes are in targets
        REQUIRE(std::find(targets.begin(), targets.end(), node->name) != targets.end());
 
   }
}

// Use file reade the possible DESIRED classes that we seek
TEST_CASE("file_reader_constructor_not", "[weight=10][valgrind]") {
    FileReader fr("../targets.csv");
    // Desired list of classes
    vector<string> targets{"CS128", "CS124", "PHYS211", "MATH221", "RHET105", "MATH231"};
    for (auto node : fr.allLocations) {
        // Make sure the desired classes are in targets
        if(node->desiredClasses.size() != 0) {
            std::cout << node->location << "hmm" << std::endl;
        }
        REQUIRE(node->desiredClasses.size() == 0);
        
        //REQUIRE(std::find(targets.begin(), targets.end(), node->name) != targets.end());
 
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