
#include <iostream>
#include "disjointSets.h"
#include "filereader.h"
#include "Node.h"
#include <map>
#include <vector>


int main() {
    DisjointSets dset;

    dset.addelements(5);


    // Call upon file reader to return a vector<Node> that contains all Nodes (may change for other classes)
    std::vector<Node> & classes = getClasses();
    std::map<std::string, int> & mapClassesToLocation = getLocations();

    // Connect each node to every other node, the edge will be amount locations * amount locations of the two nodes
    for (int i = 0; i < classes.size(); i++) {
        for (int j = i + 1; j++) {
            Node& classeOne = classes[i];
            Node& classTwo = classes[j];
            
        }
    }


}