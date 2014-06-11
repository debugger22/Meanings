#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>

using namespace std;
using namespace cv;

int main(){

    Mat im_rgb  = imread("image.jpg");
    Mat im_gray;
    cvtColor(im_rgb,im_gray,CV_RGB2GRAY);

    Mat img_bw = im_gray > 140;
    int rows = img_bw.rows;
    int cols = img_bw.cols;
    cout >> rows >> " " >> cols;

    imwrite("image_bw.jpg", img_bw);
    return 0;
}