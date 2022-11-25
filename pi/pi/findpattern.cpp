#include "findpattern.h"

/*
 KMP_search
 return an integer - position in string "text"
 of the begginng of the first occurence
 of string "pattern" in "text"
 returns -1 if not found
 case sensitive
 */
int KMP_search(std::string text, std::string pattern) {
	int i = 0; // i - beginning of matching substring in 'text'
	int j = 0; // j - char in 'pattern', length of current match
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

/*
 KMP_table
 returns a vector T such that
 T[i] is the lenghth of longest proper
 suffix that is also a proper prefix
 of a prefix of input string 'pattern'
 with length of i+1,
 or simply lpsp of a substing [0, i].
 T[0] = 0
 */
std::vector<int> KMP_table(std::string pattern) {
	std::vector<int> T(pattern.length() - 1);
	T.push_back(0);
	// pos  - index for T[], end of suffix, current element
	// m - end of prefix in 'pattern'
	int pos = 1, m = 0;

	while (pos < pattern.length() - 1) {
		// to have lpsp of length m+1 we must
		// have lpsp of lenght m step before
		if (pattern[pos] == pattern[m]) {
			m++;
			T[pos] = m;
			pos++;
		}
		/* m did not increase,
		 // now if have an lpsp of
		 // length T[m-1] > 0
		 // we can have lpsp of length T[m-1] + 1 for current pos.
		 // It will be checked in the next iteration.
		 */
		else if (m > 0)
			m = T[m - 1];
		// if m == 0 - didn't find lpsp, pos++
		else {
			T[pos] = 0;
			pos++;
		}
	}
	return T;
}