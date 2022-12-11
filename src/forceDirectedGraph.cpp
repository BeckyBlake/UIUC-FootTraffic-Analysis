#include "node.h"
#include "forceDirectedGraph.h"
#include "../lib/cs225/PNG.h"
#include "../lib/cs225/HSLAPixel.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cs225;


ForceDirectedGraph::ForceDirectedGraph(vector<Node*>& nodes) {
    graphNodes = nodes;
    randomizeLocations(100);
    
    forces.resize(graphNodes.size());
    calculatePositions(0, 1000);
}


void ForceDirectedGraph::randomizeLocations(int size) {
    for (unsigned i = 0; i < graphNodes.size(); i++) {
        graphNodes[i]->coordinate.first = rand()%size;
        graphNodes[i]->coordinate.second = rand()%size;
    }
}

float ForceDirectedGraph::magnitude(std::pair<float, float> p) {
    return sqrt(p.first*p.first + p.second * p.second);
}

void ForceDirectedGraph::calculatePositions(float epsilon, int maxIterations) {
    //set variable to indicate the number of iterations we have gone through
    int t = 1;
    float maxForce = epsilon + 1;
    //update positions while we are less than maxIterations and maxForce is > epsilon
    while(maxForce > epsilon && t < maxIterations) {
        //reset maxForce
        maxForce = 0;
        //iterate through each node and calculate the force for it
        for(unsigned i = 0; i < graphNodes.size(); i++) {
            //calculate the force for this node 
            pair<float, float> force;
            pair<float, float> attractive = calculateAttractiveForce(graphNodes.at(i));
            pair<float, float> repulsive = calculateRepulsiveForce(graphNodes.at(i));
            force.first = attractive.first - repulsive.first;
            force.second = attractive.second - repulsive.second;
            //get the magnitude for this force
            float mag = magnitude(force);
            //update maxForce if necessary
            if(mag > maxForce) { maxForce = mag; }
            //update force at this node's index
            forces.at(i) = force;
        }
        //move the node's position according to the force acting on it
        for(unsigned j = 0; j < forces.size(); j++) {
            nudge(graphNodes.at(j), forces.at(j));
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
    //the strength with which nodes push each other away
    int strength = 10;
    
    // Loop through all graphNodes in the graph
    pair<float, float> sumRepulsiveForces = {0, 0};
    for (unsigned i = 0; i < currNode->neighbors.size(); i++) {
        // Calculate the euclidean distance between currNode and neighbor
        float distance = sqrt(pow(currNode->coordinate.first - currNode->neighbors[i]->coordinate.first, 2) + pow(currNode->coordinate.second - currNode->neighbors[i]->coordinate.second, 2));   
        // calculate a direction vector from neighbor to currNode
        pair<float, float> direction = {currNode->coordinate.first - currNode->neighbors[i]->coordinate.first, currNode->coordinate.second - currNode->neighbors[i]->coordinate.second};
        pair<float, float> repulsiveForce = {direction.first * strength / distance, direction.second * strength / distance};
        sumRepulsiveForces = {sumRepulsiveForces.first + repulsiveForce.first, sumRepulsiveForces.second + repulsiveForce.second};
    }
    return sumRepulsiveForces;
}

void ForceDirectedGraph::nudge(Node* n, std::pair<float, float> force) {
    //update the position of the node
    n->coordinate.first += force.first;
    n->coordinate.second += force.second;

    if(int(n->coordinate.first) < minX) {
        minX = int(n->coordinate.first);
    }
    if(int(n->coordinate.first) > maxX) {
        maxX = int(n->coordinate.first);
    }
    if(int(n->coordinate.second) < minY) {
        minY = int(n->coordinate.second);
    }
    if(int(n->coordinate.second) > maxY) {
        maxY = int(n->coordinate.second);
    }
}


void ForceDirectedGraph::drawGraph(std::string graphFileName, std::string coordFileName) {
    //number to scale the coordinates by to make the graph bigger
    
    // Create and open a text file
    ofstream coordsFile(coordFileName);
    coordsFile << "Max x: " << maxX-minX << '\n';
    coordsFile << "Max y: " << maxY-minY << '\n';

    //create an image for the graph (background already white)
    PNG graph(maxX-minX, maxY-minY);
    //iterate through every node we have
    for(Node* node : graphNodes) {
        drawNode(node->coordinate, graph);
        coordsFile << node->location << "'s coords: " << node->coordinate.first - minX << ", " << node->coordinate.second - minY << '\n';
    }
    
    coordsFile.close();
    graph.writeToFile(graphFileName);
}

void ForceDirectedGraph::drawNode(std::pair<float, float> coords, PNG& graph) {
    int nodeSize = 3;
    
    int xCoord = int(coords.first) - int(minX);
    int yCoord = int(coords.second) - int(minY);
    //get the starting coordinates for x and y
    //we subtract the min values because we don't want negative coords if coords are negative
    int startingX = std::max(xCoord - nodeSize/2, 0);
    int startingY = std::max(yCoord - nodeSize/2, 0);

    HSLAPixel black(0,0,0);

    for(int x = startingX; x < startingX + nodeSize; x++) {
        for(int y = startingY; y < startingY + nodeSize; y++) {
            int tempX = x;
            int tempY = y;
            
            if(unsigned(x) >= graph.width()) { tempX = int(graph.width()) - 1; }
            if(unsigned(y) >= graph.height()) { tempY = int(graph.height()) - 1; }
            graph.getPixel(tempX, tempY) = black;
        }
    }
}