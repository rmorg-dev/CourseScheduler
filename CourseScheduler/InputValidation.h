#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H
#include <string>

// This header contains the function declarations for helper functions that aid in input validation and error checking.

std::string ConvertToLowercase(const std::string& str);
bool isValidCourseCode(const std::string& str);

#endif