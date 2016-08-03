#include "wordsearcher.h"
#include "utils.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

WordSearcher::WordSearcher(const string &file) : _file(file), _sorted_file(_file + "_sorted")
{
  _max_word_size = 0;
  if (!file_exists(_sorted_file))
    save_words_for_search();
}

void WordSearcher::read_words()
{
  ifstream in(_file.c_str());
  if (!in.good())
    throw std::runtime_error("failed to read " + _file);

  string word;
  while (in >> word)
  {
    _words.push_back(word);
    if (word.size() > _max_word_size)
      _max_word_size = word.size();
  }
}

void WordSearcher::pad_words()
{
  for(auto &w: _words)
    w.insert(w.size(), _max_word_size - w.size(), ' ');
}

void WordSearcher::write_sorted_words()
{
  sort(_words.begin(), _words.end());

  ofstream out(_sorted_file.c_str());
  if (!out.good())
    throw std::runtime_error("failed to write " + _sorted_file);

  for(auto &w: _words)
    out << w << "\n";
}

void WordSearcher::save_words_for_search()
{
  read_words();
  pad_words();
  write_sorted_words();
}

bool WordSearcher::exists(const string &word) const
{
  ifstream in(_sorted_file.c_str());
  string line;
  if (!in.good() || !getline(in, line))
    throw std::runtime_error("failed to read " + _sorted_file);

  size_t line_size = line.size();
  in.seekg(0, in.end);
  size_t file_size = in.tellg();
  in.seekg(0, in.beg);
  size_t lines_count = (file_size / line_size) - 1;

  auto read_word_at_line = [&](size_t line_num) -> string
  {
    in.seekg(line_num * line_size + line_num);
    in >> line;
    return line;
  };

  size_t first = 0, last = lines_count;
  while (first < last) {
    size_t mid = first + (last - first) / 2;
    string mid_word = read_word_at_line(mid);

    if (word == mid_word)
      return true;

    if (word < mid_word)
      last = mid;
    else
      first = mid + 1;
  }

  return false;
}
