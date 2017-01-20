// File   : gallery.h
// Author : Silei
// Descr  : Provide Image preview gallery

#ifndef _GALLERY_H_
#define _GALLERY_H_

#include <wx/vlbox.h>
#include <wx/event.h>
#include <wx/thread.h>
#include "transqueue.h"

wxDECLARE_EVENT(pxEVT_IMAGE_LOADED, wxThreadEvent);
wxDECLARE_EVENT(pxEVT_PROGRESS_START, wxThreadEvent);
wxDECLARE_EVENT(pxEVT_PROGRESS_UPDATE, wxThreadEvent);
wxDECLARE_EVENT(pxEVT_PROGRESS_COMPLETE, wxThreadEvent);

class Gallery : public wxVListBox , public wxThreadHelper {

    typedef TransQueue<wxImage> ImageQueue;
    typedef TransQueue<wxString> StringQueue;

    enum _CONST {
        DEF_BMP_WIDTH = 200,
        DEF_BMP_HEIGHT = 120,
        DEF_FILL_RED = 30,
        DEF_FILL_GREEN = 30,
        DEF_FILL_BLUE = 30,
    };

	public:
		Gallery(wxWindow *parent, wxWindowID id = wxID_ANY,
				const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
                long style = 0, const wxString &name = wxVListBoxNameStr);
		~Gallery();

		void OnDrawItem(wxDC &dc, const wxRect &rect, size_t n) const;
		wxCoord OnMeasureItem(size_t n) const;
        void OnImageLoaded(wxThreadEvent &event);
        void OnProgressStart(wxThreadEvent &event);
        void OnProgressUpdate(wxThreadEvent &event);
        void OnProgressComplete(wxThreadEvent &event);
        void OnClose(wxWindowDestroyEvent &event);

        void StartLoad(const wxString &path);
        void StopLoad();

        const wxString& GetSelectImagePath();

    protected:
        virtual wxThread::ExitCode Entry();
        wxSize GetFitSize(const wxSize& size);
        void SendProgressStatus(wxEventType type, size_t n);

    private:
        wxString dir_path;
        wxCriticalSection dir_path_cs;

        ImageQueue image_queue;
        StringQueue path_queue;

        wxVector<wxBitmap> previews; //image preview container
        wxArrayString image_pathes; //those pathes coressponding to images
        wxSize bitmap_size;
};

#endif //_GALLERY_H_

