#include "GoFish.h"

//CHECKS THE WIN CONDITION
bool GoFish::CheckFour(Deck* deck, int num){
    if( std::count(deck->CardDeck.begin(), deck->CardDeck.end(), num) == _FOUROFKIND){ return true; }
    return false;
}

//CHECKS WIN CONDITION
bool GoFish::CheckFour(Deck* deck){
    //CHECKS FOR 4 OF ALL NUMBERS
    for(int i = 1; i <= 13; i++){
        if( std::count(deck->CardDeck.begin(), deck->CardDeck.end(), i) == _FOUROFKIND){
            return true;
        }
    }
    return false;
}

void GoFish::LogSessionStats(){
    if(_SessionGameCount == 0) return;
    _GameLogs << "Session Stats:\nPlayer Wins: " << _SessionWtoL[0][0] << '\n';

    for(int  i = 0; i < _SessionGameCount; ++i){
        _GameLogs << "Game " << i+1 << ", you had: " << _SessionPlayerPoints[i] << " points. The enemy had: " << _SessionEnemyPoints[i] << " points.\n";
    }
}

//FIND A CARD OBJECT, FIND IT FROM A DECK. ADD IT TO 'to' DECK, REMOVE CARD FROM 'from' DECK
void GoFish::TakeFromDeck(Deck* from, Deck* to, Deck::Card card, int check = 1){
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
bool GoFish::WhileTakeFromDeck(Deck* from, Deck* to, int num){
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
void GoFish::PromptTurn(int turn, int& checkNum){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "\n----TURN " << turn << " ----\n";

    //SORT BOTH DECKS TO MAKE IT EASIER TO SEARCH THRU
    _PlayerDeck->Sort(0);
    _EnemyDeck->Sort(1);

    //TURNS WILL BE DECIDED BASED ON MODULUS 2
    //i.e EVEN TURNS WILL BE THE ENEMY TURN, ODD WILL BE PLAYER
    //IF THE TURN IS EVEN, (IF IT IS THE PLAYERS TURN)
    if(turn % 2 == 0){
        //PROMPT THE PLAYER TO TAKE A CARD
        DisplayHand(_PlayerDeck);
        std::cout << "\nIt's your turn! Enter a card number that you want to fish for: ";

        //USER VALIDATION
        while (!(std::cin >> checkNum)) {
            std::cout << "Invalid input. Please enter an integer: ";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if(checkNum > 13) checkNum = 13;
        else if(checkNum < 1) checkNum = 1;

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
            _playerPoints += abs((static_cast<float>(_playerBooks)*checkNum*_turn));
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
            _enemyPoints += abs((static_cast<float>(_enemyBooks)*enemyFish*_turn));

            PrintBooks();
        }
    }

    //CHECK FOR BOOKS
}

void GoFish::Reset(){
    _GameDeck->CardDeck.clear();
    _PlayerDeck->CardDeck.clear();
    _EnemyDeck->CardDeck.clear();
    _Pile->CardDeck.clear();

    _playerPoints = 0;
    _enemyPoints = 0;
    _playerBooks = 0;
    _enemyBooks  = 0;

    _GameDeck->CreateRandomDeck();
    _GameDeck->Shuffle();

    //HAND BOTH DECKS '_PLAYER_HANDSIZE' RANDOM CARDS EACH
    for(int i = 0; i < _PLAYER_HANDSIZE; ++i){
        TakeFromDeck(_GameDeck, _PlayerDeck, _GameDeck->GetRandomCard(), 0);
        TakeFromDeck(_GameDeck, _EnemyDeck, _GameDeck->GetRandomCard(), 0);
    }
}

void GoFish::PrintBooks(){
    std::cout << 
            "Player Books:  " << _playerBooks <<
            "\nEnemy Books: " << _enemyBooks  << '\n';
}

void GoFish::DisplayHand(Deck* deck){
    //DISPLAY THE HAND OF THE PLAYER TO THE PLAYER
    std::cout << "\nYour current hand:\n";
    _PlayerDeck->PrintDeck(2);
}

void GoFish::DisplayVictory(){
    //STORE SESSION POINTS
    _SessionPlayerPoints[_SessionGameCount] = _playerPoints;
    _SessionEnemyPoints[_SessionGameCount]  = _enemyPoints;

    if(_playerBooks > _enemyBooks){
        //player won
        std::cout << "\nYOU WON!!!\nCONGRATULATIONS. Points: " << _playerPoints << "\n\n";

        _SessionWtoL[0][0]++;
    }else if(_playerBooks < _enemyBooks){
        //enemy won
        std::cout << "\nYOU LOST!\nBETTER LUCK NEXT TIME. Points: " << _playerPoints << "\n\n";

        _SessionWtoL[1][0]++;
    }else{
        //tied
        std::cout << "\nTIED GAME!\nRARE OCCURANCE. Points: " << _playerPoints << "\n\n";
    }

    _SessionGameCount++;
}

void GoFish::MainMenu(){
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
                LogSessionStats();
                _GameLogs.close();

                exit(0);
                break;
            default:
                LogSessionStats();
                _GameLogs.close();

                exit(0);
                break;
        }
    }while(input != '3');
}

void GoFish::DisplayRules(){
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
void GoFish::StartGame(){
    std::cout << "\nStarting Game...\n\n";
    _GameLogs << "\nGame Session Started : " << date << std::endl;

    //RESET DECKS TO ENSURE NO BUGS
    Reset();

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
            _playerPoints += (_playerBooks*checkNum*_turn);
            PrintBooks();
        }
    }

    //CHECK WHO WON, DISPLAY VICTORY & RECORD LOGS
    DisplayVictory();
}

//STILL NEED TO IMPLEMENT: 
//MOVE ALL HEADER FUNCTIONS TO .CPP FILES

