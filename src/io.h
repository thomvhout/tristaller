#ifndef IO_H
#define IO_H

#include <string>
#include <vector>
#include <filesystem>

using namespace std;

vector<string> grep_dir(const string path, const string regex_name, const bool recursive);

#endif
