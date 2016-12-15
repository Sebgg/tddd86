#include "encoding.h"
#include "bitstream.h"
#include "HuffmanNode.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

/*
 * Builds the frequency table for the input stream.
 */
map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;

    int c = input.get();
    while(c != -1){
        freqTable[c] += 1;
        c = input.get();
    }

    freqTable[PSEUDO_EOF] = 1;
    return freqTable;
}

/*
 * builds the encoding tree with the help of a priority queue.
 *
 * cmpNodes is a lambda function that sorts the node based on frequency,
 * in order smallest to largest.
 */
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

/*
 * Creates the binary codes for each character in the encoding tree.
 */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    if(encodingTree == nullptr){ //Returns empty encodingmap if encodingTree is nullptr.
        return encodingMap;
    }else if(encodingTree->isLeaf()){
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

/*
 * Encodes the input to binary with help from the encodingmap and writes it bit by bit to output
 */
void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    string bitWord;
    int c = input.get();
    while(c != -1){
        bitWord += encodingMap.find(c)->second;
        c = input.get();
    }

    bitWord += encodingMap.find(PSEUDO_EOF)->second;

    for(auto const &bitt : bitWord){
        int bit = bitt - '0'; //Converts char to int
        output.writeBit(bit);
    }
}

/*
 * Decodes the binary data with the help of the encodingtree and writes it in ascii to output.
 */
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    int bitt;
    HuffmanNode* root = encodingTree;
    HuffmanNode *currNode = root;// Set start point for traverse.
    while(!input.fail()){
        bitt = input.readBit();
        if(bitt == 1){
            currNode = currNode->one; // Change currNode to right child of itself.
            if(currNode->isLeaf()){
                output.put(currNode->character);
                if(currNode->character == PSEUDO_EOF){
                    break;
                }
                currNode = root;
            }       
        }else if(bitt == 0){
            currNode = currNode->zero; // Change currNode to its left child.
            if(currNode->isLeaf()){
                output.put(currNode->character);
                if(currNode->character == PSEUDO_EOF){
                    break;
                }
                currNode = root;
            }
        }
    }
}

/*
 * Compresses the input by calling memberfunctions of encoding.cpp,
 * and writes to a file.
 */
void compress(istream& input, obitstream& output) {
    map<int, int> freqTable = buildFrequencyTable(input);
    HuffmanNode* rootNode = buildEncodingTree(freqTable);
    map<int,string> encMap = buildEncodingMap(rootNode);
    input.clear();
    input.seekg(0, ios::beg); //Resets input, so it can be used in encodeData

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
        if(key.first != freqTable.rbegin()->first){
            output.put(',');
        }
    }
    output.put('}');
    output.put('\n');
    encodeData(input, encMap, output);
    freeTree(rootNode);
}

/*
 * Decompresses the input stream and writes it to output file by calling memberfunctions of encoding.cpp.
 */
void decompress(ibitstream& input, ostream& output) {
    map<int, int> freqTable;
    string header;
    string key;
    string freq;
    string pair;
    int keyI;
    int freqI;

    getline(input, header);

    //Remove the brackets in the beginning and end of the header.
    header.erase(header.begin());
    // header.pop_back(); consider bracket as a flag as well as comma

    while(!header.empty()){ //Fills the frequency table with the given header frequencies.
        if(header.find_first_of(',') == string::npos){
            pair = header.substr(0, header.find_first_of(','));
        }else if(header.find_first_of('}') == string::npos){
        pair = header.substr(0, header.find_first_of('}'))
        }
        key = pair.substr(0, pair.find_first_of(':'));
        freq = pair.substr(pair.find_first_of(':')+1, pair.back());
        keyI = atoi(key.c_str());
        freqI = atoi(freq.c_str());
        freqTable[keyI] = freqI;
        header.erase(0, header.find_first_of(',')+1);
    }

    HuffmanNode* root = buildEncodingTree(freqTable);
    decodeData(input, root, output);
    freeTree(root);
}

/*
 * Destroys the tree and deallocates all of its allocated memory.
 * If tree is a nullptr it will do nothing. If this is not handled,
 * it will crash if you try to destroy a tree that's already been
 * destroyed.
 */
void freeTree(HuffmanNode* node) {
    if(node == nullptr){
    }else if(node->isLeaf()){
        delete node;
    } else {
        freeTree(node->one);
        freeTree(node->zero);
        delete node; // Delete the parent node as well.
    }
}
