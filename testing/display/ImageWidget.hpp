#ifndef IMAGEWIDGET_HPP
#define IMAGEWIDGET_HPP

#include <Eigen/Dense>
#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>
#include <Image_Manipulation/util/objectDetection.cuh>

class ImageWidget: public wxStaticBitmap {
// It contains the window and all objects in it
	public:
		wxPoint* clickedPoints;
		wxSize scale;
		std::string currentImagePath;
		std::string inputImagePath;
		wxBitmap* initialImage;
		wxBitmap* projectiveDistortionImage;
		wxBitmap* edgeDetectionImage;
		wxBitmap* gaussianBlurImage;
		bool projectiveIsActive;
		bool edgeDetectionIsActive;

		int counter;

		ImageWidget(wxBitmap* bitmap, wxWindow* parent, int id, const wxPoint &pos, const wxSize &size, wxSize scale, std::string inputImagePath);

		void clickedPoint(wxMouseEvent& event);
		void displayInitialImage();
		void clearPoints();
		void projectiveDistortion();
		void edgeDetection();
		void gaussianBlur();
		void objectDetection();

		DECLARE_EVENT_TABLE();
};

#endif