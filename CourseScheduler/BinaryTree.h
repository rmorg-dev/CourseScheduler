#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <string>
#include <vector>
#include <optional>

/**
 * @brief This struct contains the course information.
 */
struct Course {
	std::string courseNumber;
	std::string courseName;
	std::vector<std::string> prerequisites;
};

/**
 * @brief This struct holds the course data with pointers to left and right nodes.
 */
struct Node {
	Course course;
	Node* left;
	Node* right;

	Node() {
		left = nullptr;
		right = nullptr;
	}

	Node(Course course) {
		this->course = course;
		left = nullptr;
		right = nullptr;
	}

	~Node() {
		delete left;
		delete right;
	}
};

/**
 * @brief This class stores nodes in ascending alphanumeric order in a tree data structure.
 */
class BinaryTree {
private:
	Node* root;
	void inOrder(Node* node, std::vector<Course>& courseVector);

public:
	BinaryTree();
	~BinaryTree();
	void Insert(const Course& course);
	std::optional<Course> Search(const std::string& courseNumber);
	void InOrderPrint(std::vector<Course>& courseVector);
};

#endif