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
#include "Cube.h"
using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const size_t MIN_WORD_LENGTH = 4;
    const size_t BOARD_SIZE = 4;

    // TODO: decide the public member functions and declare them
    bool isLegit(const string& word);

    void findAll();

    string autoSearch(int nRow, int nCol, string word);

    bool isInDictionary(const string& word);

    bool isUnique(const string& word);

    bool isRUnique(const string& word);

    void makeBoard(const string& randomize);

    string printFoundWords();

    vector<string> getFoundWords();

    vector<string> getRobotWords();

    void addWord(const string& word);

    void resetGame();

    bool searchBoard( string& word);

    string printRobotResult();

private:
    void setGrid(vector<Cube*>& cubes);
    void printGrid();
    bool checkForInvalid(const string& board);
    vector<string> foundWords;
    vector<string> robotWords;
    map<int, Cube> cubeMap;
    Grid<int> grid;
    Lexicon english;
    void searchWord(string word, int nRow, int nCol, bool &found);
};

#endif
