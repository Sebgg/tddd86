#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void filterDictionaries(vector<string> &dictionary,  const int wordLength){
    /*Gets all the words from the other dictionary and inserts them into a new dictionary, overwriting the largest*/

    map<string, vector<string> > wordFamilies;
    for(string word : dictionary){
        for(int i = 0; i < wordLength; i++){
            if(string[i] == currGuess){
                //Finish looping through the word before adding to map
            }
        }

    }

}

void play(set<string> &dictionary, set<string> &largestDict, set<string> &otherDict,
          int &guessCnt, char &currGuess, const int &wordLength){
    /**/

    while(guessCnt >= 0){
        cout << "What's your next guess?" << endl;
        cin >> currGuess;
        createLargestDict(largestDict, otherDict, currGuess, wordLength);
        guessCnt--; //In the end of the while-loop for decrementing the number of guesses.
    }
}

void readDictionary(vector<string> &dictionary, const int &wordLength){
    /**/

    ifstream in("dictionary.txt");
    string wordFromDict;

    while(in >> wordFromDict){ //Read each line from dictionary.
        if(wordFromDict.length() == wordLength){
            dictionary.insert(wordFromDict);
        }
    }
    in.close();
}

int main() {
    /**/

    cout << "Welcome to Hangman." << endl;

    int wordLength;
    int guessCnt;
    char currGuess;

    cout << "How long is the word?" << endl;
    cin >> wordLength;

    cout << "How many guesses do you want? (1-26)" << endl;
    cin >> guessCnt;

    cout << "What's the first letter you want to guess on?" << endl;
    cin >> currGuess;

    vector<string> dictionary;
    readDictionary(dictionary);
    play();
    return 0;
}
