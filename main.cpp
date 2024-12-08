/* 
 * File:   main.cpp
 * Author: Kendra
 *
 * Created on October 20, 2024, 3:16 PM
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <fstream>
#include <ctime>
#include "Deck.h"
#include "GoFish.h"

using namespace std;

int main(int argc, char** argv) {
    srand(time(0));
    
    //MAKE THE GAME DECK
    Deck GameDeck;
    GameDeck.CreateRandomDeck();
    //GameDeck.PrintDeck();
    
    //PLAYER DECK, ENEMY DECK, & PILE
    Deck PlayerDeck;
    Deck EnemyDeck;
    Deck Pile;
    
    //GAME MANAGER
    GoFish GameManager(GameDeck, PlayerDeck, EnemyDeck, Pile);
    
    GameDeck.Shuffle();
    GameDeck.PrintDeck();
    
    return 0;
}

