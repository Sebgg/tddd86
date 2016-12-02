// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include <vector>
#include <queue>
// TODO: include any other headers you need
using namespace std;

template<typename T> void print_queue(T& q){
    while(!q.empty()) {
        cout << *q.top() << endl;
        q.pop();
    }
}

map<int, int> buildFrequencyTable(istream& input) {
    // Can't handle certain characters yet!
    map<int, int> freqTable;

    char c;
    while(input.get(c)){
        freqTable[c] += 1;
    }
    freqTable[256] = 1;

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
        HuffmanNode *T = new HuffmanNode(257, freq, t1, t2);
        binTree.push(T);
    }

    HuffmanNode *root = binTree.top();
    return root;
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    map<int, string> encodingMap;
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
