#include "DrawingFunctions.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include <time.h>
typedef cv::Mat WindowDraw;
namespace Canvas {
	void Canvas::Draw::CreateWindowe(std::string name, int x, int y, int width, int height, COLOR_SCALE scale, WindowDraw canvas)
	{
		cv::namedWindow(name, cv::WINDOW_FREERATIO);
		cv::moveWindow(name, x, y);
		for (int x = 0; x < canvas.rows; x++) {
			for (int y = 0; y < canvas.cols; y++) {
				canvas.at<cv::Vec3b>(x, y)[0] = 255;
				canvas.at<cv::Vec3b>(x, y)[1] = 255;
				canvas.at<cv::Vec3b>(x, y)[2] = 255;
			}
		}
		Width = width;
		Height = height;
	}
	void Canvas::Draw::SetBackgroundColor(int red, int green, int blue, std::string windowName, WindowDraw canvas)
	{
		canvas = cv::Scalar(blue, green, red);
	}
	int Draw::GetWindowWidth(std::string name)
	{
		return Width;
	}
	int Draw::GetWindowHeight(std::string name)
	{
		return Height;
	}
	void Canvas::Draw::SetBackgroundColor(RGBcolor color, std::string windowName, WindowDraw canvas)
	{
		canvas = cv::Scalar(color.blue, color.green, color.red);
	}
	void Canvas::Draw::drawPixel(int x, int y, RGBcolor color, std::string windowName, WindowDraw canvas)
	{
		canvas.at<cv::Vec3b>(y, x)[2] = color.red;
		canvas.at<cv::Vec3b>(y, x)[1] = color.green;
		canvas.at<cv::Vec3b>(y, x)[0] = color.blue;
	}
	void Canvas::Draw::drawPixel(int x, int y, int red, int green, int blue, std::string windowName, WindowDraw canvas)
	{
		canvas.at<cv::Vec3b>(y, x)[2] = red;
		canvas.at<cv::Vec3b>(y, x)[1] = green;
		canvas.at<cv::Vec3b>(y, x)[0] = blue;
	}
	void Canvas::Draw::drawLine(int x1, int y1, int x2, int y2, RGBcolor color, std::string windowName, WindowDraw canvas)
	{
		int thickness = 1;
		int lineType = 8;
		line(canvas, cv::Point(x1, y1), cv::Point(x2, y2),
			cv::Scalar(color.blue, color.green, color.red),
			thickness,
			lineType);
	}
	void Canvas::Draw::drawLine(cv::Point p1, cv::Point p2, RGBcolor color, std::string windowName, WindowDraw canvas)
	{
		int thickness = 1;
		int lineType = 8;
		line(canvas, p1, p2,
			cv::Scalar(color.blue, color.green, color.red),
			thickness,
			lineType);
	}
	void Canvas::Draw::drawLine(cv::Point p1, cv::Point p2, int red, int green, int blue, std::string windowName, WindowDraw canvas)
	{
		int thickness = 1;
		int lineType = 8;
		line(canvas, p1, p2,
			cv::Scalar(blue, green, red),
			thickness,
			lineType);
	}

	void Canvas::Draw::drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue, std::string windowName, WindowDraw canvas)
	{
		int thickness = 1;
		int lineType = 8;
		line(canvas, cv::Point(x1, y1), cv::Point(x2, y2),
			cv::Scalar(blue, green, red),
			thickness,
			lineType);
	}


	void Canvas::Draw::drawFillRect(int x, int y, int width, int height, RGBcolor color, std::string windowName, WindowDraw canvas)
	{
		int i = 0;
		for (i = 0; i < width; i++) {

			drawLine(x + i, y, x + i, y + height, color, windowName, canvas);
		}
	}
	void Canvas::Draw::drawFillRect(int x, int y, int width, int height, int red, int green, int blue, std::string windowName, WindowDraw canvas)
	{
		rectangle(canvas, cv::Point(x, y), cv::Point(x + width, y + height), cv::Scalar(red, green, blue), CV_FILLED, 8);
	}
	void Canvas::Draw::drawStrokeRect(int x, int y, int width, int height, RGBcolor color, std::string windowName, WindowDraw canvas, int borderPx)
	{
		drawLine(x, y, x + width, y, color, windowName, canvas);
		drawLine(x, y, x, y + height, color, windowName, canvas);
		drawLine(x + width, y, x + width, y + height, color, windowName, canvas);
		drawLine(x, y + height, x + width, y + height, color, windowName, canvas);

	}
	void Canvas::Draw::drawStrokeRect(int x, int y, int width, int height, int red, int green, int blue, std::string windowName, WindowDraw canvas, int borderPx)
	{
		drawLine(x, y, x + width, y, red, green, blue, windowName, canvas);
		drawLine(x, y, x, y + height, red, green, blue, windowName, canvas);
		drawLine(x + width, y, x + width, y + height, red, green, blue, windowName, canvas);
		drawLine(x, y + height, x + width, y + height, red, green, blue, windowName, canvas);

	}
	void Draw::drawText(int x, int y, std::string text, int red, int green, int blue, double scale, std::string windowName, WindowDraw canvas)
	{
		putText(canvas, text, cv::Point(x, y), 0, scale, cvScalar(red, green, blue), 0, CV_AA);
	}
	void Draw::drawPointLC(float x, float y, int windowWidth, int windowHeight, int r, int g, int b, std::string windowName, WindowDraw canvas)
	{
		Draw window;
		if (x > 0 && y > 0) {
			window.drawPixel(x*(windowWidth / 2) + (windowWidth / 2 - 1), windowHeight / 2 - y*(windowHeight / 2) + 1, r, g, b, windowName, canvas);
			std::cout << x*(windowWidth / 2) + (windowWidth / 2 - 1) << " " << windowHeight / 2 - y*(windowHeight / 2) << std::endl;
		}
		else if (x > 0 && y < 0) {
			y = -1 * y;
			std::cout << x*(windowWidth / 2) + (windowWidth / 2 - 1) << " " << windowHeight / 2 + y*(windowHeight / 2) - 1 << std::endl;
			window.drawPixel(x*(windowWidth / 2) + (windowWidth / 2 - 1), windowHeight / 2 + y*(windowHeight / 2) - 1, r, g, b, windowName, canvas);

		}
		else if (x < 0 && y>0) {
			x = -1 * x;
			window.drawPixel((1 - x) * (windowWidth / 2), windowHeight / 2 - y*(windowHeight / 2) + 1, r, g, b, windowName, canvas);
		}
		else if (x < 0 && y < 0) {
			x = -1 * x;
			y = -1 * y;
			window.drawPixel((1 - x) * (windowWidth / 2), windowHeight / 2 + y*(windowHeight / 2) - 1, r, g, b, windowName, canvas);
		}
		else if (x == 0 && y == 0) {
			window.drawPixel(windowWidth / 2, windowHeight / 2, r, g, b, windowName, canvas);
		}
		else if (x == 0 && y > 0) {
			window.drawPixel(windowWidth / 2, windowHeight / 2 - y*(windowHeight / 2) + 1, r, g, b, windowName, canvas);
		}
		else if (x == 0 && y < 0) {
			y = -1 * y;
			window.drawPixel(windowWidth / 2, windowHeight / 2 + y*(windowHeight / 2) - 1, r, g, b, windowName, canvas);
		}
		else if (x > 0 && y == 0) {
			window.drawPixel(x*(windowWidth / 2) + (windowWidth / 2 - 1), windowHeight / 2, r, g, b, windowName, canvas);
		}
		else if (x < 0 && y == 0) {
			x = -1 * x;
			window.drawPixel((1 - x)*(windowWidth / 2), windowHeight / 2, r, g, b, windowName, canvas);
		}
	}
	IplImage* Canvas::Image::cropImage(const IplImage * img, const CvRect region)
	{
		IplImage *imageCropped;
		CvSize size;

		if (img->width <= 0 || img->height <= 0 || region.width <= 0 || region.height <= 0) {
			std::cout << "ERROR in cropImage(): invalid dimensions." << std::endl;
			exit(1);
		}

		if (img->depth != IPL_DEPTH_8U) {
			std::cout << "ERROR in cropImage(): image depth is not 8." << std::endl;
			exit(1);
		}

		cvSetImageROI((IplImage*)img, region);
		size.width = region.width;
		size.height = region.height;
		imageCropped = cvCreateImage(size, IPL_DEPTH_8U, img->nChannels);
		cvCopy(img, imageCropped);

		return imageCropped;
	}

	IplImage * Canvas::Image::resizeImage(const IplImage * origImg, int newWidth, int newHeight, bool keepAspectRatio)
	{
		IplImage *outImg = 0;
		int origWidth;
		int origHeight;
		if (origImg) {
			origWidth = origImg->width;
			origHeight = origImg->height;
		}
		if (newWidth <= 0 || newHeight <= 0 || origImg == 0 || origWidth <= 0 || origHeight <= 0) {
			std::cout << "ERROR: Bad desired image size of " << newWidth << "x" << newHeight << " in resizeImage().\n";
		}

		if (keepAspectRatio) {
			CvRect r;
			float origAspect = (origWidth / (float)origHeight);
			float newAspect = (newWidth / (float)newHeight);
			if (origAspect > newAspect) {
				int tw = (origHeight * newWidth) / newHeight;
				r = cvRect((origWidth - tw) / 2, 0, tw, origHeight);
			}
			else {
				int th = (origWidth * newHeight) / newWidth;
				r = cvRect(0, (origHeight - th) / 2, origWidth, th);
			}
			IplImage *croppedImg = cropImage(origImg, r);

			outImg = resizeImage(croppedImg, newWidth, newHeight, false);
			cvReleaseImage(&croppedImg);

		}
		else {
			outImg = cvCreateImage(cvSize(newWidth, newHeight), origImg->depth, origImg->nChannels);
			if (newWidth > origImg->width && newHeight > origImg->height) {
				cvResetImageROI((IplImage*)origImg);
				cvResize(origImg, outImg, CV_INTER_LINEAR);
			}
			else {
				cvResetImageROI((IplImage*)origImg);
				cvResize(origImg, outImg, CV_INTER_AREA);
			}

		}
		return outImg;
	}
	void Canvas::Draw::drawImage(const char* path, int x, int y, int BackgroundRed, int BackgroundGreen, int BackgroundBlue, COLOR_SCALE scale, std::string windowName, WindowDraw canvas)
	{
		cv::Mat image = cv::imread(path);
		if (image.size().width + x < canvas.size().width && image.size().height + y < canvas.size().height) {
			for (int i = x; i < image.size().width + x; i++) {
				for (int j = y; j < image.size().height + y; j++) {
					if (scale == COLOR_SCALE::RGB) {
						canvas.at<cv::Vec3b>(j, i)[0] = image.at<cv::Vec3b>(j - y, i - x)[0];
						canvas.at<cv::Vec3b>(j, i)[1] = image.at<cv::Vec3b>(j - y, i - x)[1];
						canvas.at<cv::Vec3b>(j, i)[2] = image.at<cv::Vec3b>(j - y, i - x)[2];
					}
				}
			}
		}
	}
	void Canvas::Draw::drawImage(const char* path, int x, int y, int width, int height, int BackgroundRed, int BackgroundGreen, int BackgroundBlue, COLOR_SCALE scale, bool keepAspectRatio, std::string windowName, WindowDraw canvas)
	{
		IplImage *imgIn = cvLoadImage(path, CV_LOAD_IMAGE_UNCHANGED);
		IplImage *newImage;
		Image image2 = Image();
		newImage = image2.resizeImage(imgIn, width, height, keepAspectRatio);

		/*stringstream Sw, Sh;
		Sw << width;
		Sh << height;
		string New = Sw.str() + "x" + Sh.str() + "_";
		New += path;
		const char* FullName = New.c_str();*/
		cv::Mat image(cv::Size(width, height), CV_8UC3);
		image = cv::cvarrToMat(newImage);
		for (int i = x; i < width + x; i++) {
			for (int j = y; j < height + y; j++) {
				if (scale == COLOR_SCALE::RGB) {

					canvas.at<cv::Vec3b>(j, i)[0] = image.at<cv::Vec3b>(j - y, i - x)[0];
					canvas.at<cv::Vec3b>(j, i)[1] = image.at<cv::Vec3b>(j - y, i - x)[1];
					canvas.at<cv::Vec3b>(j, i)[2] = image.at<cv::Vec3b>(j - y, i - x)[2];
				}
			}
		}

	}
	char* appendCharToCharArray(char* array, char a)
	{
		size_t len = strlen(array);

		char* ret = new char[len + 2];

		strcpy(ret, array);
		ret[len] = a;
		ret[len + 1] = '\0';

		return ret;
	}
	IplImage* Canvas::Image::ReverseImage(const char* path, int width, int height, int reverseSide, COLOR_SCALE colorScale) {
		IplImage *img = cvLoadImage(path, colorScale);
		IplImage *NewResizedImage = resizeImage(img, width, height, 0);

		std::stringstream Sw, Sh, Rs;
		Sw << width;
		Sh << height;
		Rs << reverseSide;
		std::string New = Sw.str() + "x" + Sh.str() + "_";
		New += path;
		const char* FullName = New.c_str();
		std::string newR = Sw.str() + "x" + Sh.str() + "_r" + Rs.str() + "_" + path;
		const char* FullRevName = newR.c_str();
		cvSaveImage(FullName, NewResizedImage);

		IplImage *NewReversedImageI;
		cv::Mat imga(cv::Size(width, height), CV_8UC3);
		imga = cv::cvarrToMat(NewResizedImage);
		cv::Mat flipped;
		flip(imga, flipped, reverseSide);

		NewReversedImageI = cvCloneImage(&(IplImage)flipped);
		cvSaveImage(FullRevName, NewReversedImageI);
		return NewReversedImageI;
	}
	std::string Canvas::Image::GetReversedImageName(const char * imageName, int width, int height, int reverseSide)
	{
		std::stringstream Sw, Sh, Rs;
		Sw << width;
		Sh << height;
		Rs << reverseSide;
		std::string New = Sw.str() + "x" + Sh.str() + "_";
		New += imageName;
		std::string newR = Sw.str() + "x" + Sh.str() + "_r" + Rs.str() + "_" + imageName;
		const char* FullRevName = newR.c_str();
		return std::string();
	}
	void OtherFunctions::sleep(unsigned int mseconds)
	{
		clock_t goal = mseconds + clock();
		while (goal > clock());
	}
	void OtherFunctions::setHorizontY(int y)
	{
		HorizontY = y;
	}
	int OtherFunctions::getHorizontY()
	{
		return HorizontY;
	}
	void OtherFunctions::onMouse(int event, int x, int y, int flags, void* param) {
		if (event == CV_EVENT_LBUTTONDOWN) {
			MouseButtonClicked = CV_EVENT_LBUTTONDOWN;
		}
		else if (event == CV_EVENT_RBUTTONDOWN) {
			MouseButtonClicked = CV_EVENT_RBUTTONDOWN;
		}
		else {
			MouseButtonClicked = 0;
		}
		MouseX = x;
		MouseY = y;
	}
}

RGBcolor::RGBcolor(int r, int g, int b)
{
	RGBcolor::red = r;
	RGBcolor::green = g;
	RGBcolor::blue = b;
}

void RGBcolor::setColor(int r, int g, int b)
{
	RGBcolor::red = r;
	RGBcolor::green = g;
	RGBcolor::blue = b;
}
