#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;


int main(int argc, char*argv[])
{
	Mat img = imread(argv[1], 1);

	if (!img.data) {
		cout << "Could not find the image!" << endl;
		return -1;
	}

	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;
	int ch = img.channels();

	//create gray color image
	Mat gray(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//Use Gaussian filtering to remove noise
	GaussianBlur(gray, gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
	Mat output = gray.clone();


	//Use Laplace function
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			int G = +1 * gray.at<uchar>(i - 1, j - 1)
				+ gray.at<uchar>(i - 1, j)
				+ gray.at<uchar>(i + 1, j + 1)
				+ gray.at<uchar>(i, j - 1)
				- 8 * gray.at<uchar>(i, j)
				+ gray.at<uchar>(i, j + 1)
				+ gray.at<uchar>(i + 1, j - 1)
				+ gray.at<uchar>(i + 1, j)
				+ gray.at<uchar>(i + 1, j + 1);


			if (G < 0) {
				G = 0;
			}
			else if (G > 255) {
				G = 255;
			}

			output.at<uchar>(i, j) = G;
		}

	}
	//show the output images
	namedWindow("Gray Image");
	imshow("Gray Image", gray);
	namedWindow("Output Image");
	imshow("Output Image", output);
	
	//save the images
	imwrite("\gray.jpg", gray);
	imwrite("\output.jpg", output);

	waitKey(0);
	return 0;


}