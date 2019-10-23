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
        if (children.at(ch) == nullptr) {
            children.insert({ch, new MWTNode()});
        }
    }

    MWTNode* get(char ch) { return children.at(ch); }

    bool containsKey(char ch) { return children.at(ch) != NULL; }

    void setEnd() { end = true; }

    bool isEnd() { return end; }
};

#endif  // MWTNODE_HPP