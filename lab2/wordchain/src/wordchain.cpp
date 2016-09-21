#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void printCorrectStack(stack<string> &correctStack, string &w1, string &w2){
    cout << "Chain from " << w2 << " back to " <<  w1 << ":" << endl;
    while(!correctStack.empty()){
        cout << " " << correctStack.top() << " " << flush;
        /*Since we don't want to jump down one line we use flush.
         *Flush is a std function used to make sure output gets sent to
         *the terminal. endl does this too but also moves down one line.*/
        correctStack.pop();
    }
    cout << "Have a nice day!" << endl;
}

void findNeighbours(stack<string> &stackToCheck, queue<stack<string> > &wordQueueOrg,
                    set<string> &dictionary, set<string> &checkedNeighbours){
    string topWord = stackToCheck.top();
    for(unsigned int charNum = 0 ; charNum < topWord.length(); charNum++){
        for(const char& alp : ALPHABET){
            string possibleNeighbour = topWord;
            possibleNeighbour[charNum] = alp;                      
            if(dictionary.find(possibleNeighbour) != dictionary.end()
               && checkedNeighbours.find(possibleNeighbour) == checkedNeighbours.end()){
                //Code above will check if the word is in dictionary
                //by making sure it does not reach the end of the set.
                stack<string> stackCpy = stackToCheck;
                stackCpy.push(possibleNeighbour);
                wordQueueOrg.push(stackCpy);
                checkedNeighbours.insert(possibleNeighbour);
            }
        }
    }
}

void wordChain(string w1, string w2){

    queue<stack<string> > wordQueue;
    stack<string> startingWord;
    startingWord.push(w1);
    wordQueue.push(startingWord);
    set<string> checkedNeighbours;
    checkedNeighbours.insert(w1);

    ifstream input;
    input.open("dictionary.txt");
    string wordFromDict;
    set<string> dictionary;

    while(getline(input, wordFromDict)){ //Read each line from dictionary.
        dictionary.insert(wordFromDict);
    }
    input.close();

    while(!wordQueue.empty()){ //Main loop
        stack<string> stackToCheck = wordQueue.front();
        wordQueue.pop();
        if(stackToCheck.top() == w2){
            printCorrectStack(stackToCheck, w1, w2); //print stack with complete chain
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

    string word1, word2;
    cout << "Please type two words: ";
    cin >> word1 >> word2;
    wordChain(word1, word2);

    return 0;
}
