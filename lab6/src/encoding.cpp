// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "bitstream.h"
#include <vector>
#include <queue>
// TODO: include any other headers you need
using namespace std;

map<int, int> buildFrequencyTable(istream& input) {
    // Can't handle certain characters yet!
    map<int, int> freqTable;

    char c;
    while(input.get(c)){
        freqTable[c] += 1;
    }
    freqTable[PSEUDO_EOF] = 1;

    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    auto cmpNodes = [](const HuffmanNode *left, const HuffmanNode *right){return *left < *right; };
    priority_queue<HuffmanNode, vector<HuffmanNode*>, decltype(cmpNodes)> binTree(cmpNodes);
    for(auto const c : freqTable){
        HuffmanNode *T = new HuffmanNode(c.first, c.second);
        binTree.push(T);
    }

    while(binTree.size() > 1){
        HuffmanNode *t1 = binTree.top();
        binTree.pop();
        HuffmanNode *t2 = binTree.top();
        binTree.pop();
        int freq = t1->count + t2->count;
        HuffmanNode *T = new HuffmanNode(NOT_A_CHAR, freq, t1, t2);
        binTree.push(T);
    }

    HuffmanNode *root = binTree.top();
    return root;
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMapOne;
    map<int, string> encodingMap;
    if(encodingTree->isLeaf()){
        // Set all nodes value to nothing at the start. This case 1
        encodingMap[encodingTree->character] = "";
        return encodingMap;
    } else {
        // Now decide whether to be 1 or 0.
        encodingMapOne = buildEncodingMap(encodingTree->one);
        for(auto const &key : encodingMapOne){
            encodingMapOne[key.first] += "1";
        }

        encodingMap = buildEncodingMap(encodingTree->zero);
         // Now decide whether to be 1 or 0. This case 0
        for(auto const &key : encodingMap){
            encodingMap[key.first] += "0";
        }

        for(auto const &key : encodingMapOne){
            encodingMap[key.first] = key.second;
        }
        return encodingMap;
    }
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    char c;
    string bitWord;
    while(input.get(c)){
        for(auto const &key : encodingMap){
            if(key.first == c){
                bitWord += key.second;
            }
        }
    }

    for(auto const &key : encodingMap){
        if(key.first == PSEUDO_EOF){
            bitWord += key.second;
        }
    }

    for(auto const bit : bitWord){
        int bitt = bit - '0';
        output.writeBit(bitt);
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // Take ze decoded bitstream and follow the 1's n' 0's until you reach a character
    // Then Put that char in output. Simple!
    int b;
    string decoded;
    HuffmanNode *currNode = encodingTree; // Would want this to be root. Starting point.
    while(input.readBit(c){
        // Do amazing things in here.
        // Preferably we want to traverse with the read bit.
    } 
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    if(node == nullptr){
    }else if(node->isLeaf()){
        delete node;
    } else {
        freeTree(node->one);
        freeTree(node->zero);
    }
}
