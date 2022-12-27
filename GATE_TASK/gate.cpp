#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace cv;

void getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> heirachy;
	findContours(imgDil, contours, heirachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	Point r, l, r2;
	for (int i = 0; i < contours.size(); i++) {

		int area = contourArea(contours[i]);
		if (area > 5 && area < 7) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			boundRect[i] = boundingRect(conPoly[i]);
			r2 = boundRect[i].br();
		}
		else if (area > 500) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			boundRect[i] = boundingRect(conPoly[i]);
			r = boundRect[i].br();
			l = boundRect[i].tl();
		}
	}
	int midL = (l.x + r.x) / 2;
	int midR = (l.y + r2.y) / 2;
	rectangle(img, l, Point(r.x, r2.y), Scalar(0, 255, 0), 4);
	circle(img, Point(midL, midR), 5, Scalar(255, 0, 0), FILLED);
}
int main()
{
	Mat imgGray, imgBlur, imgDil, imgCanny;

	string path = "gate.jpeg";
	Mat img = imread(path);
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgCanny, img);

	imshow("Image", img);
	waitKey(0);

	return 0;
}
