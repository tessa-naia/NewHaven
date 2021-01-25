//
// Created by Tess on 2020-04-11.
//
#include <list>
#include <vector>
#include "Player.h"
#ifndef UNTITLED1_GAMEOBSERVER_H
#define UNTITLED1_GAMEOBSERVER_H
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

class Observer {
public:
    ~Observer();
    virtual void update() = 0;
protected:
    Observer();
};

class ConcreteSubject{

public:
    ConcreteSubject();
    ~ConcreteSubject();
    int* playerturnID;
    int* playerturn;
    int* resourceGen;
    int* resourcesRemaining;
    int* villagebuildingcount;
    vector<Player>* players;

    vector<Observer*>* theObservers;

    void attach(Observer* Obs);
    void detach(Observer* Obs);
    void notify();

    void setPlayers(vector<Player>* P);
    vector<Player>* getPlayers();

    void setResourcesRemaining(int* RR);
    int* getResourcesRemaining();

    void setPlayerTurn(int* Playerturn);
    int* getPlayerTurn();

    int* getresourceGen();
    void setresourceGen(int* resarray);

    int* getVillageBuildingCount();
    void setVillageBuildingCount(int* Vcount);
};

class GameObservers : public Observer {
public:
    GameObservers();
    GameObservers(ConcreteSubject* passed_sub);
    ~GameObservers();
    int* playerturn;
    int* resourceGen;
    int* villagebuildingcount;
    ConcreteSubject* subj;
    virtual void update() override;
};

class GameStatsObserver:public Observer{
public:
    ConcreteSubject* subj;
    vector<Player>* players;
    int* resourcesRemaining;
    GameStatsObserver();
    GameStatsObserver(ConcreteSubject* passed_sub);
    ~GameStatsObserver();
    void update();
};


#endif //UNTITLED1_GAMEOBSERVER_H
