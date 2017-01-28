// File   : guievent.h
// Author : Silei
// Descr  : Event  of component communication

#include <wx/event.h>

#ifndef GUIEVENT_H
#define GUIEVENT_H

wxDECLARE_EVENT(progrEVT_START, wxCommandEvent);
wxDECLARE_EVENT(progrEVT_UPDATE, wxCommandEvent);
wxDECLARE_EVENT(progrEVT_COMPLETE, wxCommandEvent);

wxDECLARE_EVENT(infoEVT_UPDATE, wxCommandEvent);


#endif //GUIEVENT_H
