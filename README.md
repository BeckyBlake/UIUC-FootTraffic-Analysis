# Location of Files
1. **cs225-project**
    a) build
        build contains all of the make and cmake files in order for our project to compile and run. 
    b) entry
        entry contains our **main.cpp** file where we use our other programs like file reader and disjointSets to get our data and process it as well. TO BE CONTINUED SINCE WE NEED TO WORK ON MAIN AGAIN
    c) lib
        UNTOUCHED MAINLY USED SINCE WE COPIED DOCKER I BELIEVE(??). WILL TOUCH UPON LATER
    d)








# cs225_project
# Team Contract

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
