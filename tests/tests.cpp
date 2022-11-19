#include <catch2/catch_test_macros.hpp>

// #include "avltree.h"

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
    FileReader fr;
    // Desired list of classes
    vector<string> targets{"CS128", "CS124", "PHYS211", "MATH221", "RHET105", "MATH231"};
    for (auto node : fr.desiredClasses) {
        // Make sure the desired classes are in targets
        REQUIRE(std::find(targets.begin(), targets.end(), node.name) != targets.end());
    }
}

// Use file reader to get a list of the OTHER UNDESIRED classes that we do NOT seek
TEST_CASE("file_reader_constructor_undesired", "[weight=10][valgrind]") {
    FileReader fr;
    // Undesired list of classes
    vector<string> targets{"CS128", "CS124", "PHYS211", "MATH221", "RHET105", "MATH231"};
    for (auto node : fr.theRest) {
        // Make sure the desired classes are NOT in our file
        REQUIRE(std::find(targets.begin(), targets.end(), node.name) == targets.end());
    }
}

TEST_CASE("disjoint set size", "[weight=10][valgrind]") {
    FileReader fr;
    // initialize disjoint set
    fr.initializeTargets();
    REQUIRE(fr.dset.size(0) == 6);
}

// TEST_CASE("test_find", "[weight=10][valgrind]") {
// 	AVLTree<string, string> tree;
//     tree.insert("C", "C++");
//     tree.insert("free", "delete");
//     tree.insert("malloc", "new");
//     tree.insert("bool", "void");
//     tree.insert("Nico", "nii");
//     REQUIRE(tree.find("C").compare("C++") == 0);
//     REQUIRE(tree.find("free").compare("delete") == 0);
//     REQUIRE(tree.find("malloc").compare("new") == 0);
//     REQUIRE(tree.find("bool").compare("void") == 0);
//     REQUIRE(tree.find("Nico").compare("nii") == 0);
// }

// TEST_CASE("test_insert_small", "[weight=5]") {
//     AVLTree<int, int> tree;
//     tree.insert(1,2);
//     tree.insert(4,5);
//     tree.insert(5,4);

//     vector<int> solnTraversal = {4, 1, 5};
//     vector<string> solnFuncCalls = {"rotateLeft"};

//     verifyTree(tree, solnTraversal, solnFuncCalls);
// }

