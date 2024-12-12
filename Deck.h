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
        //call some function to create cards based on a const array of numbers&suites
        _size = size;
        CardDeck.reserve(size);
    }
    
    Deck(){
        //call some function to create cards based on a const array of numbers&suites
        _size = 52;
        CardDeck.reserve(52);
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
    void CreateRandomDeck(){
        for(int i = 0; i < 4; ++i){
            for(int j = 1; j <= 13; ++j){
                CardDeck.emplace_back(j, SUITES[i]);
            }
        }
    }
    
    void PrintDeck(int format = 1){
        switch(format){
            case 1: 
                for(Deck::Card &card: CardDeck){
                    std::cout << card.name() << '\n';
                }
                break;
            
            case 2: 
                for(Deck::Card &card: CardDeck){
                    std::cout << card.name() << ", ";
                }
        }
    }
    
    void bublSrt(){
        for(int max = CardDeck.size() - 1; max > 0; max --){
            for(int index = 0; index < max; index++){
                if(CardDeck[index] > CardDeck[index + 1])
                    std::swap(CardDeck[index], CardDeck[index + 1]);
            }
        }
    }
    
    void selSrt(){
        int minIndex, minValue;

        for(int i = 0; i < (CardDeck.size() - 1); i++){
            minIndex = i;
            minValue = CardDeck[i].num();

            for(int index = i + 1; index < CardDeck.size(); index++){
                if(CardDeck[index].num() < minValue){
                    minValue = CardDeck[index].num();
                    minIndex = index;
                }
            }
            std::swap(CardDeck[minIndex],CardDeck[i]);
        }
    }
    
    int linSrch(int val){
        int index = -1;
        for(int i = 0; i < CardDeck.size(); i++){
            if(CardDeck.at(i) == val){
                index = i;
                return index;
            }
        }
        return index;
    }
    
    void Shuffle(){
        std::shuffle(CardDeck.begin(), CardDeck.end(), std::default_random_engine(time(0)));
    }
    
    void Sort(int type = 0){
        //std::sort(CardDeck.begin(), CardDeck.end());
        if(type == 0)
            bublSrt();
        else
            selSrt();
    }
    
    Deck::Card GetRandomCard(){
        return CardDeck.at(rand()% CardDeck.size());
    }
    
    Deck::Card ReturnAndRemove(int num){
        if(linSrch(num) != -1){
            Deck::Card card = CardDeck.at(std::distance(CardDeck.begin(), std::find(CardDeck.begin(), CardDeck.end(), num)));
            
            if(std::find(CardDeck.begin(), CardDeck.end(), card) != CardDeck.end())
                CardDeck.erase(std::find(CardDeck.begin(), CardDeck.end(), card));
            
            return card;
        }
        Deck::Card errorCard;
        return errorCard;
    }
    
private:
    int _size{};
    
    const std::string SUITES[4] = { 
        " of Spades", 
        " of Hearts", 
        " of Clubs", 
        " of Diamonds" 
    };
};


#endif /* DECK_H */

