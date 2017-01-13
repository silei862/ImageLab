#ifndef _IMAGECANVAS_H_
#define _IMAGECANVAS_H_

#include "wx_pch.h"

class ImageCanvas : public wxScrolled<wxWindow> {
  enum _CONST {
    // Default Scale Paramenter:
    SCALE_BASE = 100, // Base value of scale
    SCALE_MIN = 10, // minimum value of scale
    SCALE_MAX = 200, // maximum value of scale
    SCALE_DELTA = 5, // zoom out/in step
  };

public:
  ImageCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
              const wxPoint &pos = wxPoint(0, 0),
              const wxSize &size = wxDefaultSize);
  ~ImageCanvas();

  // provide best size
  wxSize DoGetBestSize() const;

  void SetImage(const wxImage &img);
  wxImage &GetImage();

  // Zoom & fit:
  void SetZoomPara(int base, int max, int min, int delta);
  void FitSize();
  void FitSize(int w, int h);
  void ScaleTo(int sc);
  void ZoomOut();
  void ZoomIn();

  // Refresh:
  void UpdateCanvas();
  void UpdateCanvas(int x, int y);

  ///////////////// Event Handler ////////////////////
  void OnPaint(wxPaintEvent &event);
  void OnMouseWheel(wxMouseEvent &event);
  void OnMouseLeftDown(wxMouseEvent &event);
  void OnMouseMotion(wxMouseEvent &event);

private:
  // Draw image to screen:
  void Render(wxPaintDC &dc);
  bool CaculateDispSize(int *w, int *h);

private:
  wxImage image; 		// Image to display
  int scale; 			// scale to display
  wxPoint mousePos; 	// Mouse position
  wxPoint scrollPos; 	// Scrollbar position
  float prevXPosScale;
  float prevYPosScale;
  wxPoint prevMPos;
  //////////// Scale Paramenter //////////////
  int scaleBase;
  int scaleMax;
  int scaleMin;
  int scaleDelta;
};

#endif //_IMAGECANVAS_H_
