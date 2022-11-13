#include "filereader.h"
#include "node.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
 
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
    
    vector<string> row;
    string line;
    string col;
    fstream file ("course-catalog.csv", ios::in);
    //repeat this loop while there are still lines left
    while(getline(file, line)) {
        row.clear();
        stringstream ss(line);
        //split on commas and store words in the row array
        while(getline(ss, col, ",")) {
            row.push_back(col);
        }
        //at this point we have a whole row stored in row
        //store the number of locations in locs
        //(if it's -1 it means we don't want it)
        int locs = classLocs[row.at(0)];
        if(locs >=0) {
            //initialize node
            Node temp;
            temp.name = row.at(0);
            temp.location = row.at(6) + " " + row.at(5);

            size_t DCsize = desiredClasses.size();
            //check if this name and location has not already been added
            if(DCsize > 0 && desiredClasses.at(DCsize-1).name != temp.name 
                    && desiredClasses.at(DCsize-1).location != temp.location) {
                //if it hasn't, add it to desiredClasses and increment classLocs
                desiredClasses.push_back(temp);
                classLocs[temp.name]++;
            }
        }

    }
}

FileReader::initializeLocs() {
    string line;
    fstream file("subjects.csv", ios::in);
    //repeat this loop while there are still lines left
    while(getline(file, line)) {
        //line now contains something like CS110 or something
        if(std::find(targets.begin(), targets.end(), line) != targets.end()) {
            classLocs.insert({line, 0});
        }
        else {
            classLocs.insert({line, -1});
        }
    }
}


FileReader::getClasses() {
    return desiredClasses;
}