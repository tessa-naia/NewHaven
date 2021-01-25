#pragma once
#include <iostream>
#include "Resources.h"
#include "GBMap.h"
using namespace std;

class ResourceGather {
public:
	//return integer arrays containing the values of the counts
	ResourceGather();
	//for when there are more than one tile, perhaps recursively???
	int * RG_tilesonboard(HarvestTile &H1, HarvestTile &H2, GBMap& G);
	//for a singletile
	double* RG_tile(HarvestTile &test, double arr []);
	
	double getwood();
	double getstone();
	double getsheep();
	double getwheat();

	

private:
	double* woodcount;
	double* stonecount;
	double* sheepcount;
	double* wheatcount;
	
};