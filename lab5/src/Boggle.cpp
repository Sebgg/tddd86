// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "grid.h"
#include <string>
#include <algorithm>
#include "lexicon.h"
#include <cctype>
#include "Cube.h"

using namespace std;

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

void Boggle::makeBoard(const string& randomize, const string& board){
    playerScore = 0;
    robotScore = 0;
    english.addWordsFromFile("EnglishWords.dat");
    grid.resize(BOARD_SIZE, BOARD_SIZE);
    vector<Cube*> cubes;
    if(randomize == "Y" || randomize == "y"){
        for(const auto& s : CUBES){
            Cube *c = new Cube(s);
            c->setRandom();
            cubes.push_back(c);
        }
        setGrid(cubes);
        shuffle(grid);
    } else {
        for(const auto& s : board){
            Cube *c = new Cube(s);
            cubes.push_back(c);
        }
        setGrid(cubes);
    }

}

bool Boggle::searchBoard(string& word){
    //Main function for the player search algorithm
    bool found = false;
    for(size_t nRow = 0; nRow < BOARD_SIZE; nRow++){
        for(size_t nCol = 0; nCol < BOARD_SIZE; nCol++){
            if(cubeMap[grid.get(nRow, nCol)].getTop() == word.front()){
                string tempWord = word;
                tempWord.erase(tempWord.begin());
                cubeMap[grid.get(nRow, nCol)].setVisited();
                searchWord(tempWord, nRow, nCol, found);
                cubeMap[grid.get(nRow, nCol)].setVisited();
            }
        }
    }
    return found;
}

void Boggle::searchWord(string word, int nRow, int nCol, bool &found){
    if(word.size() == 0) {
        found = true;
    } else {
        for(int row = nRow-1; row < nRow+2; row++){
            for(int col = nCol-1; col < nCol+2; col++){
                if(grid.inBounds(row, col) && (row != nRow || col != nCol)){
                    Cube neighbour = cubeMap[grid.get(row, col)];
                    if(neighbour.getTop() == word.front() && !neighbour.isVisited()){
                        neighbour.setVisited(); // Mark cube as visited
                        string tempWord = word;
                        tempWord.erase(tempWord.begin()); // word without first char
                        searchWord(tempWord, row, col, found);
                        neighbour.setVisited(); // Unmark cube
                    }
                }
            }
        }
    }
}

void Boggle::autoSearch(){
    for(size_t nRow = 0; nRow < BOARD_SIZE; nRow++){
        for(size_t nCol = 0; nCol < BOARD_SIZE; nCol++){
            string s(1, cubeMap[grid.get(nRow, nCol)].getTop());
            cubeMap[grid.get(nRow, nCol)].setVisited();
            autoSearchHelp(nRow, nCol, s);
            cubeMap[grid.get(nRow, nCol)].setVisited();
        }
    }
}

void Boggle::autoSearchHelp(int nRow, int nCol, string word){
    if(isInDictionary(word) && isLegit(word) && isUnique(word) && isRUnique(word)){
        addScore(word, 'r');
        robotWords.push_back(word);
    } else {
        for(int row = nRow-1; row < nRow+2; row++){
            for(int col = nCol-1; col < nCol+2; col++){
                if(grid.inBounds(row, col) && (row != nRow || col != nCol)){
                    if(english.containsPrefix(word + cubeMap[grid.get(row, col)].getTop())
                            && !cubeMap[grid.get(row, col)].isVisited()){
                        cubeMap[grid.get(row, col)].setVisited(); // Mark cube as visited
                        string tempWord = word;
                        tempWord += cubeMap[grid.get(row, col)].getTop();
                        autoSearchHelp(row, col, tempWord);
                        cubeMap[grid.get(row, col)].setVisited(); // Unmark cube
                    }
                }
            }
        }
    }
}

bool Boggle::checkForInvalid(const string& board){
    for(const auto& c : board){
        if(ALPHABET.find_first_of(c) == string::npos){
            return false;
        }
    }
    return true;
}

bool Boggle::isLegit(const string& word){
    return word.size() >= MIN_WORD_LENGTH && word.size() > 0;
}


bool Boggle::isInDictionary(const string& word){
    return (english.contains(word));
}

bool Boggle::isUnique(const string& word){
    for(const auto &s : foundWords){
        if(word == s) return false;
    }
    return true;
}

bool Boggle::isRUnique(const string &word){
    for(const auto &s : robotWords){
        if(word == s) return false;
    }
    return true;
}

string Boggle::printGrid() {
    string board;
    for(size_t i = 0; i < BOARD_SIZE; i++){
        for(size_t j = 0; j < BOARD_SIZE; j++){
            int pos = grid.get(i, j);
            board += cubeMap.at(pos).getTop();
        }
        board += "\n";
    }
    return board;
}

void Boggle::setGrid(vector<Cube*>& cubes) {
    int counter = 15;
    for(int i = BOARD_SIZE-1; i >= 0; i--){
        for(int j = BOARD_SIZE-1; j >= 0; j--){
            cubeMap[counter] = *cubes.back();
            grid.set(i, j, counter);
            cubes.pop_back();
            counter--;
        }
    }
}

string Boggle::printFoundWords(){
    string Words = "{";
    for(const auto word : foundWords){
        Words += "\"";
        Words += word;
        Words += "\"";
        if(word != foundWords.back()){
            Words += ", ";
        }
    }
    Words += "}";
    return Words;
}

string Boggle::printRobotResult(){
    string Words = "{";
    for(const auto word : robotWords){
        Words += "\"";
        Words += word;
        Words += "\"";
        if(word != robotWords.back()){
            Words += ", ";
        }
    }
    Words += "}";
    return Words;
}

vector<string> Boggle::getFoundWords(){
    return foundWords;
}

vector<string> Boggle::getRobotWords(){
    return robotWords;
}

void Boggle::addWord(const string& word){
    foundWords.push_back(word);
    addScore(word, 'p');
}

void Boggle::addScore(const string &word, const char& unit){
    int score = word.size() - 3;
    if(unit == 'p'){
        playerScore += score;
    } else {
        robotScore += score;
    }
}

int Boggle::getScore(const char &unit){
    if(unit == 'p'){
        return playerScore;
    } else {
        return robotScore;
    }
}

void Boggle::resetGame() {
    foundWords.clear();
    cubeMap.clear();
    robotWords.clear();
    playerScore = 0;
    robotScore = 0;
}
