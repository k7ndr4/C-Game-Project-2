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
    GoFish(Deck& GameDeck, Deck& PlayerDeck, Deck& EnemyDeck, Deck& Pile){
        
    }
    
    bool CheckFour(Deck& deck, int num){
        if( std::count(deck.CardDeck.begin(), deck.CardDeck.end(), num) == _WINCON){
            std::cout << "\nPLAYER _ WON!!!!";
            return true;
        }
        return false;
    }
    
    void TakeFromDeck(Deck& from, Deck& to, Deck::Card card){
        if( std::find(from.CardDeck.begin(), from.CardDeck.end(), card) != from.CardDeck.end()){
            to += card;
            from -= card;
        }
    }
    
    void WhileTakeFromDeck(Deck& from, Deck& to, int num){
        while(std::find(from.CardDeck.begin(), from.CardDeck.end(), num) != from.CardDeck.end()){
            //to +=
            //from -=
        }
    }
    
    void PromptTurn(){
        
    }
    
private:
    const int _WINCON = 4;
};


#endif /* GOFISH_H */

