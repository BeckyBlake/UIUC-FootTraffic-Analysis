#pragma once
#include <vector>

using namespace std;

class DisjointSets {
    public:
        // Add elements
        void addelements(int num);

        // Find
        int find(int elem);

        // Setunion (union-by-size)
        void setunion(int a, int b);

        // Size
        int size(int elem);

    private:
        vector<int> vect;


};