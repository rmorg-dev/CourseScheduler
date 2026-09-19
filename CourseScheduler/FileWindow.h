#ifndef FILEWINDOW_H
#define FILEWINDOW_H
#include "BinaryTree.h"
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/filectrl.h>

class FileWindow : public wxFrame {
public:
	FileWindow();
	void OnUserActivateFile(wxFileCtrlEvent& event);
private:
	wxPanel* filePanel;
	wxFileCtrl* file;

};

#endif

