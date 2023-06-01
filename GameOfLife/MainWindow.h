#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
class MainWindow:public wxFrame
{
	DrawingPanel* drawingPanel;
public:
	MainWindow();
	~MainWindow();
	
};

