// this source file contains the game itself.
// Main function playOneGame starts a new game
// and keeps it running as long as the player keeps
// on guessing. 

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
using namespace std;

static const int NUM_CUBES = 16;   // the number of cubes in the game

/*
 * Prints player stats to terminal output
 */
void displayPlayerstats(Boggle &boggle);

/*
 * Let player guess words
 */
void playerRound(Boggle &boggle);

/*
 * Prints computer status to terminal output
 */
void displayRobotResult(Boggle &boggle);

/*
 * Let computer end the game
 */
void robotRound(Boggle &boggle);

/*
 * Make sure that the word meets the criterias
 */
bool checkUserInput(const string &userWord, Boggle &boggle);

/*
 * Transforms a string to upper case by using ascii values
 */
void makeAllCaps(string& userWord);

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    string makeCustom;
    cout << "Do you want to randomly generate a board? ";
    getline(cin, makeCustom);
    while(!(makeCustom == "Y" || makeCustom == "y" ||
            makeCustom == "N" || makeCustom == "n")){
        cout << "Please answer yes or no " << endl;
        getline(cin, makeCustom);
    }

    string board = "";

    if(makeCustom == "N" || makeCustom == "n") {
        cout << "Write the 16 letters you want to use" << endl;
        getline(cin, board);
        while(board.size() != NUM_CUBES || !boggle.checkForInvalid(board)){
            cout << "Invalid input, should be 16 letters" << endl;
            getline(cin, board);
        }

        makeAllCaps(board);
    }

    boggle.makeBoard(makeCustom, board);
    cout << boggle.printGrid();
    playerRound(boggle);
    robotRound(boggle);
    boggle.resetGame();

}

void displayPlayerstats(Boggle& boggle){
    cout << "Your words " << "(" << boggle.getFoundWords().size() << "): "
    << boggle.printFoundWords() << endl;

    cout << "Your score: " << boggle.getScore('p') << endl;

}

void playerRound(Boggle& boggle) {
    string guessedWord;
    bool playing = true;
    while (playing){
        displayPlayerstats(boggle);
        cout << "Type a word (or press Enter to end your turn): ";
        getline(cin, guessedWord);

        makeAllCaps(guessedWord);
        cout << guessedWord << endl; // makeAllCaps works on linux

        if(guessedWord.empty()){
            playing = false;
        }else {
            if(checkUserInput(guessedWord, boggle) && boggle.searchBoard(guessedWord)){
                boggle.addWord(guessedWord);
                cout << "You've found a new word! " << "\"" << guessedWord << "\"" << endl;
            }else {
                cout << "That's not a word!" << endl;
                }
        }   
    }
}

void displayRobotResult(Boggle& boggle){
    cout << "My words " << "(" << boggle.getRobotWords().size() << "): "
    << boggle.printRobotResult() << endl;

    cout << "My score: " << boggle.getScore('r') << endl;

    if(boggle.getScore('r') > boggle.getScore('p')){
        cout << "Ha ha ha, I destroyed you. Better luck next time puny human!" << endl;
    } else {
        cout << "Fuck you Cage, and fuck you Jables! I will get you tenaciuos d" << endl;
    }
}

void robotRound(Boggle& boggle){
        cout << "It's my turn!" << endl;
        boggle.autoSearch();
        displayRobotResult(boggle);
}


bool checkUserInput(const string& userWord, Boggle& boggle){
    if(!boggle.isInDictionary(userWord)){
        cout << userWord << " could not be found in dictionary" << endl;
        return false;
    } else if (!boggle.isLegit(userWord)) {
        cout << userWord << " is too short! try with something 4 or more chars" << endl;
        return false;
    } else if (!boggle.isUnique(userWord)) {
        cout << "Looks like you've used " << userWord << " already!" << endl;
        return false;
    }
    return true;
}

void makeAllCaps(string& userWord){
     for(int i=0; userWord[i] != 0; i++){
        if(userWord[i]<=122 && userWord[i]>=97){
            userWord[i] -= 32;
        }
    }
}



/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
