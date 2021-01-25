#pragma once

#include<iostream>
#include<cstdlib>
#include <list>


struct tile {
	int data;
	int resources[4]= { -1,-1,-1,-1 };
	//-1=empty 0 = wood, 1 = sheep, 2 = stone, 3 = wheat
	int adjList[4] = { -1,-1,-1,-1};
	int x = 0;
};

struct resourceTile { 
	int resource; //resource value
	int adjList[4] = {-1,-1,-1,-1};
	int x = 0;
};

struct resAdjList {
	resourceTile* head;
};

struct resourceMap {
	int numResources;
	resourceTile* resourceList;
	resAdjList* arra;
};

struct AdjList {
	tile* head;
};


struct Graph {
	int V;//max size of graph
	AdjList* arr;
};

class GBMap {

private:

	int players;
	Graph* board;
	resourceMap* resourceList;

	tile* newAdjListNode(int data);
	resourceTile* newResourceAdjListNode(int res);
	Graph* createGraph(int V);
	resourceMap* createResourceMap(int numResources);


public:
	int getPlayers();

	Graph* getGraph();

	resourceMap* getResourceBoard();

	void addEdge(Graph* graph, int src, int dest);

	void addResourceEdge(resourceMap* graph, int src, int dest);

	void printGraph(Graph* graph);

	void printResGraph(resourceMap* resmap);

	GBMap();

	GBMap(int player);//load constructor

	int* placeTile(int location, int* res);
	
	int tileLink(resourceMap* map, int pos);

	void tileLinkHelper(resourceMap* map, int pos, int* visited, int res, std::list<int>* adj);
};



void showMap(GBMap& map);


void saveGame(GBMap& map);


GBMap loadGame();
