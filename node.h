#pragma once

#include <string>
#include <vector>

using namespace std;

struct Node {
    std::string name;
    std::string location;
    std::vector<Node> neighbors;
    std::vector<int> weights;
};