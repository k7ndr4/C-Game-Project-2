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
            std::cout << "\nPLAYER _ WON!!!!";
            return true;
        }
        return false;
    }
    
    //FIND A CARD OBJECT, FIND IT FROM A DECK. ADD IT TO 'to' DECK, REMOVE CARD FROM 'from' DECK
    void TakeFromDeck(Deck* from, Deck* to, Deck::Card card){
        if( std::find(from->CardDeck.begin(), from->CardDeck.end(), card) != from->CardDeck.end()){
            *to += card;
            *from -= card;
        }
    }
    
    void WhileTakeFromDeck(Deck* from, Deck* to, int num){
        auto itr = std::find(from->CardDeck.begin(), from->CardDeck.end(), num);
        
        //WHILE THAT NUMBER OF CARD CAN BE FOUND IN A DECK,
        while(itr != from->CardDeck.end()){
            //ADD THAT CARD TO THE 'to' DECK, AND REMOVE IT FROM THE 'from' DECK
            to->CardDeck.push_back(from->ReturnAndRemove(num));
            
            //ADVANCE THE ITERATOR
            itr = std::find(itr++, from->CardDeck.end(), num);
        }
    }
    
    void PromptTurn(){
        
    }
    
private:
    const int _WINCON = 4;
    Deck* _GameDeck = nullptr;
    Deck* _PlayerDeck = nullptr;
    Deck* _EnemyDeck = nullptr;
    Deck* _Pile = nullptr;
};


#endif /* GOFISH_H */

