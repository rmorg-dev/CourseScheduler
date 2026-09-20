#ifndef APP_H
#define APP_H
#include "BinaryTree.h"
#include <wx/app.h>
#include <string>

class App : public wxApp {
public:
	bool OnInit() override;
	int OnExit() override;
	bool ReadCSV(const wxString& filename, BinaryTree* tree);
	BinaryTree* courseTree = nullptr;
private:

};

wxDECLARE_APP(App);

#endif

