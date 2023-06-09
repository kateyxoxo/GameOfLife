#pragma once
#include "wx/wx.h"
class DrawingPanel :
    public wxPanel
{
public:
    DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoard);
    ~DrawingPanel();
    void setGridSize(int size);

private:
    void OnMouseUp(wxMouseEvent& event);
    void OnPaint(wxPaintEvent&);
    int gridSize;
    int cellSize;
    std::vector<std::vector<bool>>& gameBoard;

    wxDECLARE_EVENT_TABLE();

};

