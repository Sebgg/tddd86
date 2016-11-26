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
// TODO: include any other header files you need

using namespace std;
/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void displayPlayerstats(Boggle &boggle);

void displayRobotResult(Boggle &boggle);

void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)
    string makeCustom;
    bool playing;
    cout << "Do you want to generate a random board? " << endl;
    cin >> makeCustom;
    while(!(makeCustom == "Y" || makeCustom == "y" ||
            makeCustom == "N" || makeCustom == "n")){
        cout << "Please answer yes or no " << endl;
        cin >> makeCustom;
    }
    playing = true;
    boggle.makeBoard(makeCustom);


    while(playing){
        displayPlayerstats(boggle);
        string guessedWord;
        cout << "Type a word (or press Enter to end your turn)" << endl;
        cin >> guessedWord;

        for(int i=0;guessedWord[i]!=0;i++){
            if(guessedWord[i]<=122 && guessedWord[i]>=97){
                guessedWord[i] -= 32;
            }
        }
        // Convert string to uppercase via ascii table. Very fast. Much Optimization.



        if(boggle.isInDictionary(guessedWord) && boggle.isLegit(guessedWord) && boggle.isUnique(guessedWord)){
            if(boggle.searchBoard(guessedWord)){
                boggle.addWord(guessedWord);
                cout << "You found a new word! " << guessedWord << endl;
            } else {
                cout << "Word not on the board :-(" << endl;
            }
        } else if(guessedWord.empty()){
            //wow, robots turn!
            cout << "It's my turn!" << endl;
            boggle.findAll();
            displayRobotResult(boggle);
            playing = false;
        } else {
            cout << "Invalid input" << endl;
        }

    }
    boggle.resetGame();
}

void displayPlayerstats(Boggle& boggle){
    int score = boggle.getFoundWords().size(); //Should be changed to a function to get playerscore

    cout << "Your words " << "(" << score << "): "
    << boggle.printFoundWords() << endl;

    cout << "Your score: " << score << endl;

}

void displayRobotResult(Boggle& boggle){
    int score = boggle.getRobotWords().size(); //same as above

    cout << "My words " << "(" << score << "): "
    << boggle.printRobotResult() << endl;

    cout << "My score: " << score << endl;

    cout << "Ha ha ha, I destroyed you. Better luck next time puny human!" << endl;
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
