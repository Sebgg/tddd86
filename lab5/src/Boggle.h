// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "grid.h"
#include "lexicon.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    // TODO: decide the public member functions and declare them
    bool isLegit(const string& word);

    bool isInBoard(const string& word);

    bool isInDictionary(const string& word);

    bool isUnique(const string& word);

    void makeBoard(const string& randomize);

private:
    void setGrid(string& board);
    void printGrid();
    bool checkForInvalid(const string& board);
    vector<string> foundWords;
    Grid<char> grid;
    Lexicon english; //fix dis shit
    // TODO: decide the private member variables/functions and declare them

};

#endif
