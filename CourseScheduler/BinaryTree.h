#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <string>
#include <vector>

struct Course {
	std::string courseNumber;
	std::string courseName;
	std::vector<std::string> prerequisites;
};

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

class BinaryTree {
private:
	Node* root;
	void inOrder(Node* node);
	int size = 0;

public:
	BinaryTree();
	~BinaryTree();
	void Insert(const Course& course);
	void Search(const std::string& courseNumber);
	void InOrderPrint();
};

#endif