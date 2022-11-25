#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

int KMP_search(std::string text, std::string pattern);
std::vector<int> KMP_table(std::string);