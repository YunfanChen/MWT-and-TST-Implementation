inc = include_directories('.')
dictionary_trie = library('dictionary_trie', sources: ['DictionaryTrie.cpp'])
dictionary_trie_dep = declare_dependency(include_directories: inc,
  link_with: dictionary_trie)