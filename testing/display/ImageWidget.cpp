#include "ImageWidget.hpp"
#include "testDisplay.hpp"
#include <Magick++.h> 

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>
#include <wx/colour.h>
#include <coreutils/functions/cli/accessCli.hpp>

using namespace coreutils::functions;
using namespace Eigen;
using namespace Magick;

ImageWidget::ImageWidget(wxBitmap* bitmap, wxWindow* parent, int id, const wxPoint &pos, const wxSize &size, wxSize scale, std::string inputImagePath)
	: wxStaticBitmap(parent, id, *bitmap, pos, size)
{
	this->projectiveIsActive = false;
	this->initialImage = bitmap;
	this->clickedPoints = new wxPoint[4];
   this->counter = 0;
	this->scale = scale;
	this->inputImagePath = inputImagePath;
}

BEGIN_EVENT_TABLE ( ImageWidget, wxStaticBitmap )
	EVT_LEFT_DOWN ( ImageWidget::clickedPoint )
END_EVENT_TABLE() // The button is pressed

void ImageWidget::clickedPoint( wxMouseEvent& event ) {
	std::cout << "clickedPoint\n";
	if (counter == 4) {
		delete this->clickedPoints;
		this->clickedPoints = new wxPoint[4];
		counter = 0;
	} else {
		this->clickedPoints[counter] = event.GetPosition();
		this->clickedPoints[counter].x = this->clickedPoints[counter].x * this->scale.GetWidth() / this->initialImage->GetSize().GetWidth();
		this->clickedPoints[counter].y = this->clickedPoints[counter].y * this->scale.GetHeight() / this->initialImage->GetSize().GetHeight();
		std::cout << "x: " << this->clickedPoints[counter].x << '\n';
		std::cout << "y: " << this->clickedPoints[counter].y << '\n';
		counter++;
	}
}

void ImageWidget::projectiveDistortion () {
	if (this->projectiveIsActive) {
		this->SetBitmap(*this->initialImage);
		this->projectiveIsActive = false;
	}
	else if (counter != 4) {
		std::cout << "Invalid number of points chosen.\n";
	}
	else {
		
		// calculate the distortion
		MatrixXd transformed(4,3);
		transformed << 
		1, 1, 1, 
		1, 100, 1,
		100, 100, 1,
		100, 1, 1;

		MatrixXd A(8,9);

		std::string execute = "'convert' '-virtual-pixel' 'black' '-mattecolor' 'black' \'" + this->inputImagePath + "\' '+distort' 'Perspective' '";

		for (int i = 0; i < 4; i++) {
			MatrixXd pair(2,9);
			MatrixXd currentA((i + 1) * 2,9);
			MatrixXd temp((i + 1) * 2,9);
			int x = this->clickedPoints[i].x;
			int y = this->clickedPoints[i].y;
			int z = 1;
			int sx = transformed(i, 0);
			int sy = transformed(i, 1);

			A.block<2,9>(i * 2, 0) << 
			x, y, z, 0, 0, 0, -x * sx, -y * sx, -z * sx,
			0, 0, 0, x ,y, z, -x * sy, -y * sy, -z * sy;
			execute += std::to_string(x) + ",";
			execute += std::to_string(y) + " ";
			execute += std::to_string(sx) + ",";
			execute += std::to_string(sy) + "  ";
		}
		execute += "' 'perspectiveDistortion.png'";

		std::cout << A << "\n\n";
		FullPivLU<MatrixXd> lu(A);
		MatrixXd x = lu.kernel();
		std::cout << x << '\n';
		MatrixXd H = x.reshaped(3, 3);
		std::cout << H << '\n';
		
		std::cout << execute << '\n';
		cli::exec(execute.c_str());


		// exit(0);
		// Image image(filepath);
		// image.distort(MagickCore::DistortMethod::AffineProjectionDistortion, 16, "0, 0", true);
		// image.ToByteArray(CommonFormat);

		// make the new image
		wxImage* img = new wxImage("perspectiveDistortion.png", wxBITMAP_TYPE_PNG);
		int imageHeight = WINDOW_HEIGHT - BUTTON_HEIGHT;
		int imageWidth = WINDOW_WIDTH;
		// wxSize scale = img->GetSize();
		// img->Rescale (imageWidth, imageHeight);
		this->projectiveDistortionImage = new wxBitmap (*img);
		this->SetBitmap(*this->projectiveDistortionImage);
		this->projectiveIsActive = true;
	}
}