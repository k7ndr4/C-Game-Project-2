#include "Deck.h"

//PUBLIC FUNCS
void Deck::CreateRandomDeck(){
    for(int i = 0; i < 4; ++i){
        for(int j = 1; j <= 13; ++j){
            CardDeck.emplace_back(j, _SUITES[i]);
        }
    }
}

void Deck::CreateRandomDeck(const std::string SUITES[]){
    for(int i = 0; i < 4; ++i){
        for(int j = 1; j <= 13; ++j){
            CardDeck.emplace_back(j, SUITES[i]);
        }
    }
}

void Deck::PrintDeck(int format = 1){
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

void Deck::bublSrt(){
    for(int max = CardDeck.size() - 1; max > 0; max --){
        for(int index = 0; index < max; index++){
            if(CardDeck[index] > CardDeck[index + 1])
                std::swap(CardDeck[index], CardDeck[index + 1]);
        }
    }
}

void Deck::selSrt(){
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

int Deck::linSrch(int val){
    int index = -1;
    for(int i = 0; i < CardDeck.size(); i++){
        if(CardDeck.at(i) == val){
            index = i;
            return index;
        }
    }
    return index;
}

void Deck::Shuffle(){
    std::shuffle(CardDeck.begin(), CardDeck.end(), std::default_random_engine(time(0)));
}

void Deck::Sort(int type = 0){
    //std::sort(CardDeck.begin(), CardDeck.end());
    if(type == 0)
        bublSrt();
    else
        selSrt();
}

Deck::Card Deck::GetRandomCard(){
    return CardDeck.at(rand()% CardDeck.size());
}

Deck::Card Deck::ReturnAndRemove(int num){
    if(linSrch(num) != -1){
        Deck::Card card = CardDeck.at(std::distance(CardDeck.begin(), std::find(CardDeck.begin(), CardDeck.end(), num)));

        if(std::find(CardDeck.begin(), CardDeck.end(), card) != CardDeck.end())
            CardDeck.erase(std::find(CardDeck.begin(), CardDeck.end(), card));

        return card;
    }
    Deck::Card errorCard;
    return errorCard;
}

