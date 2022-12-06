#include "node.h"
#include <vector>

using namespace std;

class ForceDirectedGraph {
    public:
        /**
        * Constructor that will run calculatePosition and create a PNG drawing
        * based on the results
        */
        ForceDirectedGraph(vector<Node*>& nodes);
        

    private:    
        /**
        * Takes a list of nodes, each with a random starting position, and calculates
        * their new position based on the forces they have between themselves and other
        * nodes. 
        * @param nodes a list of all nodes we want to calculate positions for
        * @param epsilon the threshold that max force for any node must be less than
        * for the function to terminate before maxIterations are reached
        * @param maxIterations the max iterations we will go through before saying good enough
        * @return nothing, the new positions will be stored within the nodes themselves
        */
        void calculatePositions(vector<Node*> nodes, float epsilon, int maxIterations);

        //calculate the attractive force between two nodes
        pair<float, float> calculateAttractiveForce(Node* currNode);

        //calculate repulsive force between two nodes
        pair<float, float> calculateRepulsiveForce(Node* currNode);

        void nudge(Node* n, std::pair<float, float> force);

        vector<pair<float, float>> forces;

        void randomizeLocations(vector<Node*>& nodes);

        float magnitude(std::pair<float, float> p);
};


