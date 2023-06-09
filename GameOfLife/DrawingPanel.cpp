#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseUp)
EVT_SIZE(MainWindow::OnSizeChange)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoard):wxPanel(parent), gameBoard(gameBoard)
{
	this->Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this);
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
	gridSize = 15;
	cellSize = 10;
	this->Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this);

};
DrawingPanel::~DrawingPanel()
{

}
void DrawingPanel::setGridSize(int size)
{
	gridSize = size;
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

			int x = i * cellWidth;
			int y = j * cellHeight;

			dc.DrawRectangle(x, y, cellWidth, cellHeight);
			
		}
	}

	delete context;

}
void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
	int x = event.GetX();
	int y = event.GetY();

	int cellWidth = GetSize().GetWidth() / gridSize;
	int cellHeight = GetSize().GetHeight() / gridSize;

	int col = y / cellHeight;
	int row = x / cellWidth;

	gameBoard[row][col] = !gameBoard[row][col];

	Refresh();
}
