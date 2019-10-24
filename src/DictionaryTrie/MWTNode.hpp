/**
 * TODO: File Header
 *
 * Author:
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
    bool end;
    unordered_map<char, MWTNode*> children;
    string word;
    int count;

    MWTNode() {
        end = false;
        count = 0;
    }

    void put(char ch) {
        if (children.find(ch) == children.end()) {
            children.insert({ch, new MWTNode()});
        }
    }

    MWTNode* get(char ch) {
        if (children.find(ch) == children.end()) {
            return nullptr;
        }
        return children[ch];
    }

    bool containsKey(char ch) { return get(ch) != nullptr; }

    void setEnd() { end = true; }

    bool isEnd() { return end; }
};

#endif  // MWTNODE_HPP