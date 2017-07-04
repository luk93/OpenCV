#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	Mat img_rgb, img_gry, img_cny;
	namedWindow("Przyklad gray", CV_WINDOW_AUTOSIZE);
	namedWindow("Przyklad canny", CV_WINDOW_AUTOSIZE);

	img_rgb = imread(argv[1]);
	cvtColor(img_rgb, img_gry, COLOR_BGR2GRAY);
	imshow("Przyklad gray",img_gry);
	Canny(img_gry, img_cny, 10, 100, 3, true);
	imshow("Przyklad canny", img_cny);
	waitKey(0);
	return 0;

}

