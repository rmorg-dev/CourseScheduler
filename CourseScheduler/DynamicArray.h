#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <string>
#include <vector>
#include <optional>


class DynamicArray {
public:
	DynamicArray();
	~DynamicArray();
	DynamicArray(const DynamicArray&) = delete;
	DynamicArray& operator=(const DynamicArray&) = delete;
	void Insert(const std::string& courseNumber);
	void SortDynamicArray();
	bool Search(const std::string& courseNumber);
	void GetCourses(std::vector<std::string>& courseNumbers);

private:
	std::string* data;
	int capacity;
	int count;
	bool sorted;
	void Grow();
};

#endif