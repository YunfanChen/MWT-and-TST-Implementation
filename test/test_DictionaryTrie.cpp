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
