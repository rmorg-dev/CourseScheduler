#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <wx/frame.h>
#include <string>
#include <wx/dataview.h>

// TODO: add file documentation.

class MainWindow : public wxFrame {
public:
	MainWindow();

private:
	wxPanel* mainPanel;
	wxButton* loadCsvBtn;
	wxButton* printAllBtn;
	wxButton* printUserInputBtn;
	wxTextCtrl* userInputBox;
	wxTextCtrl* courseView;


	void OnLoadCsvClick(wxCommandEvent& event);
	void OnPrintAllClick(wxCommandEvent& event);
	void OnPrintUserInputClick(wxCommandEvent& event);
};

#endif
