#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

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
                     const string& guessedLetters){
    /*Shows all the usefull information */

    cout << "Word: " << chosenWord << "\n"
         << "Guesses left: " << guessCnt << "\n"
         << "Letters guessed: " << guessedLetters <<  endl;
    showFamilies(families);
    //Add guessedLetters and print them.
    //NOTE, fix check so char is in alphabet and not been used before.
    //NOTE, make player choose if it wants to see all families or not.
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
        string &guessedLetters, const bool &userInfo){
    /*runs evil hangman while player still have guesses left.*/

    while(guessCnt > 0){
        cout << "What's your next guess?" << endl;
        cin >> guessedChar;
        //checkChar(guessedChar);
        guessedLetters.push_back(guessedChar);
        //createLargestDict(largestDict, otherDict, currGuess, wordLength);
        createFamilies(dictionary, guessedChar, wordLength, families, defaultKey, chosenWord);
        guessCnt--; //In the end of the while-loop for decrementing the number of guesses.
        if(userInfo){
            printGameStatus(chosenWord, guessCnt, families, guessedLetters);
        }
    }
    cout << "You lose! Pepe is victorious once again >:) sucky sucky" << endl;
}

void readDictionary(vector<string> &dictionary, const int &wordLength){
    /*Creates the initial dictionary based on the first guessed letter and dictionary.txt*/

    ifstream in("dictionary.txt");  ///Users/Hampus/Documents/C++/Qt Projects/tddd86/lab2/evilhangman/res/ for hampus to test
    string wordFromDict;

    while(in >> wordFromDict){ //Read each line from dictionary.
        if(wordFromDict.length() == wordLength){
            dictionary.push_back(wordFromDict);
        }
    }
    in.close();
}
/*)
void checkChar(char &guessedChar){


    //NOTE, Finnish this please Hampus, I don't know how /Pepe

    bool notRight = true;

    for(int i = 0; i < ALPHABET.length(); i++){
        if(guessedChar == ALPHABET.at(i)){
            notRight = false;
        }
    }

    while(notRight){
        pass;
    }
}
*/

int main() {
    /**/

    cout << "Welcome to Hangman." << endl;

    int wordLength;
    int guessCnt;
    char guessedChar;
    string defaultKey;
    string chosenWord;
    string guessedLetters;
    string extraInfo;
    bool userInfo;
    map<string, vector<string> > families;

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

    //checkChar(guessedChar);
    guessCnt--;
    guessedLetters.push_back(guessedChar);

    vector<string> dictionary;
    readDictionary(dictionary, wordLength);
    initDefaultKey(wordLength, defaultKey);
    createFamilies(dictionary, guessedChar, wordLength, families, defaultKey, chosenWord);
    if(userInfo){
        printGameStatus(chosenWord, guessCnt, families, guessedLetters);
    }
    play(dictionary, families, chosenWord, guessCnt, guessedChar, wordLength, defaultKey, guessedLetters, userInfo);
    return 0;
}
