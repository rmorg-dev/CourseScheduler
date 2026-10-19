#include "DynamicArray.h"
#include "InputValidation.h"
#include <algorithm>
#include <cassert>

/**
 * @brief Initializes an empty dynamic array.
 */
DynamicArray::DynamicArray() {
	data = nullptr;
	capacity = 0;
	count = 0;
	sorted = true;
}

/**
 * @brief Releases the allocated array storage.
 */
DynamicArray::~DynamicArray() {
	delete[] data;
}

/**
 * @brief Adds a course number to the end of the array.
 * @param courseNumber Course to insert.
 */
void DynamicArray::Insert(const std::string& courseNumber) {
	if (count == capacity) { // if the array is full, expand the capacity.
		Grow();
	}
	data[count] = courseNumber;
	count++;
	sorted = false;
}

/**
 * @brief Sorts the course numbers in ascending order.
 */
void DynamicArray::SortDynamicArray() {
	std::sort(data, data + count);
	sorted = true;
}

/**
 * @brief Searches for a course number using binary search.
 * @param courseNumber Course to search for.
 * @return True if course exists; otherwise false.
 */
bool DynamicArray::Search(const std::string& courseNumber) {
	if (!sorted) { // ensures Dynamic Array will always be sorted before searching to ensure efficiency.
		SortDynamicArray();
	}

	std::string courseNumLowercase = ConvertToLowercase(courseNumber);
	int min = 0;
	int max = count - 1;

	while (min <= max) {
		int midpoint = min + (max - min) / 2;
		std::string midpointVal = ConvertToLowercase(data[midpoint]);

		if (midpointVal == courseNumLowercase) { // if midpoint value is the same, return the course.
			return true;
		}
		else if (midpointVal < courseNumLowercase) { // if midpoint value is lower, search the upper-half of the array.
			min = midpoint + 1;
		}
		else { // if midpoint value is higher, search the lower-half of the array. 
			max = midpoint - 1;
		}
	}
	return false;
}

/**
 * @brief Copies all course numbers to vector parameter.
 * @param courseNumbers vector that will hold the course numbers.
 */
void DynamicArray::GetCourses(std::vector<std::string>& courseNumbers) {
	if (!sorted) {
		SortDynamicArray();
	}

	for (int i = 0; i < count; i++) {
		courseNumbers.push_back(data[i]);
	}
}

/**
 * @brief Increases array capacity.
 */
void DynamicArray::Grow() {
	int newCapacity;
	if (capacity == 0) {
		newCapacity = 4;
	}
	else {
		newCapacity = capacity * 2;
	}
	std::string* newData = new std::string[newCapacity];
	
	assert(count <= capacity); // lets compiler know count will never be greater than capacity, and will throw an error if it ever is.
	
	for (int i = 0; i < count; i++) { // copy existing elements into new Course* block.
		newData[i] = data[i];
	}

	delete[] data; // free up the old data block.
	data = newData;
	capacity = newCapacity;
}
