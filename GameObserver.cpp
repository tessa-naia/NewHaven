//
// Created by Tess on 2020-04-11.
//
#include <stdio.h>
#include "GameObserver.h"
#include "Player.h"
#include "VillageScore.h"

Observer::Observer() {};
Observer::~Observer() {};

GameObservers::GameObservers() {
    playerturn = new int(0);
    resourceGen = new int[4];
    villagebuildingcount = new int(0);
    ConcreteSubject* subj = new ConcreteSubject();
};

GameObservers::GameObservers(ConcreteSubject* passed_sub) { subj = passed_sub; }

void GameObservers::update(){

    playerturn = subj->getPlayerTurn();
    resourceGen = subj->getresourceGen();
    villagebuildingcount = subj->getVillageBuildingCount();

    cout << "-----------------------------OBSERVER-----------------------------" << endl;
    cout << "Active player: " << *playerturn << endl;
    cout <<"Resources Generated: " << resourceGen[0] << " sheep " << resourceGen[1] << " stone " << resourceGen[2] << " wood " << resourceGen[3] << " wheat" << endl;
    cout << "Village Building Count: " << *villagebuildingcount << endl;
    cout << "------------------------------------------------------------------" << endl;
}

GameObservers::~GameObservers() {
    delete playerturn;
    delete villagebuildingcount;
    delete resourceGen;
    delete subj;
};

ConcreteSubject::ConcreteSubject() {
    playerturnID = new int(0);
    playerturn = new int(0);
    resourceGen = new int[4];
    villagebuildingcount = new int(0);
    resourcesRemaining = new int[4];
    players = new vector<Player>;
    theObservers = new vector<Observer*>;

}

ConcreteSubject::~ConcreteSubject()
{
    delete playerturn;
    delete resourceGen;
    delete villagebuildingcount;
    delete resourcesRemaining;
    delete players;
    delete theObservers;
}

void ConcreteSubject::attach(Observer* Obs) { theObservers->push_back(Obs); }
void ConcreteSubject::detach(Observer* Obs) { theObservers->erase(remove(theObservers->begin(), theObservers->end(), Obs), theObservers->end()); }
void ConcreteSubject::notify() {
    for (Observer* o : *theObservers) {
        static_cast<GameObservers*>(o)->update();
    }
}

void ConcreteSubject::setPlayerTurn(int* Playerturn) { playerturn = Playerturn; }
int* ConcreteSubject::getPlayerTurn() { return playerturn; }

int* ConcreteSubject::getresourceGen() { return resourceGen; }
void ConcreteSubject::setresourceGen(int* resarray) { resourceGen = resarray; }

int* ConcreteSubject::getVillageBuildingCount() { return villagebuildingcount; }
void ConcreteSubject::setVillageBuildingCount(int* Vcount) { villagebuildingcount = Vcount; }

void ConcreteSubject::setPlayers(vector<Player>* P) {
    for (int i=0; i<P->size(); i++) {
        players->push_back(P->at(i));
    }
}
vector<Player> *ConcreteSubject::getPlayers() {
    return players;
}
int *ConcreteSubject::getResourcesRemaining() {return resourcesRemaining;}
void ConcreteSubject::setResourcesRemaining(int *RR) { resourcesRemaining=RR; }

GameStatsObserver::GameStatsObserver()
{
    vector<Player> *players=new vector<Player>();
    resourcesRemaining = new int[4];
    ConcreteSubject* subj = new ConcreteSubject();
}

GameStatsObserver::GameStatsObserver(ConcreteSubject* passed_sub) {
    players=new vector<Player>();
    resourcesRemaining = new int[4];
    subj = passed_sub; }

GameStatsObserver::~GameStatsObserver()
{
    delete players;
    delete resourcesRemaining;
    delete subj;
}

void GameStatsObserver::update() {
    int winningScore = 0;
    int winningID;
    resourcesRemaining=subj->getResourcesRemaining();

    for (int i=0; i<subj->getPlayers()->size(); i++) {
        Player p1=subj->getPlayers()->at(i);
        players->push_back(p1);
    }
    cout << "-------------------- Game Statistics: ---------------------" << endl;
    for (int i = 0; i < players->size(); i++) {
        //Player #
        cout << "Player " << players->at(i).getCurrentID() << endl;
        //
        players->at(i).VillageMap->printMap();
        //current score
        VillageScore *VS1 = new VillageScore();
        Player pi=players->at(i);
        VS1 = pi.getVS();
        //The score is calculated using the VillageGame map and the given Player's Village Score object
        VS1->CalculateScore(*players->at(i).VillageMap);
        int *score = VS1->getScore();
        cout << "Score: " << (*score) << endl;
        //Resources remaining
        cout << "Remaining resources in the resource marker: " << endl << resourcesRemaining[0] << " Sheep, "
             << resourcesRemaining[1] << " Stone, " << resourcesRemaining[2] << " Wood, " << resourcesRemaining[3] << " Wheat"
             << endl;
        if (*score > winningScore)
            winningID = players->at(i).getCurrentID();
    }
//If its the end of the game, Player # wins msg
    cout << "---------------------------------------------------------------------------------------";
}

