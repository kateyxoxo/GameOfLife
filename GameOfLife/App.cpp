#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	mainWindow = new MainWindow("Game of Life", wxDefaultPosition, wxSize(800,800));
	mainWindow->Show();

	return true;
}