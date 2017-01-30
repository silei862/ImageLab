#include "about.h"

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

AboutPanel::AboutPanel(wxWindow *parent, wxWindowID id)
    :AboutPanelBase(parent, id)
{

}

void AboutPanel::OnMore(wxCommandEvent &event)
{
    AboutDialog *dlg= new AboutDialog(nullptr);
    dlg->Show();
}
