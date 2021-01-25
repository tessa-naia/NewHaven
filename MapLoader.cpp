//
// Created by Tess on 2020-03-01.
//
#include <string>
#include <fstream>
#include <iostream>
#include "MapLoader.h"
#include "GBMap.h"

using namespace std;

MapLoader::MapLoader() {
}

GBMap MapLoader::GBloadMap() {
    ifstream input("GBState.txt");
    int resnum = 0;
    string line;
    string player;
    string delimiter = " ";
    size_t pos = 0;
    getline(input, player);
    GBMap game(stoi(player));
    while (getline(input, line)) {
        int newTile[4];
        resnum = 0;
        pos = line.find(delimiter);
        string tlocation = line.substr(0, line.find(delimiter));
        line.erase(0, pos + delimiter.length());
        while ((pos = line.find(delimiter)) != std::string::npos) {
            string tres0 = line.substr(0, line.find(delimiter));
            line.erase(0, pos + delimiter.length());
            newTile[resnum] = stoi(tres0);
            resnum++;
        }
        if (newTile[0] != -1) {// leave empty tiles blank. Using -1 will generate a random tile
            game.placeTile(stoi(tlocation), newTile);
        }
    }
    input.close();
    return game;
}


bool MapLoader::VGcheckValidity(string f) {
    ifstream myInStream(f);
    if(myInStream.is_open()){
        while (!myInStream.eof()) {
            // read stuff from the file into a string and check
            std::string mapValues;
            getline(myInStream, mapValues);
             if(mapValues.compare("111112222233333444445555566666")==0) {
                 cout << "Valid Map" << endl;
                 cout << mapValues << endl;
             }
             else
                 cout<<"Invalid Map"<<endl;
        }
    }
    else{cout<<"Can't open";}
    return true;
}

string MapLoader::VGloadMap(string f) {
    ifstream myInStream(f);
    if(myInStream.is_open()){
        while (!myInStream.eof()) {
            // read stuff from the file into a string and check
            std::string mapValues;
            getline(myInStream, mapValues);
            if(mapValues.compare("111112222233333444445555566666")==0) {
                cout << "Valid Map" << endl;
                //cout << mapValues << endl;
                return mapValues;
            }
            else
                cout<<"Invalid Map"<<endl;
        }
    }
    else{cout<<"Can't open";
    return "";
    }
}
