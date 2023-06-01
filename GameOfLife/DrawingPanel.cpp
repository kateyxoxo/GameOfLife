#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
DrawingPanel::DrawingPanel(wxFrame* parent) :wxPanel(parent, wxID_ANY)
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
};
DrawingPanel::~DrawingPanel()
{

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
	context->DrawRectangle(100, 100, 100, 100);
}
