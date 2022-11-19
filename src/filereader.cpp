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


/* IMPORTANT THINGS TO NOTE FOR CSV FILE

order is as follows:
Subject&Number, Name, Start Time, End Time, Days of Week, Room, Building

Ex:
AAS100,Intro Asian American Studies,9:00 AM,9:50 AM,F,313,Davenport Hall

For this implementation, we only care about class a CS major would take
freshman year:
CS128, CS124, PHYS211, MATH221, RHET105, MATH231
These classes will go in desiredclasses vector and  all other classes
will go in theRest vector

Finally, the way we determine whether or not to make a node follows this
algorithm:

Is its value in classLocs -1 or something >=0

if(-1) do nothing
else make it a node and add it to desired and increment
*/

FileReader::FileReader() {
    initializeLocs();
    //initializeLocs works

    vector<string> row;
    string line;
    string col;
    fstream file ("../course-catalog.csv", ios::in);
    //repeat this loop while there are still lines left
    while(std::getline(file, line)) {
        row.clear();
        stringstream ss(line);
        //split on commas and store words in the row array
        while(std::getline(ss, col, ',')) {
            row.push_back(col);
        }
        if(row.at(0) == "SubjNum") { continue; }
        //at this point we have a whole row stored in row
        //store the number of locations in locs
        //(if it's -1 it means we don't want it)
        std::string cName = row.at(0);
        int locs = classLocs.at(cName);
        if(locs >=0) {
            //initialize node
            Node temp;
            string loc = std::string(row.at(6));
            //YES! This line removes the endline character
            loc.erase(std::remove(loc.begin(), loc.end(), '\r'), loc.end());
            loc.append(std::string(" "));
            loc.append(std::string(row.at(5)));
            temp.name = std::string(row.at(0));
            temp.location = loc;

            size_t DCsize = desiredClasses.size();
            //check if this name and location has not already been added
            // if(DCsize == 0) {
                desiredClasses.push_back(temp);
                classLocs[temp.name]++;
            // }
            // else if(DCsize > 0 && desiredClasses.at(DCsize-1).name != temp.name 
            //         && desiredClasses.at(DCsize-1).location != temp.location) {
            //     //if it hasn't, add it to desiredClasses and increment classLocs
            //     desiredClasses.push_back(temp);
            //     classLocs[temp.name]++;
            // }
        }

    }
}

void FileReader::initializeLocs() {
    string line;
    fstream file("../subjects.csv", ios::in);
    //repeat this loop while there are still lines left
    while(getline(file, line)) {
        //line now contains something like CS110 or something
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        if(std::find(targets.begin(), targets.end(), line) != targets.end()) {
            classLocs.insert({line, 0});
        }
        else {
            classLocs.insert({line, -1});
        }
    }
}

vector<Node> & FileReader::getClasses() {
    return desiredClasses;
}

std::map<std::string, int> & FileReader::getLocations() {
    return classLocs;
}

void FileReader::initializeTargets() {
    // initialize all the elements to be in 1 set
    dset.addelements(6);
    for (unsigned i = 0; i < 5; i++) {
        dset.setunion(i, i+1);
    }
}