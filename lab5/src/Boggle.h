
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
     * Robot searches through board to find every word.
     */
    void autoSearch();

    /*
     * Checks if word can be found in English dictionary
     */
    bool isInDictionary(const string& word);

    /*
     * Checks if the word has been used before by the user
     */
    bool isUnique(const string& word);

    /*
     * Checks if the word has been used before by the computer
     */
    bool isRUnique(const string& word);

    /*
     * Creates the board, lexicon, and the cube objects
     */
    void makeBoard(const string& randomize, const string& board);

    /*
     * Prints all user words
     */
    string printFoundWords();

    /*
     * Returns the vector containing user's words
     */
    vector<string> getFoundWords();

    /*
     * Returns the vector containing computer's words
     */
    vector<string> getRobotWords();

    /*
     * Adds valid word to foundWords
     */
    void addWord(const string& word);

    /*
     * Resets the game by clearing all words and resetting score
     */
    void resetGame();

    /*
     * Loops through the board searching for the beginning letter of user's word
     */
    bool searchBoard(string& word);

    /*
     * Prints computer words and score to terminal output
     */
    string printRobotResult();

    /*
     * Returns the score of either player och computer, depending on input char
     */
    int getScore(const char& unit);

    /*
     * Prints grid to terminal output
     */
    string printGrid();

    /*
     * Controls that the input for custom board only contains letters
     */
    bool checkForInvalid(const string& board);

private:

    /*
     * Places all cubes on the grid and maps them.
     */
    void setGrid(vector<Cube*>& cubes);

    /*
     * Recursive function searching board for given word
     */
    void searchWord(string word, int nRow, int nCol, bool &found);

    /*
     * Adds the correct score for either player or computer
     */
    void addScore(const string& word, const char& unit);

    /*
     * Recursive function searching the board for all words
     */
    void autoSearchHelp(int nRow, int nCol, string word);

    vector<string> foundWords;
    vector<string> robotWords;
    map<int, Cube> cubeMap;
    Grid<int> grid;
    Lexicon english;
    int playerScore;
    int robotScore;
};

#endif
