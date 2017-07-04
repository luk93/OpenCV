#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat img_rgb, img_gry, img_cny,img_pyr, img_pyr2;
	namedWindow("Przyklad 1", CV_WINDOW_AUTOSIZE);
	namedWindow("Przyklad 2", CV_WINDOW_AUTOSIZE);

	img_rgb = imread(argv[1]);
	cvtColor(img_rgb, img_gry, COLOR_BGR2GRAY);
	imshow("Przyklad 1", img_gry);
	pyrDown(img_gry, img_pyr);
	pyrDown(img_pyr, img_pyr2);
	Canny(img_pyr2, img_cny, 10 ,100, 3, true);
	imshow("Przyklad 2", img_cny);
	waitKey(0);

	int x = 16, y = 32;
	Vec3b intensity = img_rgb.at< Vec3b >(y,x);
	uchar blue = intensity[0];
	uchar green = intensity[1];
	uchar red = intensity[2];

	cout<<"W pikselu ("<<x<<", "<<y<<"): (blue,green,red) = ("<<(unsigned int)blue<<", "
		<<(unsigned int)green<<", "<<(unsigned int)red<<")"<<endl;
	cout<<"Szary piksel jest: "<<(unsigned int)img_gry.at<uchar>(y,x)<<endl;
	x/=4;
	y/=4;
	cout<<"Piramid2 piksel jest: "<<(unsigned int)img_pyr2.at<uchar>(y,x)<<endl;
	img_cny.at<uchar>(x,y) = 128;
	return 0;

}

