#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

double alpha = 1; // 1.0-3.0
int beta = 50; // 0-100

int main()
{
	Mat image;
	image = imread("barron.jpg", IMREAD_COLOR); // Read the file

	Mat bright_image = Mat::zeros(image.size(), image.type());

	if (image.empty())                      // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return 0;
	}

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				bright_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.

	imshow("Display window", image);                // Show our image inside it.
	imshow("For-Loop", bright_image);                // Show our image inside it.

	imwrite("bright.bmp", bright_image); // write to disk

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}