#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <string>
#include <vector>
#include <optional>

struct Course {
	std::string courseNumber;
	std::string courseName;
	std::vector<std::string> prerequisites;
};

class DynamicArray {
public:
	DynamicArray();
	~DynamicArray();
	DynamicArray(const DynamicArray&) = delete;
	DynamicArray& operator=(const DynamicArray&) = delete;
	void Insert(const Course& course);
	void SortDynamicArray();
	std::optional<Course> Search(const std::string& courseNumber);
	void GetCourses(std::vector<Course>& courseVector);

private:
	Course* data;
	int capacity;
	int count;
	bool sorted;
	void Grow();
};

#endif