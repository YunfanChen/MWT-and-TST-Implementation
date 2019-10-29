/**
 * This file is define the function in DictionaryTrie.
 *
 * Author: Yunfan Chen
 */
#include "DictionaryTrie.hpp"
#include <iostream>
#include "algorithm"

/** My sort method. */
bool cmpByCount(const pair<string, int>& a, const pair<string, int>& b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second > b.second;
}

vector<MWTNode*> uScoresNode;

/** Serach a word and return a node object.*/
void DictionaryTrie::searchUnderscores(string word, int index, MWTNode* node) {
    if (word.size() == 0) return;
    // cout << "now word length is :" << word.size() << endl;
    // cout << "now word index is :" << index << endl;
    if (index == word.size() - 1 &&
        (word[index] - '_' == 0 || node->containsKey(word[index]))) {
        // cout << "jinlaile!!!" << endl;
        if (word[index] == '_') {
            // cout << "!!!jinrupanduan" << endl;
            unordered_map<char, MWTNode*>::iterator iter;
            iter = node->children.begin();
            while (iter != node->children.end()) {
                if (iter->second->isEnd() == true) {
                    uScoresNode.emplace_back(iter->second);
                    // cout << "now entered is " << iter->second->word << endl;
                }
                iter++;
            }
        } else if (node->get(word[index])->isEnd() == true) {
            uScoresNode.emplace_back(node->get(word[index]));
            // cout << "now entered is " << node->get(word[index])->word <<
            // endl;
        }
        return;
    }
    if (node->containsKey(word[index])) {
        searchUnderscores(word, index + 1, node->get(word[index]));
    } else if (word[index] - '_' == 0) {
        // cout << "judge is '_' " << endl;
        unordered_map<char, MWTNode*>::iterator iter;
        iter = node->children.begin();
        while (iter != node->children.end()) {
            // cout << "iter it... " << endl;
            searchUnderscores(word, index + 1, iter->second);
            iter++;
        }
        return;
    } else {
        return;
    }
    return;
}

MWTNode* DictionaryTrie::searchNode(string word) {
    if (word.size() == 0) return root;
    MWTNode* node = root;
    for (char ch : word) {
        if (node->containsKey(ch)) {
            node = node->get(ch);
        } else {
            return nullptr;
        }
    }
    return node;
}

/** Delete all node in this Trie. */
void DictionaryTrie::deleteAll(MWTNode* root) {
    if (root == nullptr) return;
    unordered_map<char, MWTNode*>::iterator iter;
    iter = root->children.begin();
    while (iter != root->children.end()) {
        deleteAll(iter->second);
        iter++;
    }
    delete root;
}

/* Initialize the Trie. */
DictionaryTrie::DictionaryTrie() { root = new MWTNode(); }

/* Insert a word in this Trie */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    if (word.size() == 0) return false;
    MWTNode* node = root;
    for (char ch : word) {
        if (!node->containsKey(ch)) node->put(ch);
        node = node->get(ch);
    }
    if (node->word.size() == 0) {
        node->word.assign(word);
    } else {
        return false;
    }
    node->count = freq;
    node->setEnd();
    return true;
}

/* See if can find a word in this Trie */
bool DictionaryTrie::find(string word) const {
    if (word.size() == 0) return false;
    MWTNode* node = root;
    for (char ch : word) {
        if (node->containsKey(ch)) {
            node = node->get(ch);
        } else {
            return false;
        }
    }
    if (node->isEnd() == true) {
        return true;
    }
    return false;
}

/* Predict completions according to prefix */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    MWTNode* node = searchNode(prefix);
    stack<MWTNode*> sk;
    vector<string> res;
    if (node == nullptr) return res;
    vector<pair<string, int>> completion;
    if (numCompletions == 0) return res;
    sk.push(node);
    while (!sk.empty()) {
        MWTNode* node2 = sk.top();
        sk.pop();
        if (node2->isEnd() == true) {
            // kvmap.insert(make_pair(node2->count, node2->word));
            completion.emplace_back(node2->word, node2->count);
        }
        unordered_map<char, MWTNode*>::iterator iter;
        iter = node2->children.begin();
        while (iter != node2->children.end()) {
            sk.push(iter->second);
            iter++;
        }
    }
    sort(completion.begin(), completion.end(), cmpByCount);
    for (int i = 0; i < completion.size() && i < numCompletions; ++i) {
        res.push_back(completion[i].first);
    }
    return res;
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    vector<string> res;
    uScoresNode = {};
    if (numCompletions == 0 || pattern.size() == 0 || root == nullptr)
        return res;
    vector<pair<string, int>> completion;
    searchUnderscores(pattern, 0, root);
    for (int i = 0; i < uScoresNode.size(); ++i) {
        completion.emplace_back(uScoresNode[i]->word, uScoresNode[i]->count);
    }
    sort(completion.begin(), completion.end(), cmpByCount);
    for (int i = 0; i < completion.size() && i < numCompletions; ++i) {
        res.push_back(completion[i].first);
    }
    return res;
}

/* Delete the trie */
DictionaryTrie::~DictionaryTrie() { deleteAll(root); }