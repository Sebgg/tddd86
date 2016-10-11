#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void printCorrectStack(stack<string> &correctStack, string &w1, string &w2){
    /*Prints the wordchain when the correct one is found.*/

    cout << "Chain from " << w2 << " back to " <<  w1 << ":" << endl;
    while(!correctStack.empty()){
        cout << correctStack.top() << " ";// << flush;
        /*Since we don't want to jump down one line we use flush.
         *Flush is a std function used to make sure output gets sent to
         *the terminal. endl does this too but also moves down one line.*/
        correctStack.pop();
    }
    cout << "\nHave a nice day!" << endl;
}

void findNeighbours(stack<string> &stackToCheck, queue<stack<string> > &wordQueueOrg,
                    set<string> &dictionary, set<string> &checkedNeighbours){
    /*Finds and collects neighbours to top word in current stack.*/

    string topWord = stackToCheck.top();
    for(unsigned int charNum = 0 ; charNum < topWord.length(); charNum++){
        for(const char& alp : ALPHABET){
            string possibleNeighbour = topWord;
            possibleNeighbour[charNum] = alp;                      
            if(dictionary.find(possibleNeighbour) != dictionary.end()
               && checkedNeighbours.find(possibleNeighbour) == checkedNeighbours.end()){
                /*Code above will check if the word is in dictionary
                *by making sure it does not reach the end of the set.*/
                stack<string> stackCpy = stackToCheck;
                stackCpy.push(possibleNeighbour);
                wordQueueOrg.push(stackCpy);
                checkedNeighbours.insert(possibleNeighbour);
            }
        }
    }
}

void createDictionary(set<string> &dictionary, const unsigned int& wordLength){
    ifstream input("/Users/Hampus/Documents/C++/Qt Projects/tddd86/lab2/wordchain/res/dictionary.txt");
    string wordFromDict;

    while(input >> wordFromDict){ //Read each line from dictionary.
        if(wordFromDict.length() == wordLength){
            dictionary.insert(wordFromDict);
        }
    }
    input.close();
}

void wordChain(string w1, string w2, set<string> &dictionary){ //Constants?
    /*Main function that either prints the right stack,
    *or calls for findNeighbour to find new stacks.*/

    queue<stack<string> > wordQueue;
    stack<string> startingWord;
    startingWord.push(w1);
    wordQueue.push(startingWord);
    set<string> checkedNeighbours;
    checkedNeighbours.insert(w1);

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
    /*Main function for initializing the program.*/

    // Todo: check if first and last word is in dictionary.
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    string word1, word2;
    set<string> dictionary;
    cout << "Please type two words: ";
    cin >> word1 >> word2;
    int wordLength = word1.length();
    cout << wordLength << endl;
    createDictionary(dictionary, wordLength);
    if(dictionary.count(word1) == 0 && dictionary.count(word2) == 0){
        cout << "Neither of the words are in the dictionary" << endl;
        return 0;
    }else if(dictionary.count(word1) == 0){
        cout << word1 << " is not in the dictionary" << endl;
        return 0;
    }else if(dictionary.count(word2) == 0){
        cout << word2 << " is not in the dictionary" << endl;
        return 0;
    }
    wordChain(word1, word2, dictionary);

    return 0;
}
