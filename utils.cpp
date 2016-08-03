#include "utils.h"
#include <fstream>

using namespace std;

bool file_exists(const string &name) {
  ifstream f(name.c_str());
  return f.good();
}
