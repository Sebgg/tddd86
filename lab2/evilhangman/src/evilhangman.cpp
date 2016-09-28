#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void choseLargestFamily(const map<string, vector<string> >& families, vector<string>& dictionary, string& chosenWord){
    vector<string> largestFamily;
    for(auto& family : families){
        if(family.second.size() > largestFamily.size()){
            largestFamily = family.second;
            chosenWord = family.first;
        }
    }
    dictionary = largestFamily;
}

void showFamilies(const map<string, vector<string> >& families){
    for(auto const& familyKey : families){
        vector<string> currFam = familyKey.second;
        int wordsinFamily = currFam.size();
        cout << familyKey.first << ": " << wordsinFamily << endl;
    }
}

void printGameStatus(const string& chosenWord, const int& guessCnt, const map<string, vector<string> >& families){
    cout << "Word: " << chosenWord << "\n"
         << "Guesses left: " << guessCnt << endl;
    showFamilies(families);
    //Add guessedLetters and print them.
    //NOTE, fix check so char is in alphabet and not been used before.
    //NOTE2, make player chose if it wants to see all families or not.
}

void createFamilies(vector<string>& dictionary, const char& guessedChar, const int& wordLength,
                    map<string, vector<string> >& families, const string& defaultKey, string& chosenWord){
    /*Creates a key for each found family and simultaneoulsy adds the corresponding words.*/
    map<string, vector<string> > newFamilies;
    for(auto const& word : dictionary){ //Go through every word in dict.
        string newFamilyKey = defaultKey; //Create an empty basic key for family to modify.
        for(int c = 0 ; c < wordLength ; c++){ //Iterator used to go through every char in word.
            if(word[c] == guessedChar){
                newFamilyKey[c] = guessedChar; //Change family key one char at a time
            }
        }
        newFamilies[newFamilyKey].push_back(word);
    }
    families = newFamilies;
    choseLargestFamily(families, dictionary, chosenWord);
 }

void initDefaultKey(int wordLength, string& defaultKey){
    /*Function used to initialize a basic template key to be used in map of families.*/
    for(int i = 0 ; i < wordLength ; i++){
        defaultKey += "_";
    }    
}


void play(vector<string> &dictionary, map<string, vector<string> >& families, string& chosenWord,
          int &guessCnt, char &guessedChar, const int &wordLength, const string& defaultKey){
    /*runs evil hangman while player still have guesses left.*/

    while(guessCnt > 0){
        cout << "What's your next guess?" << endl;
        cin >> guessedChar;
        //createLargestDict(largestDict, otherDict, currGuess, wordLength);
        createFamilies(dictionary, guessedChar, wordLength, families, defaultKey, chosenWord);
        cout << dictionary.size() << endl;
        guessCnt--; //In the end of the while-loop for decrementing the number of guesses.
        printGameStatus(chosenWord, guessCnt, families);
    }
    cout << "You lose! Pepe is victorious once again >:) sucky sucky" << endl;
}

void readDictionary(vector<string> &dictionary, const int &wordLength){
    /**/

    ifstream in("/Users/Hampus/Documents/C++/Qt Projects/tddd86/lab2/evilhangman/res/dictionary.txt");
    string wordFromDict;

    while(in >> wordFromDict){ //Read each line from dictionary.
        if(wordFromDict.length() == wordLength){
            dictionary.push_back(wordFromDict);
        }
    }
    in.close();
}

int main() {
    /**/

    cout << "Welcome to Hangman." << endl;

    int wordLength;
    int guessCnt;
    char guessedChar;
    string defaultKey;
    string chosenWord;
    string guessedLetters;
    map<string, vector<string> > families;

    cout << "How long is the word?" << endl;
    cin >> wordLength;

    cout << "How many guesses do you want? (1-26)" << endl;
    cin >> guessCnt;

    cout << "What's the first letter you want to guess on?" << endl;
    cin >> guessedChar;

    guessCnt--;

    vector<string> dictionary;
    readDictionary(dictionary, wordLength);
    initDefaultKey(wordLength, defaultKey);
    createFamilies(dictionary, guessedChar, wordLength, families, defaultKey, chosenWord);
    printGameStatus(chosenWord, guessCnt, families);
    play(dictionary, families, chosenWord, guessCnt, guessedChar, wordLength, defaultKey);
    return 0;
}
