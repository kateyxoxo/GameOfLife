#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent) : wxPanel(parent), gridSize(15)
{
    this->Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this);
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
    gridSize = 15;
    cellSize = 10;
    this->Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this);
}

DrawingPanel::~DrawingPanel()
{
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context)
	{
		return;
	}
	context->SetPen(*wxBLACK_PEN);
	context->SetBrush(*wxWHITE_BRUSH);
	int panelWidth, panelHeight;
	GetSize(&panelWidth, &panelHeight);

	int cellWidth = panelWidth / gridSize;
	int cellHeight = panelHeight / gridSize;

	for (int i = 0; i < gridSize; i++)
	{

		for (int j = 0; j < gridSize; j++)
		{
			if (gameBoard[i][j])
			{
				dc.SetBrush(*wxLIGHT_GREY_BRUSH);
			}
			else
			{
				dc.SetBrush(*wxWHITE_BRUSH);
			}

			int x = j * cellWidth;
			int y = i * cellHeight;

			dc.DrawRectangle(x, y, cellWidth, cellHeight);

		}
	}

	delete context;
}



void DrawingPanel::SetGridSize(int size)
{
    gridSize = size;
    Refresh();
}

void DrawingPanel::SetGameBoard(const std::vector<std::vector<bool>>& board)
{
    gameBoard = board;
    Refresh();
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
    int mouseX = event.GetX();
    int mouseY = event.GetY();

    int panelWidth, panelHeight;
    GetClientSize(&panelWidth, &panelHeight);

    int cellWidth = panelWidth / gridSize;
    int cellHeight = panelHeight / gridSize;

    int row = mouseY / cellHeight;
    int col = mouseX / cellWidth;

    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize)
    {
        gameBoard[row][col] = !gameBoard[row][col];
        Refresh();
    }
}
