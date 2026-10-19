#include "InputValidation.h"
#include <cctype>
#include <algorithm>
#include <regex>
#include <string>

/**
 * @brief This function converts a string to all lowercase. Code help from https://www.geeksforgeeks.org/how-to-convert-std-string-to-lower-case-in-cpp/
 * @param str
 * @return
 */
std::string ConvertToLowercase(const std::string& str) {
	std::string strLowercase = str;
	std::transform(strLowercase.begin(), strLowercase.end(), strLowercase.begin(), tolower);

	return strLowercase;
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
