//
// Created by Tess on 2020-02-01.
//
#include <cstdio>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <iostream>
#include "Resources.h"
#ifndef COMP345_ASSIGNMENT1_VGMAPS_H
#define COMP345_ASSIGNMENT1_VGMAPS_H
#pragma once
using namespace std;
class node{
public:
    list <int> adjacent;
    int *value;
    string *colour;
    bool *facingUp;

    node();
    explicit node(int n);
    bool isBuilding(node n);
    node (int n, int v);
    //~node();
    void printAdjacency();
    int getValue();
    void setColour(std::string c);
    std::string getColour();
    void setFacingUp(bool fu);
    bool getFacingUp();
    std::list<int> getAdjacent();
};
class VGMaps {

public:
    std::vector<node> map;
    std::string name;

    VGMaps();
    VGMaps(std::string n);
    VGMaps(std::string n, std::string strmap);
    void printMap() const;
    std::string getName();
    void setName(std::string n);
    std::vector<node> getMap();
    void printMapAdjacency();
    void placeBuilding(Building* b, bool facingUp, int input);
    void buildVillage(Building* b, bool facingUp);
    void BFS(int x);
    int scoreCol(int x, int colVal);
    int scoreRow(int x, int rowVal);
    int calculatePoints();
};


#endif //COMP345_ASSIGNMENT1_VGMAPS_H
