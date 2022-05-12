#include "ImageWidget.hpp"
#include "testDisplay.hpp"
#include <Magick++.h> 

#include <fstream>

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
	this->edgeDetectionIsActive = false;
	this->initialImage = bitmap;
	this->clickedPoints = new wxPoint[4];
	this->counter = 0;
	this->scale = scale;
	this->inputImagePath = inputImagePath;
	this->currentImagePath = inputImagePath;
}

BEGIN_EVENT_TABLE ( ImageWidget, wxStaticBitmap )
	EVT_LEFT_DOWN ( ImageWidget::clickedPoint )
END_EVENT_TABLE() // The button is pressed

void ImageWidget::clickedPoint( wxMouseEvent& event ) {
	std::cout << "clickedPoint\n";
	if (counter == 4) {
		this->clearPoints();
	} 
	this->clickedPoints[counter] = event.GetPosition();
	this->clickedPoints[counter].x = this->clickedPoints[counter].x * this->scale.GetWidth() / this->initialImage->GetSize().GetWidth();
	this->clickedPoints[counter].y = this->clickedPoints[counter].y * this->scale.GetHeight() / this->initialImage->GetSize().GetHeight();
	std::cout << "x: " << this->clickedPoints[counter].x << '\n';
	std::cout << "y: " << this->clickedPoints[counter].y << '\n';
	counter++;
}

void ImageWidget::displayInitialImage() {
	this->SetBitmap(*this->initialImage);
	this->currentImagePath = this->inputImagePath;
}

void ImageWidget::clearPoints() {
	delete this->clickedPoints;
	this->clickedPoints = new wxPoint[4];
	counter = 0;
}

void ImageWidget::projectiveDistortion () {
	if (counter != 4) {
		std::cout << "Invalid number of points chosen.\n";
	}
	else {
		int size = 0;
		for (int i = 0; i < 4; i++) {
			int linXDist = this->clickedPoints[i].x - this->clickedPoints[(i + 1) % 4].x;
			int linYDist = this->clickedPoints[i].y - this->clickedPoints[(i + 1) % 4].y;
			double totalDist = sqrt(linXDist * linXDist + linYDist * linYDist);
			size += totalDist;
		}
		size /= 5;
		std::cout << size;
		// exit(0);
		MatrixXd transformed(4,3);
		transformed << 
		1, 1, 1, 
		1, size, 1,
		size, size, 1,
		size, 1, 1;

		MatrixXd A(8,9);

		std::string execute1 = "'convert' '-virtual-pixel' 'black' '-mattecolor' 'black' \'" + this->currentImagePath + "\' '+distort' 'Perspective' '";
		std::string execute2 = "'convert' '-virtual-pixel' 'black' '-mattecolor' 'black' \'" + this->currentImagePath + "\' '+distort' 'PerspectiveProjection' ";
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
			execute1 += std::to_string(x) + ",";
			execute1 += std::to_string(y) + " ";
			execute1 += std::to_string(sx) + ",";
			execute1 += std::to_string(sy) + "  ";
		}
		execute1 += "' 'perspectiveDistortion.png'";

		FullPivLU<MatrixXd> lu(A);
		MatrixXd x = lu.kernel();
		MatrixXd H = x.reshaped(3, 3);
		H *= (1 / H(2, 2));

		execute2 += "'" + 
		std::to_string(H(0, 0)) + ", " + std::to_string(H(1, 0)) + ", " + std::to_string(H(2, 0)) + ", " + 
		std::to_string(H(0, 1)) + ", " + std::to_string(H(1, 1)) + ", " + std::to_string(H(2, 1)) + ", " + 
		std::to_string(H(0, 2)) + ", " + std::to_string(H(1, 2)) + "'";
		execute2 += " 'perspectiveDistortion.png'";

		if (USINGEIGEN) {
			std::cout << execute2 << '\n';
			cli::exec(execute2.c_str());
		} else {
			std::cout << execute1 << '\n';
			cli::exec(execute1.c_str());
		}

		// make the new image
		wxImage* img = new wxImage("perspectiveDistortion.png", wxBITMAP_TYPE_PNG);
		// int imageHeight = WINDOW_HEIGHT - BUTTON_HEIGHT;
		// int imageWidth = WINDOW_WIDTH;
		// wxSize scale = img->GetSize();
		// img->Rescale (imageWidth, imageHeight);
		this->projectiveDistortionImage = new wxBitmap (*img);
		this->SetBitmap(*this->projectiveDistortionImage);
		this->currentImagePath = "perspectiveDistortion.png";
	}
}

void ImageWidget::edgeDetection() {
	std::string execute1 = "convert " + this->currentImagePath + " -canny 0x1+10%+30% edgeDetectImage.png";
	cli::exec(execute1.c_str());

	wxImage* img = new wxImage("edgeDetectImage.png", wxBITMAP_TYPE_PNG);

	this->edgeDetectionImage = new wxBitmap (*img);
	this->SetBitmap(*this->edgeDetectionImage);
	this->currentImagePath = "edgeDetectImage.png";
}

void ImageWidget::gaussianBlur() {
	std::string execute1 = "convert " + this->currentImagePath + " -blur 0x8 -channel RGB gaussianBlurImage.png";
	// std::cout << execute1.c_str() << "\n\n";
	cli::exec(execute1.c_str());

	wxImage* img = new wxImage("gaussianBlurImage.png", wxBITMAP_TYPE_PNG);

	this->gaussianBlurImage = new wxBitmap (*img);
	this->SetBitmap(*this->gaussianBlurImage);
	this->currentImagePath = "gaussianBlurImage.png";
}

void ImageWidget::objectDetection() {
	// AI Model stuff
	std::string execute1 = "'convert' \'" + this->currentImagePath + "\' -resize 224x224\! imageScaled224.png";
	// std::cout << execute1.c_str() << '\n';
	cli::exec(execute1.c_str());

	std::string execute2 = "python3 CLIP.py imageScaled224.png";
	std::string out = cli::exec(execute2.c_str());
	std::cout << out << '\n';
}