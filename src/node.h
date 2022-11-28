#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

struct Node {
    std::string name;
    //location name
    std::string location;
    std::vector<Node*> neighbors;
    std::vector<int> weights;
    //vector of the classes in this location that we
    //care about
    std::vector<string> desiredClasses;

    //all the other classes at this location
    std::vector<string> otherClasses;

    //a map to indicate whether or not this location
    //contains a certain class (0 is no 1 is yes)
    map<string, int> containsClass;

    bool inDesVector = false;
};