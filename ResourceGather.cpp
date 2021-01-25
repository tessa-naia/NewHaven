#include <iostream>
#include <list>
#include<string>
#include <math.h>
#include "ResourceGather.h"
using namespace std;
ResourceGather::ResourceGather() {
	
	stonecount = new double(0.0);
	wheatcount = new double(0.0);
	woodcount = new double(0.0);
	sheepcount = new double(0.0);

	/*top = false;
	bottom = false;
	left = false;
	right = false;*/
}
double* ResourceGather :: RG_tile(HarvestTile &test, double arr []) {
	double stone = 0;
	double wheat = 0;
	double wood = 0;
	double sheep = 0;

	stonecount = &stone;
	wheatcount = &wheat;
	woodcount = &wood;
	sheepcount = &sheep;

	double* temp1 = arr;

	list<list<string>>* temp = new list<list<string>>;

	for (auto h : *(test.getResources())) {
		temp->push_back(h);
	}
	

	

	//HarvestTiles are lists containing lists of strings
	//iterator to go over each string list contained in the list
  	list<list<string>> ::iterator it = (*temp).begin();
	
	list<string> ::iterator it2;
	//list<string>& it3 = *it;

	for (it; it != (*temp).end(); it++) {
		//reference it3 needs to be updated with each list<string> pointer in the list<list<string>>
		//it3 = *it;
		
		//for iterating over the lists contained in the list of lists
		for (it2 = (*it).begin(); it2 != (*it).end(); it2++) {
			if ((*it2).compare("stone") == 0) {
				(*stonecount)++;
			}
			if ((*it2).compare("wood") == 0) {
				(*woodcount)++;
			}
			if ((*it2).compare("sheep") == 0) {
				(*sheepcount)++;
			}
			if ((*it2).compare("wheat") == 0) {
				(*wheatcount)++;
			}
		}
	}
	
	//which would then be stuffed into this array to be returned (all values are divided by 3 because each node will be visited 3 times
	//that is if I understand how this is working...)
	
	temp1[0] = ceil(((*stonecount) / 3));
	temp1[1] = ceil(((*wheatcount) / 3));
	temp1[2] = ceil(((*woodcount) / 3));
	temp1[3] = ceil(((*sheepcount) / 3));

	return temp1;
}

//int* ResourceGather :: RG_tilesonboard(HarvestTile &H1, HarvestTile &H2, Graph *G) {
//	if(G->arr[0].head.data == 5)
//	{
//	}
//	if(bottom)
//	{
//	}
//	if(left)
//	{
//	}
//	if(right)
//	{
//	}
//}
double ResourceGather::getwood()
{
	return *woodcount;
}

double ResourceGather::getstone()
{
	return *stonecount;
}

double ResourceGather::getsheep()
{
	return *sheepcount;
}

double ResourceGather::getwheat()
{
	return *wheatcount;
}

