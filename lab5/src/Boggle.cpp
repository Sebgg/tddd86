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
        //Ska ändras så att den implementerar cube klassen
        cout << "Write the 16 letters you want to use" << endl;
        cin >> board;
        bool onlyLetters = checkForInvalid(board);
        while(board.size() != NUM_CUBES || !onlyLetters){
            cout << "Invalid input, should be 16 letters" << endl;
            cin >> board;
        }
        for(const auto& s : board){
            Cube *c = new Cube(s);
            cubes.push_back(c);
        }
        setGrid(cubes);

    }

    cout << "It's your turn!" << endl;
    printGrid();
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
    return word.size() >= MIN_WORD_LENGTH;
}

bool Boggle::isInBoard(const string& word){}

bool Boggle::isInDictionary(const string& word){
    return (english.contains(word));
}

bool Boggle::isUnique(const string& word){
    for(const auto &s : foundWords){
        if(word == s) return false;
    }
    return true;
}

void Boggle::printGrid() {
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
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

vector<string> Boggle::getFoundWords(){
    return foundWords;
}

void Boggle::addWord(const string& word){
    foundWords.push_back(word);
}
