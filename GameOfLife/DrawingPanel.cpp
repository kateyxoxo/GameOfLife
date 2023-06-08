#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
DrawingPanel::DrawingPanel(wxFrame* parent) :wxPanel(parent, wxID_ANY)
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
	gridSize = 15;
	cellSize = 10;

};
DrawingPanel::~DrawingPanel()
{

}
void DrawingPanel::setGridSize(int size)
{
	gridSize = size;
}
void DrawingPanel::OnPaint(wxPaintEvent& wxPE)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	 wxGraphicsContext *context = wxGraphicsContext::Create(dc);
	if (!context) 
	{ 
		return; 
	}
	context->SetPen(*wxBLACK_PEN);
	context->SetBrush(*wxWHITE_BRUSH);
	//context->DrawRectangle(100, 100, 100, 100);
	int panelWidth, panelHeight;
	GetSize(&panelWidth, &panelHeight);

	int cellWidth = panelWidth / gridSize;
	int cellHeight = panelHeight / gridSize;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int x = i * cellWidth;
			int y = j * cellHeight;

			context->DrawRectangle(x, y, cellWidth, cellHeight);
		}
	}

	delete context;
}
