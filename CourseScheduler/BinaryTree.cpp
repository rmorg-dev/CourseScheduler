#include "BinaryTree.h"
#include "InputValidation.h"
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <wx/wx.h>
// TODO: add file documentation.

/**
 * @brief Constructor.
 */
BinaryTree::BinaryTree() {
	this->root = nullptr; 
}

/**
 * @brief Destructor.
 */
BinaryTree::~BinaryTree() {
	delete root;
}

/**
 * @brief Inserts a course data type into the tree. Sorts by alphanumeric value.
 * @param course 
 */
void BinaryTree::Insert(const Course& course) {
	Node* currNode = root;

	if (root == nullptr) { 
		root = new Node(course); 
		return;
	}

	
	while (currNode != nullptr) {

		/* checks if the current Node's course number is alphanumerically lower than the course passed in. If yes, insert to right side of tree. If right node already exists, it traverses until it finds a null pointer. */
		if (currNode->course.courseNumber.compare(course.courseNumber) < 0) { 
			if (currNode->right == nullptr) { 
				currNode->right = new Node(course);
				return; 
			}
			else {
				currNode = currNode->right;  
			}
		}
		/* checks if the current Node's course number is alphanumerically higher than the course passed in. If yes, insert to left side of tree. If left node already exists, it traverses until it finds a null pointer. */
		else if (currNode->course.courseNumber.compare(course.courseNumber) > 0) { 
			if (currNode->left == nullptr) {  
				currNode->left = new Node(course);
				return; 
			}
			else {
				currNode = currNode->left; 
			}
		}

		else { 
			return;
		}
	}
}
/**
 * @brief Function searches the tree for the course number passed.
 * @param courseNumber 
 */
 std::optional<Course> BinaryTree::Search(const std::string& courseNumber) {
	Node* currNode = root;

	while (currNode != nullptr) { // if tree has data, the following statements will execute.
		std::string currCourseNumLowercase = ConvertToLowercase(currNode->course.courseNumber);

		// if the strings are equal, print out the course name, number, and prerequisites.
		if (currCourseNumLowercase == courseNumber) { 
			return currNode->course; 
		}

		// if the strings are not equal, and the node's course number is less than the course number passed, check the right child node.
		else if (currCourseNumLowercase < courseNumber) {  
			currNode = currNode->right;
		}

		// if the strings are not equal, and the node's course number is less than the course number passed, check the left child node.
		else if (currCourseNumLowercase > courseNumber) { 
			currNode = currNode->left;
		}
	}

	 return std::nullopt;
}


/**
 * @brief Prints the tree in alphanumeric order staring from root using inOrder traversal.
 */
void BinaryTree::InOrderPrint(std::vector<Course>& courseVector) {
	inOrder(root, courseVector);
}

/**
 * @brief Traverses the tree recursively and stores each course and its prerequisites in ascending order in a vector.
 * @param node 
 */
void BinaryTree::inOrder(Node* node, std::vector<Course>& courseVector) {
	if (node != nullptr) {
		inOrder(node->left, courseVector);
		courseVector.push_back(node->course);
		inOrder(node->right, courseVector); 
	}
}
