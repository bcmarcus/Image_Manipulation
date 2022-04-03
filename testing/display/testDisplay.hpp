#ifndef TESTDISPLAY_HPP
#define TESTDISPLAY_HPP

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
	
		MainFrame( const wxString &title, const wxPoint &pos, const wxSize &size );

		void projectiveDistortion(wxCommandEvent& event);
		void edgeDetection(wxCommandEvent& event);
		void objectDetection(wxCommandEvent& event);

		wxButton** makeButtons();

		DECLARE_EVENT_TABLE()
};

#endif