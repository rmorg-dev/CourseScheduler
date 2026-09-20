#include "App.h"
#include "MainWindow.h"
#include "FileWindow.h"
#include "BinaryTree.h"
#include <wx/frame.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


bool App::OnInit() {
	courseTree = new BinaryTree();
	MainWindow* window = new MainWindow();
	// FileWindow* TileWindows = new FileWindow();
	window->CenterOnScreen();
	window->Show();
	return true;
}

int App::OnExit() {
	delete courseTree;
	return wxApp::OnExit();
}

bool App::ReadCSV(const wxString& filename, BinaryTree* tree) {
	std::string filenameStr = filename.ToStdString();
	std::ifstream fileIn(filenameStr);
	std::vector<std::vector<std::string>> csvRows; // a super vector that contains other vectors of strings allowing for easier parsing. 
	bool successfulRead;

	if (!fileIn) {
		successfulRead = false;
		return successfulRead;
	}
	else {
		successfulRead = true;
	}

	/* read each line of the file and find each element separated by ',' on said line. These will then be stored into a string vector. This string vector will then be added into the super vector. */
	for (std::string line; getline(fileIn, line);) {
		std::istringstream ss(line);
		std::vector<std::string> row;

		for (std::string value; getline(ss, value, ',');) {
			row.push_back(value);
		}

		csvRows.push_back(row);
	}

	/* iterate through each element stored in the super vector and store them as a course data type. If greater than 2 elements exist within the super element, then the remaining elements
	are stored in the prerequisites vector. They are then inserted into the Binary Tree data structure. */
	for (const std::vector<std::string>& row : csvRows) {
		if (row.size() < 2) {
			continue;
		}

		Course course;
		course.courseNumber = row[0];
		course.courseName = row[1];

		if (row.size() > 2) {
			for (int i = 2; i < row.size(); i++) {
				course.prerequisites.push_back(row[i]);
			}
		}
		courseTree->Insert(course);
	}

	return successfulRead;
}


wxIMPLEMENT_APP(App);