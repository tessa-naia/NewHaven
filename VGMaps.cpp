//
// Created by Tess on 2020-02-01.
//

#include <cstdio>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <iostream>
#include "VGMaps.h"

using namespace std;

node::node() {
    value=0;
    string c="none";
    colour=&c;
    bool f=false;
    facingUp=&f;
}

node::node(int n) {
    value=new int;
    colour=new string;
    facingUp=new bool;
    if (n<5)
        *value=1;
    if (n>4 && n<10)
        *value=2;
    if (n>9 && n<15)
        *value=3;
    if (n>14 && n<20)
        *value=4;
    if (n>19 && n<25)
        *value=5;
    if (n>24)
        *value=6;
    *colour="none";
    *facingUp=false;
    if(n>4){
        adjacent.push_back(n-5);
    }
    if (n%5!=4) {
        adjacent.push_back(n + 1);
    }
    if(n%5!=0){
        adjacent.push_back(n-1);
    }
    if(n<25){
        adjacent.push_back(n+5);
    }
}

node::node(int n, int v) {
    value=new int;
    colour=new string;
    facingUp=new bool;
    *value=v;
    *colour="none";
    *facingUp=false;
    if(n>4){
        adjacent.push_back(n-5);
    }
    if (n%5!=4) {
        adjacent.push_back(n + 1);
    }
    if(n%5!=0){
        adjacent.push_back(n-1);
    }
    if(n<25){
        adjacent.push_back(n+5);
    }
}


bool node::isBuilding(node vgNode){
    if ((vgNode.colour)->compare("none")>0 || (vgNode.colour)->compare("none") < 0)
    {
        return true;
    }
    else
        return false;
}

void node::printAdjacency() {
    for (std::list<int>::iterator it=adjacent.begin(); it != adjacent.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

int node::getValue() {
    return *value;
}

void node::setColour(std::string c) {
    *colour=c;
}

std::string node::getColour() {
    return *colour;
}

void node::setFacingUp(bool f) {
    *facingUp=f;
}

bool node::getFacingUp() {
    return *facingUp;
}

/*node::~node() {
delete value;
value=NULL;
delete colour;
colour=NULL;
delete facingUp;
facingUp=NULL;
}*/

VGMaps::VGMaps() {
    name="unnamed";
    map=vector<node>(30);
    for(int i=0; i<30; i++){
        map[i]=node(i);
    }
}

VGMaps::VGMaps(std::string n) {
    name=n;
    map=vector<node>(30);
    for(int i=0; i<30; i++){
        map[i]=node(i);

    }
}

VGMaps::VGMaps(std::string n, std::string mapstr) {
    name=n;
    vector<int> values=vector<int>(30);
    for(std::string::size_type i = 0; i < mapstr.size(); ++i) {
        values[i]=(int)(mapstr[i])-48;
    }
    map=vector<node>(30);
    for(int i=0; i<30; i++){
        map[i]=node(i,values[i]);
    }
}

std::string VGMaps::getName() {
    return name;
}

void VGMaps::setName(std::string n) {
    name=n;
}

void VGMaps::printMapAdjacency() {
    for (int i=0; i<30; i++){
        std::cout <<i << " -->";
        map[i].printAdjacency();
    }
}

void VGMaps::printMap() const {
    cout<<"\n"<<getName()<<": \n25  26  27  28  29\n20  21  22  23  24\n15  16  17  18  19\n10  11  12  13  14\n5   6   7   8   9\n0   1   2   3   4\n";
    for (int i=0; i<30; i++){
        std::cout <<i << ": "<<map[i].getColour()<<" Value: "<<map[i].getValue()<<" Facing up: "<<map[i].getFacingUp()<<" Adjacency: ";
        map[i].printAdjacency();
    }
}


void VGMaps::BFS(int x) {
// Mark all the vertices as not visited
//bool isColour;
    bool *visited = new bool[30];
    for (int i = 0; i < 30; i++)
        visited[i] = false;

    // Create a queue for BFS
    list<int> queue;
    // Mark the current node as visited and enqueue it
    visited[x] = true;
    queue.push_back(x);

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;

    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        x = queue.front();
        cout << x << " ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = map[x].adjacent.begin(); i != map[x].adjacent.end();++i) {
            if (!visited[*i]) {

                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

void VGMaps::placeBuilding(Building* b, bool facingUp, int input) {
    if (facingUp == false) {
        if (*b->getNumber() == map[input].getValue()) {
            map[input].setColour(*b->getColor());
            map[input].setFacingUp(facingUp);
            cout << "Your building has been placed at space " << input;
            //update resource tracker
        } else
            cout << "Invalid. This building does not having a matching value to the space.";
    } else { //faceup buildings can be placed in any adjacent space

        map[input].setColour(*b->getColor());
        map[input].setFacingUp(facingUp);
        cout << "Your building has been placed at space " << input;
        //update resource tracker

        
    }
}

void VGMaps::buildVillage(Building* b, bool facingUp) {
    string c = *b->getColor();
    //check resource tracker that resources of type==colour >= building value
    int x = 29;
    list<int> placeAt;
    bool *visited = new bool[30];
    for (int i = 0; i < 30; i++)
        visited[i] = false;

    // Create a queue for BFS
    list<int> queue;
    // Mark the current node as visited and enqueue it
    visited[x] = true;
    queue.push_back(x);

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;

    while (!queue.empty()) {
        // Dequeue a vertex from queue and print it
        x = queue.front();
        if (map[x].colour->compare(c) == 0) {
            for (std::list<int>::iterator it = map[x].adjacent.begin(); it != map[x].adjacent.end(); ++it) {
                //pushes filled values
                if (map[*it].colour->compare("none") == 0)
                    placeAt.push_back(*it);
            }
        }
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = map[x].adjacent.begin(); i != map[x].adjacent.end(); ++i) {
            if (!visited[*i]) {

                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    bool okay=false;
    placeAt.sort();
    placeAt.unique();
    while(!okay){
        if (placeAt.empty()) {
            cout << "\nThere are no " << c << " buildings. ";
            cout << "Pick a empty place on the board to place your building:";
            //Print village board
            printMap();

            int input;
            cin >> input;
            if (input >= 0 && input < 30 && map[input].getColour() == "none") {
                placeBuilding(b, facingUp, input);
                cout<< map[input].getColour();
                okay=true;
            } else {
                cout << "Invalid. Out of Bounds or Village space is full.";
            }
        } else { //If there are already buildings of a colour on map new building must be adjacent
            cout << "Place at: ";
            for (std::list<int>::iterator it = placeAt.begin(); it != placeAt.end(); ++it)
                std::cout << ' ' << *it;
            int input;
            bool contains = false;
            cin >> input;
            for (std::list<int>::iterator it = placeAt.begin(); it != placeAt.end(); ++it) {
                if (input == *it)
                    contains = true;
            }
            if (contains) {
                placeBuilding(b, facingUp, input);
                okay = true;
            } else {
                cout << "Invalid. Input was not adjacent to a " << c << " building.";

            }
        }
    } //while
    queue.clear();
    placeAt.clear();
    delete[] visited;
}

int VGMaps::scoreCol(int x, int colVal) {
    int index=x;
    bool full=true;
    bool rowFacingUp=true;
    for(int i=0; i<=6; i++){
        if (map[index].getColour()=="none")
            full=false;
        if(map[index].getFacingUp()==false)
            rowFacingUp=false;
        index+=5;
    }
    if (full && rowFacingUp)
        return colVal*2;
    else if (full && !rowFacingUp)
        return colVal;
    else
        return 0;
}
int VGMaps::scoreRow(int x, int rowVal) {
    int index=x;
    bool full=true;
    bool rowFacingUp=true;
    for(int i=0; i<=5; i++){
        if (map[index].getColour()=="none")
            full=false;
        if(map[index].getFacingUp()==false)
            rowFacingUp=false;
        ++index;
    }
    if (full && rowFacingUp)
        return rowVal*2;
    else if (full && !rowFacingUp)
        return rowVal;
    else
        return 0;
}

/*int VGMaps::calculatePoints() {
    int sum=0;
    sum=scoreCol(0, 5)+scoreCol(1, 4)+scoreCol(2, 3)+scoreCol(3, 4)+scoreCol(4, 5)+scoreRow(0, 1)+
            scoreRow(5, 2)+scoreRow(10, 3)+scoreRow(15,4)+scoreRow(20, 5)+scoreRow(25, 6);
return sum;
}*/


