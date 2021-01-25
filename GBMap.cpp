#include "GBMap.h"
#include<iostream>
#include <sstream>
#include<cstdlib>
#include <fstream>
#include <time.h>
#include <list>
#include <iterator>
using namespace std;


//attributes
int players;
Graph* board;
resourceMap* resourceBoard;

//create a new node
tile* GBMap::newAdjListNode(int data) {
	tile* nptr = new tile;
	nptr->data = data;
	return nptr;
}

resourceTile* GBMap::newResourceAdjListNode(int res) {
	resourceTile* rnptr = new resourceTile;
	rnptr->resource = -1;
	return rnptr;
}

//Tile Graph
Graph* GBMap::createGraph(int V) {
	Graph* graph = new Graph;
	graph->V = V;
	graph->arr = new AdjList[V];
	for (int i = 0; i < V; i++) {
		tile* nptr = newAdjListNode(i);
		graph->arr[i].head = nptr;
	}
	return graph;
}

//Ressource Graph
resourceMap* GBMap::createResourceMap(int numResources){
	resourceMap* rGraph = new resourceMap;
	rGraph->numResources = numResources;
	rGraph->arra = new resAdjList[numResources];
	for (int i = 0; i < numResources; i++) {
		resourceTile* rnptr = newResourceAdjListNode(i);
		rGraph->arra[i].head = rnptr;
	}
	return rGraph;
}

Graph* GBMap::getGraph() {
	return board;
}

resourceMap* GBMap::getResourceBoard() {
	return resourceBoard;
}


void GBMap::addEdge(Graph* graph, int src, int dest) {
	tile* srcTile = graph->arr[src].head;
	srcTile->adjList[srcTile->x] = dest;
	srcTile->x++;
	tile* destTile = graph->arr[dest].head;
	destTile->adjList[destTile->x] = src;
	destTile->x++;
}

void GBMap::addResourceEdge(resourceMap* resgraph, int src, int dest) {
	resourceTile* srcTile = resgraph->arra[src].head;
	srcTile->adjList[srcTile->x] = dest;
	srcTile->x++;
	resourceTile* destTile = resgraph->arra[dest].head;
	destTile->adjList[destTile->x] = src;
	destTile->x++;
}

void GBMap::printGraph(Graph* graph) {
	for (int i = 0; i < graph->V; i++) {
		tile* root = graph->arr[i].head;
		cout << i << endl;
		std::cout << "Resources of " << i << ", with resources: ";
		//if (root != NULL) {
		//	std::cout << root->resources[0] << root->resources[1] << root->resources[2] << root->resources[3] << endl;
		//}
		std::cout << "Adjacency List of " << i << ": ";
		for (int j = 0; j < 4; j++){
			if (root->adjList[j] == -1){
				break;
			}
			else{
				std::cout << root->adjList[j] << " " ;
			}
		}
	
		std::cout << endl;
	}
}

void GBMap::printResGraph(resourceMap* resmap) {
	for (int i = 0; i < resmap->numResources; i++) {
		resourceTile* root = resmap->arra[i].head;
		cout << i << endl;
		std::cout << "Ressource: " << root->resource << " ";
		std::cout << "Adjacency List of " << i << ": ";
		for (int j = 0; j < 4; j++) {
			if (root->adjList[j] == -1) {
				break;
			}
			else {
				std::cout << root->adjList[j] << " ";
			}
		}

		std::cout << endl;
	}
}

GBMap::GBMap() {
	while ((players > 4) || (players < 2)) {
		std::cout << "Please select between 2 and 4 players!\n" << endl;
		cin >> players;
	}
	//2 player board
	int cornerPos[4];
	if (players == 2) {
		board = createGraph(25);
		for (int i = 0; i < 20; i++) {
			addEdge(board, i, i + 5);
			if (i % 5 != 4) {
				addEdge(board, i, i + 1);
			}

		}
		for (int i = 20; i < 24; i++) {
			addEdge(board, i, i + 1);
		}
		cornerPos[0] = 0;
		cornerPos[1] = 4;
		cornerPos[2] = 20;
		cornerPos[3] = 24;
		resourceBoard = createResourceMap(100);
		for (int i = 0; i < 80; i++) {
			
			addResourceEdge(resourceBoard, i, i + 10);
			if (i % 10 != 9) {
				addResourceEdge(resourceBoard, i, i + 1);
			}
		}
		for (int i = 80; i < 99; i++) {
			addResourceEdge(resourceBoard, i, i +1);
		}
	}
	
	//3 player board
	else if (players == 3) {
		board = createGraph(35);
		for (int i = 0; i < 30; i++) {
			addEdge(board, i, i + 5);
			if (i % 5 != 4) {
				addEdge(board, i, i + 1);
			}
		}
		for (int i = 30; i < 34; i++) {
			addEdge(board, i, i + 1);
		}
		cornerPos[0] = 5;
		cornerPos[1] = 9;
		cornerPos[2] = 25;
		cornerPos[3] = 29;
		resourceBoard = createResourceMap(140);
		for (int i = 0; i < 120; i++) {
			addResourceEdge(resourceBoard, i, i +10);
			if (i % 10 != 9) {
				addResourceEdge(resourceBoard, i, i + 1);
			}
		}
		for (int i = 120; i < 139; i++) {
			addResourceEdge(resourceBoard, i, i + 1);
		}

	}
	//4 player board
	else if (players == 4) {
		board = createGraph(49);
		for (int i = 1; i < 41; i++) {
			if (i != 6 && i != 35) {
				addEdge(board, i, i + 7);
				if (i % 7 != 6 && i != 5) {
					addEdge(board, i, i + 1);
				}
			}
		}
		for (int i = 43; i < 48; i++) {
			if (i != 47) {
				addEdge(board, i, i + 1);
			}
		}
		cornerPos[0] = 8;
		cornerPos[1] = 12;
		cornerPos[2] = 36;
		cornerPos[3] = 40;
		resourceBoard = createResourceMap(196);
		for (int i = 2; i < 182; i++) {
			if (i != 12 && i != 13 && i != 14 && i != 15 && i != 26 && i != 27 && i != 154 && i != 155 && i != 166 && i != 167 && i != 168 && i != 169 && i != 180 && i != 181) {
				addResourceEdge(resourceBoard, i, i + 14);
				if (i % 14 != 13 && i != 11 && i != 25 && i != 1 && i != 15 && i != 179) {
					addResourceEdge(resourceBoard, i, i + 1);
				}
			}
		}
		//special cases needed to be hard coded
		addResourceEdge(resourceBoard, 166, 167);
		addResourceEdge(resourceBoard, 154, 155);

		for (int i = 184; i < 194; i++) {
			if (i != 193) {
				addResourceEdge(resourceBoard, i, i + 1);
			}
		}
	}
	int res[] = { 1,1,1,1 };
	placeTile(cornerPos[0], res);
	res[0] = 1;
	res[1] = 2;
	res[2] = 0;
	res[3] = 1;
	placeTile(cornerPos[1], res);
	res[0] = 0;
	res[1] = 2;
	res[2] = 3;
	res[3] = 1;
	placeTile(cornerPos[2], res);
	res[0] = 2;
	res[1] = 3;
	res[2] = 0;
	res[3] = 1;
	placeTile(cornerPos[3], res);


	//printResGraph(resourceBoard);
}

GBMap::GBMap(int player) {
	players = player;
	int cornerPos[4];
	if (players == 2) {
		board = createGraph(25);
		for (int i = 0; i < 20; i++) {
			addEdge(board, i, i + 5);
			if (i % 5 != 4) {
				addEdge(board, i, i + 1);
			}

		}
		for (int i = 20; i < 24; i++) {
			addEdge(board, i, i + 1);
		}
		cornerPos[0] = 0;
		cornerPos[1] = 4;
		cornerPos[2] = 20;
		cornerPos[3] = 24;
	}
	//3 player board
	else if (players == 3) {
		board = createGraph(35);
		for (int i = 0; i < 30; i++) {
			addEdge(board, i, i + 5);
			if (i % 5 != 4) {
				addEdge(board, i, i + 1);
			}
		}
		for (int i = 30; i < 34; i++) {
			addEdge(board, i, i + 1);
		}
		cornerPos[0] = 6;
		cornerPos[1] = 10;
		cornerPos[2] = 26;
		cornerPos[3] = 30;
	}
	//4 player board
	else if (players == 4) {
		board = createGraph(49);
		for (int i = 1; i < 41; i++) {
			if (i != 6 && i != 35) {
				addEdge(board, i, i + 7);
				if (i % 7 != 6 && i != 5) {
					addEdge(board, i, i + 1);
				}
			}
		}
		for (int i = 43; i < 48; i++) {
			if (i != 47) {
				addEdge(board, i, i + 1);
			}
		}
		cornerPos[0] = 9;
		cornerPos[1] = 13;
		cornerPos[2] = 37;
		cornerPos[3] = 41;
	}
	int res[] = { -1,-1,-1,-1 };
	for (int i = 0; i < 4; i++) {
		placeTile(cornerPos[i], res);
	}
}

void showMap(GBMap& map) {
	map.printGraph(map.getGraph());
	map.printResGraph(resourceBoard);
}

int GBMap::getPlayers() {
	return players;
}

int* GBMap::placeTile(int location, int* res) {
	int* resourcesAr = new int[4];
	resourcesAr[0] = 0;
	resourcesAr[1] = 0;
	resourcesAr[2] = 0;
	resourcesAr[3] = 0;
	/*
	resourcesAr[0] = sheep pts
	resourcesAr[1] = stone pts
	resourcesAr[2] = wood pts
	resourcesAr[3] = wheat pts
	*/
	tile* root = board->arr[location].head;
	resourceTile* resRoot;
	int colheight = 0;
	if (players == 2 || players == 3) {
		if (location == 0 || location == 1 || location == 2 || location == 3 || location == 4) {
			colheight = 0;
		}
		else if (location == 5 || location == 6 || location == 7 || location == 8 || location == 9) {
			colheight = 1;
		}
		else if (location == 10 || location == 11 || location == 12 || location == 13 || location == 14) {
			colheight = 2;
		}
		else if (location == 15 || location == 16 || location == 17 || location == 18 || location == 19) {
			colheight = 3;
		}
		else if (location == 20 || location == 21 || location == 22 || location == 23 || location == 24) {
			colheight = 4;
		}
		else if (location == 25 || location == 26 || location == 27 || location == 28 || location == 29) {
			colheight = 5;
		}
		else if (location == 30 || location == 31 || location == 32 || location == 33 || location == 34) {
			colheight = 6;
		}

	resRoot = resourceBoard->arra[(colheight * 10) + (location * 2)].head;
	resRoot->resource = res[0];//top right
	resRoot = resourceBoard->arra[(colheight * 10) + (location * 2) + 1].head;
	resRoot->resource = res[1];//top left
	resRoot = resourceBoard->arra[(colheight * 10) + (location * 2) + 10].head;
	resRoot->resource = res[2];//bot right
	resRoot = resourceBoard->arra[(colheight * 10) + (location * 2) + 11].head;
	resRoot->resource = res[3];//bot left
	int j = 0;
	int mapsize = resourceBoard->numResources;
	int* visited = new int[mapsize];
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			j = (colheight * 10) + (location * 2);
		}
		else if (i == 1) {
			j = (colheight * 10) + (location * 2) + 1;
		}
		else if (i == 2) {
			j = (colheight * 10) + (location * 2) + 10;
		}
		else if (i == 3) {
			j = (colheight * 10) + (location * 2) + 11;
		}
		if (res[i] == 0) {
			resourcesAr[0] = resourcesAr[0]+ tileLink(resourceBoard, j);
		}
		if (res[i] == 1) {
			resourcesAr[1] = resourcesAr[1]+ tileLink(resourceBoard, j);
		}
		if (res[i] == 2) {
			resourcesAr[2] = resourcesAr[2]+ tileLink(resourceBoard, j);
		}
		if (res[i] == 3) {
			resourcesAr[3] = resourcesAr[3]+ tileLink(resourceBoard, j);
		}
	}
	

	}else if (players == 4) {
		if (location == 0 || location == 1 || location == 2 || location == 3 || location == 4 || location == 5 || location == 6) {
			colheight = 0;
		}
		else if (location == 7 || location == 8 || location == 9 || location == 10 || location == 11 || location == 12 || location == 13) {
			colheight = 1;
		}
		else if (location == 14 || location == 15 || location == 16 || location == 17 || location == 18 || location == 19 || location == 20) {
			colheight = 2;
		}
		else if (location == 21 || location == 22 || location == 23 || location == 24 || location == 25 || location == 26 || location == 27) {
			colheight = 3;
		}
		else if (location == 28 || location == 29 || location == 30 || location == 31 || location == 32 || location == 33 || location == 34) {
			colheight = 4;
		}
		else if (location == 35 || location == 36 || location == 37 || location == 38 || location == 39 || location == 40 || location == 41) {
			colheight = 5;
		}
		else if (location == 42 || location == 43 || location == 44 || location == 45 || location == 46 || location == 47 || location == 48) {
			colheight = 6;
		}

	resRoot = resourceBoard->arra[(colheight * 14) + (location * 2)].head;
	resRoot->resource = res[0];
	resRoot = resourceBoard->arra[(colheight * 14) + (location * 2) + 1].head;
	resRoot->resource = res[1];
	resRoot = resourceBoard->arra[(colheight * 14) + (location * 2) + 14].head;
	resRoot->resource = res[2];
	resRoot = resourceBoard->arra[(colheight * 14) + (location * 2) + 15].head;
	resRoot->resource = res[3];

	}
	std::cout << "Tile Placed at: " << location << endl;
	return resourcesAr;
}

//checks the individual resource board
int GBMap::tileLink(resourceMap* map, int pos) {
	int mapsize = map->numResources;
	resourceTile* root = map->arra[pos].head;
	int initialres = root->resource;
	//allocating an array
	std::list<int> adj;
	int* visited = new int[mapsize];
	for (int i = 0; i < mapsize; i++) {
		visited[i] = 0;
	}
	tileLinkHelper(map, pos, visited, initialres, &adj);
	return adj.size();
}

void GBMap::tileLinkHelper(resourceMap* map, int pos, int* visited, int res, list<int>* adj) {
	bool flag = true;
	if (visited[pos] == 0) {
		visited[pos] = 1;
		resourceTile* root = map->arra[pos].head;
		for (int j = 0; j < 4; j++) {
			if (root->resource != res && root->adjList[j] != -1) {
				break;
			}
			else {
				for (std::list<int>::iterator it = adj->begin(); it != adj->end(); ++it) {
						if (*it == pos) {
							flag = false;
						}
					}
					if (flag) {
						adj->push_back(pos);
					}
					tileLinkHelper(map, root->adjList[j], visited, res, adj);
				
			}
		}

	}
}

void saveGame(GBMap& map) {
	//TODO: FIX THIS use adj list instead
	fstream file("GBState.txt", std::ios::out | fstream::trunc);
	cout << "Saving current game state..." << endl;
	file << map.getPlayers() << endl;
	int mapsize = map.getGraph()->V;
	for (int i = 0; i < mapsize; i++) {
		tile* root = map.getGraph()->arr[i].head;
		if (root != NULL) {
			file << i << " " <<root->resources[0] << " " << root->resources[1] << " " << root->resources[2] << " " << root->resources[3] << endl;
		}
		//while (root != NULL) {
		//	std::cout << root->data << " -> ";
			//root = root->next;
		//} std::cout << endl;
	}
	file.close();
}



GBMap loadGame() {
	//TODO: Edit this so you populate resource map as well
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
