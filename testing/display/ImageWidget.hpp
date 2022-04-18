#ifndef IMAGEWIDGET_HPP
#define IMAGEWIDGET_HPP

#include <Eigen/Dense>
#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>

class ImageWidget: public wxStaticBitmap {
// It contains the window and all objects in it
	public:
		wxPoint* clickedPoints;
		wxSize scale;
		wxBitmap* initialImage;
		wxBitmap* projectiveDistortionImage;
		wxBitmap* edgeDetectionImage;
		std::string inputImagePath;
		bool projectiveIsActive;

		int counter;

		ImageWidget(wxBitmap* bitmap, wxWindow* parent, int id, const wxPoint &pos, const wxSize &size, wxSize scale, std::string inputImagePath);

		void clickedPoint(wxMouseEvent& event);
		void projectiveDistortion();

		DECLARE_EVENT_TABLE();
};

#endif