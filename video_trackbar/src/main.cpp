#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

int g_slider_position = 0;
int g_run = 1, g_dontset = 0; //zacznij w trybie pojedynczego kroku
VideoCapture g_cap;

void onTrackbarSlide (int pos, void *)
{
	g_cap.set(CAP_PROP_POS_FRAMES, pos);
	if(!g_dontset)
		g_run = 1;
	g_dontset = 0;

}
int main(int argc, char** argv)
{
	namedWindow("Strona 53", CV_WINDOW_AUTOSIZE);
	g_cap.open(string(argv[1]));
	int frames = (int) g_cap.get(CAP_PROP_FRAME_COUNT);
	int tmpw = (int) g_cap.get(CAP_PROP_FRAME_WIDTH);
	int tmph = (int) g_cap.get(CAP_PROP_FRAME_HEIGHT);
	cout<<"Wideo ma: "<<frames<<"klatek o wymiarach:"
		<<tmpw<<" x "<<tmph<<" "<<endl;
	createTrackbar("Pozycja","Strona 53",&g_slider_position, frames, onTrackbarSlide);
	Mat frame;
	while(1)
	{
		if(g_run!=0)
		{
			g_cap>>frame;
			if(frame.empty()) break;
			int current_pos = (int)g_cap.get(CAP_PROP_POS_FRAMES);
			g_dontset = 1;
			setTrackbarPos("Pozycja","Strona 53", current_pos);
			imshow("Strona 53",frame);
			g_run-=1;
		}
		char c = (char) waitKey(10);
		if(c=='s')//pojedynczy krok
		{
			g_run = 1;
			cout<<"Pojedynczy krok, start = "<<g_run<<endl;
		}
		if(c=='r')
		{
			g_run = -1;
			cout<<"Normalny tryb, start = "<<g_run<<endl;
		}
		if(c==27) break;
	}
	return(0);

}
