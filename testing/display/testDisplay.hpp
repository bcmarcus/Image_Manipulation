#ifndef TESTDISPLAY_HPP
#define TESTDISPLAY_HPP

#include "ImageWidget.hpp"

#include "wx/wxprec.h"
#include "wx/wx.h"
#include <wx/gdicmn.h>
#include <wx/evtloop.h>

#define USINGEIGEN 1
#define AILEVEL 0 //0 is MNIST, 1 is ANIMAL, 2 is CLIP
#define WINDOW_ID (wxID_HIGHEST + 1)
#define IMAGE_ID (wxID_HIGHEST + 2)
#define B1_ID (wxID_HIGHEST + 3)
#define B2_ID (wxID_HIGHEST + 4)
#define B3_ID (wxID_HIGHEST + 5)
#define B4_ID (wxID_HIGHEST + 6)
#define B5_ID (wxID_HIGHEST + 7)
#define NUM_BUTTONS 5
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 720
#define BUTTON_WIDTH (WINDOW_WIDTH / NUM_BUTTONS)
#define BUTTON_HEIGHT (WINDOW_HEIGHT / 8)

class testDisplay: public wxApp { 
		public:
			virtual bool OnInit();
	};
	
class MainFrame: public wxFrame {
// It contains the window and all objects in it
	public:
		ImageWidget* imageBitmap;
		
		MainFrame( const wxString &title, const wxPoint &pos, const wxSize &size );
		
		void initialImage(wxCommandEvent& event);\
		void clearPoints(wxCommandEvent& event);
		void projectiveDistortion(wxCommandEvent& event);
		void edgeDetection(wxCommandEvent& event);
		void objectDetection(wxCommandEvent& event);

		wxButton** makeButtons();

		DECLARE_EVENT_TABLE()
};

#endif