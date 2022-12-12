Final presentation link: https://mediaspace.illinois.edu/media/t/1_dpqs2p9y

## Github Organization
.devcontainer
    ->devcontainer.json (DockerFile for compiling)


cs225-project
    ->build
        ->contains all of the files need to operate make and cmake

    ->entry
        ->main.cpp (this is where all of our coding compilation takes place)

    ->lib (ignore, mainly just from copying over so we could use Dockerfile)

    ->src
        ->CmakeLists.txt
        ->filereader.cpp
        ->filereader.h (filereader class)
        ->forceDirectedGraph.cpp(force drawing class)
        ->forceDirectedGraph.h
        ->heap.cpp (heap used for dijkstra's)
        ->heap.h
        ->node.h (our node class)


    ->tests
        ->tests.cpp (main test file for test cases)

    ->course-catalog.csv (contains our dataset)

    ->README.md

    ->results.md

    ->targets.csv (classes we are considering as our target classes for schedules)

    ->test_classes.csv (another set of classes we used for further testing)

Dockerfile (just contains our Dockerfile)





## Running Instructions
# Compiling
1. Enter DOCKERFILE
2. Type "cd cs225-project" in terminal
3. Type "cd build" in terminal
4. Type "cmake .." in terminal
5. Type "./main" in terminal

## Running test cases
1. Type "make" in terminal
2. Run "./test" in terminal
    **Testing individual cases**
    Name of test cases and what it's purpose
    a) file_reader_instantiation_works : checks to make sure the file reader properly initializes
    b) no_repeat_locations_as_nodes : makes sure that if we inlcude a location, it's only once
    c) locations_contain_at_least_one_class : makes sure that if we insert a location, it actually has a class stored in it
    d) location_only_contains_desired_classes : makes sure that if we stored a class in location, it's a desired class
    e) graph_implementation : runs and tests the graph implementation and makes sure that the locations are vertices and edges are class connections

## Definition of data input and output
# File reader
1. File reader automatically uses a CSV of the classes and locations at UIUC
2. When inputting into the file reader, you have parameters of another CSV file. This CSV file contains the classes that you wan to research
3. The output is two vectors. One is called desiredLocations and one is called allLocations. desiredLocations is a vector which contains the locations of the classes we wanted in our dataset as well as which classes pertain to that location in another vector
4. The file reader output location is to the terminal

# BFS
1. While this isn't an exact function, we use it to do a graph traversal
2. You input a file reader and it is going to make connections between class locations
3. In the end, it connects all classes that you would travel to
4. The output location is the test cases where it'll say test case passed if the graph implementation was done correctly

# Dijkstra's
1. Input a integer that signifies the starting location, you also input a file reader
2. Using the file reader, it extracts the class location along with the edges between the classes
    - Starting point is chosen based on int inputted at beginning
3. From there it runs Dijkstra's like it would for any class
4. In the end it returns a vector of nodes which if you follow the nodes it shows the path from one class to another where you run into the least amount of kids
5. The output location is whereever Dijkstra's is called. So, if you call it in main, the output will be main.

# Force Graph Drawing
1. The force graph drawing takes in the desired locations made by the file reader as well as the weight between the edges
2. To visualize it, think of the force between two electrons using F = kq1q2/r (not our exact representation but helpful)
3. The bigger the weight of the edges (our force), then the closer the locations are placed next to each other
4. The output is a graph that now separates locations further away based on weights and common occurrences between classes
5. The force directed graph drawing is outputted in "cs225-project->build->graph.png".



## Team Contract
# cs225_project

## Communication
1. **Team Meetings** 
Our team plans to meet once a week to work on the project to maximize efficiency. These meetings will be in person or over FaceTime if it is difficult to find a meeting place. The location and time of these meetings will be dependent on each member's schedule for that upcoming week.

2. **Assistance** 
Our team has all of our numbers programmed separately as well as a group chat for the project specifically. Therefore, if any teammate needs to communicate with one another, it will be done in the groupchat or through private messaging.

3. **Respect** 
Since our meetings will be in person, we think this will make collaborating and sharing ideas that much easier since we can express those thoughts and ideas directly in person. It is extremely important that every member listens to one another and that we are all equals while working on the project. No person should have more say than another unless it was agreed upon that the idea or thought that they were expressing was decided what the team goes with.

## Collaboration

4. **Work Distribution** 
Our team will come up with the project idea and then from their split the project up into different functions and/or portions that need to be completed. Then from there, we can assign each person a particular role. Preferrably, each team member will get a portion of the assignment that they feel they excel best at.

5. **Time Commitment** 
Our team decided that 4 hours a week seems like an adequate amount of time to work on the project. However, if we feel like we are falling behind then we will adjust this accordingly.

6. **Conflict Resolution** 
Our team will try and solve any conflict or disputes directly with one another as they happen. This way we remain on the same page througout the entire project. That being said, if there were to be a conflict that we could not handle ourselves, we would probably find it most beneficial to go to our mentor for our project.

## Signatures
Xander Kick abkick2
Cain Gonzalez dcg3
Becky Blake ryblake2
Armani Chien armanic2

## Leading Question 

We want to determine foot traffic between locations for the passing periods. With the added benefit of being able to identify where certain groups of people are and avoid them (ahem CS majors).

Given two datasets, one of course catalog and one of disjointed sets of classes that a student in a major would take. We want to try and find out the foot traffic between different buildings on campus. Each building would be a node and edges would represent foottraffic, the nodes will only connect if certain criteron are met. Our group is hoping to visualize and understand the patterns in foot traffic in U of I students.

The exact algorithms we are using are BFS, Dijkstra's, and our uncovered algorithm will be the force directed graph drawing.

## Dataset Acquisition

We will be using a course catalog dataset from the U of I data science discovery website. https://discovery.cs.illinois.edu/dataset/course-catalog/ the data set's input format would be in the comma seperated values format and we will use the whole dataset. In addition, we will also be manually inputting another set of disjointed set data structure. that stores classes that a student in a specific major would take. For example a set for a year 1 CS student includes cs124, math221, phys 211, eng 100.

## Data Format

The course dataset is a 12.6k row by 27 column matrix in a csv format, and we will use columns that include major information, course location, and potentially course time. The manually entered dataset will be in a disjointed set class that has sets of classes that relate to each other.

## Data Correction

If there are no location data for the specific class, we will just not include it in our foot traffic calculation, if there are n locations for a specific class, we will divide the traffic into 1/n for each location the class is located at.

## Data Storage

We will be using an adjacency list notation to store the dataset in a more efficient format, the keys would be the course numbers eg. 225, the values would be locations stored in a list eg. [Foellinger, CIF, Siebel]. We will be saving space because we will not have to store the course numbers multiple times, but the big O will still be O(num_unique_classes * amount_of_locations_of_largest_class), as the dataset grows larger, we'd increase the number of unique classes offered and increase the number of locations they're hosted in, so the storage would grow at O(n^2) worse case.

A second dataset would be a disjointed set, and it would be O(num_majors * 12) because there would be a set for each major and at most 12 first year classes they would take. O(n).

## Algorithm 

The expected inputs are: 
1. Adjancency list storing courses and their respective locations 
2. Manually entered disjointed sets of data representing first year classes for each major. 

We will be instantiating the graph using class location as nodes, and increase the edge weight between the class locations when one student takes the two classes in those locations.

# Function Outputs
We will store the expected output for our algorithm in a map, we will have location connections as keys, and the foot traffic as values. The larger the foot traffic the higher the value. This map would represent our graph of foottraffic.

After we have the foottraffic values, we will then BFS through the nodes to find which node has the most connections and therefore understand through our project which locations are most popular during the passing period. Also, we will Dijkstra through the nodes to find the path that could allow us to avoid certain groups of people by using it in tandem with the edge weights of foottraffic. Then we will visualize the classes with the most foottraffic with a force directed graph drawing placing the ones with the most connections at the center of the graph and least connections on the edge. This will show us pockets of groups of classes that have lots of foottraffic between each other but not much overlap with other groups (eg. architechture clasess & cs classes)

# Function Efficicency
We will first be instantiating the graph and it will take O(n^2) time because we will have to check every node's connection to every other node's connection to determine the edge value.

BFS through the graph to find the most popular spot would take O(n) time, it is guaranteed that it will take at least O(n) because we have to visit every single node to calculate how much foot traffic there are.

Dijkstra's efficiency would be O((V + E) log V)

## Timeline

We have time until December 8th
So from Nov 1st till December 8th there are around 4 weeks of development and one week of presentation building.

1st Wk Nov 1st - Nov 4th: Data Acquisition, build the adjacency list using the csv, and manually key in the disjointed set of students classes.

2nd Wk: Build out the graph data structure using the Adjacency list and use the disjointed sets as tolerances to add to the edge's weights.

3rd Wk & 4th Wk: Use graph traversal algorithms, BFS to find the hotspots and draw data discovery conclusions with what we have. Dijkstra through the nodes to find paths to avoid people.

5th Wk: Prepare presentation
