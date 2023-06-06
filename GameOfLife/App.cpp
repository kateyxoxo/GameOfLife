#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	MainWindow* mainwindow = new MainWindow("Window");
	mainwindow->Show(true);

	return true;
}