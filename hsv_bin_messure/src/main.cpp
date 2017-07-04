#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture capture = VideoCapture(0);
    string window_name [] = { "Obraz z kamery", "Wykrywanie konturow", "Obraz binarny 1", "Obraz binarny 2"};
    Mat frame, img, hsv_img, binary1, binary2;

    //***
    Mat cont;
    Mat cont2;
    //***

    vector<Mat> hsv_split;
    for ( int i = 0; i < 4; i++ ) namedWindow(window_name[i], CV_WINDOW_AUTOSIZE);
    int lowerb = 2, upperb = 60, low =2, up = 40;
    float pomiar1 = 0, pomiar2 = 0, wymiar = 0;
    createTrackbar( "Dolna wartosc progowa 1", window_name[2], &lowerb, 255, NULL );
    createTrackbar( "Gorna wartosc progowa 1", window_name[2], &upperb, 255, NULL );
    createTrackbar( "Dolna wartosc progowa 2", window_name[3], &low, 255, NULL );
    createTrackbar( "Gorna wartosc progowa 2", window_name[3], &up, 255, NULL );
    while ( waitKey(20) != 27 )
    {
        capture >> frame;
        frame.copyTo(img);
        cvtColor(img, hsv_img, CV_BGR2HSV);
        split(hsv_img, hsv_split);
        inRange(hsv_split[0], lowerb, upperb, binary1);
        inRange(hsv_split[1], low, up, binary2);
        blur(binary1, binary1, cv::Size(3,3) );
        erode(binary1, binary1, cv::Mat() );
        blur(binary2, binary2, cv::Size(3,3) );
        erode(binary2, binary2, cv::Mat() );

        //***
        vector<vector<Point> > contours1, contours2;
        vector<Point> contours_poly1,contours_poly2;
        Rect boundRect1, boundRect2;
        binary1.copyTo(cont);
        binary2.copyTo(cont2);
        findContours( cont, contours1, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
        findContours(cont2, contours2, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
        int max1 = 0, i_cont1 = -1, max2 = 0, i_cont2 = -1;
        Mat drawing = Mat::zeros( cont.size(), CV_8UC3 );
        for( int i = 0; i< contours1.size(); i++ )
        {
            if ( abs(contourArea(Mat(contours1[i]))) > max1 )
            {
                max1 = abs(contourArea(Mat(contours1[i])));
                i_cont1 = i;
            }
        }
        for( int i = 0; i< contours2.size(); i++ )
                {
                    if ( abs(contourArea(Mat(contours2[i]))) > max2 )
                    {
                        max2 = abs(contourArea(Mat(contours2[i])));
                        i_cont2 = i;
                    }
                }
        if ( i_cont1 >= 0 )
        {
            approxPolyDP( Mat(contours1[i_cont1]), contours_poly1, 3, true );
            boundRect1 = boundingRect( Mat(contours_poly1) );
            fillConvexPoly(img, contours_poly1, contours_poly1.size() );
            rectangle( img, boundRect1.tl(), boundRect1.br(), Scalar(125, 125, 125), 1, 8, 0 );
            line( img, boundRect1.tl(), boundRect1.br(), Scalar(250, 250, 125), 1, 8, 0);
            line( img, Point(boundRect1.x + boundRect1.width, boundRect1.y), Point(boundRect1.x, boundRect1.y + boundRect1.height), Scalar(250, 250, 125), 1, 8, 0);
            string s;
            stringstream out;
            out <<"Srodek: "<< boundRect1.x + boundRect1.width/2 << "x" << boundRect1.y + boundRect1.height/2;
            out << " Szerokosc: "<<boundRect1.width<< " Wysokosc: "<<boundRect1.height;
            pomiar2 = (boundRect1.width + boundRect2.height) /2;
            s = out.str();
            putText( img, s, Point(10, 10), CV_FONT_HERSHEY_COMPLEX, 0.4, Scalar(20, 40, 80), 1, 8 );
            drawContours( drawing,  contours1, i_cont1, Scalar(125, 125, 250), 2 );
        }
        if ( i_cont2 >= 0 )
        {
        	approxPolyDP( Mat(contours2[i_cont2]), contours_poly2, 3, true );
        	boundRect2 = boundingRect( Mat(contours_poly2) );
        	fillConvexPoly(img, contours_poly2, contours_poly2.size());
        	rectangle( img, boundRect2.tl(), boundRect2.br(), Scalar(125, 125, 125), 1, 8, 0 );
        	line( img, boundRect2.tl(), boundRect2.br(), Scalar(250, 250, 125), 1, 8, 0);
        	line( img, Point(boundRect2.x + boundRect2.width, boundRect2.y), Point(boundRect2.x, boundRect2.y + boundRect2.height), Scalar(250, 250, 125), 1, 8, 0);
        	string st;
        	stringstream out1;
        	out1 <<"Srodek: "<< boundRect2.x + boundRect2.width/2 << "x" << boundRect2.y + boundRect2.height/2;
        	out1 << " Szerokosc: "<<boundRect2.width<< " Wysokosc: "<<boundRect2.height;
        	pomiar1 = (boundRect2.width + boundRect2.height)/2;
        	st = out1.str();
        	putText( img, st, Point(10, 40), CV_FONT_HERSHEY_COMPLEX, 0.4, Scalar(20, 40, 80), 1, 8 );
        	drawContours( drawing,  contours2, i_cont2, Scalar(125, 125, 250), 2 );
        }
        string st1;
        stringstream out2;
        wymiar = ((30 * pomiar2)/pomiar1)*2;
        out2 <<"Srednica: "<<wymiar<< " mm";
        st1 = out2.str();
        putText( img, st1, Point(450, 10), CV_FONT_HERSHEY_COMPLEX, 0.4, Scalar(20, 40, 80), 1, 8 );
        imshow(window_name[1], drawing);
        //***

        imshow(window_name[0], img );
        imshow(window_name[2], binary1);
        imshow(window_name[3], binary2);
    }
    capture.release();
    return 0;
}
