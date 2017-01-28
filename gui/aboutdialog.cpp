#include "aboutdialog.h"

const static wxString about=wxT("<p>OpenCV和wxWidgets整合性测试程序，欢迎测试。</p>");

AboutDialog::AboutDialog(wxWindow *parent, wxWindowID id)
    :AboutDialogBase(parent, id)
{
    about_html->SetPage(about);
}

void AboutDialog::OnOkButton(wxCommandEvent &event)
{
   Destroy();
}
