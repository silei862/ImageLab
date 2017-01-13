// File		: imagecanvas.cpp
// Author	: Silei
// Descr	: Display a image support zoom and drag


#include "imagecanvas.h"
#include <iostream>

ImageCanvas::ImageCanvas(wxWindow *parent,
                         wxWindowID id,
                         const wxPoint &pos,
                         const wxSize &size)
    : wxScrolled<wxWindow>(parent, id, pos, size,
                           wxVSCROLL | wxHSCROLL | wxFULL_REPAINT_ON_RESIZE),
    image(wxNullImage),
    scale(SCALE_BASE),
    scaleBase(SCALE_BASE),
    scaleMax(SCALE_MAX),
    scaleMin(SCALE_MIN),
    scaleDelta(SCALE_DELTA),
	prevXPosScale(0.5),
	prevYPosScale(0.5){

    SetCursor(wxCURSOR_HAND);
    wxColour bg(25, 25, 25);
    SetBackgroundColour(bg);
    SetMinSize(wxSize(600, 350));
    SetDoubleBuffered(true);

    Bind(wxEVT_PAINT, &ImageCanvas::OnPaint, this);
    Bind(wxEVT_MOUSEWHEEL, &ImageCanvas::OnMouseWheel, this);
    Bind(wxEVT_LEFT_DOWN, &ImageCanvas::OnMouseLeftDown, this);
    Bind(wxEVT_MOTION, &ImageCanvas::OnMouseMotion, this);
}

ImageCanvas::~ImageCanvas() {}

wxSize ImageCanvas::DoGetBestSize() const { return wxSize(600, 350); }

void ImageCanvas::SetImage(const wxImage &img) {
    image = img.Copy();
    // Refresh Canvas:
    UpdateCanvas();
}

wxImage &ImageCanvas::GetImage() { return image; }

void ImageCanvas::SetZoomPara(int base, int max, int min, int delta) {
    // Migrant to new paramenter,make scale proper to new paramenter
    scale = float(scale) / scaleBase * base;

    // preserve new paramenter:
    scaleBase = base;
    scaleMax = max;
    scaleMin = min;
    scaleDelta = delta;
}

void ImageCanvas::FitSize() {
    int w, h;
    GetClientSize(&w, &h);
    FitSize(w, h);
    UpdateCanvas();
    GetClientSize(&w, &h);
    Scroll(w / 2, h / 2);
}

void ImageCanvas::FitSize(int w, int h) {
    // Work out minimum scale to new w & h
    if (image.IsOk()) {
      wxDouble xscale = float(w) / image.GetWidth();
      wxDouble yscale = float(h) / image.GetHeight();
      scale = ((xscale < yscale) ? xscale : yscale) * scaleBase;
    }
}

void ImageCanvas::ScaleTo(int sc) {
	if (image.IsOk()) {
		if (scaleMin < sc && sc < scaleMax)
			scale = sc;
		else if (sc < scaleMin)
			scale = scaleMin;
	else
		scale = scaleMax;
	}
}

void ImageCanvas::ZoomOut() {
  	if (image.IsOk()) {
    	scale += scaleDelta;
    	scale = (scale > scaleMax) ? scaleMax : scale;
  	}
}

void ImageCanvas::ZoomIn() {

	if (image.IsOk()) {
    	scale -= scaleDelta;
    	scale = (scale < scaleDelta) ? scaleMin : scale;
	}
}

bool ImageCanvas::CaculateDispSize(int *w, int *h) {
	wxDouble scl = wxDouble(scale) / scaleBase;
	if (image.IsOk()) {
		*w = scl *image.GetWidth();
		*h = scl *image.GetHeight();
		return true;
	} else
		return false;
}

void ImageCanvas::UpdateCanvas() {
	int w, h;
	if (CaculateDispSize(&w, &h)) {
		SetScrollbars(1, 1, w + 10, h + 10, prevXPosScale*w, prevYPosScale*h, true );
		Refresh();
		prevXPosScale = GetScrollPos(wxHORIZONTAL) / w;
		prevYPosScale = GetScrollPos(wxVERTICAL) / h;
	}
}

void ImageCanvas::UpdateCanvas(int x, int y){
	int w, h;
	if (CaculateDispSize(&w, &h)) {
		int cw, ch;
		GetClientSize(&cw, &ch);
		SetScrollbars(1, 1, w, h, 0, 0, true );
		int preX = w*prevXPosScale;
		int preY = h*prevYPosScale;
		int scx = preX - x + prevMPos.x;
		int scy = preY - y + prevMPos.y;
		Scroll(w*x/cw, h*y/ch);
    	Refresh();
		prevXPosScale = GetScrollPos(wxHORIZONTAL) / w;
		prevYPosScale = GetScrollPos(wxVERTICAL) / h;
		prevMPos.x = x;
		prevMPos.y = y;
	}
}

void ImageCanvas::OnPaint(wxPaintEvent &event) {
	wxPaintDC dc(this);
	DoPrepareDC(dc);
	Render(dc);
}

void ImageCanvas::Render(wxPaintDC &dc) {
	int x, y, w, h, vw, vh;
	if (CaculateDispSize(&w, &h)) {
		GetVirtualSize(&vw, &vh);
		// Get central position:
		x = (vw - w) / 2;
		y = (vh - h) / 2;
		dc.DrawBitmap(wxBitmap(image.Scale(w, h)), x, y);
	}
}

void ImageCanvas::OnMouseWheel(wxMouseEvent &event) {
    // TODO:Eliminate image position while zoom with mouse wheel
    int rot = event.GetWheelRotation();
    if (rot > 0)
        ZoomOut();
    else
        ZoomIn();
    int x = event.GetX();
    int y = event.GetY();
    UpdateCanvas(x, y);
    event.Skip();
}

void ImageCanvas::OnMouseLeftDown(wxMouseEvent &event) {
    // preserve position of mouse
    mousePos.x = event.GetX();
    mousePos.y = event.GetY();
    scrollPos.x = GetScrollPos(wxHORIZONTAL);
    scrollPos.y = GetScrollPos(wxVERTICAL);
    event.Skip();
}

void ImageCanvas::OnMouseMotion(wxMouseEvent &event) {
    if (event.Dragging()) {
        int x, y, scx, scy;
        x = event.GetX();
        y = event.GetY();
        scx = scrollPos.x - x + mousePos.x;
        scy = scrollPos.y - y + mousePos.y;
        Scroll(scx, scy);
    }
}
