#include "Player.h"

Player::Player() 
{
	PlayerMap = NULL;
	VillageMap = NULL;

	currentID += 1;

	HT1 = NULL;
	HT2 = NULL;
	Wild_Tile = NULL;

	B1 = NULL;
	B2 = NULL;
	B3 = NULL;
	B4 = NULL;
	B5 = NULL;

	RG1 = NULL;
	VS = NULL;
}
Player::Player(GBMap &map, VGMaps &Map, ResourceGather &RG, VillageScore &VS) {
	PlayerMap = &map;
	VillageMap = &Map;

	currentID+=1;

	HT1 = NULL;
	HT2 = NULL;
	Wild_Tile = NULL;

	B1 = NULL;
	B2 = NULL;
	B3 = NULL;
	B4 = NULL;
	B5 = NULL;

	RG1 = &RG;
	this->VS = &VS;
}
int Player::getPlayerID()
{
	return playerID;
}

int Player::getCurrentID()
{
	return currentID;
}

VGMaps* Player::getVB()
{
    return VillageMap;
}

VillageScore* Player::getVS()
{
    return VS;
}
void Player::setVS(VillageScore *score) {
VS=score;
}
void Player::setPlayerID(int id)
{
	playerID = id;
}

void Player::PlaceHarvestTile(int location, HarvestTile &HT, GBMap &board) {
	HT.rotation(*HT.getResources());
	//board.placeTile(location, HT);
	/*CalculateResources();
	ResourceTracker();*/
}

void Player::DrawBuilding(Building_deck &deck) {

	if (B1 == NULL) {
		B1 = deck.draw();
	}
	else if (B2 == NULL) {
		B2 = deck.draw();
	}
	else if (B3 == NULL) {
		B3 = deck.draw();
	}
	else if (B4 == NULL) {
		B4 = deck.draw();
	}
	else if (B5 == NULL) {
		B5 = deck.draw();
	}
	else
	{
		cout << "Hand is at max (5) capacity." << endl;
	}
}

void Player::DrawHarvestTile(HarvestTile_deck &deck) {
	if (HT1 == NULL) {
		HT1 = deck.draw();
	}
	else if (HT2 == NULL) {
		HT2 = deck.draw();
	}
}



//double* Player::CalculateResources() {
//	double* answer = NULL
//	answer = RG1->RG_tilesonboard();
//	return answer;
//}
//
//void Player::BuildVillage(Building &B) {
//	VillageMap->placeBuilding(B);
//}
//
//void Player::ResourceTracker() {
//	double* ResourcesCal = NULL;
//	ResourcesCal = CalculateResources();
//	Hand.setStone(ResourceCal[0]);
//	Hand.setWheat(ResourceCal[1]);
//	Hand.setWood(ResourceCal[2]);
//	Hand.setSheep(ResourceCal[3]);
//}