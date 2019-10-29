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

    MWTNode* searchNode(string word);

    void searchUnderscores(string word, int index, MWTNode* node);

    void deleteAll(MWTNode* root);

  public:
    /* Initialize DictionaryTrie */
    DictionaryTrie();

    /* Insert a word in this Trie */
    bool insert(string word, unsigned int freq);

    /* See if can find a word in this Trie */
    bool find(string word) const;

    /* Predict completions according to prefix */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* Delete tree*/
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
