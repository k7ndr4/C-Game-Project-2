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
#include <fstream>

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
        if( std::count(deck->CardDeck.begin(), deck->CardDeck.end(), num) == _FOUROFKIND){ return true; }
        return false;
    }
    
    //CHECKS WIN CONDITION
    bool CheckFour(Deck* deck){
        //CHECKS FOR 4 OF ALL NUMBERS
        for(int i = 1; i <= 13; i++){
            if( std::count(deck->CardDeck.begin(), deck->CardDeck.end(), i) == _FOUROFKIND){
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
        
        //GO FISH!
        if(itr == from->CardDeck.end()){
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
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        std::cout << "\n----TURN " << turn << " ----\n";
        _PlayerDeck->Sort();
        
        //TURNS WILL BE DECIDED BASED ON MODULUS 2
        //i.e EVEN TURNS WILL BE THE ENEMY TURN, ODD WILL BE PLAYER
        //IF THE TURN IS EVEN, (IF IT IS THE PLAYERS TURN)
        if(turn % 2 == 0){
            //PROMPT THE PLAYER TO TAKE A CARD
            DisplayHand(_PlayerDeck);
            std::cout << "\nIt's your turn! Enter a card number that you want to fish for: ";
            
            char num{};
            std::cin >> num;
            
            //USER VALIDATION
            if(num > 13) num = 13;
            else if(num < 1) num = 1;

            if(isdigit(num)) checkNum = num;
            else checkNum = 1;
            
            //TAKE THE REQUESTED CARD
            if(!WhileTakeFromDeck(_EnemyDeck, _PlayerDeck, checkNum)){
                //GO FISH
                std::cout << "\nGo Fish!\n";
                Deck::Card tempCard = _GameDeck->GetRandomCard();
                TakeFromDeck(_GameDeck, _PlayerDeck, tempCard, 0);
                std::cout << "You received a " << tempCard.name() << '\n';
            }
            
            //CHECK FOR BOOKS
            if(CheckFour(_PlayerDeck)){
                std::cout << "\nYou have 4 " << checkNum << "'s! These cards will be removed from your hand, and your # of books will go up by 1.\n";
                
                WhileTakeFromDeck(_PlayerDeck, _Pile, checkNum);
                _playerBooks++;
                _points += (_playerBooks*checkNum*_turn);
                PrintBooks();
            }
        }
        
        //IF THE TURN IS ODD, (IT'S THE ENEMYS TURN)
        else{
            //ENEMY AI
            //WILL ASK YOU FOR A CARD TYPE THEY HAVE, IF THEY HAVE AN EMPTY HAND, THEY WILL ASK YOU FOR ONE OF YOUR CARD TYPES 
            int enemyFish{};
            if(_EnemyDeck->Size() > 0) enemyFish = _EnemyDeck->GetRandomCard().num();
            else enemyFish = _PlayerDeck->GetRandomCard().num();
            
            std::cout << "\nYour opponent is asking for " << enemyFish << "'s.";
            
            if(!WhileTakeFromDeck(_PlayerDeck, _EnemyDeck, enemyFish)){
                //GO FISH
                std::cout << "\nOpponent has to Go Fish!\n";
                Deck::Card tempCard = _GameDeck->GetRandomCard();
                TakeFromDeck(_GameDeck, _EnemyDeck, tempCard, 0);
            }
            
            if(CheckFour(_EnemyDeck)){
                std::cout << "\nYour opponent has 4 " << enemyFish << "'s! These cards will be removed from their hand, and their # of books will go up by 1.\n";
                
                WhileTakeFromDeck(_EnemyDeck, _Pile, enemyFish);
                _enemyBooks++;
                PrintBooks();
            }
        }
        
        //CHECK FOR BOOKS
    }
    
    void ResetDecks(){
        _GameDeck->CardDeck.clear();
        _PlayerDeck->CardDeck.clear();
        _EnemyDeck->CardDeck.clear();
        _Pile->CardDeck.clear();
        
        _GameDeck->CreateRandomDeck();
        _GameDeck->Shuffle();
        
        //HAND BOTH DECKS '_PLAYER_HANDSIZE' RANDOM CARDS EACH
        for(int i = 0; i < _PLAYER_HANDSIZE; ++i){
            TakeFromDeck(_GameDeck, _PlayerDeck, _GameDeck->GetRandomCard(), 0);
            TakeFromDeck(_GameDeck, _EnemyDeck, _GameDeck->GetRandomCard(), 0);
        }
    }
    
    void PrintBooks(){
        std::cout << 
                "Player Books:  " << _playerBooks <<
                "\nEnemy Books: " << _enemyBooks  << '\n';
    }
    
    void DisplayHand(Deck* deck){
        //DISPLAY THE HAND OF THE PLAYER TO THE PLAYER
        std::cout << "\nYour current hand:\n";
        _PlayerDeck->PrintDeck(2);
    }
    
    void DisplayVictory(){
        if(_playerBooks > _enemyBooks){
            //player won
            std::cout << "\nYOU WON!!!\nCONGRATULATIONS. Points: " << _points << "\n\n";
            
            //_GameLogs << "Player Won.\nPoints: " << _points << '\n';
        }else if(_playerBooks < _enemyBooks){
            //enemy won
            std::cout << "\nYOU LOST!\nBETTER LUCK NEXT TIME. Points: " << _points << "\n\n";
            
            //_GameLogs << "Enemy Won.\n";
        }else{
            //tied
            std::cout << "\nTIED GAME!\nRARE OCCURANCE. Points: " << _points << "\n\n";
            
            //_GameLogs << "Tied Game.\nPoints: " << _points << '\n';
        }
        
        //_GameLogs.close();
    }
    
    void MainMenu(){
        char input{};
        do{
            std::cout << "\nWelcome to Go Fish!\n1) Start Game\n2) Rules\n3) Exit\n";
            std::cin >> input;
            switch(input){
                case '1':
                    StartGame();
                    break;
                case '2':
                    DisplayRules();
                    break;
                case '3':
                    exit(0);
                    break;
                default:
                    exit(0);
                    break;
            }
        }while(input != '3');
    }
    
    void DisplayRules(){
        std::cout << 
                "\nThe objective of the game is to get as many 'books' as possible.\n" <<
                "You gain a 'book' by obtaining 4 of the same type of card. (i.e 4 Jacks = 1 book)\n" <<
                "The cards used to gain a 'book' will be removed from your hand.\n" << ""
                "Each turn you will ask your opponent for a type of card. If they have this type of card, they must\n" <<
                "give you all cards of that type. (i.e You ask for 7's, and the opponent has 3 7's. They must give you all 3, and vice versa.)\n" <<
                "The game will end once the entire game deck has run out of cards to fish from.\n" <<
                "The winner will be determined by who has more books. Points are determined by (the rank of your card * the amount of books you have * the current turn).\n" <<
                "Points will be displayed at the end of the game.\n";
    }
    
    //GAMEPLAY LOOP
    void StartGame(){
        std::cout << "\nStarting Game...\n\n";
        //_GameLogs << "\nGame Session Started : " << ymd;
        
        //RESET DECKS TO ENSURE NO BUGS
        ResetDecks();
        
        //INITIALIZE 'checkNum' WITH -1 SO YOU CANT ACCIDENTLY WIN A BOOK OFF START
        int checkNum = -1;
        
        //CHECK FOR GAME CONDITIONS IN WHILE LOOP
        while(_GameDeck->Size() > 0){
            PromptTurn(_turn++, checkNum);
            
            //CHECK FOR BOOKS AFTER DECK IS EMPTY
            if(CheckFour(_PlayerDeck,checkNum)){
                std::cout << "\nYou have 4 " << checkNum << "'s! These cards will be removed from your hand, and your # of books will go up by 1.\n";
                
                WhileTakeFromDeck(_PlayerDeck, _Pile, checkNum);
                _playerBooks++;
                _points += (_playerBooks*checkNum*_turn);
                PrintBooks();
            }
        }
        
        //CHECK WHO WON, DISPLAY VICTORY & RECORD LOGS
        DisplayVictory();
    }
    
    //STILL NEED TO IMPLEMENT:
    //BINARY SEARCH/LINEAR SEARCH, BUBBLE SORT, SELECTION SORT, TYPE CASTING, VALIDATING USER INPUT, OSTREAM, 
    //STATIC VARS, 1D ARRAY, PARALLEL ARRAY, FUNC(1D ARRAY), 2D ARRAY, USE OF CMATH LIBRARY
    //MOVE ALL HEADER FUNCTIONS TO .CPP FILES
    
private:
    //const std::chrono::time_point now{std::chrono::system_clock::now()};
    //const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
    
    const int _FOUROFKIND = 4;
    const int _PLAYER_HANDSIZE = 7;
    
    Deck* _GameDeck = nullptr;
    Deck* _PlayerDeck = nullptr;
    Deck* _EnemyDeck = nullptr;
    Deck* _Pile = nullptr;
    
    unsigned int _turn = 1;
    unsigned int _playerBooks = 0; //BOOKS ARE THE # OF 4 OF A KINDS
    unsigned int _enemyBooks  = 0;
    
    float _points = 0;
    
    bool _gameStarted = false;
    
    //std::ofstream _GameLogs("gameLogs.txt");
};


#endif /* GOFISH_H */

