#ifndef TESTDISPLAY_HPP
#define TESTDISPLAY_HPP

#include "ImageWidget.hpp"

#include "wx/wxprec.h"
#include "wx/wx.h"
#include <wx/gdicmn.h>
#include <wx/evtloop.h>

#define GUI 1
#define WINDOW_ID (wxID_HIGHEST + 1)
#define IMAGE_ID (wxID_HIGHEST + 2)
#define B1_ID (wxID_HIGHEST + 3)
#define B2_ID (wxID_HIGHEST + 4)
#define B3_ID (wxID_HIGHEST + 5)
#define NUM_BUTTONS 3
#define WINDOW_WIDTH 670
#define WINDOW_HEIGHT 698
#define BUTTON_WIDTH (WINDOW_WIDTH / NUM_BUTTONS)
#define BUTTON_HEIGHT (WINDOW_HEIGHT / 8)

// class testDisplay : public wxApp {
//    public:
//       void onClick ();
// 		wxButton** makeButtons(wxFrame* mainFrame);
// };
// DECLARE_APP(testDisplay)

class testDisplay: public wxApp { 
		public:
			virtual bool OnInit();
	};
	
class MainFrame: public wxFrame {
// It contains the window and all objects in it
	public:
		ImageWidget* imageBitmap;
		
		MainFrame( const wxString &title, const wxPoint &pos, const wxSize &size );

		void projectiveDistortion(wxCommandEvent& event);
		void edgeDetection(wxCommandEvent& event);
		void objectDetection(wxCommandEvent& event);
		void clickedPoint(wxMouseEvent& event);

		wxButton** makeButtons();

		DECLARE_EVENT_TABLE()
};

#endif