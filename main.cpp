#include "wordsearcher.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  try
  {
    if (argc < 1)
    {
      cout << "usage: " << argv[0] << " <words>\n";
      return -1;
    }

    string file("./words");
    WordSearcher searcher(file);

    for (int i = 1; i < argc; ++i)
    {
      string word(argv[i]);
      if (searcher.exists(word))
        cout << word << " ";
    }
    cout << "\n";
  }
  catch(const std::exception &e)
  {
    cerr << e.what() << "\n";
    return -1;
  }

  return 0;
}

