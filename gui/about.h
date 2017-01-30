
#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "gui.h"

class AboutDialog : public AboutDialogBase {
public:
    AboutDialog(wxWindow *parent, wxWindowID id = wxID_ANY);
    ~AboutDialog(){

    }

    void OnOkButton(wxCommandEvent &event);
};

class AboutPanel : public AboutPanelBase {
public:
    AboutPanel(wxWindow *parent, wxWindowID id = wxID_ANY);
    ~AboutPanel() { }

    void OnMore(wxCommandEvent &event);
};

#endif //ABOUTDIALOG_H
