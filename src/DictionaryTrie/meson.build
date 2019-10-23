inc = include_directories('.')
dictionary_trie = library('dictionary_trie', sources: ['DictionaryTrie.cpp'])
dictionary_trie_dep = declare_dependency(include_directories: inc,
  link_with: dictionary_trie)

#subdir('DictionaryTrie')
#subdir('Util')
 
benchtrie_exe = executable('benchtrie.cpp.executable', 
    sources: ['benchtrie.cpp'],
    dependencies : [dictionary_trie_dep, util_dep],
    install : true)

autocomplete_exe = executable('autocomplete.cpp.executable', 
    sources: ['autocomplete.cpp'],
    dependencies : [dictionary_trie_dep, util_dep],
    install : true)