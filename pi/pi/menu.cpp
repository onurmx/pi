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
			// check if file "pi.txt" exists if yes, open it
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
					std::cout << "ERROR! Start must be smaller than end." << std::endl;
				}
				else {
					std::string result = "";
					for (int i = start; i <= end; i++) {
						int index = KMP_search(line, std::to_string(i));
						if (index != -1) {
							result += std::to_string(i) + "," + std::to_string(index) + "\n";
						}
					}

					std::ofstream file;
					file.open("pattern_search.txt");
					file << result;
					file.close();
				}
			}
			else {
				std::cout << "File \"pi.txt\" does not exist. First Calculate!" << std::endl;
			}
		}
		else if (command == "3") {

		}
		else if (command == "4") {
			break;
		}
		else {
			std::cout << "Wrong Argument!!!" << std::endl << std::endl;
		}
	}
}