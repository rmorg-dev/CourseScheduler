#pragma once
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
	void Insert(Course course);
	void Search(string courseNumber);
	void InOrderPrint();
};

