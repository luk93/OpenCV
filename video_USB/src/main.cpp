#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, char** argv)
{
	VideoCapture cap;
	cap.open(0); //otw�rz wideo zdefiniowane jako argument
	if(!cap.isOpened())      //gdy niemo�liwe jest otworzenie wideo
	{
		cout<<"Nie mozna odtworzyc video (1)"<<endl;
		return -1;
	}
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //pobierz szeroko�� klatki wideo
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //pobierz wysoko�� klatki wideo
    cout << "Rozmiar okna : " << dWidth << " x " << dHeight << endl;
	namedWindow("Wideo", CV_WINDOW_AUTOSIZE);  //tworzenie okna o nazwie "Wideo"
		while(1)
		{
			Mat frame;
			bool bSuccess = cap.read(frame); // wczytaj nast�pn� klatk� wideo
			if (!bSuccess) //je�li niemo�liwe zako�cz wczytywanie klatek
			{
				cout << "Nie mozna odtworzyc video (2)" << endl;
			    break;
			}

			imshow("Wideo", frame);
			if(waitKey(30) == 27)
			{
				cout << "escape wcisniety przez uzytkownika" << endl;
				break;
			}
		}
	return 0;
}
