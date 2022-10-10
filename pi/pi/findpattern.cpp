#include "findpattern.h"

unsigned long int find_pattern(const std::string& pi, const std::string& pattern) {
	unsigned long int iterator = 2, stop_index = pi.length() - pattern.length() - 1, pattern_length = pattern.length();

	while (iterator <= stop_index) {
		if (pi.substr(iterator, pattern_length) == pattern)
			return iterator - 2 + 1;
		iterator++;
	}

	return 0;
}