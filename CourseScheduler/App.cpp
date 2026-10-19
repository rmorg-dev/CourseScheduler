#include "App.h"
#include "MainWindow.h"
#include "DynamicArray.h"
#include "Database.h"
#include <wx/frame.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Initializes the application as well as the DB connection and displays the main window.
 * @return True when app startup succeeds.
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
	window->SetClientSize(400, 500);
	window->CenterOnScreen();
	window->Show();
	return true;
}
/**
 * @brief Releases application resources on shutdown.
 * @return Exit status returned by wxWidgets.
 */
int App::OnExit() {
	delete courseArray;
	Database::Shutdown();
	return wxApp::OnExit();
}


wxIMPLEMENT_APP(App);