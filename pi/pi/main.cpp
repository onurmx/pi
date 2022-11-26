#include "chudnovsky.h"
#include <fstream>
#include <iostream>
#include "kmp.h"

int main() {
	try
	{
		Chudnovsky c(1000000);
		std::string result = c.computePi();
		
		// Save result to file
		std::ofstream file;
		file.open("pi.txt");
		file << result;
		file.close();

		// Search for 8190555562180504876
		int index = KMP_search(result, "8190555562180504876");
		if (index != -1)
			std::cout << "Found at index: " << index << std::endl;
		else
			std::cout << "Not found" << std::endl;
		
	}
	catch (...) {
		std::cout << "ERROR!" << std::endl;
		return -1;
	}

	return 0;
}