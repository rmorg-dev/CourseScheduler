#include "DynamicArray.h"
#include "InputValidation.h"
#include <algorithm>
#include <cassert>

DynamicArray::DynamicArray() {
	data = nullptr;
	capacity = 0;
	count = 0;
	sorted = true;
}


DynamicArray::~DynamicArray() {
	delete[] data;
}


void DynamicArray::Insert(const Course& course) {
	if (count == capacity) { // if the array is full, expand the capacity.
		Grow();
	}
	data[count] = course;
	count++;
	sorted = false;
}


void DynamicArray::SortDynamicArray() {
	std::sort(data, data + count, [](const Course& a, const Course& b) {
		return ConvertToLowercase(a.courseNumber) < ConvertToLowercase(b.courseNumber); 
	});
	sorted = true;
}


std::optional<Course> DynamicArray::Search(const std::string& courseNumber) {
	if (!sorted){ // ensures Dynamic Array will always be sorted before searching to ensure efficiency.
		SortDynamicArray();
	}

	std::string courseNumLowercase = ConvertToLowercase(courseNumber);
	int min = 0;
	int max = count - 1;

	while (min <= max) {
		int midpoint = min + (max - min) / 2;
		std::string midpointVal = ConvertToLowercase(data[midpoint].courseNumber);

		if (midpointVal == courseNumLowercase) { // if midpoint value is the same, return the course.
			return data[midpoint];
		}
		else if (midpointVal < courseNumLowercase) { // if midpoint value is lower, search the upper-half of the array.
			min = midpoint + 1;
		}
		else { // if midpoint value is higher, search the lower-half of the array. 
			max = midpoint - 1;
		}
	}
	return std::nullopt;
}


void DynamicArray::GetCourses(std::vector<Course>& courseVector) {
	if (!sorted) {
		SortDynamicArray();
	}

	for (int i = 0; i < count; i++) {
		courseVector.push_back(data[i]);
	}
}

void DynamicArray::Grow() {
	int newCapacity;
	if (capacity == 0) {
		newCapacity = 4;
	}
	else {
		newCapacity = capacity * 2;
	}
	Course* newData = new Course[newCapacity];
	
	assert(count <= capacity); // lets compiler know count will never be greater than capacity, and will throw an error if it ever is.
	
	for (int i = 0; i < count; i++) { // copy existing elements into new Course* block.
		newData[i] = data[i];
	}

	delete[] data; // free up the old data block.
	data = newData;
	capacity = newCapacity;
}
