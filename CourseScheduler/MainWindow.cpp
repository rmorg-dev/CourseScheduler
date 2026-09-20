#define _CRT_SECURE_NO_WARNINGS // wxWidgets keeps throwing C4996 errors.

#include "MainWindow.h"
#include "FileWindow.h"
#include "App.h"
#include "InputValidation.h"
#include <wx/frame.h>
#include <wx/filectrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/log.h>
#include <wx/stattext.h>
#include <wx/font.h>


/**
 * @brief Main window constructor.
 */
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Course Scheduler") {
	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(600, 600), wxSize(500, 500));
	header = new wxStaticText(mainPanel, wxID_ANY, "COURSE LOOK-UP", wxPoint(150, 25), wxSize(150, 25));
	loadCsvBtn = new wxButton(mainPanel, wxID_ANY, "LOAD CSV DATA", wxPoint(50, 50), wxSize(150,25));
	printAllBtn = new wxButton(mainPanel, wxID_ANY, "PRINT ALL COURSES", wxPoint(200, 50), wxSize(150,25));
	printUserInputBtn = new wxButton(mainPanel, wxID_ANY, "SEARCH COURSE", wxPoint(200, 100), wxSize(150,25));
	userInputBox = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(50, 100), wxSize(150, 25));
	courseView = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(50, 150), wxSize(300, 300), wxTE_MULTILINE | wxTE_READONLY);

	font = header->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	header->SetFont(font);

	loadCsvBtn->Bind(wxEVT_BUTTON, &MainWindow::OnLoadCsvClick, this);
	printAllBtn->Bind(wxEVT_BUTTON, &MainWindow::OnPrintAllClick, this);
	printUserInputBtn->Bind(wxEVT_BUTTON, &MainWindow::OnPrintUserInputClick, this);


}

/**
 * @brief Opens the file window when a user clicks on the Load CSV button.
 * @param event 
 */
void MainWindow::OnLoadCsvClick(wxCommandEvent& event) {
	FileWindow* fileWindow = new FileWindow();
	fileWindow->Show();
}

/**
 * @brief Prints out all of the current courses stored in the binary tree into a multi-line, read-only text box.
 * @param event 
 */
void MainWindow::OnPrintAllClick(wxCommandEvent& event) {
	courseView->SetValue("");

	std::vector<Course> courseVector;
	wxGetApp().courseTree->InOrderPrint(courseVector);
	wxString outputString;
	for (const Course& course : courseVector) {
		outputString.append(course.courseNumber);
		outputString.append(": ");
		outputString.append(course.courseName);
		outputString.append("\n\n");
	}
	courseView->AppendText(outputString);
}

/**
 * @brief Prints out the course information for a course number entered by the user after clicking on the search course button.
 * @param event 
 */
void MainWindow::OnPrintUserInputClick(wxCommandEvent& event) {
	courseView->SetValue("");
	std::string courseNumber = userInputBox->GetValue().ToStdString();
	if (!isValidCourseCode(courseNumber)) {
		wxLogMessage("Invalid format. Please type the course number without spaces. EX: CSCI300");
		return;
	}

	std::string courseNumberLowercase = ConvertToLowercase(courseNumber);
	auto specificCourse = wxGetApp().courseTree->Search(courseNumberLowercase);

	if (specificCourse.has_value()){
		Course c = specificCourse.value();
		wxString outputString;
		outputString.append(c.courseNumber);
		outputString.append(": ");
		outputString.append(c.courseName);

		if (c.prerequisites.size() > 0) {
			outputString.append("\nPREREQUISITES: \n");
				for (int i = 0; i < c.prerequisites.size(); i++) {
					outputString.append(c.prerequisites[i]);
					outputString.append("\n");
				}
		}
		courseView->AppendText(outputString);
	}

	else {
		wxLogMessage("Course Number not found!");
	}
}




