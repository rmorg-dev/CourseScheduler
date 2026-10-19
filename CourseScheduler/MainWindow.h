#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/stattext.h>

/**
 * @brief This class contains the function and variable declarations required for the Main Window.
 */
class MainWindow : public wxFrame {
public:
	MainWindow();

private:
	wxPanel* mainPanel;
	wxStaticText* header;
	wxButton* printAllBtn;
	wxButton* printUserInputBtn;
	wxButton* addCourseBtn;
	wxTextCtrl* courseNumberBox;
	wxTextCtrl* courseNameBox;
	wxTextCtrl* prerequisiteBox;
	wxTextCtrl* userInputBox;
	wxTextCtrl* courseView;
	wxFont font;


	void OnAddCourseClick(wxCommandEvent& event);
	void OnPrintAllClick(wxCommandEvent& event);
	void OnPrintUserInputClick(wxCommandEvent& event);
};

#endif
