#include "menu.h"

void menu() {
	while (true) {
		std::string command;
		std::cout << "Press 1 to calculate pi." << std::endl;
		std::cout << "Press 2 to calculate f_pi function." << std::endl;
		std::cout << "Press 3 to compare two files." << std::endl;
		std::cout << "Press 4 to exit from program." << std::endl;
		std::cout << ">> ";
		std::cin >> command;
		std::cout << std::endl;

		if (command == "1") {
			try
			{
				std::string digits;
				std::cout << "Enter number of digits after dot to calculate." << std::endl;
				std::cout << ">> ";
				std::cin >> digits;
				std::cout << std::endl;

				if (stoi(digits) < 15) {
					std::cout << "Digit should be greater or equal to 15." << std::endl;
					continue;
				}

				Chudnovsky c(stoi(digits));
				std::string result = c.computePi();

				std::cout << "Saving result to file..." << std::endl;
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

				long long int start = std::stoll(start_string), end = std::stoll(end_string);
				if (start > end) {
					std::cout << "ERROR! Lower bound should less than upper bound." << std::endl << std::endl;
				}
				else {
					std::string result = "";

					// calculate time
					clock_t t0, t1;
					t0 = clock();
					std::cout << "Pattern seach has been started..." << std::endl;
					int index = KMP_search(line, std::to_string(start));
					if (index != -1) {
						result += std::to_string(start) + "," + std::to_string(index);
					}
					else {
						result += std::to_string(start) + ",-1";
					}
					for (long long int i = ++start; i <= end; i++) {
						index = KMP_search(line, std::to_string(i));
						if (index != -1) {
							result += "\n" + std::to_string(i) + "," + std::to_string(index);
						}
						else {
							result += "\n" + std::to_string(i) + ",-1";
						}
					}
					t1 = clock();
					double time = (double)(t1 - t0) / CLOCKS_PER_SEC;
					std::cout << "Pattern search completed in " << (double)(t1 - t0) / CLOCKS_PER_SEC << " seconds." << std::endl;

					std::cout << "Saving result to file..." << std::endl;
					std::ofstream file;
					file.open("f_pi.txt");
					file << result;
					file.close();
					std::cout << "Result saved to \"f_pi.txt\"." << std::endl << std::endl;
				}
			}
			else {
				std::cout << "File \"pi.txt\" does not exist. First Calculate Pi!" << std::endl << std::endl;
			}
		}
		else if (command == "3") {
			// ask user compare digits of pi or f_pi
			std::string compare;
			std::cout << "Press 1 to compare digits of pi." << std::endl;
			std::cout << "Press 2 to compare f_pi table." << std::endl;
			std::cout << ">> ";
			std::cin >> compare;
			std::cout << std::endl;

			if (compare == "1") {
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

					int index = 0;
					while ((line1[index] == line2[index]) && (line1[index] != '\0' && line2[index] != '\0')) {
						index++;

					}

					if (index == line1.length() && index == line2.length()) {
						std::cout << "Files are identical." << std::endl << std::endl;
					}
					else {
						std::cout << "Files are different." << std::endl;
						std::cout << "Difference start at index " << index << "." << std::endl << std::endl;
					}
				}
				else {
					std::cout << "ERROR! File does not exist." << std::endl;
				}
			}
			else if (compare == "2") {
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
					int index = 1;
					int result = 1;
					while (std::getline(f1, line1) && std::getline(f2, line2)) {
						if (line1 != line2) {
							result = 0;
							break;
						}
						index++;
					}
					if (result == 1) {
						std::cout << "Files are identical." << std::endl << std::endl;
					}
					else {
						std::cout << "Files are different at line " << index << "." << std::endl << std::endl;
					}
				}
				else {
					std::cout << "ERROR! File does not exist." << std::endl;
				}
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