#include "node.h"
#include "../lib/cs225/PNG.h"
#include "../lib/cs225/HSLAPixel.h"
#include <vector>

using namespace std;
using namespace cs225;

class ForceDirectedGraph {
    public:
        /**
        * Constructor that will run calculatePosition and create a PNG drawing
        * based on the results
        */
        ForceDirectedGraph(vector<Node*>& nodes);
        
        /**
        * Draws the graph and stores it in a png with the given name 
        * @param fileName name you want to the PNG to have
        */
        void drawGraph(std::string fileName);

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
        void calculatePositions(float epsilon, int maxIterations);

        //calculate the attractive force between two nodes
        pair<float, float> calculateAttractiveForce(Node* currNode);

        //calculate repulsive force between two nodes
        pair<float, float> calculateRepulsiveForce(Node* currNode);

        void nudge(Node* n, std::pair<float, float> force);

        vector<pair<float, float>> forces;

        void randomizeLocations(int size);

        float magnitude(std::pair<float, float> p);

        vector<Node*> graphNodes;

        void drawNode(std::pair<float, float> coords, PNG& graph, int scale);

        //variables used for drawing the graph
        float maxX = 0;
        float maxY = 0;
        float minY = 0;
        float minX = 0;
};


