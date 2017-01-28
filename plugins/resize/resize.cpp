
#include <wx/choice.h>
#include "resize.h"

const wxImageResizeQuality ResizeGui::quality[] = {wxIMAGE_QUALITY_NEAREST,
                                                  wxIMAGE_QUALITY_BILINEAR,
                                                  wxIMAGE_QUALITY_BICUBIC};

void ResizeGui::OnWidthSpinChanged(wxSpinEvent &event)
{
    if(lockratio_check->IsChecked()){
        int w = width_spin->GetValue();
        int h = wxDouble(w)/ratio;
        height_spin->SetValue(h);
    }
}

void ResizeGui::OnHeightSpinChanged(wxSpinEvent &event)
{
    if(lockratio_check->IsChecked()){
        int h = height_spin->GetValue();
        int w = wxDouble(h)*ratio;
        width_spin->SetValue(w);
    }
}

void ResizeGui::OnApply(wxCommandEvent &event)
{
    wxImage image = GetImage();
    int w = width_spin->GetValue();
    int h = height_spin->GetValue();
    int choice = alg_choice->GetSelection();
    wxImageResizeQuality q = quality[choice];
    image.Rescale(w,h,q);
    wxString cap = wxString::Format("%s-[%dx%d]", GetCurrentPageText(), w, h);
    AddImage(image, cap);
}

void ResizeGui::UpdateSizeValue()
{
    wxImage image = GetImage();
    if(!image.IsOk())
        return;

    int w = image.GetWidth();
    int h = image.GetHeight();

    ratio = wxDouble(w)/wxDouble(h);

    width_spin->SetValue(w);
    height_spin->SetValue(h);
}
