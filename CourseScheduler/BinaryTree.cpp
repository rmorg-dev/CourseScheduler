#include "BinaryTree.h"



BinaryTree::BinaryTree() {
	this->root = nullptr; // assigns the tree's root to nullptr.
}

/* insert a course into the tree. */
void BinaryTree::Insert(Course course) {
	Node* currNode = root;

	if (root == nullptr) { // if there is no data in the tree, the root will be null.
		root = new Node(course); // so we assign the course to the root and exit the function.
		return;
	}

	while (currNode != nullptr) { // if the root is not null ptr, we traverse through the tree until we find a spot to insert the course. 
		if (currNode->course.courseNumber.compare(course.courseNumber) < 0) { // this checks if the currNode's course number is alphanumerically lower than the course number of the course passed in, if yes, we insert into the right.
			if (currNode->right == nullptr) { // if there is no node stored on the right of the currNode,
				currNode->right = new Node(course); // we simply store the new course in the right child node.
				return; // then exit the function.
			}
			else {
				currNode = currNode->right; // if there is a node to the right of currNode, then we continue to traverse. 
			}

		}
		else if (currNode->course.courseNumber.compare(course.courseNumber) > 0) { // this checks if the currNode's course number is alphanumerically higher than the course number of the course passed in; if yes, we insert into the left.
			if (currNode->left == nullptr) { // if there is no left child node, 
				currNode->left = new Node(course); // we simply store the new course in the left child node. 
				return; // then exit the function.
			}
			else {
				currNode = currNode->left; // if there is a node to the left of currNode, then we continue to traverse.
			}
		}

		else { // if neither of these conditions are met, it means we are trying to insert a node we already have. Since there are no duplicates...
			return; // we simply exit the function. 
		}
	}
}
/*
* Function searches the tree for the course number passed.
*/
void BinaryTree::Search(string courseNumber) {
	Node* currNode = root;
	string lowerCaseCourseNum = ConvertToLowercase(courseNumber); // converting to lowercase to check against valid user input that was input in all caps or all lowercase. removes a validation barrier and is easier for user.

	while (currNode != nullptr) { // if tree has data, the following statements will execute.
		string lowerNodeCourseNum = ConvertToLowercase(currNode->course.courseNumber); // the currNode's course number is converted to lowercase to check against the courseNumber passed.
		if (lowerNodeCourseNum == lowerCaseCourseNum) { // if the strings are equal, print out the course name, number, and prerequisites.
			cout << currNode->course.courseNumber << ": " << currNode->course.courseName << endl;
			cout << "Prerequisites: " << endl;
			for (int i = 0; i < currNode->course.prerequisites.size(); i++) { // have to loop for the prerequisites because it is a vector. 
				cout << currNode->course.prerequisites[i] << endl;
			}
			cout << endl;
			return; // exit the function.
		}
		else if (lowerNodeCourseNum < lowerCaseCourseNum) { // if the strings are not equal, and the node's course number is less than the course number passed, check the right child node. 
			currNode = currNode->right;
		}
		else if (lowerNodeCourseNum > lowerCaseCourseNum) { // if the strings are not equal, and the node's course number is greater than the course number passed, check the left child node.
			currNode = currNode->left;
		}
	}

	cout << courseNumber << " not found." << endl; // if the course number is not found in the tree, the error statement is printed. 
}


/*
* Prints the tree in alphanumeric order staring from root using inOrder traversal.
*/
void BinaryTree::InOrderPrint() {
	inOrder(root);
}
/*
* Traverses the tree in order and prints out each course and its prerequisites.
*/
void BinaryTree::inOrder(Node* node) {
	if (node != nullptr) {
		inOrder(node->left); //traverses the left-most node first.

		// this is the print statement for the node. NOTE: I didn't put any prerequisites because there were none listed in the sample output.
		cout << "     " << node->course.courseNumber << ": " << node->course.courseName << endl << endl;
		inOrder(node->right); //then traverse the right-most node.
	}
}
