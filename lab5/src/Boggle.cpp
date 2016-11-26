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

void Boggle::makeBoard(const string& randomize){
    string board = "";
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
        cout << "Write the 16 letters you want to use" << endl;
        cin >> board;
        while(board.size() != NUM_CUBES || !checkForInvalid(board)){
            cout << "Invalid input, should be 16 letters" << endl;
            cin >> board;
        }
        for(int i=0;board[i]!=0;i++){
            if(board[i]<=122 && board[i]>=97){
                board[i] -= 32;
            }
        }
        // Convert string to uppercase via ascii table. Very fast. Much Optimization.
        for(const auto& s : board){
            Cube *c = new Cube(s);
            cubes.push_back(c);
        }
        setGrid(cubes);
    }

    cout << "It's your turn!" << endl;
    printGrid();
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
                        tempWord.erase(tempWord.begin()); // word with out first char
                        searchWord(tempWord, row, col, found);
                        neighbour.setVisited(); // Unmark cube
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

void Boggle::findAll(){
    for(size_t row = 0; row < BOARD_SIZE; row++){
        for(size_t col = 0; col < BOARD_SIZE; col++){
            string word = "a";
            while(word != ""){
                word = autoSearch(row, col, "");
                robotWords.push_back(word);
            }
        }
    }
}

string Boggle::autoSearch(int nRow, int nCol, string word){
    if(isInDictionary(word) && isLegit(word) && isUnique(word) && isRUnique(word)) {
        return word;
    } else {
        for(int row = nRow-1; row < nRow+2; row++){
            for(int col = nCol-1; col < nCol+2; col++){
                if(grid.inBounds(row, col) && (row != nRow || col != nCol)){
                    Cube neighbour = cubeMap[grid.get(row, col)];
                    if(english.containsPrefix(word + neighbour.getTop()) && !neighbour.isVisited()){
                        neighbour.setVisited();
                        word += neighbour.getTop();
                        word += autoSearch(row, col, word);
                        neighbour.setVisited();
                    }
                }
            }
        }
        return word;
    }
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

void Boggle::printGrid() {
    for(size_t i = 0; i < BOARD_SIZE; i++){
        for(size_t j = 0; j < BOARD_SIZE; j++){
            int pos = grid.get(i, j);
            cout << cubeMap.at(pos).getTop();
        }
        cout << endl;
    }
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
        Words += word;
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
        Words += word;
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
}

void Boggle::resetGame() {
    foundWords.clear();
    cubeMap.clear();
}
