/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Deck.h
 * Author: Kendra
 *
 * Created on December 8, 2024, 4:46 AM
 */

#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>

class Deck{
public: 
    struct Card{
        public:
            Card(){
                
            }
            
            Card(int num, std::string suite){
                _number = num;
                _suite  = suite;
            }
            
            bool operator==(const Deck::Card& card2){
                if( card2._number == this->_number && card2._suite == this->_suite ) return true;
                return false;
            }
            
            bool operator==(const int num){
                if(num == this->_number) return true;
                return false;
            }
            
            bool operator>(const Deck::Card& card2){
                return this->_number > card2._number;
            }
            
            bool operator>(const int num){
                return this->_number > num;
            }
            
            bool operator<(const Deck::Card& card2){
                return this->_number < card2._number;
            }
            
            bool operator<(const int num){
                return this->_number < num;
            }
            
            bool operator>=(const Deck::Card& card2){
                return this->_number >= card2._number;
            }
            
            bool operator>=(const int num){
                return this->_number >= num;
            }
            
            bool operator<=(const Deck::Card& card2){
                return this->_number <= card2._number;
            }
            
            bool operator<=(const int num){
                return this->_number <= num;
            }
            
            inline std::string name(){ return numToVal() + _suite; }
            inline std::string suite() { return _suite; }
            inline int num() { return _number; }
            
        private:
            int _number{}; //PHYSICAL CARD NUMBER, ANYTHING ABOVE 10 CORRELATES TO THE FACE CARDS. (i.e JOKER = 11, QUEEN = 12, KING = 13}
            std::string _suite{};
            
            inline std::string numToVal(){
                if(_number == 1) return "Ace";
                if(_number <=10) return std::to_string(_number);
                switch(_number){
                    case 11: return "Jack";
                    case 12: return "Queen";
                    case 13: return "King";
                    default: return "Jack";
                }
            }
    };
    
    Deck(int size){
        _size = size;
        CardDeck.reserve(size);
    }
    
    Deck(){
        _size = 52;
        CardDeck.reserve(52);
    }
    
    Deck(bool create){
        if(create) CreateRandomDeck(_SUITES);
    }
    
    Deck& operator +=(Deck::Card card){
        CardDeck.push_back(card);
        return *this;
    }
    
    Deck& operator -=(Deck::Card card){
        //FIND IF CARD PRESENT, IF IT IS DELETE IT FROM CardDeck
        if( std::find(CardDeck.begin(), CardDeck.end(), card) != CardDeck.end()){
            CardDeck.erase(std::find(CardDeck.begin(), CardDeck.end(), card));
        }
        return *this;
    }
    
    //THE DECK ITSELF
    std::vector<Deck::Card> CardDeck{};
    
    //GETTERS
    inline int Size(){ return CardDeck.size(); }
    
    //PUBLIC FUNCS
    void CreateRandomDeck();
    void CreateRandomDeck(const std::string SUITES[]);
    void PrintDeck(int format);
    void bublSrt();
    void selSrt();

    int linSrch(int val);
    
    void Shuffle();
    void Sort(int type);
    
    Deck::Card GetRandomCard();
    Deck::Card ReturnAndRemove(int num);
    
private:
    int _size{};
    
    inline const static std::string _SUITES[4] = { 
        " of Spades", 
        " of Hearts", 
        " of Clubs", 
        " of Diamonds" 
    };
};


#endif /* DECK_H */

