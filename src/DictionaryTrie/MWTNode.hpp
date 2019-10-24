/**
 * This file define the multi-way trie's node.
 *
 * Author: Yunfan Chen
 */
#ifndef MWTNODE_HPP
#define MWTNODE_HPP

#include <hash_map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class MWTNode {
  public:
    bool end;  // if this character is the end of a word
    unordered_map<char, MWTNode*>
        children;  // save his child nodes as a unordered_map
    string word;   // if this is the end of the word, save the word string in
                   // this node.
    int count;     // if this is the end of the word, save the word frequency in
                // this node.

    /** Initialize the MWTNode. */
    MWTNode() {
        end = false;
        count = 0;
    }

    /** Add a new character in this node's children map. */
    void put(char ch) {
        if (children.find(ch) == children.end()) {
            children.insert({ch, new MWTNode()});
        }
    }

    /** Get a node object by the character. */
    MWTNode* get(char ch) {
        if (children.find(ch) == children.end()) {
            return nullptr;
        }
        return children[ch];
    }

    /** Check if this node's map contains a key. */
    bool containsKey(char ch) { return get(ch) != nullptr; }

    /** Set this node as a end node. */
    void setEnd() { end = true; }

    /** Return if this node is a end node. */
    bool isEnd() { return end; }
};

#endif  // MWTNODE_HPP