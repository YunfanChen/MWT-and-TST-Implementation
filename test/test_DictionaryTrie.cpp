/**
 * TODO: File HEADER
 *
 * Author:
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty test */
TEST(DictTrieTests, EMPTY_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.find("abrakadabra"), false);
}

/* TODO */
TEST(DictTrieTests, TEST_ONE) {
    DictionaryTrie dict;
    dict.insert("apple", 10);
    dict.insert("banana", 20);
    dict.insert("app", 5);
    dict.insert("application", 100);
    ASSERT_EQ(dict.find("app"), true);
}

TEST(DictTrieTests, TEST_TWO) {
    DictionaryTrie dict;
    dict.insert("apple", 10);
    dict.insert("banana", 20);
    dict.insert("app", 5);
    dict.insert("application", 100);
    ASSERT_EQ(dict.find("banban"), false);
}

TEST(DictTrieTests, TEST_THREE) {
    DictionaryTrie dict;
    dict.insert("apple", 10);
    dict.insert("banana", 20);
    dict.insert("app", 5);
    dict.insert("application", 100);
    vector<string> vec;
    vec.push_back("application");
    ASSERT_EQ(dict.predictCompletions("app", 1), vec);
}

TEST(DictTrieTests, TEST_FOUR) {
    DictionaryTrie dict;
    dict.insert("apple", 10);
    dict.insert("banana", 20);
    dict.insert("app", 5);
    dict.insert("application", 100);
    vector<string> vec;
    ASSERT_EQ(dict.predictCompletions("ab", 2), vec);
}

TEST(DictTrieTests, TEST_FIVE) {
    DictionaryTrie dict;
    dict.insert("apo", 10);
    dict.insert("ban", 20);
    dict.insert("app", 5);
    dict.insert("appli", 100);
    vector<string> vec;
    vec.push_back("ban");
    vec.push_back("apo");
    vec.push_back("app");
    ASSERT_EQ(dict.predictUnderscores("___", 3), vec);
}

TEST(DictTrieTests, TEST_SIX) {
    DictionaryTrie dict;
    dict.insert("apo", 10);
    dict.insert("ban", 20);
    dict.insert("app", 5);
    dict.insert("appli", 100);
    vector<string> vec;
    ASSERT_EQ(dict.predictUnderscores("_", 3), vec);
}

TEST(DictTrieTests, TEST_SEVEN) {
    DictionaryTrie dict;
    dict.insert("apo", 10);
    dict.insert("ban", 20);
    dict.insert("a", 5);
    dict.insert("appli", 100);
    vector<string> vec;
    vec.push_back("a");
    ASSERT_EQ(dict.predictUnderscores("_", 3), vec);
}
