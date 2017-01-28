
#include <wx/aui/auibook.h>
#include <imagecanvas.h>
#include "plugin.h"

wxDEFINE_EVENT(plugEVT_PAGE_CHANGED, wxCommandEvent);

Plugin::Plugin(wxAuiNotebook *book, PluginCategroy cate, const wxString &plug_name)
    :image_book(book), categroy(cate), name(plug_name)
{

}

wxImage &Plugin::GetImage() const
{
    if(!image_book)
        return wxNullImage;

    ImageCanvas *canvas = dynamic_cast<ImageCanvas*>(image_book->GetCurrentPage());
    if(canvas)
        return canvas->GetImage();
    else
        return wxNullImage;
    }

void Plugin::SetImage(const wxImage &image)
{
    if(!image_book)
        return;

    ImageCanvas *canvas = dynamic_cast<ImageCanvas*>(image_book->GetCurrentPage());
    if(!canvas)
        return;
    if(!image.IsOk())
        return;

    canvas->SetImage(image);
}

void Plugin::AddImage(const wxImage &image, const wxString &cap)
{
    if(!image_book)
        return;

    if(!image.IsOk())
        return;

    ImageCanvas *canvas = new ImageCanvas(image_book);
    image_book->AddPage(canvas, cap, true);
    canvas->SetImage(image);
    canvas->FitSize();
}

wxString Plugin::GetCurrentPageText()
{
    if(!image_book | !image_book->GetPageCount())
        return wxEmptyString;

    return image_book->GetPageText(image_book->GetSelection());
}
