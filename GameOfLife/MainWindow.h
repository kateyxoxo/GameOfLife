#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
class MainWindow :public wxFrame
{
	DrawingPanel* drawingPanel;
	wxBoxSizer* boxSizer;
public:
	MainWindow(const wxString& title);
	void OnSizeChange(wxSizeEvent& event);
	std::vector<std::vector<bool>> gameBoard;
	void initializeGrid();
	~MainWindow();
	int gridSize = 15;




};
