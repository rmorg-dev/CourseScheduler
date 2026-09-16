#include "MainWindow.h"
#include <wx/frame.h>
#include <wx/filectrl.h>
#include <wx/panel.h>

/**
 * @brief Constructor.
 */
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Course Scheduler") {
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
	wxFileCtrl* file = new wxFileCtrl(mainPanel, wxID_ANY, "", "", "CSV Files (*csv)|*.csv", wxFC_OPEN, wxPoint(150, 50), wxSize(150, 50), "FILE SELECTION");
}



