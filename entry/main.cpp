
#include <iostream>
#include <vector>
#include "disjointSets.h"
#include "filereader.h"
#include "node.h"

using namespace std;


int main() {
    DisjointSets dset;

    dset.addelements(5);

    FileReader fr;

    vector<Node> desired = fr.getClasses();   

    for(Node n : fr.desiredClasses) {
        std::cout << n.name << std::endl;
        std::cout << n.location << std::endl;
    }
    
}