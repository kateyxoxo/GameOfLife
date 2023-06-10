#pragma once

#include <wx/wx.h>
#include <wx/timer.h>
#include "DrawingPanel.h"

enum
{
    ID_PLAY = wxID_HIGHEST + 1,
    ID_PAUSE,
    ID_NEXT,
    ID_CLEAR
};

class MainWindow : public wxFrame
{
public:
    MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnSizeChange(wxSizeEvent& event);
    void InitializeGrid();
    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void NextGeneration();

private:
    DrawingPanel* drawingPanel;
    std::vector<std::vector<bool>> gameBoard;
    int gridSize;
    int generationCount;
    int livingCellCount;
    wxStatusBar* statusBar;
    wxToolBar* toolbar;
    wxTimer* gameTimer;
    int timerInterval;
    void UpdateLivingCellCount();
    int CountLivingNeighbors(int row, int col) const;
    void ClearBoard();
    void CalculateNextGeneration();
    int CountLivingCells();
    void UpdateStatusBar();

    wxDECLARE_EVENT_TABLE();
};