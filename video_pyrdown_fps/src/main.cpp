#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int g_slider_position = 0; //example 4
VideoCapture cap;

void onTrackbarSlide (int pos, void *)
{
	cap.set(CAP_PROP_POS_FRAMES, pos);
}

int main (int argc, char** argv)
{

	cap.open(argv[1]); 	//otwórz wideo zdefiniowane jako argument
	if(!cap.isOpened())      //gdy niemo¿liwe jest otworzenie wideo
	{
		cout<<"Nie mozna odtworzyc video (1)"<<endl;
		return -1;
	}
	Size size(	(int)cap.get(CV_CAP_PROP_FRAME_WIDTH)/2,
				(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT)/2);
	int fps = (int) cap.get(CAP_PROP_FRAME_COUNT);
	namedWindow("Wideo", CV_WINDOW_AUTOSIZE);
	namedWindow("PyrDown", CV_WINDOW_AUTOSIZE);
	createTrackbar("FPS","PyrDown",&g_slider_position, fps, onTrackbarSlide);
	VideoWriter writer;
	writer.open("/home/pi/workspace/pyrdown.avi" ,CV_FOURCC('M','J','P','G'), fps, size);
	Mat pyrdown_frame, rgb_frame;

		while(1)
		{
			cap>>rgb_frame;
			if(rgb_frame.empty())
			{
				cout << "Nie mozna odtworzyc video (2)" << endl;
			    break;
			}

			imshow("Wideo", rgb_frame);
			pyrDown(rgb_frame, pyrdown_frame);
			int current_pos = (int)cap.get(CAP_PROP_POS_FRAMES);
			setTrackbarPos("FPS","PyrDown", current_pos);
			imshow("PyrDown", pyrdown_frame);
			writer<<pyrdown_frame;
			if(waitKey(30) == 27)
			{
				cout << "escape wcisniety przez uzytkownika" << endl;
				break;
			}
		}
		cap.release();
	return 0;
}
