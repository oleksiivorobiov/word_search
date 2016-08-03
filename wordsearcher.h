#ifndef WORDSEARCHER_H
#define WORDSEARCHER_H

#include <string>
#include <vector>

class WordSearcher
{
  std::string _file, _sorted_file;
  size_t _max_word_size;
  std::vector<std::string> _words;
  void read_words();
  void pad_words();
  void write_sorted_words();
  void save_words_for_search();
  void binary_search();
public:
  WordSearcher(const std::string &file);
  bool exists(const std::string &word) const;
};

#endif // WORDSEARCHER_H
