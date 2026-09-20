#ifndef APP_H
#define APP_H
#include "BinaryTree.h"
#include <wx/app.h>
#include <string>
#include <regex>

class App : public wxApp {
public:
	bool OnInit() override;
	int OnExit() override;
	bool ReadCSV(const wxString& filename, BinaryTree* courseTree);
	BinaryTree* courseTree = nullptr;
private:

};

DECLARE_APP(App);

#endif

