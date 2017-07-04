#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

void Gauss (const Mat & image)
{
	namedWindow("Gauss in", CV_WINDOW_AUTOSIZE);
	namedWindow("Gauss out", CV_WINDOW_AUTOSIZE);
	imshow("Gauss in", image);

	Mat out;
	GaussianBlur(image,out,Size(5,5), 3, 3);
	GaussianBlur(out,out,Size(5,5), 3, 3);
	imshow("Gauss out", out);
	waitKey(0);

}
int main (int argc, char** argv)
{
	Mat img = imread(argv[1],-1);
	Gauss(img);
	return 0;
}

