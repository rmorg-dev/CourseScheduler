#include "App.h"
#include "MainWindow.h"
#include <wx/frame.h>

bool App::OnInit() {
	MainWindow* window = new MainWindow();
	window->Show();
	return true;
}