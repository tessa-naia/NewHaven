#pragma once
#include "VGMaps.h"
#include "ResourceGather.h"
#include "VillageScore.h"
#include "GBMap.h"


class Player {
private:
    static int currentID;
    int playerID;
    GBMap* PlayerMap;
    //Hand* my_Hand;
    ResourceGather* RG1;
    VillageScore* VS;

public:
        Player();
        Player(GBMap &map, VGMaps &Map, ResourceGather &RG, VillageScore &VS);

        VGMaps* VillageMap;
        HarvestTile* HT1;
        HarvestTile* HT2;
        HarvestTile* Wild_Tile;

        int getPlayerID();
        int getCurrentID();
        void setPlayerID(int id);
        Building* B1;
        Building* B2;
        Building* B3;
        Building* B4;
        Building* B5;
        /*void setGB(GBMap &Map);
        void setVB(VGMaps &Map);
        void setHT(HarvestTile &Tile);
        void setBuilding(Building &B);
        void setRG(ResourceGather &RG);*/
        void setVS(VillageScore *score);
        
       // GBMap* getGB();
        VGMaps* getVB();
        HarvestTile* getHT1();
        Building* getBuilding();
        //ResourceGather* getRG();
        VillageScore* getVS();
        
       void PlaceHarvestTile(int location, HarvestTile &HT, GBMap& board);
       void DrawBuilding(Building_deck &deck);
       void DrawHarvestTile(HarvestTile_deck &deck);
     /*  double* CalculateResources();
      void BuildVillage(Building &B);
       void ResourceTracker();*/
    /*   ~Player() {
           delete PlayerMap;
           delete VillageMap;
           delete HT1;
           delete HT2;
           delete Wild_Tile;
           delete B1;
           delete B2;
           delete B3;
           delete B4;
           delete B5;
           delete RG1;
           delete VS;
      }*/
};
