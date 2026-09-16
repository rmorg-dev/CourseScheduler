#include "BinaryTree.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <regex>
#include <limits>
#include <ios>

// TODO: add file documentation.

/**
 * @brief This function converts a string to all lowercase. Code help from https://www.geeksforgeeks.org/how-to-convert-std-string-to-lower-case-in-cpp/
 * @param str 
 * @return 
 */
std::string ConvertToLowercase(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), tolower);

	return str;
}

void ReadCSV(std::string filename, BinaryTree* courseTree) {
	std::ifstream fileIn(filename);
	std::vector<std::vector<std::string>> csvRows; // a super vector that contains other vectors of strings allowing for easier parsing. 

	if (!fileIn) { 
		std::cout << "File could not be opened!" << std::endl;
		return;
	}

	/* read each line of the file and find each element separated by ',' on said line. These will then be stored into a string vector. This string vector will then be added into the super vector. */
	for (std::string line; getline(fileIn, line);) { 
		std::istringstream ss(line); 
		std::vector<std::string> row; 

		for (std::string value; getline(ss, value, ',');) { 
			row.push_back(value);
		}

		csvRows.push_back(row); 
	}

	/* iterate through each element stored in the super vector and store them as a course data type. If greater than 2 elements exist within the super element, then the remaining elements 
	are stored in the prerequisites vector. They are then inserted into the Binary Tree data structure. */
	for (const std::vector<std::string>& row : csvRows) {  
		if (row.size() < 2) { 
			continue;
		}

		Course course;  
		course.courseNumber = row[0];
		course.courseName = row[1];

		if (row.size() > 2) { 
			for (int i = 2; i < row.size(); i++) { 
				course.prerequisites.push_back(row[i]);
			}
		}
		courseTree->Insert(course); 
	}

	std::cout << "file loaded successfully!" << std::endl;
}

/**
 * @brief This function validates user input's formatting. Code help from: 
 * https://www.geeksforgeeks.org/how-to-validate-user-input-in-cpp/ 
 * https://www.geeksforgeeks.org/write-regular-expressions/
 * https://cplusplus.com/reference/regex/regex_match/
 * @param input 
 * @return 
 */
bool isValidCourseCode(const std::string& input) {
	std::regex pattern("[A-Za-z]+[0-9]+");

	return regex_match(input, pattern); 
}



int main() {
	int selection = 0;
	BinaryTree* course = new BinaryTree();
	std::string fileName;
	std::string courseNumber;
	const int LOAD = 1;
	const int PRINT_ALL = 2;
	const int PRINT_INDV = 3;
	const int EXIT_PROGRAM = 4;
	bool valid = false;

		while (selection != 4) {
			std::cout << "COURSE SEARCH MENU:" << std::endl;
			std::cout << "     1. Load CSV file." << std::endl;
			std::cout << "     2. Print list of all courses." << std::endl;
			std::cout << "     3. Print individual course and its prerequisites." << std::endl;
			std::cout << "     4. Exit program." << std::endl;
			std::cout << "ENTER A SELECTION: " << std::endl;
			std::cin >> selection;

			/* checking the stream to see if input is valid.If cin raises a fail flag, reset the fail state and ignore all input in the stream then output an error statement.
			Code help: https://latedev.wordpress.com/2011/09/13/simple-input-bullet-proofing-in-c/ */
			if (std::cin.fail()) { 
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Selection must be a number." << std::endl << std::endl;
				continue;
			}
			std::cin.ignore();
			std::cout << std::endl;
		
			switch (selection) {
				case LOAD:  
					std::cout << "Enter the name of the CSV file: " << std::endl;
					getline(std::cin, fileName); 
					ReadCSV(fileName, course); 
					std::cout << std::endl; 
					break;

				case PRINT_ALL: 
					std::cout << "FULL COURSE LIST:" << std::endl; 
					course->InOrderPrint(); 
					break; 

				case PRINT_INDV: 
					std::cout << "Enter the course ID you want to search without spaces (ex. CSCI300): " << std::endl;
					do {  
						getline(std::cin, courseNumber);
						std::cout << std::endl;
						valid = isValidCourseCode(courseNumber);
						if (!valid) {
							std::cout << "Invalid Format, please enter the course ID without spaces." << std::endl;
						}
					} while (!valid);
					course->Search(courseNumber);
					std::cout << std::endl;
					break;

				case EXIT_PROGRAM: 
					std::cout << "Goodbye!" << std::endl; 
					delete course;
					return 0;
					

				default: 
					std::cout << "Invalid Number! Please choose from the options on the menu." << std::endl << std::endl;
			}
		}

		std::cout << "Goodbye!" << std::endl; 
		delete course;
		return 0; 
}


