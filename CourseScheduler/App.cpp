#include "App.h"
#include "MainWindow.h"
#include "FileWindow.h"
#include "DynamicArray.h"
#include "Database.h"
#include <wx/frame.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Determines what the app will open and do when code is run.
 * @return 
 */
bool App::OnInit() {
	Database::InitializeDB("courses.db");

	if (Database::IsEmpty()) {
		Database::InsertFromCSV("courses.csv");
	}

	courseArray = new DynamicArray();
	Database::LoadAllCourseNumbers(*courseArray);
	courseArray->SortDynamicArray();
	MainWindow* window = new MainWindow();
	// FileWindow* TileWindows = new FileWindow();
	window->SetClientSize(400, 500);
	window->CenterOnScreen();
	window->Show();
	return true;
}
/**
 * @brief Determines what the app will do when the user exits the program completely.
 * @return 
 */
int App::OnExit() {
	delete courseArray;
	Database::Shutdown();
	return wxApp::OnExit();
}


wxIMPLEMENT_APP(App);