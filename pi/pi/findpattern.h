#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int KMP_search(std::string text, std::string pattern);
std::vector<int> KMP_table(std::string);