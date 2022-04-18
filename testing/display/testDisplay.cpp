#include <Magick++.h> 
#include <stdlib.h>

#include "wx/wxprec.h"
#include "wx/wx.h"
#include <wx/gdicmn.h>
#include <wx/evtloop.h>

#include <filesystem>

#include "testDisplay.hpp"
#include "ImageWidget.hpp"

#include <coreutils/functions/cli/accessCli.hpp>
#include <Image_Manipulation/util/imageUtil.hpp>
#include <Eigen/Dense>
 
using Eigen::MatrixXd;
using namespace std;
using namespace coreutils::functions;

IMPLEMENT_APP(testDisplay) // Initializes the MainApp class and tells our program
  // to run it
bool testDisplay::OnInit()
{
	wxInitAllImageHandlers();
	// Create an instance of our frame, or window(wxFrame*)NULL, WINDOW_ID, wxT("MainFrame"), wxPoint(-1,-1),  wxSize(670,698)
	MainFrame *mainFrame = new MainFrame(wxT("MainFrame"), wxPoint(-1,-1), wxSize(WINDOW_WIDTH,WINDOW_HEIGHT));
	mainFrame->Show(TRUE); // show the window
	SetTopWindow(mainFrame); // and finally, set it as the main window

	return TRUE;
} 

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
	EVT_BUTTON ( B1_ID, MainFrame::projectiveDistortion )
	EVT_BUTTON ( B2_ID, MainFrame::edgeDetection )
	EVT_BUTTON ( B3_ID, MainFrame::objectDetection )
END_EVENT_TABLE() // The button is pressed

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size): wxFrame((wxFrame*)NULL,  - 1, title, pos, size){
	
	// this->SetMinClientSize (size);
   // this->SetMaxClientSize (size);

	// string inputImagePath = imageEdit::util::imageFromFileHandler();
	string inputImagePath = "/home/aralyth/Downloads/tiles.png";
	wxImage* img = new wxImage(inputImagePath, wxBITMAP_TYPE_PNG);
	int imageHeight = WINDOW_HEIGHT - BUTTON_HEIGHT;
	int imageWidth = WINDOW_WIDTH;
	wxSize scale = img->GetSize();
	img->Rescale (imageWidth, imageHeight);
	wxBitmap* bitmap = new wxBitmap (*img);
	this->imageBitmap = new ImageWidget(bitmap, this, wxID_ANY, *(new wxPoint (0, BUTTON_HEIGHT)), *(new wxSize (imageWidth, imageHeight)), scale, inputImagePath);
	makeButtons();
}

void MainFrame::projectiveDistortion( wxCommandEvent& event ) {
	// wxPoint 	GetLogicalPosition (const wxDC &dc) const
	

	std::cout << "projectiveDistortion\n";
	this->imageBitmap->projectiveDistortion();
}

void MainFrame::edgeDetection( wxCommandEvent& event ) {
	std::cout << "edgeDetection\n";
	// Close(TRUE); // Tells the OS to quit running this process
}

void MainFrame::objectDetection( wxCommandEvent& event ) {
	std::cout << "objectDetection\n";
	// Close(TRUE); // Tells the OS to quit running this process
}

wxButton** MainFrame::makeButtons() {
	wxButton** buttonList = new wxButton*[3];
	wxButton* B1 = new wxButton(this, B1_ID, _T("Projective\nDistortion"), *(new wxPoint (BUTTON_WIDTH * 0, 0)), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT), 0);
	wxButton* B2 = new wxButton(this, B2_ID, _T("Edge\nDetection"), *(new wxPoint (BUTTON_WIDTH * 1, 0)), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT), 0);
	wxButton* B3 = new wxButton(this, B3_ID, _T("Object\nDetection"), *(new wxPoint (BUTTON_WIDTH * 2, 0)), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT), 0);

	buttonList[0] = B1;
	buttonList[1] = B2;
	buttonList[2] = B3;
	return buttonList;
}


