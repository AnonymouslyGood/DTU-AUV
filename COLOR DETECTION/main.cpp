#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat imageHSV, mask;
int hmin=38,smin=0,vmin=146;
int hmax=72,smax=174,vmax=195;
int main()
{
    Mat image = imread("/home/ankitkumar/project/sample.jpeg");

    cvtColor(image, imageHSV, COLOR_BGR2HSV);
    namedWindow("Trackbars", (250 , 640));

    createTrackbar("Hue min", "Trackbars", &hmin, 179);
    createTrackbar("Hue max", "Trackbars", &hmax, 179);
    createTrackbar("Sat min", "Trackbars", &smin, 255);
    createTrackbar("Sat max", "Trackbars", &smax, 255);
    createTrackbar("Val min", "Trackbars", &vmin, 255);
    createTrackbar("Val max", "Trackbars", &vmax, 255);

    while (true)
    {
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imageHSV, lower, upper, mask);
        imshow("Image", image);
        imshow("ImageHSV", imageHSV);
        imshow("Image Mask",mask);
        waitKey(1);
    }
    return 0;
}
