#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void findNeighbours(stack<string> &stackToCheck, queue<stack<string>> &wordQueueOrg, map<string, string> &dictionary){
    string topWord = stackToCheck.top();
    for(char& c : topWord){
        for(const char& alp : ALPHABET){
            string possibleNeighbour = topWord;
            possibleNeighbour.replace(topWord.find(c), 1, alp);
            if(dictionary.find(possibleNeighbour)){
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

    ifstream input;
    input.open("dictionary.txt");
    string wordFromDict;
    map<string, string> dictionary;

    while(getline(input, wordFromDict)){
        dictionary.insert(wordFromDict, wordFromDict);
    }
    input.close();

    while(!wordQueue.empty()){
        stack<string> stackToCheck = wordQueue.front();
        wordQueue.pop();
        if(stackToCheck.top() == w2){
            //print stack with complete chain
        }
        else {
            findNeighbours(stackToCheck, wordQueue, dictionary);
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
