//
// Created by Tess
//

#ifndef VGMAPSTESTS_MAPLOADER_H
#define VGMAPSTESTS_MAPLOADER_H
#include <string>
#include <vector>
#include <iostream>
#include "GBMap.h"


using namespace std;

class MapLoader {
public:
    MapLoader();
    GBMap GBloadMap();
    bool VGcheckValidity(string f);
    string VGloadMap(string f);
};


#endif //VGMAPSTESTS_MAPLOADER_H
