#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;
int main (int argc, char** argv)
{
	Mat src1 = imread(argv[1],1);
	Mat src2 = imread(argv[2],1);
	if(argc==9&&!src1.empty()&&!src2.empty())
	{
		int x = atoi(argv[3]);
		int y = atoi(argv[4]);
		int w = atoi(argv[5]);
		int h = atoi(argv[6]);
		double alpha = (double)atof(argv[7]);
		double beta = (double)atof(argv[8]);
		Mat roi1(src1, Rect(x,y,w,h));
		Mat roi2(src2, Rect(0,0,w,h));

		addWeighted(roi, aplha, roi2, beta, 0.0, roi1);
		namedWindwo("Alpha blend",1);
		imshow("Alpha blend",src2);
		waitKey(0);
	}
	return 0;
}
