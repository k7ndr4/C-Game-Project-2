/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   GoFish.h
 * Author: Kendra
 *
 * Created on December 8, 2024, 5:35 AM
 */

#ifndef GOFISH_H
#define GOFISH_H

#include "Deck.h"
#include <chrono>
#include <thread>
#include <iomanip>
#include <fstream>
#include <ctime>

class GoFish{
public:
    GoFish(Deck* GameDeck, Deck* PlayerDeck, Deck* EnemyDeck, Deck* Pile){
        _GameDeck = GameDeck;
        _PlayerDeck = PlayerDeck;
        _EnemyDeck = EnemyDeck;
        _Pile = Pile;
        
        _GameLogs.open("logs.txt",std::fstream::app);
    }
    
    ~GoFish(){
        delete _GameDeck;
        delete _PlayerDeck;
        delete _EnemyDeck;
        delete _Pile;
        
        LogSessionStats();
        _GameLogs.close();
    }
    
    //CHECKS THE WIN CONDITION
    bool CheckFour(Deck* deck, int num);
    
    //CHECKS WIN CONDITION
    bool CheckFour(int& check, Deck* deck);
    
    //LOG SESSION STATS
    void LogSessionStats();
    
    //FIND A CARD OBJECT, FIND IT FROM A DECK. ADD IT TO 'to' DECK, REMOVE CARD FROM 'from' DECK
    void TakeFromDeck(Deck* from, Deck* to, Deck::Card card, int check);
    
    //FIND A CARD NUMBER, KEEP TAKING FROM THE DECK UNTIL IT IS NO LONGER PRESENT
    bool WhileTakeFromDeck(Deck* from, Deck* to, int num);
    
    //GAMEPLAY TURN
    void PromptTurn(int turn, int& checkNum);
    
    void Reset();
    void PrintBooks();
    void DisplayHand(Deck* deck);
    void DisplayRules();
    void DisplayVictory();
    void MainMenu();
    
    //GAMEPLAY LOOP
    void StartGame();
private:
    //YMD
    time_t now = time(0);
    char* date = ctime(&now);
   
    //GAME RULES
    const int _FOUROFKIND = 4;
    const int _PLAYER_HANDSIZE = 7;
    
    //GAME DECKS
    Deck* _GameDeck = nullptr;
    Deck* _PlayerDeck = nullptr;
    Deck* _EnemyDeck  = nullptr;
    Deck* _Pile = nullptr;
    
    //GAME STATS
    unsigned int _turn = 1; //CURRENT TURN
    unsigned int _playerBooks = 0; //BOOKS ARE THE # OF 4 OF A KINDS
    unsigned int _enemyBooks  = 0; 
    
    float _playerPoints = 0;
    float _enemyPoints = 0;
    
    bool _gameStarted = false;
    
    //GAME LOGS
    std::ofstream _GameLogs{};
    
    int _SessionWtoL[2][1] = {{0}, {0}}; //SESSIONS WINS TO LOSSES ([0][] = PLAYER, [1][] = ENEMY)
    int _SessionGameCount = 0; //NUMBER OF GAMES PLAYED IN THIS SESSION
    int _SessionPlayerPoints[10]; //SESSION POINTS, INDEX INDICATES GAME
    int _SessionEnemyPoints[10];
    std::string _playerName{}; //PLAYER NAME
};
#endif /* GOFISH_H */