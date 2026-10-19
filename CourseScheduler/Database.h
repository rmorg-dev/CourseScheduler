#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include "DynamicArray.h"
class Database {
public:
	static bool InitializeDB(const std::string& dbFilePath);
	static bool InsertFromCSV(const std::string& csvFilePath);
	static bool LoadAllCourseNumbers(DynamicArray& courseArray);
	static std::string GetAllCourses();
	static std::string GetCoursePrereqs(const std::string& courseNumber);
	static bool InsertCourse(const std::string& courseNumber, const std::string& courseName, const std::vector<std::string>& prereqs);
	static bool IsEmpty();
	static void Shutdown();
};

#endif
