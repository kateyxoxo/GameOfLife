#include "MainWindow.h"
MainWindow::MainWindow() :wxFrame(nullptr, wxID_ANY, "Game of Life.", wxPoint(200, 200))
{
	drawingPanel = new DrawingPanel(this);
}
MainWindow::~MainWindow()
{

}