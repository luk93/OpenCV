#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture capture = VideoCapture(0);
    string window_name [] = { "Obraz z kamery", "Wykrywanie konturow", "Obraz binarny" };
    Mat frame, img, hsv_img, binary;

    //***
    Mat cont;
    //***

    vector<Mat> hsv_split;
    for ( int i = 0; i < 3; i++ ) namedWindow(window_name[i], CV_WINDOW_AUTOSIZE);
    int lowerb = 2, upperb = 60;
    createTrackbar( "Dolna wartosc progowa", window_name[2], &lowerb, 255, NULL );
    createTrackbar( "Gorna wartosc progowa", window_name[2], &upperb, 255, NULL );
    while ( waitKey(20) != 27 )
    {
        capture >> frame;
        frame.copyTo(img);
        cvtColor(img, hsv_img, CV_BGR2HSV);
        split(hsv_img, hsv_split);
        inRange(hsv_split[0], lowerb, upperb, binary);
        blur(binary, binary, cv::Size(3,3) );
        erode(binary, binary, cv::Mat() );

        //***
        vector<vector<Point> > contours;
        vector<Point> contours_poly;
        Rect boundRect;
        binary.copyTo(cont);
        findContours( cont, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
        int max = 0, i_cont = -1;
        Mat drawing = Mat::zeros( cont.size(), CV_8UC3 );
        for( int i = 0; i< contours.size(); i++ )
        {
            if ( abs(contourArea(Mat(contours[i]))) > max )
            {
                max = abs(contourArea(Mat(contours[i])));
                i_cont = i;
            }
        }
        if ( i_cont >= 0 )
        {
            approxPolyDP( Mat(contours[i_cont]), contours_poly, 3, true );
            boundRect = boundingRect( Mat(contours_poly) );
            fillConvexPoly(img, contours_poly, contours_poly.size() );
            rectangle( img, boundRect.tl(), boundRect.br(), Scalar(125, 125, 125), 1, 8, 0 );
            line( img, boundRect.tl(), boundRect.br(), Scalar(250, 250, 125), 1, 8, 0);
            line( img, Point(boundRect.x + boundRect.width, boundRect.y), Point(boundRect.x, boundRect.y + boundRect.height), Scalar(250, 250, 125), 1, 8, 0);
            string s;
            stringstream out;
            out <<"Srodek: "<< boundRect.x + boundRect.width/2 << "x" << boundRect.y + boundRect.height/2;
            out << " Szerokosc: "<<boundRect.width<< " Wysokosc: "<<boundRect.height;
            s = out.str();
            putText( img, s, Point(10, 30), CV_FONT_HERSHEY_COMPLEX, 0.4, Scalar(20, 40, 80), 1, 8 );
            drawContours( drawing,  contours, i_cont, Scalar(125, 125, 250), 2 );
        }
        imshow(window_name[1], drawing);
        //***

        imshow(window_name[0], img );
        imshow(window_name[2], binary);
    }
    capture.release();
    return 0;
}
