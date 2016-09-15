# Part 1: Paper-and-pencil Assignment: Color, Grayscale, and Binary Images; Projections

# 1. Color, Grayscale, and Binary Images:
## a. Describe two ways of representing color in an image.
    RGB & HSV
	
## b. For each representation, write a program that creates a grayscale image.

RGB -> Grayscale
```c++
	#include <cv.h>
	#include <highgui.h>
	#include <opencv2/imgproc/imgproc.hpp>
	#include <stdio.h>

	using namespace cv;

	int main( int argc, char** argv )
	{
		 char* imageName = argv[1];

		 Mat image;
		 image = imread( imageName, 1 );

		 if( argc != 2 || !image.data )
		 {
		   printf( " No image data \n " );
		   return -1;
		 }

		 Mat gray_image;
		 cvtColor( image, gray_image, CV_BGR2GRAY );

		 imwrite( "../../images/Gray_Image.jpg", gray_image );

		 namedWindow( imageName, CV_WINDOW_AUTOSIZE );
		 namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

		 imshow( imageName, image );
		 imshow( "Gray image", gray_image );

		 waitKey(0);

		 return 0;
	}
```

HSV -> Grayscale: Take V and use it as grayscale
```c++
Mat im = imread("barron.jpg", CV_LOAD_IMAGE_COLOR);

Mat imHSV;
cvtColor(im, imHSV, CV_BGR2HSV);
imshow("HSV", imHSV);

Mat hsv_channels[3];
cv::split( imHSV, hsv_channels );
//take third channel
imshow("HSV to gray", hsv_channels[2]);

imshow("BGR", im);
cvtColor(im, im, CV_BGR2GRAY);
imshow("BGR to gray", im);

waitKey();
```

## c. Provide code to transform a grayscale image I(x,y) into a binary image B(x,y).

# 2. Projections:

## a. Define the horizontal and vertical projection vectors H and V mathematically for a binary image B(x,y).



## b. Give code to compute H and V.

```c++
#include <cv.h>
#include <highgui.h>

using namespace cv;

int main( int argc, char** argv )
{
    Mat src, hsv;
    if( argc != 2 || !(src=imread(argv[1], 1)).data )
        return -1;

    cvtColor(src, hsv, CV_BGR2HSV);

    // Quantize the hue to 30 levels
    // and the saturation to 32 levels
    int hbins = 30, sbins = 32;
    int histSize[] = {hbins, sbins};
    // hue varies from 0 to 179, see cvtColor
    float hranges[] = { 0, 180 };
    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {0, 1};

    calcHist( &hsv, 1, channels, Mat(), // do not use mask
             hist, 2, histSize, ranges,
             true, // the histogram is uniform
             false );
    double maxVal=0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 10;
    Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

    for( int h = 0; h < hbins; h++ )
        for( int s = 0; s < sbins; s++ )
        {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal*255/maxVal);
            rectangle( histImg, Point(h*scale, s*scale),
                        Point( (h+1)*scale - 1, (s+1)*scale - 1),
                        Scalar::all(intensity),
                        CV_FILLED );
        }

    namedWindow( "Source", 1 );
    imshow( "Source", src );

    namedWindow( "H-S Histogram", 1 );
    imshow( "H-S Histogram", histImg );
    waitKey();
}
```

# 3. Object size. Assume your binary image B(x,y) contains a single white object in a black background.

## a. Give the mathematical formula for computing the area of the object.
B(x,y) = 1 if I(x,y) > T
       = 0 otherwise
Area = sum[x = xdim-1] sum[y=ydim-1] B(x,y)

## b. Give code to compute the area.


