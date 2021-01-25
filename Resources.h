#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <time.h>

using namespace std;

class HarvestTile {
public:
    void printTile();
    HarvestTile();
	list<list<string>>* rotation(list<list<string>>& Res);
	list<list<string>>* getResources();
	void setResources(list<list<string>>* Res);

    int* convertHT(HarvestTile& HT);
    //void BFS(HarvestTile &H1);
    bool Visit1;
    bool Visit2;
    bool Visit3;
    bool Visit4;
	//function(HarvestTile, orientation) {
		// check adjacey inside tile
		// update counter
		// check adacent nodes ith oher tiles
		// recursion
	//}
   // ~HarvestTile();
private:
    list<list<string>>* Resources;
    int random_int;
    
};

class HarvestTile_deck {
public:
    HarvestTile_deck();
    HarvestTile* draw();
    vector<HarvestTile>* getDeck();
    void printdeck();
    static int drawn;
    //~HarvestTile_deck();
private:
       
       vector<HarvestTile>* HT_deck;
      
};

class Building {
public:
    Building();
    Building(int num, string col, string opp);
    
	string* getColor();
	string* getOppositeSide();
	int* getNumber();
    bool* getDrawn();

	void setColor(string col);
	void setOppositeSide(string opp);
	void setNumber(int num);
    void setDrawn(bool d);

	void printBuilding();
   // ~Building();
private:
    string* oppositeside;
    string* color;
    int* number;
    bool* drawn;

};

class Building_deck {
public:
        Building_deck();
        
        Building* draw();
      vector<Building>* getDeck();
		static vector<int> amt;
        static int drawn;
        void printBuildingDeck();
        //~Building_deck();

private:
        vector<Building>* B_deck;
		
        
    };

class Hand {
public:
   Hand();
   void exchange();
   int* getWood();
   int* getStone();
   int* getWheat();
   int* getSheep();

private:   
    int* wood_marker;
    int* stone_marker;
    int* wheat_marker;
    int* sheep_marker;
   
  
};