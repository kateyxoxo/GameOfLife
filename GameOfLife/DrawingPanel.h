#pragma once
#include "wx/wx.h"
class DrawingPanel :
    public wxPanel
{
public:
        DrawingPanel(wxFrame*);
        ~DrawingPanel();
private:
        void OnPaint(wxPaintEvent&);
        int gridSize;
        int cellSize;

};


