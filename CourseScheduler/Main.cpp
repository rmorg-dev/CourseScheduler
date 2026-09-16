#include "BinaryTree.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <regex>

/**
 * @brief This function converts a string to all lowercase. Code help from https://www.geeksforgeeks.org/how-to-convert-std-string-to-lower-case-in-cpp/
 * @param str 
 * @return 
 */
std::string ConvertToLowercase(const std::string& str) {
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



