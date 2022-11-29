#pragma once

#include <string>
#include <vector>

int KMP_search(std::string text, std::string pattern);
std::vector<int> KMP_table(std::string);