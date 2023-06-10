#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
#include "DrawingPanel.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_MENU(ID_PLAY, MainWindow::OnPlay)
EVT_MENU(ID_PAUSE, MainWindow::OnPause)
EVT_MENU(ID_NEXT, MainWindow::OnNext)
EVT_MENU(ID_CLEAR, MainWindow::OnClear)
EVT_TIMER(wxID_ANY, MainWindow::OnTimer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size),
    gridSize(15),
    generationCount(0),
    livingCellCount(0),
    timerInterval(50)
{
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(topSizer);

    drawingPanel = new DrawingPanel(this);
    topSizer->Add(drawingPanel, 1, wxEXPAND | wxALL, 0);

    statusBar = CreateStatusBar();

    toolbar = CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL | wxTB_FLAT);
    toolbar->AddTool(ID_PLAY, "Play", wxBitmap(play_xpm));
    toolbar->AddTool(ID_PAUSE, "Pause", wxBitmap(pause_xpm));
    toolbar->AddTool(ID_NEXT, "Next", wxBitmap(next_xpm));
    toolbar->AddSeparator();
    toolbar->AddTool(ID_CLEAR, "Clear", wxBitmap(trash_xpm));
    toolbar->Realize();

    gameTimer = new wxTimer(this, wxID_ANY);

    InitializeGrid();
    drawingPanel->SetGameBoard(gameBoard);

    Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);

    UpdateLivingCellCount();
    UpdateStatusBar();
}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
    if (drawingPanel != nullptr)
    {
        wxSize windowSize = GetSize();
        drawingPanel->SetSize(windowSize);
        drawingPanel->SetGridSize(gridSize);
        drawingPanel->Refresh();
    }
    event.Skip();
}

void MainWindow::InitializeGrid()
{
    gameBoard.resize(gridSize, std::vector<bool>(gridSize, false));
    drawingPanel->SetGridSize(gridSize);
    drawingPanel->SetGameBoard(gameBoard);
    livingCellCount = 0; // Initialize the living cell count to 0
    UpdateStatusBar();
}

void MainWindow::UpdateStatusBar()
{
    wxString statusText = wxString::Format("Generation: %d, Living Cells: %d", generationCount, livingCellCount);
    statusBar->SetStatusText(statusText);
}

void MainWindow::OnPlay(wxCommandEvent& event)
{
    gameTimer->Start(timerInterval);
}

void MainWindow::OnPause(wxCommandEvent& event)
{
    gameTimer->Stop();
}

void MainWindow::OnNext(wxCommandEvent& event)
{
    NextGeneration();
}

void MainWindow::OnClear(wxCommandEvent& event)
{
    ClearBoard();
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
    CalculateNextGeneration();
}

void MainWindow::NextGeneration()
{
    std::vector<std::vector<bool>> sandbox = gameBoard; // Create a sandbox to store the next generation

    int newLivingCellCount = 0; // Initialize the count for the next generation

    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            int livingNeighbors = CountLivingNeighbors(row, col);
            bool isAlive = gameBoard[row][col];

            if (isAlive)
            {
                // Living cell rules
                if (livingNeighbors < 2 || livingNeighbors > 3)
                {
                    sandbox[row][col] = false; // Cell dies in the next generation
                }
                else
                {
                    sandbox[row][col] = true; // Cell lives in the next generation
                    newLivingCellCount++; // Increment the count for each living cell
                }
            }
            else
            {
                // Dead cell rules
                if (livingNeighbors == 3)
                {
                    sandbox[row][col] = true; // Cell becomes alive in the next generation
                    newLivingCellCount++; // Increment the count for each newly alive cell
                }
            }
        }
    }

    gameBoard.swap(sandbox); // Move the data from the sandbox to the game board
    generationCount++; // Increment the generation count
    livingCellCount = newLivingCellCount; // Update the living cell count

    UpdateStatusBar(); // Update the status bar text
    drawingPanel->SetGameBoard(gameBoard); // Update the game board in the drawing panel
    drawingPanel->Refresh(); // Refresh the drawing panel
    UpdateLivingCellCount(); // Update the living cell count (optional, if needed elsewhere)
}

int MainWindow::CountLivingCells()
{
    int count = 0;

    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            if (gameBoard[row][col])
                count++;
        }
    }

    return count;
}

void MainWindow::UpdateLivingCellCount()
{
    int count = 0;

    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            if (gameBoard[row][col])
                count++;
        }
    }

    livingCellCount = count;
}


int MainWindow::CountLivingNeighbors(int row, int col) const
{
    int count = 0;

    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            if (i == 0 && j == 0)
                continue;

            int neighborRow = row + i;
            int neighborCol = col + j;

            // Wrap around the grid
            if (neighborRow < 0)
                neighborRow = gridSize - 1;
            else if (neighborRow >= gridSize)
                neighborRow = 0;

            if (neighborCol < 0)
                neighborCol = gridSize - 1;
            else if (neighborCol >= gridSize)
                neighborCol = 0;

            if (gameBoard[neighborRow][neighborCol])
                count++;
        }
    }

    return count;
}

void MainWindow::CalculateNextGeneration()
{
    std::vector<std::vector<bool>> nextGeneration = gameBoard;
    int newLivingCellCount = 0; // Initialize the count for the next generation

    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            int livingNeighbors = CountLivingNeighbors(row, col);
            bool isAlive = gameBoard[row][col];

            if (isAlive)
            {
                if (livingNeighbors < 2 || livingNeighbors > 3)
                {
                    nextGeneration[row][col] = false;
                }
                else
                {
                    nextGeneration[row][col] = true;
                    newLivingCellCount++; // Increment the count for each living cell
                }
            }
            else
            {
                if (livingNeighbors == 3)
                {
                    nextGeneration[row][col] = true;
                    newLivingCellCount++; // Increment the count for each newly alive cell
                }
            }
        }
    }

    gameBoard.swap(nextGeneration);
    generationCount++;
    livingCellCount = newLivingCellCount; // Update the living cell count
    UpdateStatusBar();
    drawingPanel->SetGameBoard(gameBoard);
    drawingPanel->Refresh();
    UpdateLivingCellCount();
}



void MainWindow::ClearBoard()
{
    gameBoard.clear();
    gameBoard.resize(gridSize, std::vector<bool>(gridSize, false));
    generationCount = 0;
    livingCellCount = 0; // Reset living cell count
    UpdateStatusBar();
    drawingPanel->SetGameBoard(gameBoard);
    drawingPanel->Refresh();
}