#define _CRT_SECURE_NO_WARNINGS // wxWidgets keeps throwing C4996 errors. These errors 

#include "MainWindow.h"
#include <wx/frame.h>
#include <wx/filectrl.h>
#include <wx/panel.h>

/**
 * @brief Constructor.
 */
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Course Scheduler") {
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
	wxFileCtrl* file = new wxFileCtrl(mainPanel, wxID_ANY, wxEmptyString, wxEmptyString, "CSV Files (*csv)|*.csv", wxFC_OPEN);

}




