#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Trwa: wyswietl_obraz ObrazDoOdczytuWyswietlania\n" << endl;
     return -1;
    }

    Mat obraz;
    obraz = imread(argv[1]);  	// Wczytaj obraz

    if(! obraz.data )          	// Sprawdz zrodlo
    {
        cout <<  "Nie mozna otworzyc lub znalezc obrazu\n" << std::endl ;
        return -1;
    }

    namedWindow("OBRAZ", CV_WINDOW_AUTOSIZE);
    imshow("OBRAZ", obraz);						// Wyswietl obraz
    waitKey();                               	// Czekaj na wcisniecie klawisza
    return 0;
}
