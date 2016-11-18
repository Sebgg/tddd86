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

        if(boggle.isInDictionary(guessedWord) && boggle.isLegit(guessedWord) && boggle.isUnique(guessedWord)){
            //Magical shit happens here.
            boggle.addWord(guessedWord);
            cout << "You found a new word! " << guessedWord << endl;
        } else if(guessedWord.size() == 0){
            //wow, robots turn!
        } else {
            cout << "Invalid input" << endl;
        }

        if(boggle.getFoundWords().size() > 3){
            playing = false;
        }
    }
    boggle.resetGame();
}

void displayPlayerstats(Boggle& boggle){
    cout << "Your words " << "(" << boggle.getFoundWords().size() << "): "
    << boggle.printFoundWords() << endl;

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
