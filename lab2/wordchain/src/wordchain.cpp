#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void findNeighbours(stack<string> &stackToCheck, queue<stack<string>> &wordQueueOrg,
                    map<string, string> &dictionary, map<string, string> &checkedNeighbours){
    string topWord = stackToCheck.top();
    for(char& c : topWord){
        for(const char& alp : ALPHABET){
            string possibleNeighbour = topWord;
            possibleNeighbour[charNum] = alp;
            //How to use charNum as index? .size and .lenght does not seem to work.
            if(dictionary.find(possibleNeighbour) && !checkedNeighbours.find(possibleNeighbour)){
                //NOTE neither of the operations used in the if returns a bool. Needs to be fixed.
                //Essentially want to make sure the word is a valid word AND that it hasn't been used.
                stack<string> stackCpy = stackToCheck;
                stackCpy.push(possibleNeighbour);
                wordQueueOrg.push(stackCpy);
            }
        }
    }
}

void wordChain(string w1, string w2){

    queue<stack<string>> wordQueue;
    stack<string> startingWord;
    startingWord.push(w1);
    wordQueue.push(startingWord);
    map<string, string> checkedNeighbours;
    checkedNeighbours.insert(w1, w1);

    ifstream input;
    input.open("dictionary.txt");
    string wordFromDict;
    map<string, string> dictionary;

    while(getline(input, wordFromDict)){ //Read each line from dictionary.
        dictionary.insert(wordFromDict, wordFromDict);
    }
    input.close();

    while(!wordQueue.empty()){ //Main loop
        stack<string> stackToCheck = wordQueue.front();
        wordQueue.pop();
        if(stackToCheck.top() == w2){
            //print stack with complete chain
        }
        else {
            findNeighbours(stackToCheck, wordQueue, dictionary, checkedNeighbours);
        }

    }
}

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    // TODO: Finish the program!

    string word1, word2;
    cout << "Please type two words: ";
    cin >> word1 >> word2;
    wordChain(word1, word2);



    return 0;
}
