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
	wxButton* loadCsvBtn;
	wxButton* printAllBtn;
	wxButton* printUserInputBtn;
	wxTextCtrl* userInputBox;
	wxTextCtrl* courseView;
	wxFont font;


	void OnLoadCsvClick(wxCommandEvent& event);
	void OnPrintAllClick(wxCommandEvent& event);
	void OnPrintUserInputClick(wxCommandEvent& event);
};

#endif
