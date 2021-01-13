#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
Mat rotate(Mat src, double angle)   
{
	Mat dst;      
	Point2f pt(src.cols / 2., src.rows / 2.);          
	Mat r = getRotationMatrix2D(pt, angle, 1.0);  
	cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
	// adjust transformation matrix
	r.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
	r.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;
    warpAffine(src, dst, r, bbox.size());
	return dst;         
}
int main()
{
	Mat image = imread("road.jpg");
	if (image.empty())
	{
		cout << "error";
		cin.get();
		return -1;
	}
	string windowname("image processing");
	namedWindow(windowname);
	Mat dst;      
	
	imshow(windowname, image);
	waitKey(0);
	destroyWindow(windowname);
	double n;
	cin >> n;
	dst = rotate(image, n);
	imshow(windowname, dst);
	waitKey(0);
	destroyWindow(windowname);
}