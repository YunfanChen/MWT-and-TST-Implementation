/**
 * This is implementation of dictionary trie
 * by mulit-way trie.
 *
 * Author: Yunfan Chen
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include "MWTNode.hpp"

using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    MWTNode* root;

    MWTNode* searchNode(string word) {
        if (word.size() == 0) return nullptr;
        MWTNode* node = root;
        for (char ch : word) {
            if (node->containsKey(ch)) {
                node = node->get(ch);
            } else {
                delete node;
                return nullptr;
            }
        }
        return node;
    }

    void deleteAll(MWTNode* root) {
        if (root == nullptr) return;
        unordered_map<char, MWTNode*>::iterator iter;
        iter = root->children.begin();
        while (iter != root->children.end()) {
            deleteAll(iter->second);
            iter++;
        }
        delete root;
        root = nullptr;
    }

    bool cmp(const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    }

  public:
    /* TODO: add function header */
    DictionaryTrie() { root = 0; };

    /* TODO: add function header */
    bool insert(string word, unsigned int freq) {
        if (word.size() == 0) return false;
        MWTNode* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) node->put(ch);
            node = node->get(ch);
        }
        if (node->word.size() == 0) {
            node->word.assign(word);
        } else {
            delete node;
            return false;
        }
        node->count = freq;
        node->setEnd();
        return true;
    };

    /* TODO: add function header */
    bool find(string word) const {
        if (word.size() == 0) return false;
        MWTNode* node = root;
        for (char ch : word) {
            if (node->containsKey(ch)) {
                node = node->get(ch);
            } else {
                delete node;
                return false;
            }
        }
        if (node->isEnd == true) {
            delete node;
            return true;
        } else {
            delete node;
            return false;
        }
    };

    /* TODO: add function header */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions) {
        MWTNode* node = searchNode(prefix);
        stack<MWTNode*> sk;
        vector<string> res(numCompletions);
        map<string, int> kvmap;
        if (numCompletions == 0) return res;
        sk.push(node);
        while (!sk.empty()) {
            MWTNode* node2 = sk.top();
            if (node2->isEnd == true) {
                kvmap.insert(make_pair(node2->word, node2->count));
            }
            stack<MWTNode*> sk2;
            unordered_map<char, MWTNode*>::iterator iter;
            iter = node2->children.begin();
            while (iter != node2->children.end()) {
                sk2.push(iter->second);
                iter++;
            }
            while (!sk2.empty()) {
                MWTNode* node3 = sk2.top();
                sk.push(node);
            }
        }
        vector<pair<string, int>> vec(kvmap.begin(), kvmap.end());
        sort(vec.begin(), vec.end(), cmp);
        for (int i = 0; i < numCompletions; ++i) {
            if (i == vec.size()) break;
            res.push_back(vec[i].first);
        }
        return res;
    };

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    ~DictionaryTrie() { deleteAll(root); };
};

#endif  // DICTIONARY_TRIE_HPP
