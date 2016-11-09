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
    grid.resize(BOARD_SIZE, BOARD_SIZE);
    if(randomize == "Y" || randomize == "y"){
        for(const auto& s : CUBES){
            int rand = randomInteger(0, 5);
            board += s[rand];
        }
        setGrid(board);
        shuffle(grid);
    } else {
        cout << "Write the 16 letters you want to use" << endl;
        cin >> board;
        bool onlyLetters = checkForInvalid(board);
        while(board.size() != NUM_CUBES || !onlyLetters){
            cout << "Invalid input, should be 16 letters" << endl;
            cin >> board;
        }
        setGrid(board);

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
    return (dict.contains(word));
}

bool Boggle::isUnique(const string& word){
    for(const string& s : foundWords){
        if(word == s) return false;
    }
    foundWords.push_back(word);
    return true;
}

void Boggle::printGrid() {
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            cout << grid.get(i, j);
        }
        cout << endl;
    }
}

void Boggle::setGrid(string& board) {
    for(int i = BOARD_SIZE-1; i >= 0; i--){
        for(int j = BOARD_SIZE-1; j >= 0; j--){
            grid.set(i, j, board.back());
            board.pop_back();
        }
    }
}

// TODO: implement the members you declared in Boggle.h
