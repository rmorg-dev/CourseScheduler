#include "BinaryTree.h"
#include <string>
#include <wx/app.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <regex>
#include <limits>
#include <ios>









//int main() {
//	int selection = 0;
//	BinaryTree* course = new BinaryTree();
//	std::string fileName;
//	std::string courseNumber;
//	const int LOAD = 1;
//	const int PRINT_ALL = 2;
//	const int PRINT_INDV = 3;
//	const int EXIT_PROGRAM = 4;
//	bool valid = false;
//
//		while (selection != 4) {
//			std::cout << "COURSE SEARCH MENU:" << std::endl;
//			std::cout << "     1. Load CSV file." << std::endl;
//			std::cout << "     2. Print list of all courses." << std::endl;
//			std::cout << "     3. Print individual course and its prerequisites." << std::endl;
//			std::cout << "     4. Exit program." << std::endl;
//			std::cout << "ENTER A SELECTION: " << std::endl;
//			std::cin >> selection;
//
//			/* checking the stream to see if input is valid.If cin raises a fail flag, reset the fail state and ignore all input in the stream then output an error statement.
//			Code help: https://latedev.wordpress.com/2011/09/13/simple-input-bullet-proofing-in-c/ */
//			if (std::cin.fail()) { 
//				std::cin.clear();
//				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//				std::cout << "Selection must be a number." << std::endl << std::endl;
//				continue;
//			}
//			std::cin.ignore();
//			std::cout << std::endl;
//		
//			switch (selection) {
//				case LOAD:  
//					std::cout << "Enter the name of the CSV file: " << std::endl;
//					getline(std::cin, fileName); 
//					ReadCSV(fileName, course); 
//					std::cout << std::endl; 
//					break;
//
//				case PRINT_ALL: 
//					std::cout << "FULL COURSE LIST:" << std::endl; 
//					course->InOrderPrint(); 
//					break; 
//
//				case PRINT_INDV: 
//					std::cout << "Enter the course ID you want to search without spaces (ex. CSCI300): " << std::endl;
//					do {  
//						getline(std::cin, courseNumber);
//						std::cout << std::endl;
//						valid = isValidCourseCode(courseNumber);
//						if (!valid) {
//							std::cout << "Invalid Format, please enter the course ID without spaces." << std::endl;
//						}
//					} while (!valid);
//					course->Search(courseNumber);
//					std::cout << std::endl;
//					break;
//
//				case EXIT_PROGRAM: 
//					std::cout << "Goodbye!" << std::endl; 
//					delete course;
//					return 0;
//					
//
//				default: 
//					std::cout << "Invalid Number! Please choose from the options on the menu." << std::endl << std::endl;
//			}
//		}
//
//		std::cout << "Goodbye!" << std::endl; 
//		delete course;
//		return 0; 
//}


