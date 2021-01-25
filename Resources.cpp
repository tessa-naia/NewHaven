#include "Resources.h"

int HarvestTile_deck::drawn = 0;
HarvestTile::HarvestTile() {
	
	//randomly generate tiles as adjacency list
	Resources = new list<list<string>>;
	Visit1 = false;
	Visit2 = false;
	Visit3 = false;
	Visit4 = false;
	random_int = 0;
	bool flag = true;

	while (flag)
	{

		int sheep_counter = 0;
		int wheat_counter = 0;
		int wood_counter = 0;
		int stone_counter = 0;

		for (int i = 0; i < 4; i++) {

			random_int = ((rand() % 12) + 1);

			if ((random_int == 1 || random_int == 2 || random_int == 3)) {
				list<string> R1 = { "wheat" };
				(*Resources).push_back(R1);
				wheat_counter++;
			}
			if ((random_int == 4 || random_int == 5 || random_int == 6)) {
				list<string> R2 = { "wood" };
				(*Resources).push_back(R2);
				wood_counter++;
			}
			if ((random_int == 7 || random_int == 8 || random_int == 9)) {
				list<string> R3 = { "stone" };
				(*Resources).push_back(R3);
				stone_counter++;
			}
			if ((random_int == 10 || random_int == 11 || random_int == 12)) {
				list<string> R4 = { "sheep" };
				(*Resources).push_back(R4);
				sheep_counter++;
			}
		}

		if (((sheep_counter == 1) && (wheat_counter == 1) && (stone_counter == 1) && (wood_counter == 1)) || ((sheep_counter == 4) || (wheat_counter == 4) || (stone_counter == 4) || (wood_counter == 4)))
		{
			Resources = new list<list<string>>;
			flag = true;
		}
		else
		{
			flag = false;
		}
	}
	//to iterate through the list of lists

	//primary iterator going over nodes
	list<list<string>> ::iterator it = (*Resources).begin();

	//secondary iterator adding nodes into the adjaceny list of a given node
	list<list<string>> ::iterator it_b = (*Resources).begin();
	
	//basic tile shape
	// N1 -  N2
	//  |    |
	// N3 -  N4


	//Node 1 will have edges to Node 2 and Node 3

	//advance to Node 2
	 advance(it_b, 1);
	//put the string contained in the list at Node 2 into adjacency list of Node 1
	 (*it).push_back((*it_b).front());
	 //advance to Node 3
	 advance(it_b, 1);
	 //put the string contained in the list at Node 3 into adjacency list of Node 1
	(*it).push_back((*it_b).front());

	//same procedure as above occurs for the next Nodes


	//advance to Node 2 with primary iterator, it will have edges between Node 1 and Node 4
	advance(it, 1);

	//go back to Node 1 with secondary iterator
	it_b = (*Resources).begin();
	(*it).push_back((*it_b).front());
	//advance to Node 4 (starts from 0th index)
	advance(it_b, 3);
	(*it).push_back((*it_b).front());


	//advance to Node 3 with primary iterator, edges between N1 and N4
	advance(it, 1);

	//Go back to Node 1 with secondary iterator
	it_b = (*Resources).begin();
	(*it).push_back((*it_b).front());
	//Go to Node 4
	advance(it_b, 3);
	(*it).push_back((*it_b).front());


	//advance to Node 4 with primary iterator, edges between N2 and N3
	advance(it, 1);

	//Go back to Node 1 with secondary iterator
	it_b = (*Resources).begin();
	//advance to Node 2
	advance(it_b, 1);
	(*it).push_back((*it_b).front());
	//advance to Node 3
	advance(it_b, 1);
	(*it).push_back((*it_b).front());

	//HarvestTile complete!
	
}
list<list<string>>* HarvestTile::rotation(list<list<string>>& Res)
{	
	//get resources
	list<list<string>>* The_Resources = &Res;
	//iterate ver the list of resources
	list<list<string>> ::iterator it = (*The_Resources).begin();

	//temporary values used in order to reassign
	list<string> tempN1 = (*it);
	advance(it, 1);
	list<string> tempN2 = (*it);
	advance(it, 1);
	list<string> tempN3 = (*it);
	advance(it, 1);
	list<string> tempN4 = (*it);

	//get all values
		/*list<string> N1 = (*it);
		advance(it, 1);
		list<string> N2 = (*it);
		advance(it, 1);
		list<string> N3 = (*it);
		advance(it, 1);
		list<string> N4 = (*it);*/

	it = (*The_Resources).begin();
	
	int option;
	cout << "Please choose an option for clockwise rotation: " << endl;
	cout << "1 = no rotation" << endl;
	cout << "2 = 1 rotation" << endl;
	cout << "3 = 2 rotations" << endl;
	cout << "4 = 3 rotations" << endl;

	cin >> option;

	
	while(option >= 1 && option <= 4){

		//option 1
	//print just the tile
		if (option == 1) {
			break;
		}
		//option2 = 1 rotation clockwise


		if (option == 2) {
			////assign N3 to N1
			//N1 = tempN3;
			//cout << N1.front();
			////N1 to N2
			//N2 = tempN1;
			//cout << N2.front();
			////N4 to N3
			//N3 = tempN4;
			//cout << N3.front();
			////N2 to N4
			//N4 = tempN2;
			//cout << N4.front();
			//it = (*The_Resources).begin();


			(*it) = tempN3;
			advance(it, 1);
			(*it) = tempN1;
			advance(it, 1);
			(*it) = tempN4;
			advance(it, 1);
			(*it) = tempN2;
		}
		//option 3 = 2 rotations clockwise

		if (option == 3) {
			////assign N4 to N1
			//N1 = tempN4;
			//cout << N1.front();
			////N3 to N2
			//N2 = tempN3;
			//cout << N2.front();
			////N2 to N3
			//N3 = tempN2;
			//cout << N3.front();
			////N1 to N4
			//N4 = tempN1;
			//cout << N4.front();
			//it = (*The_Resources).begin();


			(*it) = tempN4;
			advance(it, 1);
			(*it) = tempN3;
			advance(it, 1);
			(*it) = tempN2;
			advance(it, 1);
			(*it) = tempN1;
		}

		//option4 = 3 rotations clockwise
		if (option == 4) {
			
			(*it) = tempN2;
			advance(it, 1);
			(*it) = tempN4;
			advance(it, 1);
			(*it) = tempN1;
			advance(it, 1);
			(*it) = tempN3;
		}

		cin >> option;
	}
	it = (*The_Resources).end();
	return The_Resources;

}
void HarvestTile::setResources(list<list<string>>* Res) 
{
	Resources = Res;
}

list<list<string>>* HarvestTile::getResources() 
{

	return Resources;
}
void HarvestTile::printTile()
{
	//to iterate over the list of lists
	list<list<string>> ::iterator it = (*Resources).begin();

	//to iterate over a given node list with all it's adjacent nodes
	list<string> ::iterator it2;

	cout << endl;
	for (it; it != (*Resources).end(); it++) {
		
		//for loop printing out list<string> values
		for (it2 = (*it).begin(); it2 != (*it).end(); it2++) {
			cout << *it2 << " -> ";
		}
		cout << "NULL" << endl;

	}
	cout << endl;

}
int* HarvestTile::convertHT(HarvestTile& HT)
{
	list<list<string>>* TheRes = HT.getResources();
	int* ResTiles = new int[4];
	int i = 0;
	list<list<string>> ::iterator it = TheRes->begin();
	list<string> ::iterator it2 = (*it).begin();

	for (it; it != TheRes->end(); it++)
	{
		it2 = (*it).begin();
		if ((*it2).compare("sheep") == 0)
		{
			ResTiles[i] = 0;
			i++;
		}
		if ((*it2).compare("stone") == 0)
		{
			ResTiles[i] = 1;
			i++;
		}
		if ((*it2).compare("wood") == 0)
		{
			ResTiles[i] = 2;
			i++;
		}
		if ((*it2).compare("wheat") == 0)
		{
			ResTiles[i] = 3;
			i++;
		}


	}

	return ResTiles;
}
//HarvestTile::~HarvestTile() {
//	delete Resources;
//}

//void HarvestTile::BFS(HarvestTile &H1)
//{
//	list<list<string>>* TheBoys = H1.getResources();
//	list<string> queue;
//	string temp;
//
//	H1.Visit1 = true;
//	
//	list<list<string>> ::iterator it = TheBoys->begin();
//	list<string> ::iterator it2 = (*it).begin();
//	
//	queue.push_back(*it2);
//
//	while(!queue.empty())
//	{
//		temp = queue.front();
//		cout << temp << endl;
//		queue.pop_front();
//
//		for(it = TheBoys->begin(); it != TheBoys->end(); it++)
//		{
//			it2 = (*it).begin();
//			if (!H1.Visit2) {
//				Visit2 = true;
//				queue.push_back(*it2);
//			}
//			else if (!H1.Visit3) {
//				Visit3 = true;
//				queue.push_back(*it2);
//			}
//			else if (!H1.Visit4) {
//				Visit4 = true;
//				queue.push_back(*it2);
//			}
//		}
//	}
//}

void HarvestTile_deck::printdeck()
{
	int count = 1;

for (auto H : (*HT_deck))
{
	cout <<"Tile count = "<< count << endl;
	H.printTile();
	cout << endl;
	count++;
}
}

HarvestTile_deck::HarvestTile_deck() 
{
	HT_deck = new vector<HarvestTile>;
	
	for (int i = 0; i < 60; i++) {
		HarvestTile H = HarvestTile();
		(*HT_deck).push_back(H);
	}
}

vector<HarvestTile>* HarvestTile_deck::getDeck()
{
	return HT_deck;
}
HarvestTile* HarvestTile_deck::draw()
{
	//to check if the deck is empty or has negative values
	if (drawn < 0 || drawn >= 60)
		{
				cout << "Deck is empty... EXITING" << endl;
				exit(0);
		}

	//pointer to a given HarvestTile is returned
	HarvestTile* HT = &(*HT_deck)[drawn];

	cout << "Harvest Tile has been drawn." << endl;
	//The HarvestTile is considered "drawn" and thus the static value pertaining to the HarvestTile_deck class increments
	drawn++;
	return HT;
}
//
//HarvestTile_deck::~HarvestTile_deck() {
//	delete HT_deck;
//}

vector<int> Building_deck::amt(143);
int Building_deck::drawn = 0;
Building::Building() 
{
	color = NULL;
	oppositeside = NULL;
	number = NULL;
	drawn = 0;
}
Building::Building(int num, string col, string opp)
{
	color = new string(col);
	oppositeside = new string(opp);
	number = new int(num);
	drawn = new bool(false);


}
string* Building::getColor()
{
	return color;
}

int* Building::getNumber()
{
	return number;
}

string* Building::getOppositeSide()
{
	return oppositeside;
}
vector<Building>* Building_deck::getDeck()
{

	return B_deck;
}
bool* Building::getDrawn()
{
	return drawn;
}

void Building::setColor(string col)
{
	color = new string(col);
}

void Building::setDrawn(bool d)
{
	drawn = new bool(d);
}

void Building::setOppositeSide(string oppo)
{
	oppositeside = new string(oppo);
}

void Building::setNumber(int num)
{
	number = new int(num);
}
//Building::~Building() {
//	delete color;
//	delete oppositeside;
//	delete color;
//	delete number;
//}

Building_deck::Building_deck()
{
	

	B_deck = new vector<Building>;
	
	//creating 4x(for each color) tiles 1-6 (inner for loops) 6x (outer for loop)
	for (int j = 0; j < 6; j++) {

		for (int i = 1; i < 7; i++) {
			string type = "red";
			string oppo = "forest";
			Building B(i, type, oppo);
			(*B_deck).push_back(B);
		}

		for (int i = 1; i < 7; i++) {
			string type = "green";
			string oppo = "meadow";
			Building B = Building(i, type, oppo);
			(*B_deck).push_back(B);
		}

		for (int i = 1; i < 7; i++) {
			string type = "gray";
			string oppo = "quarry";
			Building B = Building(i, type, oppo);
			(*B_deck).push_back(B);
		}

		for (int i = 1; i < 7; i++) {
			string type = "yellow";
			string oppo = "wheatfield";
			Building B = Building(i, type, oppo);
			(*B_deck).push_back(B);


		}
	}
	

}
Building* Building_deck::draw()
{
	////static int array where the ints correspond to positions in the Deck
	//if (amt.size() == 0) {
	//	cout << "Deck is empty!" << endl;
	//	exit(0);
	//}
	//for (int i = 0; i < amt.size(); i++)
	//	amt.at(i) = i;

	//int rando = (rand() % (amt.size()));
	//
	//if (amt.size() == 1) {
	//	rando = 0;
	//}

	///*Building* B = &(*B_deck)[amt.at(rando)];
	//B[amt.at(rando)].setDrawn(true);*/
	if (B_deck->size() == 0) {
		cout << "no more buildings in deck!" << endl;
		exit(0);
	}
	Building* B = &(*B_deck)[0];
	B[0].setDrawn(true);
	

	int new_size = B_deck->size()-1;
	int tempCounter = 0;

	vector<Building>* temp = new vector<Building>(new_size);

	for (int i = 0; i < B_deck->size(); i++)
	{
		if ((*(*B_deck)[i].getDrawn())==1)
		{
			cout << "Building has been drawn, removing from deck." << endl;
			
		}
		else
		{
			(*temp)[tempCounter] = (*B_deck)[i];
			tempCounter++;
		}
	}

	B_deck = temp;
	B_deck->resize(temp->size());
	
	return B;

	
}

void Building::printBuilding()
{
	cout << endl;
	cout << "The color is: " << *color << endl;
	cout << "The number is: " << *number << endl;
	cout << "The opposite side is: " << *oppositeside << endl;
	cout << endl;
}

void Building_deck::printBuildingDeck()
{
	int count = 1;

	for (auto B : (*B_deck))
	{
		cout << "Building count = " << count << endl;
		B.printBuilding();
		cout << endl;
		count++;
	}
}

//Building_deck::~Building_deck() {
//	delete B_deck;
//}
Hand::Hand() {
	wood_marker = NULL;
	stone_marker = NULL;
	wheat_marker = NULL;
	sheep_marker = NULL;
}

int* Hand::getWood() {
	return wood_marker;
}

int* Hand::getSheep() {
	return sheep_marker;
}
int* Hand::getWheat() {
	return wheat_marker;
}
int* Hand::getStone() {
	return stone_marker;
}

//void Hand::exchange(HarvestTile HT) {
//	PlaceHarvestTile(HT);
//	CalculateResources();
//}
