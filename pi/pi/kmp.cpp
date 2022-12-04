#include "kmp.h"

int KMP_search(std::string text, std::string pattern) {
	int i = 0;
	int j = 0;
	unsigned long pLength = pattern.length();
	unsigned long tLength = text.length();
	std::vector<int> T = KMP_table(pattern);

	while (i + pLength <= tLength) {
		if (text[i + j] == pattern[j]) {
			j++;
			if (j == pLength)
				return i;
		}
		else if (j == 0) {
			i++;
		}
		else {
			i += j - T[j - 1];
			j = T[j - 1];
		}
	}
	return -1;
}

std::vector<int> KMP_table(std::string pattern) {
	std::vector<int> T(pattern.length() - 1);
	T.push_back(0);
	int pos = 1, m = 0;

	while (pos < pattern.length() - 1) {
		if (pattern[pos] == pattern[m]) {
			m++;
			T[pos] = m;
			pos++;
		}
		else if (m > 0)
			m = T[m - 1];
		else {
			T[pos] = 0;
			pos++;
		}
	}
	return T;
}