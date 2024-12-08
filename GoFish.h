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

class GoFish{
public:
    GoFish(Deck* GameDeck, Deck* PlayerDeck, Deck* EnemyDeck, Deck* Pile){
        _GameDeck = GameDeck;
        _PlayerDeck = PlayerDeck;
        _EnemyDeck = EnemyDeck;
        _Pile = Pile;
    }
    
    ~GoFish(){
        delete _GameDeck;
        delete _PlayerDeck;
        delete _EnemyDeck;
        delete _Pile;
    }
    
    //CHECKS THE WIN CONDITION
    bool CheckFour(Deck* deck, int num){
        if( std::count(deck->CardDeck.begin(), deck->CardDeck.end(), num) == _WINCON){
            std::cout << "\n_______ WON!!!!";
            return true;
        }
        return false;
    }
    
    //CHECKS WIN CONDITION
    bool CheckFour(Deck* deck){
        //CHECKS FOR 4 OF ALL NUMBERS
        for(int i = 1; i <= 13; i++){
            if( std::count(deck->CardDeck.begin(), deck->CardDeck.end(), i) == _WINCON){
                std::cout << "\n ______ WON!!!!";
                return true;
            }
        }
        return false;
    }
    
    //FIND A CARD OBJECT, FIND IT FROM A DECK. ADD IT TO 'to' DECK, REMOVE CARD FROM 'from' DECK
    void TakeFromDeck(Deck* from, Deck* to, Deck::Card card, int check = 1){
        if(check == 1){
            if( std::find(from->CardDeck.begin(), from->CardDeck.end(), card) != from->CardDeck.end()){
                *to += card;
                *from -= card;
            }
        }
        else{
            *to += card;
            *from -= card;
        }
    }
    
    //FIND A CARD NUMBER, KEEP TAKING FROM THE DECK UNTIL IT IS NO LONGER PRESENT
    bool WhileTakeFromDeck(Deck* from, Deck* to, int num){
        auto itr = std::find(from->CardDeck.begin(), from->CardDeck.end(), num);
        
        if(itr == from->CardDeck.end()){
            //GO FISH
            std::cout << "\nGo Fish!\n";
            return false;
        }
        //WHILE THAT NUMBER OF CARD CAN BE FOUND IN A DECK,
        int count = 0;
        while(itr != from->CardDeck.end()){
            //ADD THAT CARD TO THE 'to' DECK, AND REMOVE IT FROM THE 'from' DECK
            to->CardDeck.push_back(from->ReturnAndRemove(num));
            
            //ADVANCE THE ITERATOR
            itr = std::find(itr++, from->CardDeck.end(), num);
            count++;
        }
        
        //DISPLAY WHAT CARD WAS TOOK
        std::cout << "\nTook " << count << " " << num << "'s.\n";
        return true;
    }
    
    //GAMEPLAY TURN
    void PromptTurn(int turn, int& checkNum){
        std::cout << "\n----TURN " << turn << " ----\n";
        _PlayerDeck->Sort();
        
        //TURNS WILL BE DECIDED BASED ON MODULUS 2
        //i.e EVEN TURNS WILL BE THE ENEMY TURN, ODD WILL BE PLAYER
        //IF THE TURN IS EVEN, (IF IT IS THE PLAYERS TURN)
        if(turn % 2 == 0){
            //PROMPT THE PLAYER TO TAKE A CARD
            DisplayHand(_PlayerDeck);
            std::cout << "\nIt's your turn! Enter a card number that you want to fish for.\n";
            
            int num{};
            std::cin >> num;
            checkNum = num;
            
            WhileTakeFromDeck(_EnemyDeck, _PlayerDeck, num);
        }
        
        //IF THE TURN IS ODD, (IT'S THE ENEMYS TURN)
        else{
            //ENEMY AI HERE
        }
        
        //MAKE SURE BOTH DECKS HAVE ATLEAST '_PLAYER_HANDSIZE' CARDS
        while(_PlayerDeck->Size() < _PLAYER_HANDSIZE){
            TakeFromDeck(_GameDeck, _PlayerDeck, _GameDeck->GetRandomCard(), 0);
        }
        
        while(_EnemyDeck->Size() < _PLAYER_HANDSIZE){
            TakeFromDeck(_GameDeck, _EnemyDeck, _GameDeck->GetRandomCard(), 0);
        }
    }
    
    void DisplayHand(Deck* deck){
        //DISPLAY THE HAND OF THE PLAYER TO THE PLAYER
        std::cout << "\nYour current hand:\n";
        _PlayerDeck->PrintDeck(2);
    }
    
    //GAMEPLAY LOOP
    void StartGame(){
        std::cout << "\nStarting Game...\n\n";
        //SHUFFLE DECK
        _GameDeck->Shuffle();
        
        //INITIALIZE 'checkNum' WITH -1 SO YOU CANT ACCIDENTLY WIN THE GAME OFF START
        int checkNum = -1;

        //HAND BOTH DECKS 4 RANDOM CARDS EACH
        for(int i = 0; i < _PLAYER_HANDSIZE; ++i){
            TakeFromDeck(_GameDeck, _PlayerDeck, _GameDeck->GetRandomCard(), 0);
            TakeFromDeck(_GameDeck, _EnemyDeck, _GameDeck->GetRandomCard(), 0);
        }
        
        //CHECK FOR WIN CONDITIONS IN WHILE LOOP
        while(!CheckFour(_PlayerDeck,checkNum) && !CheckFour(_EnemyDeck, checkNum)){
            PromptTurn(_turn++, checkNum);
        }
    }
    
    //STILL NEED TO ADD "BOOMS" (four of a kind)
    //PLAY UNTIL NO MORE CARDS, WINNER IS DETERMINED BY WHO HAS MORE "BOOMS"
    //STILL NEED TO IMPLEMENT:
    //BINARY SEARCH/LINEAR SEARCH, BUBBLE SORT, SELECTION SORT, TYPE CASTING, VALIDATING USER INPUT, DO-WHILE, OSTREAM, 
    //STATIC VARS, EXIT() FUNC, 1D ARRAY, PARALLEL ARRAY, FUNC(1D ARRAY), 2D ARRAY, 
    //MOVE ALL HEADER FUNCTIONS TO .CPP FILES
    
private:
    const int _WINCON = 4;
    const int _PLAYER_HANDSIZE = 7;
    
    Deck* _GameDeck = nullptr;
    Deck* _PlayerDeck = nullptr;
    Deck* _EnemyDeck = nullptr;
    Deck* _Pile = nullptr;
    
    int _turn = 1;
    
    bool _gameStarted = false;
};


#endif /* GOFISH_H */

