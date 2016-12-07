#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void playAgain(int& guessCnt, bool& playing){
    guessCnt = 0;
    string playAgain;
    cout << "Do you want to play again? Y/N" << endl;
    cin >> playAgain;
    if(playAgain == "N" || playAgain == "n"){
        playing = false;
    }
}

bool checkChar(const char &guessedChar, const set<char>& guessedLetters){
    /*Makes sure the guessed character is in the alphabet and has not been used earlier*/

    for(auto const& character : ALPHABET){
        if(guessedChar == character && guessedLetters.find(guessedChar) == guessedLetters.end()){
            return true;
        }
    }
    return false;
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

void showExtraInfo(const vector<string>& dictionary){
    /*Shows how many words are left in the dictionary to choose from*/

    cout << "Words to choose from: " << dictionary.size() << endl;
}

void printGameStatus(const string& chosenWord, const int& guessCnt, const set<char>& guessedLetters,
                    const bool& userInfo, const vector<string>& dictionary){
    /*Shows all the usefull information */

    cout << "Word: " << chosenWord << "\n"
         << "Guesses left: " << guessCnt << "\n"
         << "Guessed letters: " << flush;
    for(auto const& letter : guessedLetters){
        cout << letter << " " << flush;
    }
    cout << endl;
    if(userInfo){
        showExtraInfo(dictionary);
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

void readDictionary(vector<string> &dictionary, const int &wordLength){
    /*Creates the initial dictionary based on the word length letter and dictionary.txt*/

    //ifstream in("/Users/Hampus/Documents/C++/Qt Projects/tddd86/lab2/evilhangman/res/dictionary.txt");  // for OSX
    ifstream in("dictionary.txt"); // for linux
    string wordFromDict;
    dictionary.clear();

    while(in >> wordFromDict){ //Read each line from dictionary.
        if(wordFromDict.length() == wordLength){
            dictionary.push_back(wordFromDict);
        }
    }
    in.close();
}

void play(vector<string>& dictionary, map<string, vector<string> >& families, string& chosenWord,
          int& guessCnt, char &guessedChar, int &wordLength, string& defaultKey,
        set<char> &guessedLetters, bool &userInfo, bool& playing){
    /*runs evil hangman while player still have guesses left.*/

    while(playing){
        string extraInfo;
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

        families.clear();

        readDictionary(dictionary, wordLength);
        while(dictionary.empty()){
            cout << "There aren't any words of that length in the dictionary, try again!" << endl;
            cin >> wordLength;
            readDictionary(dictionary, wordLength);
        }

        cout << "How many guesses do you want? (1-26)" << endl;
        cin >> guessCnt;

        initDefaultKey(wordLength, defaultKey);
        while(guessCnt > 0){
            string oldKey = defaultKey;
            cout << "What's your next guess?" << endl;
            cin >> guessedChar;

            while(!checkChar(guessedChar, guessedLetters)){
                cout << "Invalid input. Remember, only letters "
                     << "and do not guess the same letter twice." << endl;
                cout << "What's your next guess?" << endl;
                cin >> guessedChar;
            }

            guessedLetters.insert(guessedChar);
            createFamilies(dictionary, guessedChar, wordLength, families, defaultKey, chosenWord);

            if(oldKey == defaultKey){
              guessCnt--;
            }

            printGameStatus(chosenWord, guessCnt, guessedLetters, userInfo, dictionary);
            if(checkWin(defaultKey)){
                cout << "Congratulations, you beat me!\n" << endl;
                playAgain(guessCnt, playing);
            }
        }
        if(!checkWin(defaultKey)){
            cout << "You lose!" << endl;
            cout << "My word was " << dictionary.front() << endl;
            playAgain(guessCnt, playing);
        }
    }
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

    play(dictionary, families, chosenWord, guessCnt, guessedChar, wordLength, defaultKey,
             guessedLetters, userInfo, playing);
    return 0;
}
