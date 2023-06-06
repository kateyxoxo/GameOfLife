#include "MainWindow.h"
MainWindow::MainWindow(const wxString& title) :wxFrame(nullptr, wxID_ANY, "Game of Life.", wxPoint(200, 200))
{
	drawingPanel = new DrawingPanel(this);
	boxSizer = new wxBoxSizer(wxVERTICAL);
	boxSizer->Add(drawingPanel, 1, wxEXPAND | wxALL);
	this->SetSizer(boxSizer);
	this->Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);
}
void MainWindow::OnSizeChange(wxSizeEvent& event)
{
	wxSize windowSize = event.GetSize();
	drawingPanel->SetSize(windowSize);
	event.Skip();
}
MainWindow::~MainWindow()
{

}
