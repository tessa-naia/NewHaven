#include "GBMap.h"
#include "Player.h"
#include "ResourceGather.h"
#include "Resources.h"
#include "VGMaps.h"
#include"GameObserver.h"
#include <stdlib.h>
int Player::currentID = 0;
int* resourceMarker = new int[4];
ConcreteSubject *subject = new ConcreteSubject();
ConcreteSubject *statsSubj = new ConcreteSubject();

GameObservers *Obs1 = new GameObservers(subject);
GameObservers* Obs2 = new GameObservers(subject);
GameStatsObserver* StatsObs = new GameStatsObserver(statsSubj);
int* PlayerTurn(bool P1, bool P2, bool P3, bool P4)
{
	int* Pturn = new int(0);
	if (P1)
	{
		Pturn = new int(1);
		return Pturn;
	}else if(P2)
	{
		Pturn = new int(2);
		return Pturn;
	}else if(P3)
	{
		Pturn = new int(3);
		return Pturn;
	}else if (P4)
	{
		Pturn = new int(4);
		return Pturn;
	}
	return Pturn;
}
int main()
{
	
	subject->attach(Obs1);
	subject->attach(Obs2);
    statsSubj->attach(StatsObs);

	GBMap map;
	int numberOfPlayers = map.getPlayers();
	int numberOfTurns;
	Player P1;
	Player P2;
	Player P3;
	Player P4;
	
	HarvestTile_deck harvestTileDeck = HarvestTile_deck();

	Building_deck buildingDeck = Building_deck();

	resourceMarker[0] = 0;
	resourceMarker[1] = 0;
	resourceMarker[2] = 0;
	resourceMarker[3] = 0;

	int* resourcesGathered = new int[4]; // position 0 = sheep, 1 = stone, 2 = wood, 3 = wheat
	if (numberOfPlayers == 2)
	{
		numberOfTurns = 20;

		Player P1 = Player();
		int player1ID = P1.getCurrentID();
		P1.setPlayerID(player1ID);
		cout << endl;
		cout << "Player 1 ID: ";
		cout << P1.getPlayerID() << endl << endl;

		P1.VillageMap = new VGMaps("Gilford");
		VillageScore* vs1 = new VillageScore();
		P1.setVS(vs1);

		P1.DrawHarvestTile(harvestTileDeck);
		P1.DrawHarvestTile(harvestTileDeck);
		

		P1.DrawBuilding(buildingDeck);
		P1.DrawBuilding(buildingDeck);
		P1.DrawBuilding(buildingDeck);
		P1.DrawBuilding(buildingDeck);
		P1.DrawBuilding(buildingDeck);

		cout << endl;

		Player P2 = Player();
		int player2ID = P2.getCurrentID();
		P2.setPlayerID(player2ID);
		cout << "Player 2 ID: ";
		cout << P2.getPlayerID() << endl << endl;

		P2.VillageMap = new VGMaps("Milford");
        VillageScore* vs2 = new VillageScore();
        P2.setVS(vs2);

		P2.DrawHarvestTile(harvestTileDeck);
		P2.DrawHarvestTile(harvestTileDeck);

		P2.DrawBuilding(buildingDeck);
		P2.DrawBuilding(buildingDeck);
		P2.DrawBuilding(buildingDeck);
		P2.DrawBuilding(buildingDeck);
		P2.DrawBuilding(buildingDeck);

		cout << endl;

		bool gameDoneFlag = false;
		int turnsTaken = 0;

		bool player1Turn = true;
		bool player2Turn = false;
		bool player3Turn = false;
		bool player4Turn = false;
		
		
		while (!gameDoneFlag)
		{
			if (turnsTaken == 20)
			{
				gameDoneFlag = true;
			}
			if (player1Turn)
			{
				int harvestTileNumber = 0;
				int tilePlacement;

				//player 1 actions

				cout << "Player 1 turn: " << endl;

				cout << "Select a harvest tile: " << endl;
				cout << "Harvest Tile 1: ";
				HarvestTile* ht = P1.HT1;
				ht->printTile();
				cout << "Harvest Tile 2: ";
				HarvestTile* ht2 = P1.HT2;
				ht2->printTile();
				cout << "Enter 1 or 2:" << endl;
				cin >> harvestTileNumber;
				cout << "Which position would you like to place the tile?" << endl;
				cin >> tilePlacement;
				if (harvestTileNumber == 1)
				{
					int * harvestTileArray = P1.HT1->convertHT(*P1.HT1);
					resourcesGathered =  map.placeTile(tilePlacement, harvestTileArray);
					P1.HT1 = NULL;	
				}
				else if (harvestTileNumber == 2)
				{
					int* harvestTileArray = P1.HT2->convertHT(*P1.HT2);
					resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
					P1.HT2 = NULL;
				}

				std::cout << resourcesGathered[0] << " Sheep " << resourcesGathered[1] << " Stone " << resourcesGathered[2] << " Wood " << resourcesGathered[3] << " Wheat " << endl << endl;
			
				resourceMarker[0] = resourcesGathered[0];
				resourceMarker[1] = resourcesGathered[1];
				resourceMarker[2] = resourcesGathered[2];
				resourceMarker[3] = resourcesGathered[3];

				int* test = PlayerTurn(player1Turn, player2Turn, player3Turn, player4Turn);
				int* test2 = new int(2);
				subject->setPlayerTurn(test);
				subject->setresourceGen(resourcesGathered);
				subject->setVillageBuildingCount(test2);
				subject->notify();
				//P1.BuildVillage(); //player 1 builds buildings ontop of the village board
				//access the buildings in player 1's hand
				//print out the buildings, let player 1 choose which building to build
				//choose where to place the building
				//subtract the resources used from resource marker

				
				bool ableToBuild = false;

				while (!ableToBuild)
				{

			    ableToBuild = true;
			    
				cout << "These are your buildings (Player 1), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
				if (P1.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P1.B1;
					b1->printBuilding();
				}
				if (P1.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P1.B2;
					b2->printBuilding();
				}
				if (P1.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P1.B3;
					b3->printBuilding();
				}
				if (P1.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P1.B4;
					b4->printBuilding();
				}
				if (P1.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P1.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
				{
					numberOfTurns++;
					break;
				}

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P1.B1;
					break;
				case 2: selectedBuilding = P1.B2;
					break;
				case 3:	selectedBuilding = P1.B3;
					break;
				case 4:	selectedBuilding = P1.B4;
					break;
				case 5:	selectedBuilding = P1.B5;
					break;
				}

				
					int amountNeeded = *selectedBuilding->getNumber();
					string typeNeeded = *selectedBuilding->getColor();

					//red = wood, green = sheep, yellow = wheat, gray = stone

					if (typeNeeded.compare("red") == 0)
					{
						typeNeeded = "wood";
						if (amountNeeded > resourceMarker[2])
						{
							cout << "Not enough wood to build this building." << endl;
							ableToBuild = false;
						}
						else
						{
							resourceMarker[2] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P1.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P1.B1 = NULL;
								break;
							case 2: P1.B2 = NULL;
								break;
							case 3:	 P1.B3 = NULL;
								break;
							case 4:	 P1.B4 = NULL;
								break;
							case 5:	 P1.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}
                        //GameStatObserver update
                        int * resourcePtr=resourceMarker;
                        statsSubj->setResourcesRemaining(resourcePtr);
                        vector<Player>* playerVect=new vector<Player>;
                        playerVect->push_back(P1);
                        playerVect->push_back(P2);
                        statsSubj->setPlayers(playerVect);
                        statsSubj->notify();

					}
					else if (typeNeeded.compare("yellow") == 0)
					{
						typeNeeded = "wheat";
						if (amountNeeded > resourceMarker[3])
						{
							cout << "Not enough wheat to build this building." << endl;
							ableToBuild = false;
						}
						else
						{
							resourceMarker[3] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P1.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P1.B1 = NULL;
								break;
							case 2: P1.B2 = NULL;
								break;
							case 3:	 P1.B3 = NULL;
								break;
							case 4:	 P1.B4 = NULL;
								break;
							case 5:	 P1.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}
					else if (typeNeeded.compare("green") == 0)
					{
						typeNeeded = "sheep";
						if (amountNeeded > resourceMarker[0])
						{
							cout << "Not enough sheep to build this building." << endl;
							ableToBuild = false;
						}
						else
						{
							resourceMarker[0] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P1.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P1.B1 = NULL;
								break;
							case 2: P1.B2 = NULL;
								break;
							case 3:	 P1.B3 = NULL;
								break;
							case 4:	 P1.B4 = NULL;
								break;
							case 5:	 P1.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}
					else if (typeNeeded.compare("gray") == 0)
					{
						typeNeeded = "stone";
						if (amountNeeded > resourceMarker[1])
						{
							cout << "Not enough stone to build this building." << endl;
							ableToBuild = false;
						}
						else
						{
							resourceMarker[1] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P1.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P1.B1 = NULL;
								break;
							case 2: P1.B2 = NULL;
								break;
							case 3:	 P1.B3 = NULL;
								break;
							case 4:	 P1.B4 = NULL;
								break;
							case 5:	 P1.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}

					

				}

				cout << endl;

				//remaining resources can be used by other players

				bool player2Extra = false;
				int player2ExtraTurn; 
				cout << "Would Player 2 like to use the remaining resources? Yes (1) or No (0):" << endl;
				cin >> player2ExtraTurn;
				if (player2ExtraTurn == 1)
				{
					player2Extra = true;
				}
				
				while (player2Extra)
				{

					player2Extra = false;

					cout << "These are your buildings (Player 2), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
					if (P2.B1 != NULL) {
						cout << "Building 1";
						Building* b1 = P2.B1;
						b1->printBuilding();
					}
					if (P2.B2 != NULL) {
						cout << "Building 2";
						Building* b2 = P2.B2;
						b2->printBuilding();
					}
					if (P2.B3 != NULL) {
						cout << "Building 3";
						Building* b3 = P2.B3;
						b3->printBuilding();
					}
					if (P2.B4 != NULL) {
						cout << "Building 4";
						Building* b4 = P2.B4;
						b4->printBuilding();
					}
					if (P2.B5 != NULL) {
						cout << "Building 5";
						Building* b5 = P2.B5;
						b5->printBuilding();
					}
					int buildingNumber;
					cin >> buildingNumber;

					if (buildingNumber == -1)
					{
						numberOfTurns++;
						break;
					}
						

					Building* selectedBuilding = new Building();

					switch (buildingNumber)
					{
					case 1: selectedBuilding = P2.B1;
						break;
					case 2: selectedBuilding = P2.B2;
						break;
					case 3:	selectedBuilding = P2.B3;
						break;
					case 4:	selectedBuilding = P2.B4;
						break;
					case 5:	selectedBuilding = P2.B5;
						break;
					}


					int amountNeeded = *selectedBuilding->getNumber();
					string typeNeeded = *selectedBuilding->getColor();

					//red = wood, green = sheep, yellow = wheat, gray = stone

					if (typeNeeded.compare("red") == 0)
					{
						typeNeeded = "wood";
						if (amountNeeded > resourceMarker[2])
						{
							cout << "Not enough wood to build this building." << endl;
							player2Extra = true;
						}
						else
						{
							resourceMarker[2] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P2.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P2.B1 = NULL;
								break;
							case 2: P2.B2 = NULL;
								break;
							case 3:	 P2.B3 = NULL;
								break;
							case 4:	 P2.B4 = NULL;
								break;
							case 5:	 P2.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}
					else if (typeNeeded.compare("yellow") == 0)
					{
						typeNeeded = "wheat";
						if (amountNeeded > resourceMarker[3])
						{
							cout << "Not enough wheat to build this building." << endl;
							player2Extra = true;
						}
						else
						{
							resourceMarker[3] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P2.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P2.B1 = NULL;
								break;
							case 2: P2.B2 = NULL;
								break;
							case 3:	 P2.B3 = NULL;
								break;
							case 4:	 P2.B4 = NULL;
								break;
							case 5:	 P2.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}
					else if (typeNeeded.compare("green") == 0)
					{
						typeNeeded = "sheep";
						if (amountNeeded > resourceMarker[0])
						{
							cout << "Not enough sheep to build this building." << endl;
							player2Extra = true;
						}
						else
						{
							resourceMarker[0] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P2.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P2.B1 = NULL;
								break;
							case 2: P2.B2 = NULL;
								break;
							case 3:	 P2.B3 = NULL;
								break;
							case 4:	 P2.B4 = NULL;
								break;
							case 5:	 P2.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}
					else if (typeNeeded.compare("gray") == 0)
					{
						typeNeeded = "stone";
						if (amountNeeded > resourceMarker[1])
						{
							cout << "Not enough stone to build this building." << endl;
							player2Extra = true;
						}
						else
						{
							resourceMarker[1] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P2.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P2.B1 = NULL;
								break;
							case 2: P2.B2 = NULL;
								break;
							case 3:	 P2.B3 = NULL;
								break;
							case 4:	 P2.B4 = NULL;
								break;
							case 5:	 P2.B5 = NULL;
								break;
							}
							
							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}

					

				}
				
				int zeroResources = 0;
				for (int i = 0; i < 3; i++)
				{
					if (resourcesGathered[i] == 0)
					{
						zeroResources++;
					}
				}

				for (int i = 0; i < zeroResources; i++)
				{
					P1.DrawBuilding(buildingDeck);
				}

				//after all players build/pass

				resourceMarker[0] = 0;
				resourceMarker[1] = 0;
				resourceMarker[2] = 0;
				resourceMarker[3] = 0;


				P1.DrawHarvestTile(harvestTileDeck);
				numberOfTurns++;

				// ask if the other players want to build with remaining resources or pass

				player2Turn = true;
				player1Turn = false;

			}
			if (player2Turn)
			{
				int harvestTileNumber = 0;
				int tilePlacement;

				cout << "Player 2 turn: " << endl;
				//player 2 actions
				
				cout << "Select a harvest tile: " << endl;
				cout << "Harvest Tile 1: ";
				HarvestTile* ht = P2.HT1;
				ht->printTile();
				cout << "Harvest Tile 2: ";
				HarvestTile* ht2 = P2.HT2;
				ht2->printTile();
				cout << "Enter 1 or 2:" << endl;
				cin >> harvestTileNumber;
				cout << "Which position would you like to place the tile?" << endl;
				cin >> tilePlacement;
				if (harvestTileNumber == 1)
				{
					int* harvestTileArray = P2.HT1->convertHT(*P2.HT1);
					resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
					P2.HT1 = NULL;
				}
				else if (harvestTileNumber == 2)
				{
					int* harvestTileArray = P2.HT2->convertHT(*P2.HT2);
					resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
					P2.HT2 = NULL;
				}

				std::cout << resourcesGathered[0] << " Sheep " << resourcesGathered[1] << " Stone " << resourcesGathered[2] << " Wood " << resourcesGathered[3] << " Wheat " << endl << endl;

				resourceMarker[0] = resourcesGathered[0];
				resourceMarker[1] = resourcesGathered[1];
				resourceMarker[2] = resourcesGathered[2];
				resourceMarker[3] = resourcesGathered[3];

				


				//P2.BuildVillage(); //player 2 builds buildings ontop of the village board
				//access the buildings in player 2's hand
				//print out the buildings, let player 2 choose which building to build
				//choose where to place the building
				//subtract the resources used from resource marker
				

				//remaining resources can be used by other players
				//after all players build/pass

				bool ableToBuild = false;

				while (!ableToBuild)
				{

					ableToBuild = true;

					cout << "These are your buildings (Player 2), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
					if (P2.B1 != NULL) {
						cout << "Building 1";
						Building* b1 = P2.B1;
						b1->printBuilding();
					}
					if (P2.B2 != NULL) {
						cout << "Building 2";
						Building* b2 = P2.B2;
						b2->printBuilding();
					}
					if (P2.B3 != NULL) {
						cout << "Building 3";
						Building* b3 = P2.B3;
						b3->printBuilding();
					}
					if (P2.B4 != NULL) {
						cout << "Building 4";
						Building* b4 = P2.B4;
						b4->printBuilding();
					}
					if (P2.B5 != NULL) {
						cout << "Building 5";
						Building* b5 = P2.B5;
						b5->printBuilding();
					}
					int buildingNumber;
					cin >> buildingNumber;

					if (buildingNumber == -1)
					{
						numberOfTurns++;
						break;
					}

					Building* selectedBuilding = new Building();

					switch (buildingNumber)
					{
					case 1: selectedBuilding = P2.B1;
						break;
					case 2: selectedBuilding = P2.B2;
						break;
					case 3:	selectedBuilding = P2.B3;
						break;
					case 4:	selectedBuilding = P2.B4;
						break;
					case 5:	selectedBuilding = P2.B5;
						break;
					}


					int amountNeeded = *selectedBuilding->getNumber();
					string typeNeeded = *selectedBuilding->getColor();

					//red = wood, green = sheep, yellow = wheat, gray = stone

					if (typeNeeded.compare("red") == 0)
					{
						typeNeeded = "wood";
						if (amountNeeded > resourceMarker[2])
						{
							cout << "Not enough wood to build this building." << endl;
							ableToBuild = false;
						}
						else
						{
							resourceMarker[2] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P2.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P2.B1 = NULL;
								break;
							case 2: P2.B2 = NULL;
								break;
							case 3:	 P2.B3 = NULL;
								break;
							case 4:	 P2.B4 = NULL;
								break;
							case 5:	 P2.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}
					else if (typeNeeded.compare("yellow") == 0)
					{
						typeNeeded = "wheat";
						if (amountNeeded > resourceMarker[3])
						{
							cout << "Not enough wheat to build this building." << endl;
							ableToBuild = false;
						}
						else
						{
							resourceMarker[3] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P2.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P2.B1 = NULL;
								break;
							case 2: P2.B2 = NULL;
								break;
							case 3:	 P2.B3 = NULL;
								break;
							case 4:	 P2.B4 = NULL;
								break;
							case 5:	 P2.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}
					else if (typeNeeded.compare("green") == 0)
					{
						typeNeeded = "sheep";
						if (amountNeeded > resourceMarker[0])
						{
							cout << "Not enough sheep to build this building." << endl;
							ableToBuild = false;
						}
						else
						{
							resourceMarker[0] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P2.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P2.B1 = NULL;
								break;
							case 2: P2.B2 = NULL;
								break;
							case 3:	 P2.B3 = NULL;
								break;
							case 4:	 P2.B4 = NULL;
								break;
							case 5:	 P2.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}
					else if (typeNeeded.compare("gray") == 0)
					{
						typeNeeded = "stone";
						if (amountNeeded > resourceMarker[1])
						{
							cout << "Not enough stone to build this building." << endl;
							ableToBuild = false;
						}
						else
						{
							resourceMarker[1] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P2.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P2.B1 = NULL;
								break;
							case 2: P2.B2 = NULL;
								break;
							case 3:	 P2.B3 = NULL;
								break;
							case 4:	 P2.B4 = NULL;
								break;
							case 5:	 P2.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}



				}

				cout << endl;

				//remaining resources can be used by other players

				bool player1Extra = false;
				int player1ExtraTurn;
				cout << "Would Player 1 like to use the remaining resources? Yes (1) or No (0):" << endl;
				cin >> player1ExtraTurn;
				if (player1ExtraTurn == 1)
				{
					player1Extra = true;
				}

				while (player1Extra)
				{

					player1Extra = false;
						cout << "These are your buildings (Player 1), Select a building from 1 to 5: Type -1 if you want to pass." << endl;
						if (P1.B1 != NULL) {
							cout << "Building 1";
							Building* b1 = P1.B1;
							b1->printBuilding();
						}
						if (P1.B2 != NULL) {
							cout << "Building 2";
							Building* b2 = P1.B2;
							b2->printBuilding();
						}
						if (P1.B3 != NULL) {
							cout << "Building 3";
							Building* b3 = P1.B3;
							b3->printBuilding();
						}
						if (P1.B4 != NULL) {
							cout << "Building 4";
							Building* b4 = P1.B4;
							b4->printBuilding();
						}
						if (P1.B5 != NULL) {
							cout << "Building 5";
							Building* b5 = P1.B5;
							b5->printBuilding();
						}

					int buildingNumber;
					cin >> buildingNumber;

					if (buildingNumber == -1)
						break;

					Building* selectedBuilding = new Building();

					switch (buildingNumber)
					{
					case 1: selectedBuilding = P1.B1;
						break;
					case 2: selectedBuilding = P1.B2;
						break;
					case 3:	selectedBuilding = P1.B3;
						break;
					case 4:	selectedBuilding = P1.B4;
						break;
					case 5:	selectedBuilding = P1.B5;
						break;
					}


					int amountNeeded = *selectedBuilding->getNumber();
					string typeNeeded = *selectedBuilding->getColor();

					//red = wood, green = sheep, yellow = wheat, gray = stone

					if (typeNeeded.compare("red") == 0)
					{
						typeNeeded = "wood";
						if (amountNeeded > resourceMarker[2])
						{
							cout << "Not enough wood to build this building." << endl;
							player1Extra = true;
						}
						else
						{
							resourceMarker[2] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P1.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P1.B1 = NULL;
								break;
							case 2: P1.B2 = NULL;
								break;
							case 3:	 P1.B3 = NULL;
								break;
							case 4:	 P1.B4 = NULL;
								break;
							case 5:	 P1.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}
					else if (typeNeeded.compare("yellow") == 0)
					{
						typeNeeded = "wheat";
						if (amountNeeded > resourceMarker[3])
						{
							cout << "Not enough wheat to build this building." << endl;
							player1Extra = true;
						}
						else
						{
							resourceMarker[3] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P1.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P1.B1 = NULL;
								break;
							case 2: P1.B2 = NULL;
								break;
							case 3:	 P1.B3 = NULL;
								break;
							case 4:	 P1.B4 = NULL;
								break;
							case 5:	 P1.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}
					else if (typeNeeded.compare("green") == 0)
					{
						typeNeeded = "sheep";
						if (amountNeeded > resourceMarker[0])
						{
							cout << "Not enough sheep to build this building." << endl;
							player1Extra = true;
						}
						else
						{
							resourceMarker[0] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P1.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P1.B1 = NULL;
								break;
							case 2: P1.B2 = NULL;
								break;
							case 3:	 P1.B3 = NULL;
								break;
							case 4:	 P1.B4 = NULL;
								break;
							case 5:	 P1.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}
					else if (typeNeeded.compare("gray") == 0)
					{
						typeNeeded = "stone";
						if (amountNeeded > resourceMarker[1])
						{
							cout << "Not enough stone to build this building." << endl;
							player1Extra = true;
						}
						else
						{
							resourceMarker[1] -= amountNeeded;
							int whichSide;
							bool faceUp;
							cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
							cin >> whichSide;

							if (whichSide == 0)
							{
								faceUp = true;
							}
							else if (whichSide)
							{
								faceUp = false;
							}

							P1.VillageMap->buildVillage(selectedBuilding, faceUp);
							selectedBuilding = NULL;
							switch (buildingNumber)
							{
							case 1:  P1.B1 = NULL;
								break;
							case 2: P1.B2 = NULL;
								break;
							case 3:	 P1.B3 = NULL;
								break;
							case 4:	 P1.B4 = NULL;
								break;
							case 5:	 P1.B5 = NULL;
								break;
							}

							cout << endl;
							cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
						}

					}



				}

				int zeroResources = 0;
				for (int i = 0; i < 3; i++)
				{
					if (resourcesGathered[i] == 0)
					{
						zeroResources++;
					}
				}

				for (int i = 0; i < zeroResources; i++)
				{
					P2.DrawBuilding(buildingDeck);
				}

				resourceMarker[0] = 0;
				resourceMarker[1] = 0;
				resourceMarker[2] = 0;
				resourceMarker[3] = 0;


				P2.DrawHarvestTile(harvestTileDeck);

				numberOfTurns++;
				player1Turn = true;
				player2Turn = false;
				
			}
		}

	}
else if (numberOfPlayers == 3)
	{
		numberOfTurns = 30;

		Player P1 = Player();
		int player1ID = P1.getCurrentID();
		P1.setPlayerID(player1ID);
		cout << endl;
		cout << "Player 1 ID: ";
		cout << P1.getPlayerID() << endl << endl;

		P1.VillageMap = new VGMaps("Gilford");

		P1.DrawHarvestTile(harvestTileDeck);
		P1.DrawHarvestTile(harvestTileDeck);


		P1.DrawBuilding(buildingDeck);
		P1.DrawBuilding(buildingDeck);
		P1.DrawBuilding(buildingDeck);
		P1.DrawBuilding(buildingDeck);
		P1.DrawBuilding(buildingDeck);

		cout << endl;

		Player P2 = Player();
		int player2ID = P2.getCurrentID();
		P2.setPlayerID(player2ID);
		cout << "Player 2 ID: ";
		cout << P2.getPlayerID() << endl << endl;

		P2.VillageMap = new VGMaps("Milford");

		P2.DrawHarvestTile(harvestTileDeck);
		P2.DrawHarvestTile(harvestTileDeck);

		P2.DrawBuilding(buildingDeck);
		P2.DrawBuilding(buildingDeck);
		P2.DrawBuilding(buildingDeck);
		P2.DrawBuilding(buildingDeck);
		P2.DrawBuilding(buildingDeck);

		cout << endl;
		Player P3 = Player();
		int player3ID = P3.getCurrentID();
		P3.setPlayerID(player3ID);
		cout << "Player 3 ID: ";
		cout << P3.getPlayerID() << endl;
		P3.VillageMap = new VGMaps("Pilford");

		P3.DrawHarvestTile(harvestTileDeck);
		P3.DrawHarvestTile(harvestTileDeck);

		P3.DrawBuilding(buildingDeck);
		P3.DrawBuilding(buildingDeck);
		P3.DrawBuilding(buildingDeck);
		P3.DrawBuilding(buildingDeck);
		P3.DrawBuilding(buildingDeck);
		
		
		
		bool gameDoneFlag = false;
		int turnsTaken = 0;

		bool player1Turn = true;
		bool player2Turn = false;
		bool player3Turn = false;
		bool player4Turn = false;

		
		while (!gameDoneFlag)
		{
			if (turnsTaken == 30)
			{
				gameDoneFlag = true;
			}

		if (player1Turn)
		{
			int harvestTileNumber = 0;
			int tilePlacement;

			//player 1 actions

			cout << "Player 1 turn: " << endl;

			cout << "Select a harvest tile: " << endl;
			cout << "Harvest Tile 1: ";
			HarvestTile* ht = P1.HT1;
			ht->printTile();
			cout << "Harvest Tile 2: ";
			HarvestTile* ht2 = P1.HT2;
			ht2->printTile();
			cout << "Enter 1 or 2:" << endl;
			cin >> harvestTileNumber;
			cout << "Which position would you like to place the tile?" << endl;
			cin >> tilePlacement;
			if (harvestTileNumber == 1)
			{
				int* harvestTileArray = P1.HT1->convertHT(*P1.HT1);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P1.HT1 = NULL;
			}
			else if (harvestTileNumber == 2)
			{
				int* harvestTileArray = P1.HT2->convertHT(*P1.HT2);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P1.HT2 = NULL;
			}

			std::cout << resourcesGathered[0] << " Sheep " << resourcesGathered[1] << " Stone " << resourcesGathered[2] << " Wood " << resourcesGathered[3] << " Wheat " << endl << endl;

			resourceMarker[0] = resourcesGathered[0];
			resourceMarker[1] = resourcesGathered[1];
			resourceMarker[2] = resourcesGathered[2];
			resourceMarker[3] = resourcesGathered[3];

			//P1.BuildVillage(); //player 1 builds buildings ontop of the village board
			//access the buildings in player 1's hand
			//print out the buildings, let player 1 choose which building to build
			//choose where to place the building
			//subtract the resources used from resource marker


			bool ableToBuild = false;

			while (!ableToBuild)
			{

				ableToBuild = true;

				cout << "These are your buildings (Player 1), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
			
				
				if (P1.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P1.B1;
					b1->printBuilding();
				}
				if (P1.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P1.B2;
					b2->printBuilding();
				}
				if (P1.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P1.B3;
					b3->printBuilding();
				}
				if (P1.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P1.B4;
					b4->printBuilding();
				}
				if (P1.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P1.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;
				
				Building* selectedBuilding = new Building();
				
				if (buildingNumber == -1)
					break;

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P1.B1;
					break;
				case 2: selectedBuilding = P1.B2;
					break;
				case 3:	selectedBuilding = P1.B3;
					break;
				case 4:	selectedBuilding = P1.B4;
					break;
				case 5:	selectedBuilding = P1.B5;
					break;
				
				}

				
				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}

				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}

				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}

				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}

				}



			}

			cout << endl;

			//remaining resources can be used by other players

			bool player2Extra = false;
			int player2ExtraTurn;
			cout << "Would Player 2 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player2ExtraTurn;
			if (player2ExtraTurn == 1)
			{
				player2Extra = true;
			}

			while (player2Extra)
			{

				player2Extra = false;

				cout << "These are your buildings (Player 2), Select a building from 1 to 5, Enter -1 if you want to pass:" << endl;
				if (P2.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P2.B1;
					b1->printBuilding();
				}
				if (P2.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P2.B2;
					b2->printBuilding();
				}
				if (P2.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P2.B3;
					b3->printBuilding();
				}
				if (P2.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P2.B4;
					b4->printBuilding();
				}
				if (P2.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P2.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P2.B1;
					break;
				case 2: selectedBuilding = P2.B2;
					break;
				case 3:	selectedBuilding = P2.B3;
					break;
				case 4:	selectedBuilding = P2.B4;
					break;
				case 5:	selectedBuilding = P2.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}bool player3Extra = false;
			int player3ExtraTurn;
			cout << "Would Player 3 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player3ExtraTurn;
			if (player3ExtraTurn == 1)
			{
				player3Extra = true;
			}

			while (player3Extra)
			{

				player3Extra = false;

				cout << "These are your buildings (Player 2), Select a building from 1 to 5, Enter -1 if you want to pass:" << endl;
				if (P3.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P3.B1;
					b1->printBuilding();
				}
				if (P3.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P3.B2;
					b2->printBuilding();
				}
				if (P3.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P3.B3;
					b3->printBuilding();
				}
				if (P3.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P3.B4;
					b4->printBuilding();
				}
				if (P3.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P3.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P3.B1;
					break;
				case 2: selectedBuilding = P3.B2;
					break;
				case 3:	selectedBuilding = P3.B3;
					break;
				case 4:	selectedBuilding = P3.B4;
					break;
				case 5:	selectedBuilding = P3.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}

			int zeroResources = 0;
			for (int i = 0; i < 3; i++)
			{
				if (resourcesGathered[i] == 0)
				{
					zeroResources++;
				}
			}

			for (int i = 0; i < zeroResources; i++)
			{
				P1.DrawBuilding(buildingDeck);
			}

			//after all players build/pass

			resourceMarker[0] = 0;
			resourceMarker[1] = 0;
			resourceMarker[2] = 0;
			resourceMarker[3] = 0;


			P1.DrawHarvestTile(harvestTileDeck);
			numberOfTurns++;

			// ask if the other players want to build with remaining resources or pass

			player2Turn = true;
			player1Turn = false;
			player3Turn = false;

		}
		if (player2Turn)
		{
			int harvestTileNumber = 0;
			int tilePlacement;

			cout << "Player 2 turn: " << endl;
			//player 2 actions

			cout << "Select a harvest tile: " << endl;
			cout << "Harvest Tile 1: ";
			HarvestTile* ht = P2.HT1;
			ht->printTile();
			cout << "Harvest Tile 2: ";
			HarvestTile* ht2 = P2.HT2;
			ht2->printTile();
			cout << "Enter 1 or 2:" << endl;
			cin >> harvestTileNumber;
			cout << "Which position would you like to place the tile?" << endl;
			cin >> tilePlacement;
			if (harvestTileNumber == 1)
			{
				int* harvestTileArray = P2.HT1->convertHT(*P2.HT1);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P2.HT1 = NULL;
			}
			else if (harvestTileNumber == 2)
			{
				int* harvestTileArray = P2.HT2->convertHT(*P2.HT2);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P2.HT2 = NULL;
			}

			std::cout << resourcesGathered[0] << " Sheep " << resourcesGathered[1] << " Stone " << resourcesGathered[2] << " Wood " << resourcesGathered[3] << " Wheat " << endl << endl;

			resourceMarker[0] = resourcesGathered[0];
			resourceMarker[1] = resourcesGathered[1];
			resourceMarker[2] = resourcesGathered[2];
			resourceMarker[3] = resourcesGathered[3];



			//P2.BuildVillage(); //player 2 builds buildings ontop of the village board
			//access the buildings in player 2's hand
			//print out the buildings, let player 2 choose which building to build
			//choose where to place the building
			//subtract the resources used from resource marker


			//remaining resources can be used by other players
			//after all players build/pass

			bool ableToBuild = false;

			while (!ableToBuild)
			{

				ableToBuild = true;

				cout << "These are your buildings (Player 2), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
				if (P2.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P2.B1;
					b1->printBuilding();
				}
				if (P2.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P2.B2;
					b2->printBuilding();
				}
				if (P2.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P2.B3;
					b3->printBuilding();
				}
				if (P2.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P2.B4;
					b4->printBuilding();
				}
				if (P2.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P2.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				Building* selectedBuilding = new Building();
				if (buildingNumber == -1)
					break;
				switch (buildingNumber)
				{
				case 1: selectedBuilding = P2.B1;
					break;
				case 2: selectedBuilding = P2.B2;
					break;
				case 3:	selectedBuilding = P2.B3;
					break;
				case 4:	selectedBuilding = P2.B4;
					break;
				case 5:	selectedBuilding = P2.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}

			cout << endl;

			//remaining resources can be used by other players

			bool player1Extra = false;
			int player1ExtraTurn;
			cout << "Would Player 1 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player1ExtraTurn;
			if (player1ExtraTurn == 1)
			{
				player1Extra = true;
			}

			while (player1Extra)
			{

				player1Extra = false;
				cout << "These are your buildings (Player 1), Select a building from 1 to 5: Type -1 if you want to pass." << endl;
				if (P1.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P1.B1;
					b1->printBuilding();
				}
				if (P1.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P1.B2;
					b2->printBuilding();
				}
				if (P1.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P1.B3;
					b3->printBuilding();
				}
				if (P1.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P1.B4;
					b4->printBuilding();
				}
				if (P1.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P1.B5;
					b5->printBuilding();
				}

				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P1.B1;
					break;
				case 2: selectedBuilding = P1.B2;
					break;
				case 3:	selectedBuilding = P1.B3;
					break;
				case 4:	selectedBuilding = P1.B4;
					break;
				case 5:	selectedBuilding = P1.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}
			bool player3Extra = false;
			int player3ExtraTurn;
			cout << "Would Player 3 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player3ExtraTurn;
			if (player3ExtraTurn == 1)
			{
				player3Extra = true;
			}

			while (player3Extra)
			{

				player3Extra = false;
				cout << "These are your buildings (Player 3), Select a building from 1 to 5: Type -1 if you want to pass." << endl;
				if (P3.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P3.B1;
					b1->printBuilding();
				}
				if (P3.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P3.B2;
					b2->printBuilding();
				}
				if (P3.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P3.B3;
					b3->printBuilding();
				}
				if (P3.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P3.B4;
					b4->printBuilding();
				}
				if (P3.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P3.B5;
					b5->printBuilding();
				}

				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P3.B1;
					break;
				case 2: selectedBuilding = P3.B2;
					break;
				case 3:	selectedBuilding = P3.B3;
					break;
				case 4:	selectedBuilding = P3.B4;
					break;
				case 5:	selectedBuilding = P3.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}

			int zeroResources = 0;
			for (int i = 0; i < 3; i++)
			{
				if (resourcesGathered[i] == 0)
				{
					zeroResources++;
				}
			}

			for (int i = 0; i < zeroResources; i++)
			{
				P2.DrawBuilding(buildingDeck);
			}

			resourceMarker[0] = 0;
			resourceMarker[1] = 0;
			resourceMarker[2] = 0;
			resourceMarker[3] = 0;


			P2.DrawHarvestTile(harvestTileDeck);

			numberOfTurns++;
			player3Turn = true;
			player1Turn = false;
			player2Turn = false;
			
		}if (player3Turn)
		{
			int harvestTileNumber = 0;
			int tilePlacement;

			//player 3 actions

			cout << "Player 3 turn: " << endl;

			cout << "Select a harvest tile: " << endl;
			cout << "Harvest Tile 1: ";
			HarvestTile* ht = P3.HT1;
			ht->printTile();
			cout << "Harvest Tile 2: ";
			HarvestTile* ht2 = P3.HT2;
			ht2->printTile();
			cout << "Enter 1 or 2:" << endl;
			cin >> harvestTileNumber;
			cout << "Which position would you like to place the tile?" << endl;
			cin >> tilePlacement;
			if (harvestTileNumber == 1)
			{
				int* harvestTileArray = P3.HT1->convertHT(*P3.HT1);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P3.HT1 = NULL;
			}
			else if (harvestTileNumber == 2)
			{
				int* harvestTileArray = P3.HT2->convertHT(*P3.HT2);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P3.HT2 = NULL;
			}

			std::cout << resourcesGathered[0] << " Sheep " << resourcesGathered[1] << " Stone " << resourcesGathered[2] << " Wood " << resourcesGathered[3] << " Wheat " << endl << endl;

			resourceMarker[0] = resourcesGathered[0];
			resourceMarker[1] = resourcesGathered[1];
			resourceMarker[2] = resourcesGathered[2];
			resourceMarker[3] = resourcesGathered[3];

			//P1.BuildVillage(); //player 1 builds buildings ontop of the village board
			//access the buildings in player 1's hand
			//print out the buildings, let player 1 choose which building to build
			//choose where to place the building
			//subtract the resources used from resource marker


			bool ableToBuild = false;

			while (!ableToBuild)
			{

				ableToBuild = true;

				cout << "These are your buildings (Player 3), Select a building from 1 to 5, Enter -1 if you want to pass " << endl;
				if (P3.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P3.B1;
					b1->printBuilding();
				}
				if (P3.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P3.B2;
					b2->printBuilding();
				}
				if (P3.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P3.B3;
					b3->printBuilding();
				}
				if (P3.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P3.B4;
					b4->printBuilding();
				}
				if (P3.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P3.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				Building* selectedBuilding = new Building();
				if (buildingNumber == -1)
					break;
				switch (buildingNumber)
				{
				case 1: selectedBuilding = P3.B1;
					break;
				case 2: selectedBuilding = P3.B2;
					break;
				case 3:	selectedBuilding = P3.B3;
					break;
				case 4:	selectedBuilding = P3.B4;
					break;
				case 5:	selectedBuilding = P3.B5;
					break;
				}

				
				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}

			cout << endl;
			bool player1Extra = false;
			int player1ExtraTurn;
			cout << "Would Player 1 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player1ExtraTurn;
			if (player1ExtraTurn == 1)
			{
				player1Extra = true;
			}

			while (player1Extra)
			{

				player1Extra = false;

				cout << "These are your buildings (Player 1), Select a building from 1 to 5: Type -1 if you want to pass." << endl;
				if (P1.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P1.B1;
					b1->printBuilding();
				}
				if (P1.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P1.B2;
					b2->printBuilding();
				}
				if (P1.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P1.B3;
					b3->printBuilding();
				}
				if (P1.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P1.B4;
					b4->printBuilding();
				}
				if (P1.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P1.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P1.B1;
					break;
				case 2: selectedBuilding = P1.B2;
					break;
				case 3:	selectedBuilding = P1.B3;
					break;
				case 4:	selectedBuilding = P1.B4;
					break;
				case 5:	selectedBuilding = P1.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}
			//remaining resources can be used by other players

			bool player2Extra = false;
			int player2ExtraTurn;
			cout << "Would Player 2 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player2ExtraTurn;
			if (player2ExtraTurn == 1)
			{
				player2Extra = true;
			}

			while (player2Extra)
			{

				player2Extra = false;

				cout << "These are your buildings (Player 2), Select a building from 1 to 5: Type -1 if you want to pass." << endl;
				if (P2.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P2.B1;
					b1->printBuilding();
				}
				if (P2.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P2.B2;
					b2->printBuilding();
				}
				if (P2.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P2.B3;
					b3->printBuilding();
				}
				if (P2.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P2.B4;
					b4->printBuilding();
				}
				if (P2.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P2.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P2.B1;
					break;
				case 2: selectedBuilding = P2.B2;
					break;
				case 3:	selectedBuilding = P2.B3;
					break;
				case 4:	selectedBuilding = P2.B4;
					break;
				case 5:	selectedBuilding = P2.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
			}

			int zeroResources = 0;
			for (int i = 0; i < 3; i++)
			{
				if (resourcesGathered[i] == 0)
				{
					zeroResources++;
				}
			}

			for (int i = 0; i < zeroResources; i++)
			{
				P3.DrawBuilding(buildingDeck);
			}

			//after all players build/pass

			resourceMarker[0] = 0;
			resourceMarker[1] = 0;
			resourceMarker[2] = 0;
			resourceMarker[3] = 0;


			P3.DrawHarvestTile(harvestTileDeck);
			numberOfTurns++;

			// ask if the other players want to build with remaining resources or pass
			player1Turn = true;
			player2Turn = false;
			player3Turn = false;

		}
		}
		}
		else if (numberOfPlayers == 4)
	{
	numberOfTurns = 40;

	Player P1 = Player();
	int player1ID = P1.getCurrentID();
	P1.setPlayerID(player1ID);
	cout << endl;
	cout << "Player 1 ID: ";
	cout << P1.getPlayerID() << endl << endl;

	P1.VillageMap = new VGMaps("Gilford");

	P1.DrawHarvestTile(harvestTileDeck);
	P1.DrawHarvestTile(harvestTileDeck);


	P1.DrawBuilding(buildingDeck);
	P1.DrawBuilding(buildingDeck);
	P1.DrawBuilding(buildingDeck);
	P1.DrawBuilding(buildingDeck);
	P1.DrawBuilding(buildingDeck);

	cout << endl;

	Player P2 = Player();
	int player2ID = P2.getCurrentID();
	P2.setPlayerID(player2ID);
	cout << "Player 2 ID: ";
	cout << P2.getPlayerID() << endl << endl;

	P2.VillageMap = new VGMaps("Milford");

	P2.DrawHarvestTile(harvestTileDeck);
	P2.DrawHarvestTile(harvestTileDeck);

	P2.DrawBuilding(buildingDeck);
	P2.DrawBuilding(buildingDeck);
	P2.DrawBuilding(buildingDeck);
	P2.DrawBuilding(buildingDeck);
	P2.DrawBuilding(buildingDeck);

	cout << endl;
	Player P3 = Player();
	int player3ID = P3.getCurrentID();
	P3.setPlayerID(player3ID);
	cout << "Player 3 ID: ";
	cout << P3.getPlayerID() << endl;
	P3.VillageMap = new VGMaps("Pilford");

	P3.DrawHarvestTile(harvestTileDeck);
	P3.DrawHarvestTile(harvestTileDeck);

	P3.DrawBuilding(buildingDeck);
	P3.DrawBuilding(buildingDeck);
	P3.DrawBuilding(buildingDeck);
	P3.DrawBuilding(buildingDeck);
	P3.DrawBuilding(buildingDeck);

	cout << endl;


	Player P4 = Player();
	int player4ID = P4.getCurrentID();
	P4.setPlayerID(player1ID);
	cout << endl;
	cout << "Player 4 ID: ";
	cout << P4.getPlayerID() << endl << endl;

	P4.VillageMap = new VGMaps("Bilford");

	P4.DrawHarvestTile(harvestTileDeck);
	P4.DrawHarvestTile(harvestTileDeck);


	P4.DrawBuilding(buildingDeck);
	P4.DrawBuilding(buildingDeck);
	P4.DrawBuilding(buildingDeck);
	P4.DrawBuilding(buildingDeck);
	P4.DrawBuilding(buildingDeck);

	cout << endl;



	bool gameDoneFlag = false;
	int turnsTaken = 0;

	bool player1Turn = true;
	bool player2Turn = false;
	bool player3Turn = false;
	bool player4Turn = false;


	while (!gameDoneFlag)
	{
		if (turnsTaken == 40)
		{
			gameDoneFlag = true;
		}

		if (player1Turn)
		{
			int harvestTileNumber = 0;
			int tilePlacement;

			//player 1 actions

			cout << "Player 1 turn: " << endl;

			cout << "Select a harvest tile: " << endl;
			cout << "Harvest Tile 1: ";
			HarvestTile* ht = P1.HT1;
			ht->printTile();
			cout << "Harvest Tile 2: ";
			HarvestTile* ht2 = P1.HT2;
			ht2->printTile();
			cout << "Enter 1 or 2:" << endl;
			cin >> harvestTileNumber;
			cout << "Which position would you like to place the tile?" << endl;
			cin >> tilePlacement;
			if (harvestTileNumber == 1)
			{
				int* harvestTileArray = P1.HT1->convertHT(*P1.HT1);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P1.HT1 = NULL;
			}
			else if (harvestTileNumber == 2)
			{
				int* harvestTileArray = P1.HT2->convertHT(*P1.HT2);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P1.HT2 = NULL;
			}

			std::cout << resourcesGathered[0] << " Sheep " << resourcesGathered[1] << " Stone " << resourcesGathered[2] << " Wood " << resourcesGathered[3] << " Wheat " << endl << endl;

			resourceMarker[0] = resourcesGathered[0];
			resourceMarker[1] = resourcesGathered[1];
			resourceMarker[2] = resourcesGathered[2];
			resourceMarker[3] = resourcesGathered[3];

			//P1.BuildVillage(); //player 1 builds buildings ontop of the village board
			//access the buildings in player 1's hand
			//print out the buildings, let player 1 choose which building to build
			//choose where to place the building
			//subtract the resources used from resource marker


			bool ableToBuild = false;

			while (!ableToBuild)
			{

				ableToBuild = true;

				cout << "These are your buildings (Player 1), Select a building from 1 to 5, Enter -1 if you want to pass:  " << endl;



				if (P1.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P1.B1;
					b1->printBuilding();
				}
				if (P1.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P1.B2;
					b2->printBuilding();
				}
				if (P1.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P1.B3;
					b3->printBuilding();
				}
				if (P1.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P1.B4;
					b4->printBuilding();
				}
				if (P1.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P1.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				Building* selectedBuilding = new Building();

				if (buildingNumber == -1)
					break;

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P1.B1;
					break;
				case 2: selectedBuilding = P1.B2;
					break;
				case 3:	selectedBuilding = P1.B3;
					break;
				case 4:	selectedBuilding = P1.B4;
					break;
				case 5:	selectedBuilding = P1.B5;
					break;

				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}

			cout << endl;

			//remaining resources can be used by other players

			bool player2Extra = false;
			int player2ExtraTurn;
			cout << "Would Player 2 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player2ExtraTurn;
			if (player2ExtraTurn == 1)
			{
				player2Extra = true;
			}

			while (player2Extra)
			{

				player2Extra = false;

				cout << "These are your buildings (Player 2), Select a building from 1 to 5: Type -1 if you want to pass." << endl;
				if (P2.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P2.B1;
					b1->printBuilding();
				}
				if (P2.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P2.B2;
					b2->printBuilding();
				}
				if (P2.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P2.B3;
					b3->printBuilding();
				}
				if (P2.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P2.B4;
					b4->printBuilding();
				}
				if (P2.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P2.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P2.B1;
					break;
				case 2: selectedBuilding = P2.B2;
					break;
				case 3:	selectedBuilding = P2.B3;
					break;
				case 4:	selectedBuilding = P2.B4;
					break;
				case 5:	selectedBuilding = P2.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}
			bool player3Extra = false;
			int player3ExtraTurn;
			cout << "Would Player 3 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player3ExtraTurn;
			if (player3ExtraTurn == 1)
			{
				player3Extra = true;
			}

			while (player3Extra)
			{

				player3Extra = false;

				cout << "These are your buildings (Player 2), Select a building from 1 to 5: Type -1 if you want to pass." << endl;
				if (P3.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P3.B1;
					b1->printBuilding();
				}
				if (P3.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P3.B2;
					b2->printBuilding();
				}
				if (P3.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P3.B3;
					b3->printBuilding();
				}
				if (P3.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P3.B4;
					b4->printBuilding();
				}
				if (P3.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P3.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P3.B1;
					break;
				case 2: selectedBuilding = P3.B2;
					break;
				case 3:	selectedBuilding = P3.B3;
					break;
				case 4:	selectedBuilding = P3.B4;
					break;
				case 5:	selectedBuilding = P3.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
			}

			bool player4Extra = false;
			int player4ExtraTurn;
			cout << "Would Player 4 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player4ExtraTurn;
			if (player4ExtraTurn == 1)
			{
				player4Extra = true;
			}

			while (player4Extra)
			{

				player4Extra = false;

				cout << "These are your buildings (Player 4), Select a building from 1 to 5: Type -1 if you want to pass." << endl;
				if (P4.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P4.B1;
					b1->printBuilding();
				}
				if (P4.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P4.B2;
					b2->printBuilding();
				}
				if (P4.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P4.B3;
					b3->printBuilding();
				}
				if (P4.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P4.B4;
					b4->printBuilding();
				}
				if (P4.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P4.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P4.B1;
					break;
				case 2: selectedBuilding = P4.B2;
					break;
				case 3:	selectedBuilding = P4.B3;
					break;
				case 4:	selectedBuilding = P4.B4;
					break;
				case 5:	selectedBuilding = P4.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
			}


			int zeroResources = 0;
			for (int i = 0; i < 3; i++)
			{
				if (resourcesGathered[i] == 0)
				{
					zeroResources++;
				}
			}

			for (int i = 0; i < zeroResources; i++)
			{
				P1.DrawBuilding(buildingDeck);
			}

			//after all players build/pass

			resourceMarker[0] = 0;
			resourceMarker[1] = 0;
			resourceMarker[2] = 0;
			resourceMarker[3] = 0;


			P1.DrawHarvestTile(harvestTileDeck);
			numberOfTurns++;

			// ask if the other players want to build with remaining resources or pass

			player2Turn = true;
			player1Turn = false;
			player3Turn = false;
			player4Turn = false;

		}
		if (player2Turn)
		{
			int harvestTileNumber = 0;
			int tilePlacement;

			cout << "Player 2 turn: " << endl;
			//player 2 actions

			cout << "Select a harvest tile: " << endl;
			cout << "Harvest Tile 1: ";
			HarvestTile* ht = P2.HT1;
			ht->printTile();
			cout << "Harvest Tile 2: ";
			HarvestTile* ht2 = P2.HT2;
			ht2->printTile();
			cout << "Enter 1 or 2:" << endl;
			cin >> harvestTileNumber;
			cout << "Which position would you like to place the tile?" << endl;
			cin >> tilePlacement;
			if (harvestTileNumber == 1)
			{
				int* harvestTileArray = P2.HT1->convertHT(*P2.HT1);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P2.HT1 = NULL;
			}
			else if (harvestTileNumber == 2)
			{
				int* harvestTileArray = P2.HT2->convertHT(*P2.HT2);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P2.HT2 = NULL;
			}

			std::cout << resourcesGathered[0] << " Sheep " << resourcesGathered[1] << " Stone " << resourcesGathered[2] << " Wood " << resourcesGathered[3] << " Wheat " << endl << endl;

			resourceMarker[0] = resourcesGathered[0];
			resourceMarker[1] = resourcesGathered[1];
			resourceMarker[2] = resourcesGathered[2];
			resourceMarker[3] = resourcesGathered[3];

			bool ableToBuild = false;

			while (!ableToBuild)
			{

				ableToBuild = true;

				cout << "These are your buildings (Player 2), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
				if (P2.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P2.B1;
					b1->printBuilding();
				}
				if (P2.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P2.B2;
					b2->printBuilding();
				}
				if (P2.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P2.B3;
					b3->printBuilding();
				}
				if (P2.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P2.B4;
					b4->printBuilding();
				}
				if (P2.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P2.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				Building* selectedBuilding = new Building();
				if (buildingNumber == -1)
					break;
				switch (buildingNumber)
				{
				case 1: selectedBuilding = P2.B1;
					break;
				case 2: selectedBuilding = P2.B2;
					break;
				case 3:	selectedBuilding = P2.B3;
					break;
				case 4:	selectedBuilding = P2.B4;
					break;
				case 5:	selectedBuilding = P2.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}

			cout << endl;

			//remaining resources can be used by other players

			bool player1Extra = false;
			int player1ExtraTurn;
			cout << "Would Player 1 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player1ExtraTurn;
			if (player1ExtraTurn == 1)
			{
				player1Extra = true;
			}

			while (player1Extra)
			{

				player1Extra = false;
				cout << "These are your buildings (Player 1), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
				if (P1.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P1.B1;
					b1->printBuilding();
				}
				if (P1.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P1.B2;
					b2->printBuilding();
				}
				if (P1.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P1.B3;
					b3->printBuilding();
				}
				if (P1.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P1.B4;
					b4->printBuilding();
				}
				if (P1.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P1.B5;
					b5->printBuilding();
				}

				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P1.B1;
					break;
				case 2: selectedBuilding = P1.B2;
					break;
				case 3:	selectedBuilding = P1.B3;
					break;
				case 4:	selectedBuilding = P1.B4;
					break;
				case 5:	selectedBuilding = P1.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}
			bool player3Extra = false;
			int player3ExtraTurn;
			cout << "Would Player 3 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player3ExtraTurn;
			if (player3ExtraTurn == 1)
			{
				player3Extra = true;
			}

			while (player3Extra)
			{

				player3Extra = false;
				cout << "These are your buildings (Player 3), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
				if (P3.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P3.B1;
					b1->printBuilding();
				}
				if (P3.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P3.B2;
					b2->printBuilding();
				}
				if (P3.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P3.B3;
					b3->printBuilding();
				}
				if (P3.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P3.B4;
					b4->printBuilding();
				}
				if (P3.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P3.B5;
					b5->printBuilding();
				}

				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P3.B1;
					break;
				case 2: selectedBuilding = P3.B2;
					break;
				case 3:	selectedBuilding = P3.B3;
					break;
				case 4:	selectedBuilding = P3.B4;
					break;
				case 5:	selectedBuilding = P3.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player3Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
			}

			bool player4Extra = false;
			int player4ExtraTurn;
			cout << "Would Player 4 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player4ExtraTurn;
			if (player4ExtraTurn == 1)
			{
				player4Extra = true;
			}

			while (player4Extra)
			{

				player4Extra = false;

				cout << "These are your buildings (Player 4), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
				if (P4.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P4.B1;
					b1->printBuilding();
				}
				if (P4.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P4.B2;
					b2->printBuilding();
				}
				if (P4.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P4.B3;
					b3->printBuilding();
				}
				if (P4.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P4.B4;
					b4->printBuilding();
				}
				if (P4.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P4.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P4.B1;
					break;
				case 2: selectedBuilding = P4.B2;
					break;
				case 3:	selectedBuilding = P4.B3;
					break;
				case 4:	selectedBuilding = P4.B4;
					break;
				case 5:	selectedBuilding = P4.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
			}

			int zeroResources = 0;
			for (int i = 0; i < 3; i++)
			{
				if (resourcesGathered[i] == 0)
				{
					zeroResources++;
				}
			}

			for (int i = 0; i < zeroResources; i++)
			{
				P2.DrawBuilding(buildingDeck);
			}

			resourceMarker[0] = 0;
			resourceMarker[1] = 0;
			resourceMarker[2] = 0;
			resourceMarker[3] = 0;


			P2.DrawHarvestTile(harvestTileDeck);

			numberOfTurns++;
			player3Turn = true;
			player1Turn = false;
			player2Turn = false;
			player4Turn = false;

		}if (player3Turn)
		{
			int harvestTileNumber = 0;
			int tilePlacement;

			//player 3 actions

			cout << "Player 3 turn: " << endl;

			cout << "Select a harvest tile: " << endl;
			cout << "Harvest Tile 1: ";
			HarvestTile* ht = P3.HT1;
			ht->printTile();
			cout << "Harvest Tile 2: ";
			HarvestTile* ht2 = P3.HT2;
			ht2->printTile();
			cout << "Enter 1 or 2:" << endl;
			cin >> harvestTileNumber;
			cout << "Which position would you like to place the tile?" << endl;
			cin >> tilePlacement;
			if (harvestTileNumber == 1)
			{
				int* harvestTileArray = P3.HT1->convertHT(*P3.HT1);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P3.HT1 = NULL;
			}
			else if (harvestTileNumber == 2)
			{
				int* harvestTileArray = P3.HT2->convertHT(*P3.HT2);
				resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
				P3.HT2 = NULL;
			}

			std::cout << resourcesGathered[0] << " Sheep " << resourcesGathered[1] << " Stone " << resourcesGathered[2] << " Wood " << resourcesGathered[3] << " Wheat " << endl << endl;

			resourceMarker[0] = resourcesGathered[0];
			resourceMarker[1] = resourcesGathered[1];
			resourceMarker[2] = resourcesGathered[2];
			resourceMarker[3] = resourcesGathered[3];

			//P1.BuildVillage(); //player 1 builds buildings ontop of the village board
			//access the buildings in player 1's hand
			//print out the buildings, let player 1 choose which building to build
			//choose where to place the building
			//subtract the resources used from resource marker


			bool ableToBuild = false;

			while (!ableToBuild)
			{

				ableToBuild = true;

				cout << "These are your buildings (Player 3), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
				if (P3.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P3.B1;
					b1->printBuilding();
				}
				if (P3.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P3.B2;
					b2->printBuilding();
				}
				if (P3.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P3.B3;
					b3->printBuilding();
				}
				if (P3.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P3.B4;
					b4->printBuilding();
				}
				if (P3.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P3.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				Building* selectedBuilding = new Building();
				if (buildingNumber == -1)
					break;
				switch (buildingNumber)
				{
				case 1: selectedBuilding = P3.B1;
					break;
				case 2: selectedBuilding = P3.B2;
					break;
				case 3:	selectedBuilding = P3.B3;
					break;
				case 4:	selectedBuilding = P3.B4;
					break;
				case 5:	selectedBuilding = P3.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						ableToBuild = false;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P3.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P3.B1 = NULL;
							break;
						case 2: P3.B2 = NULL;
							break;
						case 3:	 P3.B3 = NULL;
							break;
						case 4:	 P3.B4 = NULL;
							break;
						case 5:	 P3.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}

			cout << endl;
			bool player1Extra = false;
			int player1ExtraTurn;
			cout << "Would Player 1 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player1ExtraTurn;
			if (player1ExtraTurn == 1)
			{
				player1Extra = true;
			}

			while (player1Extra)
			{

				player1Extra = false;

				cout << "These are your buildings (Player 1), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
				if (P1.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P1.B1;
					b1->printBuilding();
				}
				if (P1.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P1.B2;
					b2->printBuilding();
				}
				if (P1.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P1.B3;
					b3->printBuilding();
				}
				if (P1.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P1.B4;
					b4->printBuilding();
				}
				if (P1.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P1.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P1.B1;
					break;
				case 2: selectedBuilding = P1.B2;
					break;
				case 3:	selectedBuilding = P1.B3;
					break;
				case 4:	selectedBuilding = P1.B4;
					break;
				case 5:	selectedBuilding = P1.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player1Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P1.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P1.B1 = NULL;
							break;
						case 2: P1.B2 = NULL;
							break;
						case 3:	 P1.B3 = NULL;
							break;
						case 4:	 P1.B4 = NULL;
							break;
						case 5:	 P1.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}



			}
			//remaining resources can be used by other players

			bool player2Extra = false;
			int player2ExtraTurn;
			cout << "Would Player 2 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player2ExtraTurn;
			if (player2ExtraTurn == 1)
			{
				player2Extra = true;
			}

			while (player2Extra)
			{

				player2Extra = false;

				cout << "These are your buildings (Player 2), Select a building from 1 to 5, Enter -1 if you want to pass:" << endl;
				if (P2.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P2.B1;
					b1->printBuilding();
				}
				if (P2.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P2.B2;
					b2->printBuilding();
				}
				if (P2.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P2.B3;
					b3->printBuilding();
				}
				if (P2.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P2.B4;
					b4->printBuilding();
				}
				if (P2.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P2.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P2.B1;
					break;
				case 2: selectedBuilding = P2.B2;
					break;
				case 3:	selectedBuilding = P2.B3;
					break;
				case 4:	selectedBuilding = P2.B4;
					break;
				case 5:	selectedBuilding = P2.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player2Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P2.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P2.B1 = NULL;
							break;
						case 2: P2.B2 = NULL;
							break;
						case 3:	 P2.B3 = NULL;
							break;
						case 4:	 P2.B4 = NULL;
							break;
						case 5:	 P2.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
			}
			bool player4Extra = false;
			int player4ExtraTurn;
			cout << "Would Player 4 like to use the remaining resources? Yes (1) or No (0):" << endl;
			cin >> player4ExtraTurn;
			if (player4ExtraTurn == 1)
			{
				player4Extra = true;
			}

			while (player4Extra)
			{

				player4Extra = false;

				cout << "These are your buildings (Player 4), Select a building from 1 to 5, Enter -1 if you want to pass:" << endl;
				if (P4.B1 != NULL) {
					cout << "Building 1";
					Building* b1 = P4.B1;
					b1->printBuilding();
				}
				if (P4.B2 != NULL) {
					cout << "Building 2";
					Building* b2 = P4.B2;
					b2->printBuilding();
				}
				if (P4.B3 != NULL) {
					cout << "Building 3";
					Building* b3 = P4.B3;
					b3->printBuilding();
				}
				if (P4.B4 != NULL) {
					cout << "Building 4";
					Building* b4 = P4.B4;
					b4->printBuilding();
				}
				if (P4.B5 != NULL) {
					cout << "Building 5";
					Building* b5 = P4.B5;
					b5->printBuilding();
				}
				int buildingNumber;
				cin >> buildingNumber;

				if (buildingNumber == -1)
					break;

				Building* selectedBuilding = new Building();

				switch (buildingNumber)
				{
				case 1: selectedBuilding = P4.B1;
					break;
				case 2: selectedBuilding = P4.B2;
					break;
				case 3:	selectedBuilding = P4.B3;
					break;
				case 4:	selectedBuilding = P4.B4;
					break;
				case 5:	selectedBuilding = P4.B5;
					break;
				}


				int amountNeeded = *selectedBuilding->getNumber();
				string typeNeeded = *selectedBuilding->getColor();

				//red = wood, green = sheep, yellow = wheat, gray = stone

				if (typeNeeded.compare("red") == 0)
				{
					typeNeeded = "wood";
					if (amountNeeded > resourceMarker[2])
					{
						cout << "Not enough wood to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[2] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("yellow") == 0)
				{
					typeNeeded = "wheat";
					if (amountNeeded > resourceMarker[3])
					{
						cout << "Not enough wheat to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[3] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("green") == 0)
				{
					typeNeeded = "sheep";
					if (amountNeeded > resourceMarker[0])
					{
						cout << "Not enough sheep to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[0] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
				else if (typeNeeded.compare("gray") == 0)
				{
					typeNeeded = "stone";
					if (amountNeeded > resourceMarker[1])
					{
						cout << "Not enough stone to build this building." << endl;
						player4Extra = true;
					}
					else
					{
						resourceMarker[1] -= amountNeeded;
						int whichSide;
						bool faceUp;
						cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
						cin >> whichSide;

						if (whichSide == 0)
						{
							faceUp = true;
						}
						else if (whichSide)
						{
							faceUp = false;
						}

						P4.VillageMap->buildVillage(selectedBuilding, faceUp);
						selectedBuilding = NULL;
						switch (buildingNumber)
						{
						case 1:  P4.B1 = NULL;
							break;
						case 2: P4.B2 = NULL;
							break;
						case 3:	 P4.B3 = NULL;
							break;
						case 4:	 P4.B4 = NULL;
							break;
						case 5:	 P4.B5 = NULL;
							break;
						}

						cout << endl;
						cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
					}
				}
			}

			int zeroResources = 0;
			for (int i = 0; i < 3; i++)
			{
				if (resourcesGathered[i] == 0)
				{
					zeroResources++;
				}
			}

			for (int i = 0; i < zeroResources; i++)
			{
				P3.DrawBuilding(buildingDeck);
			}

			//after all players build/pass

			resourceMarker[0] = 0;
			resourceMarker[1] = 0;
			resourceMarker[2] = 0;
			resourceMarker[3] = 0;


			P3.DrawHarvestTile(harvestTileDeck);
			numberOfTurns++;

			// ask if the other players want to build with remaining resources or pass
			player4Turn = true;
			player1Turn = false;
			player2Turn = false;
			player3Turn = false;

		}
	if (player4Turn)
	{
		int harvestTileNumber = 0;
		int tilePlacement;

		//player 4 actions

		cout << "Player 4 turn: " << endl;

		cout << "Select a harvest tile: " << endl;
		cout << "Harvest Tile 1: ";
		HarvestTile* ht = P4.HT1;
		ht->printTile();
		cout << "Harvest Tile 2: ";
		HarvestTile* ht2 = P4.HT2;
		ht2->printTile();
		cout << "Enter 1 or 2:" << endl;
		cin >> harvestTileNumber;
		cout << "Which position would you like to place the tile?" << endl;
		cin >> tilePlacement;
		if (harvestTileNumber == 1)
		{
			int* harvestTileArray = P4.HT1->convertHT(*P4.HT1);
			resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
			P4.HT1 = NULL;
		}
		else if (harvestTileNumber == 2)
		{
			int* harvestTileArray = P4.HT2->convertHT(*P4.HT2);
			resourcesGathered = map.placeTile(tilePlacement, harvestTileArray);
			P4.HT2 = NULL;
		}

		std::cout << resourcesGathered[0] << " Sheep " << resourcesGathered[1] << " Stone " << resourcesGathered[2] << " Wood " << resourcesGathered[3] << " Wheat " << endl << endl;

		resourceMarker[0] = resourcesGathered[0];
		resourceMarker[1] = resourcesGathered[1];
		resourceMarker[2] = resourcesGathered[2];
		resourceMarker[3] = resourcesGathered[3];

		//P1.BuildVillage(); //player 1 builds buildings ontop of the village board
		//access the buildings in player 1's hand
		//print out the buildings, let player 1 choose which building to build
		//choose where to place the building
		//subtract the resources used from resource marker


		bool ableToBuild = false;

		while (!ableToBuild)
		{

			ableToBuild = true;

			cout << "These are your buildings (Player 4), Select a building from 1 to 5, Enter -1 if you want to pass: " << endl;
			if (P4.B1 != NULL) {
				cout << "Building 1";
				Building* b1 = P4.B1;
				b1->printBuilding();
			}
			if (P4.B2 != NULL) {
				cout << "Building 2";
				Building* b2 = P4.B2;
				b2->printBuilding();
			}
			if (P4.B3 != NULL) {
				cout << "Building 3";
				Building* b3 = P4.B3;
				b3->printBuilding();
			}
			if (P4.B4 != NULL) {
				cout << "Building 4";
				Building* b4 = P4.B4;
				b4->printBuilding();
			}
			if (P4.B5 != NULL) {
				cout << "Building 5";
				Building* b5 = P4.B5;
				b5->printBuilding();
			}
			int buildingNumber;
			cin >> buildingNumber;

			Building* selectedBuilding = new Building();
			if (buildingNumber == -1)
				break;
			switch (buildingNumber)
			{
			case 1: selectedBuilding = P4.B1;
				break;
			case 2: selectedBuilding = P4.B2;
				break;
			case 3:	selectedBuilding = P4.B3;
				break;
			case 4:	selectedBuilding = P4.B4;
				break;
			case 5:	selectedBuilding = P4.B5;
				break;
			}


			int amountNeeded = *selectedBuilding->getNumber();
			string typeNeeded = *selectedBuilding->getColor();

			//red = wood, green = sheep, yellow = wheat, gray = stone

			if (typeNeeded.compare("red") == 0)
			{
				typeNeeded = "wood";
				if (amountNeeded > resourceMarker[2])
				{
					cout << "Not enough wood to build this building." << endl;
					ableToBuild = false;
				}
				else
				{
					resourceMarker[2] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P3.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P4.B1 = NULL;
						break;
					case 2:  P4.B2 = NULL;
						break;
					case 3:	 P4.B3 = NULL;
						break;
					case 4:	 P4.B4 = NULL;
						break;
					case 5:	 P4.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("yellow") == 0)
			{
				typeNeeded = "wheat";
				if (amountNeeded > resourceMarker[3])
				{
					cout << "Not enough wheat to build this building." << endl;
					ableToBuild = false;
				}
				else
				{
					resourceMarker[3] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P4.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P4.B1 = NULL;
						break;
					case 2:  P4.B2 = NULL;
						break;
					case 3:	 P4.B3 = NULL;
						break;
					case 4:	 P4.B4 = NULL;
						break;
					case 5:	 P4.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("green") == 0)
			{
				typeNeeded = "sheep";
				if (amountNeeded > resourceMarker[0])
				{
					cout << "Not enough sheep to build this building." << endl;
					ableToBuild = false;
				}
				else
				{
					resourceMarker[0] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P4.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P4.B1 = NULL;
						break;
					case 2: P4.B2 = NULL;
						break;
					case 3:	 P4.B3 = NULL;
						break;
					case 4:	 P4.B4 = NULL;
						break;
					case 5:	 P4.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("gray") == 0)
			{
				typeNeeded = "stone";
				if (amountNeeded > resourceMarker[1])
				{
					cout << "Not enough stone to build this building." << endl;
					ableToBuild = false;
				}
				else
				{
					resourceMarker[1] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P4.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P4.B1 = NULL;
						break;
					case 2: P4.B2 = NULL;
						break;
					case 3:	 P4.B3 = NULL;
						break;
					case 4:	 P4.B4 = NULL;
						break;
					case 5:	 P4.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}



		}

		cout << endl;
		bool player1Extra = false;
		int player1ExtraTurn;
		cout << "Would Player 1 like to use the remaining resources? Yes (1) or No (0):" << endl;
		cin >> player1ExtraTurn;
		if (player1ExtraTurn == 1)
		{
			player1Extra = true;
		}

		while (player1Extra)
		{

			player1Extra = false;

			cout << "These are your buildings (Player 1), Select a building from 1 to 5, Enter -1 if you want to pass:" << endl;
			if (P1.B1 != NULL) {
				cout << "Building 1";
				Building* b1 = P1.B1;
				b1->printBuilding();
			}
			if (P1.B2 != NULL) {
				cout << "Building 2";
				Building* b2 = P1.B2;
				b2->printBuilding();
			}
			if (P1.B3 != NULL) {
				cout << "Building 3";
				Building* b3 = P1.B3;
				b3->printBuilding();
			}
			if (P1.B4 != NULL) {
				cout << "Building 4";
				Building* b4 = P1.B4;
				b4->printBuilding();
			}
			if (P1.B5 != NULL) {
				cout << "Building 5";
				Building* b5 = P1.B5;
				b5->printBuilding();
			}
			int buildingNumber;
			cin >> buildingNumber;

			if (buildingNumber == -1)
				break;

			Building* selectedBuilding = new Building();

			switch (buildingNumber)
			{
			case 1: selectedBuilding = P1.B1;
				break;
			case 2: selectedBuilding = P1.B2;
				break;
			case 3:	selectedBuilding = P1.B3;
				break;
			case 4:	selectedBuilding = P1.B4;
				break;
			case 5:	selectedBuilding = P1.B5;
				break;
			}


			int amountNeeded = *selectedBuilding->getNumber();
			string typeNeeded = *selectedBuilding->getColor();

			//red = wood, green = sheep, yellow = wheat, gray = stone

			if (typeNeeded.compare("red") == 0)
			{
				typeNeeded = "wood";
				if (amountNeeded > resourceMarker[2])
				{
					cout << "Not enough wood to build this building." << endl;
					player1Extra = true;
				}
				else
				{
					resourceMarker[2] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P1.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P1.B1 = NULL;
						break;
					case 2: P1.B2 = NULL;
						break;
					case 3:	 P1.B3 = NULL;
						break;
					case 4:	 P1.B4 = NULL;
						break;
					case 5:	 P1.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("yellow") == 0)
			{
				typeNeeded = "wheat";
				if (amountNeeded > resourceMarker[3])
				{
					cout << "Not enough wheat to build this building." << endl;
					player1Extra = true;
				}
				else
				{
					resourceMarker[3] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P1.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P1.B1 = NULL;
						break;
					case 2: P1.B2 = NULL;
						break;
					case 3:	 P1.B3 = NULL;
						break;
					case 4:	 P1.B4 = NULL;
						break;
					case 5:	 P1.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("green") == 0)
			{
				typeNeeded = "sheep";
				if (amountNeeded > resourceMarker[0])
				{
					cout << "Not enough sheep to build this building." << endl;
					player1Extra = true;
				}
				else
				{
					resourceMarker[0] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P1.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P1.B1 = NULL;
						break;
					case 2: P1.B2 = NULL;
						break;
					case 3:	 P1.B3 = NULL;
						break;
					case 4:	 P1.B4 = NULL;
						break;
					case 5:	 P1.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("gray") == 0)
			{
				typeNeeded = "stone";
				if (amountNeeded > resourceMarker[1])
				{
					cout << "Not enough stone to build this building." << endl;
					player1Extra = true;
				}
				else
				{
					resourceMarker[1] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P1.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P1.B1 = NULL;
						break;
					case 2: P1.B2 = NULL;
						break;
					case 3:	 P1.B3 = NULL;
						break;
					case 4:	 P1.B4 = NULL;
						break;
					case 5:	 P1.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
		}
		//remaining resources can be used by other players

		bool player2Extra = false;
		int player2ExtraTurn;
		cout << "Would Player 2 like to use the remaining resources? Yes (1) or No (0):" << endl;
		cin >> player2ExtraTurn;
		if (player2ExtraTurn == 1)
		{
			player2Extra = true;
		}

		while (player2Extra)
		{

			player2Extra = false;

			cout << "These are your buildings (Player 2), Select a building from 1 to 5, Enter -1 if you want to pass:" << endl;
			if (P2.B1 != NULL) {
				cout << "Building 1";
				Building* b1 = P2.B1;
				b1->printBuilding();
			}
			if (P2.B2 != NULL) {
				cout << "Building 2";
				Building* b2 = P2.B2;
				b2->printBuilding();
			}
			if (P2.B3 != NULL) {
				cout << "Building 3";
				Building* b3 = P2.B3;
				b3->printBuilding();
			}
			if (P2.B4 != NULL) {
				cout << "Building 4";
				Building* b4 = P2.B4;
				b4->printBuilding();
			}
			if (P2.B5 != NULL) {
				cout << "Building 5";
				Building* b5 = P2.B5;
				b5->printBuilding();
			}
			int buildingNumber;
			cin >> buildingNumber;

			if (buildingNumber == -1)
				break;

			Building* selectedBuilding = new Building();

			switch (buildingNumber)
			{
			case 1: selectedBuilding = P2.B1;
				break;
			case 2: selectedBuilding = P2.B2;
				break;
			case 3:	selectedBuilding = P2.B3;
				break;
			case 4:	selectedBuilding = P2.B4;
				break;
			case 5:	selectedBuilding = P2.B5;
				break;
			}


			int amountNeeded = *selectedBuilding->getNumber();
			string typeNeeded = *selectedBuilding->getColor();

			//red = wood, green = sheep, yellow = wheat, gray = stone

			if (typeNeeded.compare("red") == 0)
			{
				typeNeeded = "wood";
				if (amountNeeded > resourceMarker[2])
				{
					cout << "Not enough wood to build this building." << endl;
					player2Extra = true;
				}
				else
				{
					resourceMarker[2] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P2.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P2.B1 = NULL;
						break;
					case 2: P2.B2 = NULL;
						break;
					case 3:	 P2.B3 = NULL;
						break;
					case 4:	 P2.B4 = NULL;
						break;
					case 5:	 P2.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("yellow") == 0)
			{
				typeNeeded = "wheat";
				if (amountNeeded > resourceMarker[3])
				{
					cout << "Not enough wheat to build this building." << endl;
					player2Extra = true;
				}
				else
				{
					resourceMarker[3] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P2.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P2.B1 = NULL;
						break;
					case 2: P2.B2 = NULL;
						break;
					case 3:	 P2.B3 = NULL;
						break;
					case 4:	 P2.B4 = NULL;
						break;
					case 5:	 P2.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("green") == 0)
			{
				typeNeeded = "sheep";
				if (amountNeeded > resourceMarker[0])
				{
					cout << "Not enough sheep to build this building." << endl;
					player2Extra = true;
				}
				else
				{
					resourceMarker[0] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P2.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P2.B1 = NULL;
						break;
					case 2: P2.B2 = NULL;
						break;
					case 3:	 P2.B3 = NULL;
						break;
					case 4:	 P2.B4 = NULL;
						break;
					case 5:	 P2.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("gray") == 0)
			{
				typeNeeded = "stone";
				if (amountNeeded > resourceMarker[1])
				{
					cout << "Not enough stone to build this building." << endl;
					player2Extra = true;
				}
				else
				{
					resourceMarker[1] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P2.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P2.B1 = NULL;
						break;
					case 2: P2.B2 = NULL;
						break;
					case 3:	 P2.B3 = NULL;
						break;
					case 4:	 P2.B4 = NULL;
						break;
					case 5:	 P2.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
		}
		bool player3Extra = false;
		int player3ExtraTurn;
		cout << "Would Player 4 like to use the remaining resources? Yes (1) or No (0):" << endl;
		cin >> player3ExtraTurn;
		if (player3ExtraTurn == 1)
		{
			player3Extra = true;
		}

		while (player3Extra)
		{

			player3Extra = false;

			cout << "These are your buildings (Player 3), Select a building from 1 to 5, Enter -1 if you want to pass:" << endl;
			if (P3.B1 != NULL) {
				cout << "Building 1";
				Building* b1 = P3.B1;
				b1->printBuilding();
			}
			if (P3.B2 != NULL) {
				cout << "Building 2";
				Building* b2 = P3.B2;
				b2->printBuilding();
			}
			if (P3.B3 != NULL) {
				cout << "Building 3";
				Building* b3 = P3.B3;
				b3->printBuilding();
			}
			if (P3.B4 != NULL) {
				cout << "Building 4";
				Building* b4 = P3.B4;
				b4->printBuilding();
			}
			if (P3.B5 != NULL) {
				cout << "Building 5";
				Building* b5 = P3.B5;
				b5->printBuilding();
			}
			int buildingNumber;
			cin >> buildingNumber;

			if (buildingNumber == -1)
				break;

			Building* selectedBuilding = new Building();

			switch (buildingNumber)
			{
			case 1: selectedBuilding = P3.B1;
				break;
			case 2: selectedBuilding = P3.B2;
				break;
			case 3:	selectedBuilding = P3.B3;
				break;
			case 4:	selectedBuilding = P3.B4;
				break;
			case 5:	selectedBuilding = P3.B5;
				break;
			}


			int amountNeeded = *selectedBuilding->getNumber();
			string typeNeeded = *selectedBuilding->getColor();

			//red = wood, green = sheep, yellow = wheat, gray = stone

			if (typeNeeded.compare("red") == 0)
			{
				typeNeeded = "wood";
				if (amountNeeded > resourceMarker[2])
				{
					cout << "Not enough wood to build this building." << endl;
					player3Extra = true;
				}
				else
				{
					resourceMarker[2] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P3.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P3.B1 = NULL;
						break;
					case 2:  P3.B2 = NULL;
						break;
					case 3:	 P3.B3 = NULL;
						break;
					case 4:	 P3.B4 = NULL;
						break;
					case 5:	 P3.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("yellow") == 0)
			{
				typeNeeded = "wheat";
				if (amountNeeded > resourceMarker[3])
				{
					cout << "Not enough wheat to build this building." << endl;
					player3Extra = true;
				}
				else
				{
					resourceMarker[3] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P3.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P3.B1 = NULL;
						break;
					case 2:  P3.B2 = NULL;
						break;
					case 3:	 P3.B3 = NULL;
						break;
					case 4:	 P3.B4 = NULL;
						break;
					case 5:	 P3.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("green") == 0)
			{
				typeNeeded = "sheep";
				if (amountNeeded > resourceMarker[0])
				{
					cout << "Not enough sheep to build this building." << endl;
					player3Extra = true;
				}
				else
				{
					resourceMarker[0] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P3.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P4.B1 = NULL;
						break;
					case 2: P4.B2 = NULL;
						break;
					case 3:	 P4.B3 = NULL;
						break;
					case 4:	 P4.B4 = NULL;
						break;
					case 5:	 P4.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
			else if (typeNeeded.compare("gray") == 0)
			{
				typeNeeded = "stone";
				if (amountNeeded > resourceMarker[1])
				{
					cout << "Not enough stone to build this building." << endl;
					player3Extra = true;
				}
				else
				{
					resourceMarker[1] -= amountNeeded;
					int whichSide;
					bool faceUp;
					cout << "Would you like to place this building face-up (0) or facedown (1)?" << endl;
					cin >> whichSide;

					if (whichSide == 0)
					{
						faceUp = true;
					}
					else if (whichSide)
					{
						faceUp = false;
					}

					P3.VillageMap->buildVillage(selectedBuilding, faceUp);
					selectedBuilding = NULL;
					switch (buildingNumber)
					{
					case 1:  P3.B1 = NULL;
						break;
					case 2:  P3.B2 = NULL;
						break;
					case 3:	 P3.B3 = NULL;
						break;
					case 4:	 P3.B4 = NULL;
						break;
					case 5:	 P3.B5 = NULL;
						break;
					}

					cout << endl;
					cout << "Remaining resources in the resource marker: " << endl << resourceMarker[0] << " Sheep, " << resourceMarker[1] << " Stone, " << resourceMarker[2] << " Wood, " << resourceMarker[3] << " Wheat" << endl;
				}
			}
		}

		int zeroResources = 0;
		for (int i = 0; i < 3; i++)
		{
			if (resourcesGathered[i] == 0)
			{
				zeroResources++;
			}
		}

		for (int i = 0; i < zeroResources; i++)
		{
			P4.DrawBuilding(buildingDeck);
		}

		//after all players build/pass

		resourceMarker[0] = 0;
		resourceMarker[1] = 0;
		resourceMarker[2] = 0;
		resourceMarker[3] = 0;


		P4.DrawHarvestTile(harvestTileDeck);
		numberOfTurns++;

		// ask if the other players want to build with remaining resources or pass
		player1Turn = true;
		player2Turn = false;
		player2Turn = false;
		player4Turn = false;

	}
		}

		}
	}
	
	
