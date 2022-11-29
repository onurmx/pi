#include "menu.h"

void menu() {
	while (true) {
		std::string command;
		std::cout << "Press 1 to calculate pi." << std::endl;
		std::cout << "Press 2 to find numbers in the interval from pi." << std::endl;
		std::cout << "Press 3 to compare two files" << std::endl;
		std::cout << "Press 4 to exit from program." << std::endl;
		std::cout << ">> ";
		std::cin >> command;
		std::cout << std::endl;

		if (command == "1") {
			try
			{
				std::string digits;
				std::cout << "Enter number of digits to calculate." << std::endl;
				std::cout << ">> ";
				std::cin >> digits;
				std::cout << std::endl;

				if (stoi(digits) < 15) {
					std::cout << "Digit should be greater or equal to 15." << std::endl;
					continue;
				}

				Chudnovsky c(stoi(digits));
				std::string result = c.computePi();

				std::ofstream file;
				file.open("pi.txt");
				file << result;
				file.close();
				std::cout << "Result saved to \"pi.txt\"." << std::endl << std::endl;
			}
			catch (...) {
				std::cout << "ERROR!" << std::endl;
			}
		}
		else if (command == "2") {
			std::ifstream file;
			file.open("pi.txt");
			if (file.is_open()) {
				std::string line;
				std::getline(file, line);
				file.close();

				std::string start_string, end_string;
				std::cout << "Enter lower bound of interval." << std::endl;
				std::cout << ">> ";
				std::cin >> start_string;
				std::cout << std::endl;
				std::cout << "Enter upper bound of interval." << std::endl;
				std::cout << ">> ";
				std::cin >> end_string;

				int start = stoi(start_string), end = stoi(end_string);
				if (start > end) {
					std::cout << "ERROR! Start must be smaller than end." << std::endl << std::endl;
				}
				else {
					std::string result = "";

					// calculate time
					clock_t t0, t1;
					t0 = clock();
					std::cout << "Pattern seach has been started..." << std::endl;
					for (int i = start; i <= end; i++) {
						int index = KMP_search(line, std::to_string(i));
						if (index != -1) {
							result += std::to_string(i) + "," + std::to_string(index) + "\n";
						}
					}
					t1 = clock();
					double time = (double)(t1 - t0) / CLOCKS_PER_SEC;
					std::cout << "Pattern search completed in " << (double)(t1 - t0) / CLOCKS_PER_SEC << " seconds." << std::endl;
					std::cout << "Result saved to \"pattern_search.txt\"." << std::endl << std::endl;

					std::ofstream file;
					file.open("pattern_search.txt");
					file << result;
					file.close();
				}
			}
			else {
				std::cout << "File \"pi.txt\" does not exist. First Calculate Pi!" << std::endl << std::endl;
			}
		}
		else if (command == "3") {
			std::string file1, file2;
			std::cout << "Enter first file name." << std::endl;
			std::cout << ">> ";
			std::cin >> file1;
			std::cout << std::endl;
			std::cout << "Enter second file name." << std::endl;
			std::cout << ">> ";
			std::cin >> file2;
			std::cout << std::endl;

			std::ifstream f1, f2;
			f1.open(file1);
			f2.open(file2);

			if (f1.is_open() && f2.is_open()) {
				std::string line1, line2;
				std::getline(f1, line1);
				std::getline(f2, line2);
				f1.close();
				f2.close();
				

				if (line1 == line2) {
					std::ofstream file;
					file.open("compare.txt");
					file << "File " << file1 << " and file " << file2 << " are the same." << std::endl;
					file.close();
					std::cout << "Result saved to \"compare.txt\"." << std::endl << std::endl;
				}
				else {
					std::ofstream file;
					file.open("compare.txt");
					file << "File " << file1 << " and file " << file2 << " are not the same." << std::endl;
					file.close();
					std::cout << "Result saved to \"compare.txt\"." << std::endl << std::endl;
				}
			}
			else {
				std::cout << "ERROR! File does not exist." << std::endl;
			}
		}
		else if (command == "4") {
			break;
		}
		else {
			std::cout << "Wrong Argument!!!" << std::endl << std::endl;
		}
	}
}