#ifndef APP_H
#define APP_H
#include "DynamicArray.h"
#include <wx/app.h>
#include <string>

/**
 * @brief This class contains the functions and variables required for the program to run.
 */
class App : public wxApp {
public:
	bool OnInit() override;
	int OnExit() override;
	bool ReadCSV(const wxString& filename, DynamicArray* array);
	DynamicArray* courseArray = nullptr;
};

wxDECLARE_APP(App);

#endif

