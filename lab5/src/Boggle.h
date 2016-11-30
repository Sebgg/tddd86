
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

    /*
     * Checks if the word is at least 4 characters long
     */
    bool isLegit(const string& word);

    /*
     * The
     */
    void autoSearch();

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

    int getScore(const char& unit);

    Lexicon english; //Temporarily public for testing reasons


private:
    void setGrid(vector<Cube*>& cubes);
    void printGrid();
    bool checkForInvalid(const string& board);
    vector<string> foundWords;
    vector<string> robotWords;
    map<int, Cube> cubeMap;
    Grid<int> grid;

    int playerScore;
    int robotScore;
    void searchWord(string word, int nRow, int nCol, bool &found);
    void addScore(const string& word, const char& unit);
    void autoSearchHelp(int nRow, int nCol, string word);
};

#endif
