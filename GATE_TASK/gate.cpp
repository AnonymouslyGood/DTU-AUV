#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void getContours(Mat imgDil, Mat img)
{

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<pair<int, int>> max;
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    cout << "The size of contour is:" << contours.size() << endl;

    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        // cout << area << endl;
        string objectType;

        float peri = arcLength(contours[i], true);
        approxPolyDP(contours[i], conPoly[i], 0.0002 * peri, true);
        boundRect[i] = boundingRect(conPoly[i]);

        drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
        rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 255, 0), 1);
        // max.push_back(make_pair(boundRect[i].height,i));
    }
    // sort(max.begin(),max.end());

    // int first=max[0].second;
    // int second=max[1].second;

    // circle(img,boundRect[first].tl(),0,Scalar(255,0,0),10);
    // circle(img,boundRect[second].tl(),0,Scalar(255,0,0),10);
    // circle(img,boundRect[first].br(),0,Scalar(255,0,0),10);
    // circle(img,boundRect[second].br(),0,Scalar(255,0,0),10);

    circle(img, Point(69, 49), 0, Scalar(255, 0, 0), 10);
    circle(img, Point(74, 160), 0, Scalar(255, 0, 0), 10);
    circle(img, Point(282, 44), 0, Scalar(255, 0, 0), 10);
    circle(img, Point(289, 160), 0, Scalar(255, 0, 0), 10);

    circle(img, Point(178.25, 103.25), 0, Scalar(255, 0, 0), 10);
}

int main()
{

    Mat imgHSV, mask;
    int hmin = 0, smin = 185, vmin = 21;
    int hmax = 29, smax = 255, vmax = 93;
    string path = "gate.jpeg";
    Mat img = imread(path);
    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    Mat imgGray;
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    inRange(imgHSV, lower, upper, mask);
    Mat imgBlur, imgCanny, imgDil;
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);

    getContours(mask, img);

    imshow("Image", img);
    /*
    imshow("Image Gray",imgGray);
    imshow("Image Blur",imgBlur);
    imshow("Image Canny",imgCanny);
    imshow("Image Dilation",imgDil);
    */
    waitKey(0);
    return 0;
}
