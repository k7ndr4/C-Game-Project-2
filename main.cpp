/* 
 * File:   main.cpp
 * Author: Kendra
 *
 * Created on October 20, 2024, 3:16 PM
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {
    srand(time(0));
    
    //DIFFICULTY POINTS
    const int WIN_EASY = 65; //NUM OF POINTS TO WIN THE GAME (easy)
    const int WIN_MED  = 100; //NUM OF POINTS TO WIN THE GAME (medium)
    const int WIN_HARD = 150; //NUM OF POINTS TO WIN THE GAME (hard)
    
    //CONTROLS
    const char STRT_BTN = '1';
    const char EXIT_BTN  = '3';
    
    //GAME VARS
    const int BAD_NUM   = 1; //THE SIDE OF THE DIE THAT WILL RESULT IN ENDING YOUR TURN
    const int DIE_SIDES = 6; //AMOUNT OF SIDES ON THE DIE
    unsigned int currRoll = 0; //THE CURRENT SIDE OF THE DIE THAT HAS BEEN ROLLED 'i.e: 5'
    unsigned int currTurn = 1; //THE CURRENT NUMBER OF TURNS THE PLAYER IS ON
    float points = 0;
    
    //EXPLAIN RULES
    char input;
    while(input != EXIT_BTN){
        cout << "Welcome to the game of Pig Dice!\n" <<
                "To play the game, you roll a die as many times as you'd like to try and reach \n\n" << 
                "EASY: " << WIN_EASY << " points\nMEDIUM: " << WIN_MED << " points\nHARD: " << WIN_HARD << " points\n\nin a minimum amount of turns.\n" <<
                "The catch is, if you roll a " << BAD_NUM << " your points will revert back to the amount of points you had since the last time you chose to end a turn manually, and the amount of turns will increase by 1.\n" <<
                "You may end your turn at any time to save the number of points you have, and try to minimize the amount of turns until you reach the desired amount of points.\n" <<
                "Type " << STRT_BTN <<  " to start the game, or type " << EXIT_BTN << " to exit the program.\n\n";

        //CAPTURE USER INPUT & START THE GAME IF REQUESTED
          cin >> input;
    //    if(input == EXIT_BTN){
    //        cout << "Exiting game...\n";
    //        exit(0);
    //    }else if(input == STRT_BTN){
    //        //DO NOTHING, CONTINUE ON WITH PROGRAM
    //    }else{
    //        cout << "Exiting game...\n";
    //        exit(0);
    //    }

        //CHOOSE DIFFICULTY
        char diff;
        string diffStr;
        int currCon;
        cout << "Please choose your difficulty...\n" <<
                "Enter 'E' for Easy   (" << WIN_EASY <<  " points)\n" <<
                "Enter 'M' for Medium (" << WIN_MED  <<  " points)\n" <<
                "Enter 'H' for Hard   (" << WIN_HARD <<  " points)\n";
        cin >> diff;

        switch(diff){
            case 'E': 
                currCon = WIN_EASY;
                diffStr = "EASY";
                break;

            case 'M': 
                currCon = WIN_MED;
                diffStr = "MEDIUM";
                break;

            case 'H': 
                currCon = WIN_HARD;
                diffStr = "HARD";
                break;

            default : 
                currCon = WIN_EASY;
                diffStr = "EASY";
                break;
        }


        //START THE GAME & CREATE A TEXT FILE
        ofstream MyFile("gameLogs.txt");
        MyFile << "\nGame Session Started\n";

        cout << "\nSTARTING GAME on " <<  diffStr << " DIFFICULTY\n\n";

        //GAME LOOP
        char roll;
        int cPoint = 0;
        do{
            cout << "Roll the die by inputting 'R', or input anything else to stop your turn.\n";
            cin >> roll;

        //IF THE PLAYER CHOOSES TO CONTINUE ROLLING THE DIE
            if(roll == 'R'){

                //ROLL THE DIE & OUTPUT THE RESULT
                currRoll = rand()%DIE_SIDES+1;
                cout << "You rolled a " << currRoll << '\n';

                //IF THE DIE ROLL LANDED ON '1' THEN THE PLAYER LOSES THEIR POINTS AND THE TURN # INCREASES
                if(currRoll == 1){
                    points = cPoint;
                    cout << "Your points have been reverted to " << cPoint << " points. You are currently on turn: " << currTurn++ << '\n';
                    cout << "\nTURN: " << currTurn << '\n';
                }else{
                    points += float(currRoll);
                    cout << "Your current amount of points are: " << points << '\n';
                }
        //IF THE PLAYER CHOOSES TO MANUALLY END THE TURN
            }else{
                cout << fixed << setprecision(0) << 
                        "You have chosen to end your turn. It is currently turn " << currTurn++ <<
                        "\nYou have " << points << " amount of points.\n\n";
                cPoint = points;
            }
        }while(points < currCon);

        //ENSURE THAT THE WHILE LOOP BROKE BECAUSE PLAYER REACHED WIN CONDITION
        bool beatGame = points >= currCon ? true : false;
        if(beatGame){
            cout << "Congratulations! You have beat the game on " << diffStr << " difficulty, in " << currTurn << " turns!\n\n";
        }

        //RECORD DATA IN FILE
        const int DATANUM = 2;

        for(int i = 0; i < DATANUM; ++i){
            string output;

            if(i == 0) output = "Difficulty: " + diffStr + "\n";
            else if(i == 1) output = "Amt of Turns: " + to_string(currTurn) + "\n";
            else output = "---------\n\n";

            MyFile << output;
        }

        MyFile.close();
    }
    
    return 0;
}

