#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/* -----------------NOTE-------------------
 * Needs to be fixed with chosing largest family.
 * rn it does not keep a letter if it is revealed.
 * it is like the game forgets what has been done before.*/

bool checkChar(const char &guessedChar, set<char>& guessedLetters){
    /*Makes sure the guessed character is in the alphabet and has not been used earlier*/

    bool notRight = false;

    for(auto const& character : ALPHABET){
        if(guessedChar == character && guessedLetters.find(guessedChar) == guessedLetters.end()){
            notRight = true;
        }
    }
    return notRight;
}

void chooseLargestFamily(const map<string, vector<string> >& families, vector<string>& dictionary, string& chosenWord){
    /*Compares all families and chooses the largest for the dictionary*/

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
    /*Shows the families for the user*/

    for(auto const& familyKey : families){
        vector<string> currFam = familyKey.second;
        int wordsinFamily = currFam.size();
        cout << familyKey.first << ": " << wordsinFamily << endl;
    }
}

void printGameStatus(const string& chosenWord, const int& guessCnt, const map<string, vector<string> >& families,
                     const set<char>& guessedLetters, const bool& userInfo){
    /*Shows all the usefull information */

    cout << "Word: " << chosenWord << "\n"
         << "Guesses left: " << guessCnt << "\n"
         << "Guessed letters: " << flush;
    for(auto const& letter : guessedLetters){
        cout << letter << " " << flush;
    }
    cout << endl;
    if(userInfo){
        showFamilies(families);
    }
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
    chooseLargestFamily(families, dictionary, chosenWord);
 }

void initDefaultKey(int wordLength, string& defaultKey){
    /*Function used to initialize a basic template key to be used in map of families.*/

    for(int i = 0 ; i < wordLength ; i++){
        defaultKey += "_";
    }
}


void play(vector<string> &dictionary, map<string, vector<string> >& families, string& chosenWord,
          int &guessCnt, char &guessedChar, const int &wordLength, const string& defaultKey,
        set<char> &guessedLetters, const bool &userInfo){
    /*runs evil hangman while player still have guesses left.*/

    while(guessCnt > 0){
        cout << "What's your next guess?" << endl;
        cin >> guessedChar;

        while(!checkChar(guessedChar, guessedLetters)){
            cout << "Invalid input. Remember, only letters "
                 << "and do not guess the same letter twice.\n" << endl;
            cout << "What's your next guess?" << endl;
            cin >> guessedChar;
        }

        guessedLetters.insert(guessedChar);
        createFamilies(dictionary, guessedChar, wordLength, families, defaultKey, chosenWord);
        guessCnt--; //In the end of the while-loop for decrementing the number of guesses.
        printGameStatus(chosenWord, guessCnt, families, guessedLetters, userInfo);
    }
    cout << "You lose! Pepe is victorious once again >:)" << endl;
}

void readDictionary(vector<string> &dictionary, const int &wordLength){
    /*Creates the initial dictionary based on the first guessed letter and dictionary.txt*/

    //ifstream in("/Users/Hampus/Documents/C++/Qt Projects/tddd86/lab2/evilhangman/res/dictionary.txt");  // for OSX
    ifstream in("dictionary.txt");  // for linux
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
    set<char> guessedLetters;
    string extraInfo;
    bool userInfo = false;
    map<string, vector<string> > families;

    cout << "Do you want to know extra information about the game? Y/N: " << endl;
    cin >> extraInfo;

    if(extraInfo == "Y" || extraInfo == "y"){ //checks to see if the users wants to see extra information about the game
        userInfo = true;
    }

    cout << "How long is the word?" << endl;
    cin >> wordLength;

    cout << "How many guesses do you want? (1-26)" << endl;
    cin >> guessCnt;

    cout << "What's the first letter you want to guess on?" << endl;
    cin >> guessedChar;

    while(checkChar(guessedChar, guessedLetters) != true){
        cout << "Invalid input, use only lower case letters in the English alphabet.\n" << endl;
        cout << "What's the first letter you want to guess on?" << endl;
        cin >> guessedChar;
    }

    guessCnt--;
    guessedLetters.insert(guessedChar);

    vector<string> dictionary;
    readDictionary(dictionary, wordLength);
    initDefaultKey(wordLength, defaultKey);
    createFamilies(dictionary, guessedChar, wordLength, families, defaultKey, chosenWord);    
    printGameStatus(chosenWord, guessCnt, families, guessedLetters, userInfo);
    play(dictionary, families, chosenWord, guessCnt, guessedChar, wordLength, defaultKey, guessedLetters, userInfo);
    return 0;
}
