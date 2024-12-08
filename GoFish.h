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
        return false;
    }
    
    void TakeFromDeck(Deck& from, Deck& to, Deck::Card card){
        if( std::find(from.CardDeck.begin(), from.CardDeck.end(), card) != from.CardDeck.end()){
            to += card;
            from -= card;
        }
    }
private:
    const int _WINCON = 4;
};


#endif /* GOFISH_H */

