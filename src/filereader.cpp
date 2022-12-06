#include "filereader.h"
#include "node.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
using namespace std;

//ctrl f then alt enter



/* IMPORTANT THINGS TO NOTE FOR CSV FILE

order is as follows:
Subject&Number, Name, Start Time, End Time, Days of Week, Room, Building

Ex:
AAS100,Intro Asian American Studies,9:00 AM,9:50 AM,F,313,Davenport Hall

For this implementation, we only care about class a CS major would take
freshman year:
CS128, CS124, PHYS211, MATH221, RHET105, MATH231
These classes will go in desiredClasses vector and  all other classes
will go in theRest vector

Finally, the way we determine whether or not to make a node follows this
algorithm:

Is its value in classLocs -1 or something greater than or equal to 0

if(-1) add it to theRest vector
else add it to desired and increment locations

Also, there are 114 unique locations
*/
FileReader::FileReader(string targets_file) {
    //initialize isDesired 
    initializeHelpers(targets_file);
    
    //initialize important variables
    vector<string> row;
    string line, col;
    fstream file ("../cc-sorted-locations.txt", ios::in);
    //keeps track of the location we're currently looking at
    size_t currIndex = 0;

    //repeat this loop while there are still lines left
    while(std::getline(file, line)) {
        row.clear();
        stringstream ss(line);
        //split on commas and store words in the row array
        while(std::getline(ss, col, '\t')) {
            row.push_back(col);
        }
        //we want to skip the first row
        if(row.at(0) == "SubjNum") { continue; }
        //store the name in a variable
        string locationName = row.at(row.size()-1);
        //get rid of the '\r' at the end of the line
        locationName.erase(std::remove(locationName.begin(), locationName.end(), '\r'), locationName.end());
        //store whether or not it's desired
        int des = isDesired[row.at(0)];
        //create a node pointer to store the node we want to alter
        Node* node;
        //if this if statement runs it means that we have moved onto the next location
        if(currIndex < allLocations.size() && locationName != allLocations.at(currIndex)->location) {
            // currIndex++;
            //****************************************************
            //THIS BIT OF CODE SEPARATES DESIRED AND ALL LOCATIONS
            //****************************************************
            if(allLocations.at(currIndex)->inDesVector) {
                allLocations.pop_back();
            }
            else {
                currIndex++;
            }
        }
        //we have a new location, so we have to create new node
        if(currIndex == allLocations.size()) {
            node = new Node();
            node->location = locationName;
            allLocations.push_back(node);
        }
        //get the current location
        node = allLocations.at(currIndex);

        addClass(node, row.at(0), des);
    }
    //to see if the very last location had desired classes
    if(allLocations.at(currIndex)->inDesVector) {
        allLocations.pop_back();
    }
}

FileReader::~FileReader() {
    for(Node* n : allLocations) { delete n; }
}

void FileReader::addClass(Node* node, string cName, int des) {
    //make sure the node doesn't already contain class
    if(node->containsClass[cName] == 0) {
        //set it to say it contains it now
        node->containsClass[cName] = 1;
        //if the class we are inputting is desired, add it to DC vector
        if(des == 1) {
            node->desiredClasses.push_back(cName);
        }
        //else add it to other classes
        else {
            node->otherClasses.push_back(cName);
        }
    }
    //if this node isn't in the desiredLocations vector yet, add it
    if(!node->inDesVector && des == 1) {
        desiredLocations.push_back(node);
        node->inDesVector = true;
    }
}

void FileReader::initializeHelpers(string targets_file) {
    string line;
    fstream file(targets_file, ios::in);
    //repeat this loop while there are still lines left
    while(getline(file, line)) {
        //line now contains something like CS110 or something
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        //indicate in isDesired that we want this class
        isDesired.insert({line, 1});
        dclasses.push_back(line);
    }
}

void FileReader::initializeTargets() {
    // initialize all the elements to be in 1 set
    dset.addelements(6);
    for (unsigned i = 0; i < 5; i++) {
        dset.setunion(i, i+1);
    }
}