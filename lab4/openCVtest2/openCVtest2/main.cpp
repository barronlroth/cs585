/**
 CS585_Lab4.cpp
 @author: Ajjen Joshi
 @version: 1.0 9/25/2014
 
 CS585 Image and Video Computing Fall 2014
 Lab 4
 --------------
 This program introduces the following concepts:
 a) Understanding and applying basic morphological operations on images
 b) Finding and labeling blobs in a binary image
 --------------
 */


#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/**
 Function that detects blobs from a binary image
 @param binaryImg The source binary image (binary image contains pixels labeled 0 or 1 (not 255))
 @param blobs Vector to store all blobs, each of which is stored as a vector of 2D x-y coordinates
 */
void FindBinaryLargeObjects(const Mat &binaryImg, vector <vector<Point2i>> &blobs);

int main(int argc, char **argv)
{
    // read image as grayscale
    Mat img = imread("/Users/barron/Developer/bu/cs585/lab4/openCVtest2/openCVtest2/blob.png", 0);
    if (!img.data) {
        cout << "File not found" << std::endl;
        return -1;
    }
    
    // create windows
    namedWindow("Original");
    namedWindow("binary");
    namedWindow("labelled");
    imshow("Original", img);
    // perform morphological operations to remove small objects (noise) and fill black spots inside objects
    // %TODO
    // Documentation on erode: http://docs.opencv.org/modules/imgproc/doc/filtering.html?highlight=erode#erode
    // Documentation on dilate: http://docs.opencv.org/modules/imgproc/doc/filtering.html?highlight=erode#dilate
    
    // initialize structuring element for morphological operations
    
    //perform erosions and dilations
    
    
    //convert thresholded image to binary image
    Mat binary;
    threshold(img, binary, 0.0, 1.0, THRESH_BINARY);
    
    //initialize vector to store all blobs
    vector <vector<Point2i>> blobs;
    
    //call function that detects blobs and modifies the input binary image to store blob info
    FindBinaryLargeObjects(binary, blobs);
    
    //display the output
    Mat output = Mat::zeros(img.size(), CV_8UC3);
    // Randomly color the blobs
    
    
    //show the binary image, as well as the labelled image
    waitKey(0);
    
    return 0;
}

void FindBinaryLargeObjects(const Mat &binary, vector <vector<Point2i>> &blobs)
{
    //clear blobs vector
    blobs.clear();
    
    //labelled image of type CV_32SC1
    Mat label_image;
    binary.convertTo(label_image, CV_32SC1);
    
    //label count starts at 2
    int label_count = 2;
    
    
    //cout << "The number of blobs in the image is: " << label_count;
    //Code derived from: http://nghiaho.com/
}

