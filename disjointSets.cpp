#include "disjointSets.h"

void DisjointSets::addelements(int num) {
    for(int i = 0; i < num; i++) {
        vect.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if(vect[elem] < 0) { return elem; }
    else { return find(vect[elem]); }
}

void DisjointSets::setunion(int a, int b) {
    int root1 = find(a);
    int root2 = find(b);
    int newSize = vect[root1] + vect[root2];

    // We have to check which one is the larger set and set the largest set
    // to newSize and the other set to the size of the larger set
    if(vect[root1] < vect[root2]) {
        vect[root2] = root1;
        vect[root1] = newSize;
    }
    else {
        vect[root1] = root2;
        vect[root2] = newSize;
    }
}

int DisjointSets::size(int elem) {
    // Uptree and union by size so we find set and multiply by negative 1
    return vect[find(elem)] * -1;
}
