#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main (int argc, char** argv)
{
	VideoCapture cap;
	cap.open(0); //otwórz wideo zdefiniowane jako argument
	if(!cap.isOpened())      //gdy niemo¿liwe jest otworzenie wideo
	{
		cout<<"Nie mozna odtworzyc video (1)"<<endl;
		return -1;
	}

	namedWindow("Wideo", CV_WINDOW_AUTOSIZE);
	namedWindow("Canny", CV_WINDOW_AUTOSIZE);
	Mat rgb_frame, rgb_gauss_frame, gray_frame, canny_frame;

		while(1)
		{
			cap>>rgb_frame;
			if(rgb_frame.empty())
			{
				cout << "Nie mozna odtworzyc video (2)" << endl;
			    break;
			}

			GaussianBlur(rgb_frame, rgb_gauss_frame, Size(5,5),0,0);
			cvtColor(rgb_gauss_frame, gray_frame, CV_BGR2GRAY);
			Canny(gray_frame, canny_frame, 50, 100, 3,true);
			imshow("Wideo", rgb_frame);
			imshow("Canny", canny_frame);
			if(waitKey(30) == 27)
			{
				cout << "escape wcisniety przez uzytkownika" << endl;
				break;
			}
		}
		cap.release();
	return 0;
}
