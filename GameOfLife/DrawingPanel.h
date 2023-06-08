#pragma once
#include "wx/wx.h"
class DrawingPanel :
    public wxPanel
{
public:
        DrawingPanel(wxFrame*);
        ~DrawingPanel();
        void setGridSize(int size);
private:
        void OnPaint(wxPaintEvent&);
        int gridSize;
        int cellSize;
};


