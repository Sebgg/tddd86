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
    map<int, string> encodingMap;
    if(encodingTree->isLeaf()){
        // Set all nodes value to nothing at the start. This case 1
        encodingMap[encodingTree->character] = "";
        return encodingMap;
    } else {
        // Now decide whether to be 1 or 0.
        for(auto const &key : buildEncodingMap(encodingTree->one)){
            encodingMap[key.first] = "1" + key.second;
        }

         // Now decide whether to be 1 or 0. This case 0
        for(auto const &key : buildEncodingMap(encodingTree->zero)){
            encodingMap[key.first] = "0" + key.second;
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
    int bitt;
    HuffmanNode* root = encodingTree;
    HuffmanNode *currNode = root;// Would want this to be root. Starting point.
    while(!input.fail()){
        bitt = input.readBit();
        if(bitt == 1){
            currNode = currNode->one; // Change currNode to right child of itself.
            if(currNode->isLeaf()){
                output.put(currNode->character);
                currNode = root;
            }       
        }else if(bitt == 0){
            currNode = currNode->zero; // Change currNode to its left child.
            if(currNode->isLeaf()){
                output.put(currNode->character);
                currNode = root;
            }
        }
    }
}

void compress(istream& input, obitstream& output) {
    map<int, int> freqTable = buildFrequencyTable(input);
    HuffmanNode* rootNode = buildEncodingTree(freqTable);
    map<int,string> encMap = buildEncodingMap(rootNode);
    
    output.put('{');
    for(auto const &key : freqTable){
        string tmp1 = to_string(key.first);
        for(auto const &c1 : tmp1){
            output.put(c1); 
        }
        output.put(':');
        string tmp2 = to_string(key.second);
        for(auto const &c2 : tmp2){
            output.put(c2);
        }
        output.put(',');
        // output.put(' '); UNECESSARY, why waste space yao.
    }
    output.put('}');
    encodeData(input, encMap, output);
    freeTree(rootNode);

}

void decompress(ibitstream& input, ostream& output) {
    map<int, int> freqTable;
    string header;

    string key;
    string freq;
    while(input.getline(header)){
        header.erase(header.begin());
        int i = 0;
        while(header[i] != '}'){
            int j = i - 1;
            while(header[i] != ':'){
                key += header[i];
                i++;
            }
            i++;
            while(header[i] != ','){
                freq += header[i];
                i++;
            }
            i++;
            int actualKey = atoi(key.c_str());
            int actualFreq = atoi(freq.c_str());
            freqTable[actualKey] = actualFreq;
            header.erase(0, i);
        }
        break;
        // NOTE this may not work at all 
    }
    HuffmanNode* root = buildEncodingTree(freqTable);
    decodeData(input, root, output);
    freeTree(root);
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
