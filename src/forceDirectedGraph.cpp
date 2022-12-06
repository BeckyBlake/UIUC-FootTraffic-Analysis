#include "node.h"
#include "forceDirectedGraph.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;


ForceDirectedGraph::ForceDirectedGraph(vector<Node*>& nodes) {
    randomizeLocations(nodes);
    
    forces.resize(nodes.size());
    calculatePositions(nodes, 0, 1000);
}

void ForceDirectedGraph::randomizeLocations(vector<Node*>& nodes) {
    for (unsigned i = 0; i < nodes.size(); i++) {
        nodes[i]->coordinate.first = i;
        nodes[i]->coordinate.second = i;
    }
}

float ForceDirectedGraph::magnitude(std::pair<float, float> p) {
    return sqrt(p.first*p.first + p.second * p.second);
}

void ForceDirectedGraph::calculatePositions(vector<Node*> nodes, float epsilon, int maxIterations) {
    //set variable to indicate the number of iterations we have gone through
    int t = 1;
    float maxForce = epsilon + 1;
    //update positions while we are less than maxIterations and maxForce is > epsilon
    while(maxForce > epsilon && t < maxIterations) {
        //reset maxForce
        maxForce = 0;
        //iterate through each node and calculate the force for it
        for(unsigned i = 0; i < nodes.size(); i++) {
            //calculate the force for this node 
            pair<float, float> force;
            force.first = calculateAttractiveForce(nodes.at(i)).first - calculateRepulsiveForce(nodes.at(i)).first;
            force.second = calculateAttractiveForce(nodes.at(i)).second - calculateRepulsiveForce(nodes.at(i)).second;
            //get the magnitude for this force
            float mag = magnitude(force);
            //update maxForce if necessary
            if(mag > maxForce) { maxForce = mag; }
            //update force at this node's index
            forces.at(i) = force;
        }
        //move the node's position according to the force acting on it
        for(unsigned j = 0; j < forces.size(); j++) {
            nudge(nodes.at(j), forces.at(j));
        }

        t++;
    }
}
    

pair<float, float> ForceDirectedGraph::calculateAttractiveForce(Node* currNode) {
    // Loop through all neighbors of currNode
    pair<float, float> sumAttractiveForces = {0, 0};
    for (unsigned i = 0; i < currNode->neighbors.size() ; i++) {
        // Calculate the euclidean distance between currNode and neighbor
        float distance = sqrt(pow(currNode->coordinate.first - currNode->neighbors[i]->coordinate.first, 2) + pow(currNode->coordinate.second - currNode->neighbors[i]->coordinate.second, 2));   
        // calculate a direction vector from neighbor to currNode
        pair<float, float> direction = {currNode->coordinate.first - currNode->neighbors[i]->coordinate.first, currNode->coordinate.second - currNode->neighbors[i]->coordinate.second};
        pair<float, float> attractiveForce = {direction.first * currNode->weights[i] / distance, direction.second * currNode->weights[i] / distance};
        sumAttractiveForces = {sumAttractiveForces.first + attractiveForce.first, sumAttractiveForces.second + attractiveForce.second};
    }
    return sumAttractiveForces;
}

pair<float, float> ForceDirectedGraph::calculateRepulsiveForce(Node* currNode) {
    // Loop through all nodes in the graph
    pair<float, float> sumRepulsiveForces = {0, 0};
    for (unsigned i = 0; i < currNode->neighbors.size(); i++) {
        // Calculate the euclidean distance between currNode and neighbor
        float distance = sqrt(pow(currNode->coordinate.first - currNode->neighbors[i]->coordinate.first, 2) + pow(currNode->coordinate.second - currNode->neighbors[i]->coordinate.second, 2));   
        // calculate a direction vector from neighbor to currNode
        pair<float, float> direction = {currNode->coordinate.first - currNode->neighbors[i]->coordinate.first, currNode->coordinate.second - currNode->neighbors[i]->coordinate.second};
        pair<float, float> repulsiveForce = {direction.first * 1 / distance, direction.second * 1 / distance};
        sumRepulsiveForces = {sumRepulsiveForces.first + repulsiveForce.first, sumRepulsiveForces.second + repulsiveForce.second};
    }
    return sumRepulsiveForces;
}

void ForceDirectedGraph::nudge(Node* n, std::pair<float, float> force) {
    //update the position of the node
    n->coordinate.first += force.first;
    n->coordinate.second += force.second;
}
