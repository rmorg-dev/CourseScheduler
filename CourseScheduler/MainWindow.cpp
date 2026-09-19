#define _CRT_SECURE_NO_WARNINGS // wxWidgets keeps throwing C4996 errors. These errors 

#include "MainWindow.h"
#include "FileWindow.h"
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

	loadCsvBtn->Bind(wxEVT_BUTTON, &MainWindow::OnLoadCsvClick, this);
	printAllBtn->Bind(wxEVT_BUTTON, &MainWindow::OnPrintAllClick, this);
	printUserInputBtn->Bind(wxEVT_BUTTON, &MainWindow::OnPrintUserInputClick, this);


}

void MainWindow::OnLoadCsvClick(wxCommandEvent& event) {
	FileWindow* fileWindow = new FileWindow();
	fileWindow->Show();
}

void MainWindow::OnPrintAllClick(wxCommandEvent& event) {
}

void MainWindow::OnPrintUserInputClick(wxCommandEvent& event) {
}




