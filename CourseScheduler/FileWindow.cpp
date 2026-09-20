#include "FileWindow.h"
#include "App.h"
#include <wx/filectrl.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/log.h>

FileWindow::FileWindow() : wxFrame(nullptr, wxID_ANY, "File Search") {
	filePanel = new wxPanel(this);
	file = new wxFileCtrl(filePanel, wxID_ANY, wxEmptyString, wxEmptyString, "CSV Files (*csv)|*.csv", wxFC_OPEN);
	file->Bind(wxEVT_FILECTRL_FILEACTIVATED, &FileWindow::OnUserActivateFile, this);
}

void FileWindow::OnUserActivateFile(wxFileCtrlEvent& event) {
	bool fileReadStatus = wxGetApp().ReadCSV(file->GetFilename(), wxGetApp().courseTree);
	if (!fileReadStatus) {
		wxLogMessage("File Load Failed!");
	}
	else {
		wxLogMessage("File Load Successful!");
	}
}