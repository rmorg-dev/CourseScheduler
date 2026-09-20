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


/**
 * @brief Constructor.
 */
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Course Scheduler") {
	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(600, 600), wxSize(500, 500));
	loadCsvBtn = new wxButton(mainPanel, wxID_ANY, "LOAD CSV DATA", wxPoint(20, 10), wxDefaultSize);
	printAllBtn = new wxButton(mainPanel, wxID_ANY, "PRINT ALL COURSES", wxPoint(130, 10), wxDefaultSize);
	printUserInputBtn = new wxButton(mainPanel, wxID_ANY, "SEARCH COURSE", wxPoint(260, 10), wxDefaultSize);
	userInputBox = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(100, 50), wxDefaultSize);
	courseView = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(100, 100), wxSize(600, 600), wxTE_MULTILINE | wxTE_READONLY);

	loadCsvBtn->Bind(wxEVT_BUTTON, &MainWindow::OnLoadCsvClick, this);
	printAllBtn->Bind(wxEVT_BUTTON, &MainWindow::OnPrintAllClick, this);
	printUserInputBtn->Bind(wxEVT_BUTTON, &MainWindow::OnPrintUserInputClick, this);


}

void MainWindow::OnLoadCsvClick(wxCommandEvent& event) {
	FileWindow* fileWindow = new FileWindow();
	fileWindow->Show();
}

void MainWindow::OnPrintAllClick(wxCommandEvent& event) {
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
	courseView->IsModified() == true;
}

void MainWindow::OnPrintUserInputClick(wxCommandEvent& event) {
	if (courseView->IsModified() == true) {
		courseView->SetValue("");
	}

	std::string courseNumber = userInputBox->GetValue().ToStdString();
	if (!isValidCourseCode(courseNumber)) {
		wxLogMessage("Invalid format. Please type the course number without spaces similar to the example.");
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
			outputString.append("\n PREREQUISITES: \n");
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




