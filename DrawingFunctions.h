#include <opencv2\opencv.hpp>

#include <math.h>
#include <iostream>
#include <string>
#include <time.h>
enum COLOR_SCALE { RGB = 1, GRAY_SCALE = 2 };
typedef cv::Mat WindowDraw;
class RGBcolor {
public:
	int red, green, blue;
	RGBcolor(int r, int g, int b);
	RGBcolor() {}
	void setColor(int r, int g, int b);
};
namespace Canvas {

	class OtherFunctions {
	private:
		int HorizontY;
	public:
		void sleep(unsigned int mseconds);
		void setHorizontY(int y);
		int getHorizontY();
		int MouseX, MouseY, MouseButtonClicked;
		void onMouse(int event, int x, int y, int flags, void* param);

	};

	class Draw {
	public:

		int Color_Scale;
		void CreateWindowe(std::string name, int x, int y, int width, int height, COLOR_SCALE scale, WindowDraw canvas);
		int GetWindowWidth(std::string name);
		int GetWindowHeight(std::string name);
		void SetBackgroundColor(RGBcolor color, std::string windowName, WindowDraw canvas);
		void SetBackgroundColor(int red, int green, int blue, std::string windowName, WindowDraw canvas);
		void drawPixel(int x, int y, RGBcolor color, std::string windowName, WindowDraw canvas);
		void drawPixel(int x, int y, int red, int green, int blue, std::string windowName, WindowDraw canvas);
		void drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue, std::string windowName, WindowDraw canvas);
		void drawLine(cv::Point p1, cv::Point p2, RGBcolor color, std::string windowName, WindowDraw canvas);
		void drawLine(int x1, int y1, int x2, int y2, RGBcolor color, std::string windowName, WindowDraw canvas);
		void drawLine(cv::Point p1, cv::Point p2, int red, int green, int blue, std::string windowName, WindowDraw canvas);
		void drawLineLC(cv::Point p1, cv::Point p2, int red, int green, int blue, std::string windowName, WindowDraw canvas);
		void drawFillRect(int x, int y, int width, int height, RGBcolor color, std::string windowName, WindowDraw canvas);
		void drawFillRect(int x, int y, int width, int height, int red, int green, int blue, std::string windowName, WindowDraw canvas);

		void Draw::drawImage(const char* path, int x, int y, int width, int height, int BackgroundRed, int BackgroundGreen, int BackgroundBlue, COLOR_SCALE scale, bool keepAspectRatio, std::string windowName, WindowDraw canvas);
		void Draw::drawImage(const char* path, int x, int y, int BackgroundRed, int BackgroundGreen, int BackgroundBlue, COLOR_SCALE scale, std::string windowName, WindowDraw canvas);

		void drawStrokeRect(int x, int y, int width, int height, RGBcolor color, std::string windowName, WindowDraw canvas, int borderPx = 1);
		void drawStrokeRect(int x, int y, int width, int height, int red, int green, int blue, std::string windowName, WindowDraw canvas, int borderPx = 1);
		void drawPointLC(float x, float y, int windowWidth, int windowHeight, int r, int g, int b, std::string windowName, WindowDraw canvas);
		void drawText(int x, int y, std::string text, int red, int green, int blue, double scale, std::string windowName, WindowDraw canvas);
	private:	int Width, Height;
	};

	class Image {
	public:
		IplImage* cropImage(const IplImage *img, const CvRect region);
		IplImage* resizeImage(const IplImage *origImg, int newWidth, int newHeight, bool keepAspectRatio);
		IplImage* ReverseImage(const char* path, int width, int height, int reverseSide, COLOR_SCALE colorScale);
		std::string GetReversedImageName(const char* imageName, int width, int height, int reverseSide);
	};
};
