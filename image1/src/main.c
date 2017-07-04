#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>



int main(int argc, char** argv)
{

  if(argc<2){
    printf("Trwa: image1 - Obraz do odczytu i wyswietlania\n");
    exit(0);
  }

  IplImage* obraz = 0;
  obraz = cvLoadImage(argv[1], 0);

  if(!obraz){ 										// Sprawdz zrodlo
    printf("Nie mozna otworzyc lub znalezc obrazu\n");
    exit(0);
  }

  cvNamedWindow("OBRAZ", CV_WINDOW_AUTOSIZE);	// Stworz okno
  cvMoveWindow("OBRAZ", 100, 100);
  cvShowImage("OBRAZ", obraz );					// Pokaz obraz
  cvWaitKey(0);								// Czekaj na wcisniecie klawisza
  cvReleaseImage(&obraz);
  cvDestroyWindow("OBRAZ");					//Zamknij okno
  return 0;
}
