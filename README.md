# Image Processing Suite

The Image Processing Suite is an interactive application designed to manipulate and distort images in order to test the resiliency of state-of-the-art object detection algorithms. The project was initially prototyped in Matlab, then implemented in C++ for the user interface and image alterations, and Python was used for the object detection.

## Description

The Image Processing Suite is a comprehensive tool for testing the robustness of object detection algorithms against various image manipulations. The suite allows users to apply a variety of distortions to images, including blurring, rotating, and altering the perspective, and then tests how well object detection algorithms can still identify objects in the manipulated images. The results of our tests have shown that these algorithms are extremely resilient to these types of distortions.

## Features

- **Interactive User Interface**: Built in C++, the UI allows users to easily select and manipulate images.
- **Image Alterations**: The suite includes a variety of image manipulation tools, including blurring, rotating, and perspective alteration.
- **Object Detection**: Implemented in Python, the object detection component tests how well state-of-the-art algorithms can identify objects in manipulated images.

## Installation

### Required libraries
#### wxWidgets

```
apt-key adv --fetch-keys https://repos.codelite.org/CodeLite.asc

sudo apt-add-repository 'deb https://repos.codelite.org/wx3.1.5/ubuntu/ focal universe'

sudo apt-get update
sudo apt-get install libwxbase3.1-0-unofficial
sudo apt-get install libwxbase3.1unofficial-dev
sudo apt-get install libwxgtk3.1-0-unofficial
sudo apt-get install libwxgtk3.1unofficial-dev
sudo apt-get install wx3.1-headers
sudo apt-get install wx-common
sudo apt-get install libwxgtk-webview3.1-0-unofficial

sudo apt-get install libwxbase3.1-0-unofficial-dbg  
sudo apt-get install libwxgtk3.1-0-unofficial-dbg 
sudo apt-get install libwxgtk-webview3.1-0-unofficial-dbg
sudo apt-get install libwxgtk-media3.1-0-unofficial-dbg 

sudo apt install zlib1g
sudo apt install zlib1g-dev
```

#### ImageMagick

```
git clone https://github.com/ImageMagick/ImageMagick.git ImageMagick-7.1.0
cd ImageMagick-7.1.0
sudo apt-get install -y libtiff-dev
sudo apt-get install -y libjpeg62-dev 
sudo apt-get install -y libpng-dev
./configure
make

#If build fails, try gmake instead.

sudo make install
sudo ldconfig /usr/local/lib
make check
```

## Usage

To use the Image Processing Suite, you first need to launch the application. Here's a basic example of how to use the suite:

1. Launch the application.
2. Select an image to manipulate.
3. Choose the type of distortion to apply (blur, rotate, alter perspective).
4. Apply the distortion.
5. Run the object detection algorithm on the manipulated image.
6. Review the results to see how well the algorithm was able to identify objects in the manipulated image.