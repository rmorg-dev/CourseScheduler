#define _CRT_SECURE_NO_WARNINGS // wxWidgets keeps throwing C4996 errors. These errors 

#include "MainWindow.h"
#include <wx/frame.h>
#include <wx/filectrl.h>
#include <wx/panel.h>
#include <wx/button.h>

/**
 * @brief Constructor.
 */
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Course Scheduler") {
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY, wxPoint(600, 600), wxSize(500, 500));
	mainPanel->Center();
	wxButton* loadCSVBtn = new wxButton(mainPanel, wxID_ANY, "LOAD CSV DATA", wxPoint(20, 10), wxDefaultSize);
	wxButton* printAllBtn = new wxButton(mainPanel, wxID_ANY, "PRINT ALL COURSES", wxPoint(130, 10), wxDefaultSize);
	wxButton* printUserInputBtn = new wxButton(mainPanel, wxID_ANY, "SEARCH COURSE", wxPoint(260, 10), wxDefaultSize);
	// TODO: save for separate window.
	//wxFileCtrl* file = new wxFileCtrl(mainPanel, wxID_ANY, wxEmptyString, wxEmptyString, "CSV Files (*csv)|*.csv", wxFC_OPEN);

}




