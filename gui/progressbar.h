// File		: progressbar.h
// Author	: Silei
// Descr	: Provide progress indicator


#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "wx_pch.h"

class ProgressBar : public wxControl {
	
private:
 	enum _CONST {
		DEF_WIDTH = 100,
		DEF_HEIGHT = 30,
		HT_MARGIN = 2,
		VT_MARGIN = 2,
		FONT_SIZE = 10,
	};
	const static wxDouble default_value;
	const static wxString default_format;

public:
    ProgressBar(wxWindow *parent, wxWindowID id = wxID_ANY,
                const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize,
                long style = wxFULL_REPAINT_ON_RESIZE | wxBORDER_NONE,
                const wxValidator &validator = wxDefaultValidator,
                const wxString &name = wxControlNameStr);

	~ProgressBar();

	wxSize DoGetBestSize() const;
	void OnPaint(wxPaintEvent &event);

	// Drawing style:
	inline void SetFrontPen(const wxPen &pen) { front_pen = pen; }

	inline void SetFrontBrush(const wxBrush &brush) { front_brush = brush; }

	inline void SetBackPen(const wxPen &pen) { back_pen = pen; }

	inline void SetBackBrush(const wxBrush &brush) { back_brush = brush; }

	inline void SetFormat(const wxString &format) { this->format = format; }

	inline void SetFontColour(const wxColour &colour) { font_colour = colour; }

	inline void SetBackColour(const wxColour &colour) { back_colour = colour; }

	inline void SetPercentFont(const wxFont &font) { this->font = font; }

	void SetValue(wxDouble val);

private:
	wxDouble value;
	wxPen front_pen;
	wxPen back_pen;
	wxBrush front_brush;
	wxBrush back_brush;
	wxString format;
	wxColour font_colour;
	wxColour back_colour;
	wxFont font;
};

#endif // PROGRESSBAR_H
