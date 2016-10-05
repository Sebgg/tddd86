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

void initializeGame(int& wordLength, int& guessCnt, char& guessedChar, string& defaultKey, string& chosenWord,
                    set<char>& guessedLetters, bool& userInfo, map<string, vector<string> >& families, vector<string>& dictionary,
                    bool& playing);

void playAgain(int& wordLength, int& guessCnt, char& guessedChar, string& defaultKey, string& chosenWord,
                    set<char>& guessedLetters, bool& userInfo, map<string, vector<string> > families,
                    vector<string>& dictionary, bool& playing){
    string playAgain;
    cout << "Do you want to play again? Y/N" << endl;
    cin >> playAgain;
    if(playAgain == "Y" || playAgain == "y"){
        initializeGame(wordLength, guessCnt, guessedChar, defaultKey, chosenWord, guessedLetters,
                       userInfo, families, dictionary, playing);
    } else {
        guessCnt = 0;
        playing = false;
    }
}

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

bool checkWin(const string& defaultKey){
    /*Checks if the player has guessed all letters correctly*/

    for(auto const& c : defaultKey){
        if(c == '_'){
            return false;
        }
    }
    return true;
}

void chooseLargestFamily(const map<string, vector<string> >& families, vector<string>& dictionary, string& chosenWord,
                         string& defaultKey){
    /*Compares all families and chooses the largest for the dictionary*/

    vector<string> largestFamily;
    string largestFamilyKey = defaultKey;
    for(auto& family : families){
        if(family.second.size() > largestFamily.size()){
            largestFamily = family.second;
            chosenWord = family.first;
            largestFamilyKey = family.first;
        }
    }
    dictionary = largestFamily;
    defaultKey = largestFamilyKey;
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
                    map<string, vector<string> >& families, string& defaultKey, string& chosenWord){
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
    chooseLargestFamily(families, dictionary, chosenWord, defaultKey);
 }

void initDefaultKey(int wordLength, string& defaultKey){
    /*Function used to initialize a basic template key to be used in map of families.*/
    string placeHolder;
    for(int i = 0 ; i < wordLength ; i++){
        placeHolder += "_";
    }
    defaultKey = placeHolder;
}




void play(vector<string>& dictionary, map<string, vector<string> >& families, string& chosenWord,
          int& guessCnt, char &guessedChar, int &wordLength, string& defaultKey,
        set<char> &guessedLetters, bool &userInfo, bool& playing){
    /*runs evil hangman while player still have guesses left.*/

    while(playing){
        while(guessCnt > 0){
            string oldKey = defaultKey;
            cout << "What's your next guess?" << endl;
            cin >> guessedChar;

            while(checkChar(guessedChar, guessedLetters) != true){
                cout << "Invalid input. Remember, only letters "
                     << "and do not guess the same letter twice." << endl;
                cout << "What's your next guess?" << endl;
                cin >> guessedChar;
            }

            guessedLetters.insert(guessedChar);
            createFamilies(dictionary, guessedChar, wordLength, families, defaultKey, chosenWord);
            if(checkWin(defaultKey)){
                printGameStatus(chosenWord, guessCnt, families, guessedLetters, userInfo);
                cout << "Congratulations, you beat me!\n" << endl;
                playAgain(wordLength, guessCnt, guessedChar, defaultKey, chosenWord, guessedLetters,
                               userInfo, families, dictionary, playing);
            }
            if(oldKey == defaultKey){
              guessCnt--;
            }
            //In the end of the while-loop for decrementing the number of guesses.
            printGameStatus(chosenWord, guessCnt, families, guessedLetters, userInfo);
        }
        if(!checkWin(defaultKey)){
            printGameStatus(chosenWord, guessCnt, families, guessedLetters, userInfo);
            cout << "You lose!\n" << endl;
            cout << "My word was " << dictionary.front() << endl;
            playAgain(wordLength, guessCnt, guessedChar, defaultKey, chosenWord, guessedLetters,
                           userInfo, families, dictionary, playing);
        }
    }
}

void readDictionary(vector<string> &dictionary, const int &wordLength){
    /*Creates the initial dictionary based on the first guessed letter and dictionary.txt*/

    //ifstream in("/Users/Hampus/Documents/C++/Qt Projects/tddd86/lab2/evilhangman/res/dictionary.txt");  // for OSX
    ifstream in("dictionary.txt"); // for linux
    string wordFromDict;

    while(in >> wordFromDict){ //Read each line from dictionary.
        if(wordFromDict.length() == wordLength){
            dictionary.push_back(wordFromDict);
        }
    }
    in.close();
}

void initializeGame(int& wordLength, int& guessCnt, char& guessedChar, string& defaultKey, string& chosenWord,
                    set<char>& guessedLetters, bool& userInfo, map<string, vector<string> >& families,
                    vector<string>& dictionary, bool& playing){
    /*Initializes the game and its constants*/

    string extraInfo;
    playing = true;
    guessedLetters.clear();
    chosenWord = "";

    cout << "Do you want to know extra information about the game? Y/N: " << endl;
    cin >> extraInfo;

    if(extraInfo == "Y" || extraInfo == "y"){ //checks to see if the users wants to see extra information about the game
        userInfo = true;
    } else {
        userInfo = false;
    }

    cout << "How long is the word?" << endl;
    cin >> wordLength;

    cout << "How many guesses do you want? (1-26)" << endl;
    cin >> guessCnt;

    cout << "What's the first letter you want to guess on?" << endl;
    cin >> guessedChar;

    while(!checkChar(guessedChar, guessedLetters)){
        cout << "Invalid input, use only lower case letters in the English alphabet." << endl;
        cout << "What's the first letter you want to guess on?" << endl;
        cin >> guessedChar;
    }

    guessCnt--;
    guessedLetters.insert(guessedChar);

    readDictionary(dictionary, wordLength);
    while(dictionary.empty()){
        cout << "There aren't any words of that length in the dictionary, try again!" << endl;
        cin >> wordLength;
        readDictionary(dictionary, wordLength);
    }
    initDefaultKey(wordLength, defaultKey);
    createFamilies(dictionary, guessedChar, wordLength, families, defaultKey, chosenWord);
    printGameStatus(chosenWord, guessCnt, families, guessedLetters, userInfo);
}


int main() {
    /*Main function for the program*/


    cout << "Welcome to Hangman." << endl;

    int wordLength;
    int guessCnt;
    char guessedChar;
    string defaultKey;
    string chosenWord;
    set<char> guessedLetters;
    bool userInfo;
    map<string, vector<string> > families;
    vector<string> dictionary;
    bool playing = true;

    initializeGame(wordLength, guessCnt, guessedChar, defaultKey, chosenWord, guessedLetters,
                   userInfo, families, dictionary, playing);
    play(dictionary, families, chosenWord, guessCnt, guessedChar, wordLength, defaultKey,
             guessedLetters, userInfo, playing);
    return 0;
}
