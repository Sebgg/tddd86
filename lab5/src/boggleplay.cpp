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
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)
    string makeCustom;
    cout << "Do you want to generate a random board? " << endl;
    cin >> makeCustom;
    while(!(makeCustom == "Y" || makeCustom == "y" ||
            makeCustom == "N" || makeCustom == "n")){
        cout << "Please answer yes or no " << endl;
        cin >> makeCustom;
    }

    boggle.makeBoard(makeCustom);
    string guessedWord;
    cout << "Type a word (or press Enter to end your turn)" << endl;
    cin >> guessedWord;

    if(!boggle.isInDictionary(guessedWord) || !boggle.isLegit(guessedWord) || !boggle.isUnique(guessedWord)){
        cout << "coolt" << endl;
    }
    cout << "you did it" << endl;
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
