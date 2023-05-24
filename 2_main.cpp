#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;

int main()
{
    setlocale(LC_ALL, "ru");

    cv::Mat img = cv::imread("C:/Users/Таиссия Савенова/Desktop/курсовая/image1.jpg");
    namedWindow("Pic", WINDOW_AUTOSIZE);
    cv::imshow("Pic", img);
    cv::moveWindow("Pic", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
