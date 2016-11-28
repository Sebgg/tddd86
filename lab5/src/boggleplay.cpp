// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
using namespace std;
/*
 * Plays one game of Boggle using the given boggle game state object.
 */

// function declarations
void displayPlayerstats(Boggle &boggle);
void playerRound(Boggle &boggle);
void displayRobotResult(Boggle &boggle);
void robotRound(Boggle &boggle);
bool checkUserInput(const string &userWord, Boggle &boggle);

void playOneGame(Boggle& boggle) {
    string makeCustom;
    cout << "Do you want to randomly generate a board? ";
    getline(cin, makeCustom);
    while(!(makeCustom == "Y" || makeCustom == "y" ||
            makeCustom == "N" || makeCustom == "n")){
        cout << "Please answer yes or no " << endl;
        getline(cin, makeCustom);
    }
    boggle.makeBoard(makeCustom);


    playerRound(boggle);
    robotRound(boggle);
    boggle.resetGame();

    /*
    if(makeCustom == "Y"){
        bool cont = true;
        while(cont){
            string searchWord;
            cout << "Searchword: " << endl;
            cin >> searchWord;
            string ans;
            cout << boggle.english.containsPrefix(searchWord) << " or " << boggle.english.contains(searchWord);
            cin >> ans;

            if(ans == "exit") cont = false;
        }
    }*/
}

void displayPlayerstats(Boggle& boggle){
    int score = boggle.getFoundWords().size(); //Should be changed to a function to get playerscore

    cout << "Your words " << "(" << score << "): "
    << boggle.printFoundWords() << endl;

    cout << "Your score: " << boggle.getScore('p') << endl;

}

void playerRound(Boggle& boggle) {
    string guessedWord;
    bool playing = true;
    while (playing){
        cout << "Type a word (or press Enter to end your turn): ";
        getline(cin, guessedWord);

        for(int i=0; guessedWord[i] != 0; i++){
            if(guessedWord[i]<=122 && guessedWord[i]>=97){
                guessedWord[i] -= 32;
            }
        }

        if(guessedWord.empty()){
            cout << "Shit, I did a fuck" << endl;
            playing = false;
        } else{
            if(checkUserInput(guessedWord, boggle)){
                if(boggle.searchBoard(guessedWord)){
                    boggle.addWord(guessedWord);
                    cout << "You've found a new word!" << endl;
                } else {
                    cout << "That's not a word!" << endl;
                }
            }
        }
        displayPlayerstats(boggle);
    }
}

void displayRobotResult(Boggle& boggle){
    int score = boggle.getRobotWords().size(); //same as above

    cout << "My words " << "(" << score << "): "
    << boggle.printRobotResult() << endl;

    cout << "My score: " << boggle.getScore('r') << endl;

    cout << "Ha ha ha, I destroyed you. Better luck next time puny human!" << endl;
}

void robotRound(Boggle& boggle){
        cout << "It's my turn!" << endl;
        boggle.findAll();
        displayRobotResult(boggle);
}


bool checkUserInput(const string& userWord, Boggle& boggle){
    if(!boggle.isInDictionary(userWord)){
        cout << "Word could not be found in dictionary" << endl;
        return false;
    } else if (!boggle.isLegit(userWord)) {
        cout << "Word is too short! try with something 4 or more chars" << endl;
        return false;
    } else if (!boggle.isUnique(userWord)) {
        cout << "Looks like you've used that one!" << endl;
        return false;
    }
    return true;
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
