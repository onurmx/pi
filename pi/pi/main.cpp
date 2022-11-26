#include "chudnovsky.h"
#include <iostream>
#include "kmp.h"

int main() {
	try
	{
		// Instantiation
		Chudnovsky objMain(1000000);

		// Compute PI
		objMain.compPi();
	}
	catch (...) {
		std::cout << "ERROR!" << std::endl;
		return -1;
	}

	return 0;
}