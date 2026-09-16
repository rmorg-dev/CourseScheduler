#include "BinaryTree.h"
#include <iostream>
#include <string>
#include <vector>


/**
 * @brief Constructor.
 */
BinaryTree::BinaryTree() {
	this->root = nullptr; 
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
void BinaryTree::Search(const std::string& courseNumber) {
	Node* currNode = root;
	// std::string lowerCaseCourseNum = ConvertToLowercase(courseNumber); 

	while (currNode != nullptr) { // if tree has data, the following statements will execute.
		//TODO: remove std::string lowerNodeCourseNum = ConvertToLowercase(currNode->course.courseNumber); // the currNode's course number is converted to lowercase to check against the courseNumber passed.
		
		// if the strings are equal, print out the course name, number, and prerequisites.
		if (currNode->course.courseNumber == courseNumber) { 
			std::cout << currNode->course.courseNumber << ": " << currNode->course.courseName << std::endl;
			std::cout << "Prerequisites: " << std::endl;
			for (int i = 0; i < currNode->course.prerequisites.size(); i++) {
				std::cout << currNode->course.prerequisites[i] << std::endl;
			}
			std::cout << std::endl;
			return; 
		}

		// if the strings are not equal, and the node's course number is less than the course number passed, check the right child node.
		else if (currNode->course.courseNumber < courseNumber) {  
			currNode = currNode->right;
		}

		// if the strings are not equal, and the node's course number is less than the course number passed, check the left child node.
		else if (currNode->course.courseNumber > courseNumber) { 
			currNode = currNode->left;
		}
	}

	std::cout << courseNumber << " not found." << std::endl; 
}


/**
 * @brief Prints the tree in alphanumeric order staring from root using inOrder traversal.
 */
void BinaryTree::InOrderPrint() {
	inOrder(root);
}

/**
 * @brief Traverses the tree recursively and prints out each course and its prerequisites in ascending order.
 * @param node 
 */
void BinaryTree::inOrder(Node* node) {
	if (node != nullptr) {
		inOrder(node->left);

		std::cout << "     " << node->course.courseNumber << ": " << node->course.courseName << std::endl << std::endl;
		inOrder(node->right); 
	}
}
