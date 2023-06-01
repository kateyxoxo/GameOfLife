#pragma once
#include "wx/wx.h"
class DrawingPanel :
    public wxPanel
{
public:
        DrawingPanel(wxFrame*);
        ~DrawingPanel();
        void OnPaint(wxPaintEvent&);
};


