#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;
Mat src, canny, gray;
int main(int argc, char** argv )
{
	namedWindow("src", CV_WINDOW_AUTOSIZE );;
	namedWindow("gray", CV_WINDOW_AUTOSIZE );
	namedWindow("wyniki",CV_WINDOW_AUTOSIZE);
    VideoCapture capture = VideoCapture(0);
    while ( waitKey(20) != 27 )
    {
   	string string;
   	stringstream out;
    capture >> src;
    Canny(src, canny, 50, 200, 3);
    cvtColor(canny, gray, CV_GRAY2BGR);
    vector<Vec2f> lines;
    // detect lines
    HoughLines(canny, lines, 1, CV_PI/180, 150, 0, 0 );
    // draw lines
    Mat wyniki = Mat::zeros(canny.size(), CV_8UC3 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( gray, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
        out<<i<<" rho: "<<a<<" theta: "<<b;
        string = out.str();
        putText(wyniki, string, Point(30,10),FONT_HERSHEY_SIMPLEX, 0.3,(250,250,250), 1);
    }
    imshow("src", src);
    imshow("gray", gray);
    imshow("wyniki", wyniki);
    }
    capture.release();
    return 0;
}
