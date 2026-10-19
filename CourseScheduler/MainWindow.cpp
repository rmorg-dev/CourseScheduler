#define _CRT_SECURE_NO_WARNINGS // wxWidgets keeps throwing C4996 errors.

#include "MainWindow.h"
#include "App.h"
#include "InputValidation.h"
#include "Database.h"
#include <wx/frame.h>
#include <wx/filectrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/log.h>
#include <wx/stattext.h>
#include <wx/font.h>
#include <wx/sizer.h>
#include <wx/msgdlg.h>


/**
 * @brief Main window constructor.
 */
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Course Scheduler") {
	mainPanel = new wxPanel(this, wxID_ANY);
	header = new wxStaticText(mainPanel, wxID_ANY, "COURSE LOOK-UP");
	printAllBtn = new wxButton(mainPanel, wxID_ANY, "PRINT ALL COURSES");
	addCourseBtn = new wxButton(mainPanel, wxID_ANY, "ADD COURSE");
	courseNumberBox = new wxTextCtrl(mainPanel, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1));
	courseNameBox = new wxTextCtrl(mainPanel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
	prerequisiteBox = new wxTextCtrl(mainPanel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
	printUserInputBtn = new wxButton(mainPanel, wxID_ANY, "SEARCH COURSE");
	userInputBox = new wxTextCtrl(mainPanel, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1));
	courseView = new wxTextCtrl(mainPanel, wxID_ANY, "", wxDefaultPosition, wxSize(300, 300), wxTE_MULTILINE | wxTE_READONLY);

	font = header->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	header->SetFont(font);

	// search function box
	wxBoxSizer* buttonBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonBoxSizer->Add(printAllBtn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	buttonBoxSizer->AddSpacer(30);
	buttonBoxSizer->Add(userInputBox, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	buttonBoxSizer->Add(printUserInputBtn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	// add course box 
	wxBoxSizer* addCourseSizer = new wxBoxSizer(wxHORIZONTAL);
	addCourseSizer->Add(new wxStaticText(mainPanel, wxID_ANY, "Course Number:"), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
	addCourseSizer->Add(courseNumberBox, 0, wxALL, 5);
	addCourseSizer->Add(new wxStaticText(mainPanel, wxID_ANY, "Course Name:"), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
	addCourseSizer->Add(courseNameBox, 0, wxALL, 5);
	addCourseSizer->Add(new wxStaticText(mainPanel, wxID_ANY, "Course Prerequisites (comma-separated, course number only):"), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
	addCourseSizer->Add(prerequisiteBox, 0, wxALL, 5);
	addCourseSizer->Add(addCourseBtn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	
	
	
	// overall layout
	wxBoxSizer* windowSizer = new wxBoxSizer(wxVERTICAL);
	windowSizer->Add(header, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
	windowSizer->Add(addCourseSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
	windowSizer->Add(buttonBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
	windowSizer->Add(courseView, 1, wxEXPAND | wxALL, 10);

	mainPanel->SetSizer(windowSizer);
	windowSizer->SetSizeHints(mainPanel);

	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->Add(mainPanel, 1, wxEXPAND);
	this->SetSizerAndFit(frameSizer);

	printAllBtn->Bind(wxEVT_BUTTON, &MainWindow::OnPrintAllClick, this);
	printUserInputBtn->Bind(wxEVT_BUTTON, &MainWindow::OnPrintUserInputClick, this);
	addCourseBtn->Bind(wxEVT_BUTTON, &MainWindow::OnAddCourseClick, this);

}

void MainWindow::OnAddCourseClick(wxCommandEvent& event) {
	std::string courseNum = courseNumberBox->GetValue().ToStdString();
	std::string courseName = courseNameBox->GetValue().ToStdString();
	std::string prereqs = prerequisiteBox->GetValue().ToStdString();

	if (!isValidCourseCode(courseNum)) {
		wxLogMessage("Invalid course number. Ex: CSCI300");
		return;
	}

	if (courseName.empty()) {
		wxLogMessage("Course name cannot be empty.");
		return;
	}

	std::vector<std::string> prereqVector = SplitPrereqs(prereqs);
	for (const std::string& prereq : prereqVector){
		if (!isValidCourseCode(prereq)) {
			wxLogMessage("Invalid prerequisite course number. Prerequisites must follow the same format as course numbers.");
			return;
		}
	}

	if (wxGetApp().courseArray->Search(courseNum)) {
		wxLogMessage("A course with that number already exists.");
		return;
	}

	wxString confirmationMsg;
	confirmationMsg << "Course Number: " << courseNum << "\n" << "Course Name: " << courseName << "\n" << "Prerequisites: " << (prereqVector.empty() ? wxString("none") : wxString(prereqs)) << "\n\n" << "Add this course?";

	wxMessageDialog confirmationDlg(this, confirmationMsg, "Confirm New Course", wxYES_NO | wxICON_QUESTION);

	if (confirmationDlg.ShowModal() != wxID_YES) {
		return;
	}

	if (!Database::InsertCourse(courseNum, courseName, prereqVector)) {
		wxLogMessage("Failed to add course to the database.");
		return;
	}

	wxGetApp().courseArray->Insert(courseNum);

	courseNumberBox->SetValue("");
	courseNameBox->SetValue("");
	prerequisiteBox->SetValue("");
	wxLogMessage("Course added successfully.");
}

/**
 * @brief Prints out all of the current courses stored in the binary tree into a multi-line, read-only text box.
 * @param event 
 */
void MainWindow::OnPrintAllClick(wxCommandEvent& event) {
	courseView->SetValue("");
	wxString outputString;
	outputString = Database::GetAllCourses();
	courseView->AppendText(outputString);
	courseView->SetFont(courseView->GetFont().Bold());
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

	auto specificCourse = wxGetApp().courseArray->Search(courseNumber);

	if (specificCourse){
		wxString outputString;
		outputString = Database::GetCoursePrereqs(courseNumber);
		courseView->AppendText(outputString);
		courseView->SetFont(courseView->GetFont().Bold());
	}

	else {
		wxLogMessage("Course Number not found!");
	}
}	





