#pragma once

#include "wx/wx.h"
#include <vector>

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent);
    ~DrawingPanel();
    void OnMouseUp(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);
    void SetGridSize(int size);
    void SetGameBoard(const std::vector<std::vector<bool>>& board);

private:
    wxGraphicsContext* context;
    int gridSize;
    int cellSize;
    std::vector<std::vector<bool>> gameBoard;

    wxDECLARE_EVENT_TABLE();
};