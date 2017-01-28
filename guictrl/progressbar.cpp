// File		: progressbar.cpp
// Author	: Silei
// Descr	: Provide progress indicator

#include "progressbar.h"
#include "guievent.h"

const wxDouble ProgressBar::default_value       = 0.0;
const wxString ProgressBar::default_format      = _ ( "%.1f%%" );

ProgressBar::ProgressBar ( wxWindow *parent, wxWindowID id, const wxPoint &pos,
                           const wxSize &size, long style,
                           const wxValidator &validator, const wxString &name )
    :wxControl ( parent, id, pos, size, style, validator, name ),
    value ( ProgressBar::default_value ),
    progress_num(0),
    max_num(DEF_MAX_NUM),
    front_pen ( wxPen ( wxColour ( 10, 10, 10 ), 2 ) ),
    back_pen ( wxPen ( wxColour ( 0, 10, 10 ), 1 ) ),
    front_brush ( wxBrush ( wxColour ( 120, 120, 120 ), wxBRUSHSTYLE_BDIAGONAL_HATCH ) ),
    back_brush ( wxBrush ( wxColour ( 50, 50, 50 ) ) ),
    format ( default_format ),
    font_colour ( wxColour ( 230, 230, 230 ) ),
    back_colour ( wxColour ( 30, 30, 30 ) ),
    font ( wxFont ( FONT_SIZE, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) ) {

    SetBackgroundColour ( back_colour );

    Bind ( wxEVT_PAINT, &ProgressBar::OnPaint, this );

    //This make progress bar update by event-driving
    Bind (progrEVT_START, &ProgressBar::OnStart, this);
    Bind (progrEVT_UPDATE, &ProgressBar::OnUpdate, this);
    Bind (progrEVT_COMPLETE, &ProgressBar::OnComplete, this);
}

ProgressBar::~ProgressBar() {}

void ProgressBar::SetValue ( wxDouble val ) {
    if ( 0.0 < val && val <= 1.0 )
        value = val;
    else if ( val > 1.0 )
        value = 1.0;
    else
        value = 0.0;
    this->Refresh();
}

wxSize ProgressBar::DoGetBestSize() const  {
    return wxSize ( DEF_WIDTH, DEF_HEIGHT );
}

void ProgressBar::OnPaint ( wxPaintEvent &event ) {
    wxPaintDC dc ( this );
    PrepareDC ( dc );

    // Get paint area size:
    int w, h;
    GetVirtualSize ( &w, &h );
    w -= HT_MARGIN * 2;
    h -= VT_MARGIN * 2;

    // Draw back rectangle:
    dc.SetPen ( back_pen );
    dc.SetBrush ( back_brush );
    dc.DrawRectangle ( HT_MARGIN, VT_MARGIN, w, h );

    // Draw front rectangle:
    dc.SetPen ( front_pen );
    dc.SetBrush ( front_brush );
    int pw = w * value;
    dc.DrawRectangle ( HT_MARGIN, VT_MARGIN, pw, h );

    // Draw Percentage:
    wxString ps;
    ps.Printf ( format, value * 100 );
    dc.SetFont ( font );
    dc.SetTextForeground ( font_colour );
    dc.DrawText ( ps, w / 2 - FONT_SIZE, ( h - FONT_SIZE ) / 2 );
}

void ProgressBar::OnStart(wxCommandEvent &event) {
    SetValue(0.0);
    progress_num = 0;
    max_num = event.GetExtraLong();
    Refresh();
}

void ProgressBar::OnUpdate(wxCommandEvent &event) {
    progress_num++;
    progress_num = (progress_num <= max_num) ? progress_num : max_num;
    if(max_num)
        SetValue(wxDouble(progress_num)/wxDouble(max_num));
    else
        SetValue(1.0);
    Refresh();
}

void ProgressBar::OnComplete(wxCommandEvent &event) {
    SetValue(1.0);
    Refresh();
}
