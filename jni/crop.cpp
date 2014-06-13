#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat dst;
    Mat im_rgb = imread("test3.jpg");  // Load image
    int r = int(im_rgb.rows);  // Get width of the image
    int c = int(im_rgb.cols);  // Get height of the image
    cout<<r<<" "<<c;
    r=r/2;
    c=c/2;

    if(r<c) {
        im_rgb = im_rgb.t();
        flip(im_rgb, im_rgb, 1);
    }
    // Set position by hit and trial
    int i=r-r/30;
    int j = c-3*c/10;
    int x = j;
    int y = 3*c/10;
    // Get the cropping rectangle
    Rect rect = Rect( j, i, x, y );
    cout<<i<<" "<<j<<" "<<x<<" "<<y;
    Mat im_gray;
    im_rgb(rect).copyTo(dst);
    cvtColor(dst,im_gray,CV_RGB2GRAY);

    Mat img_bw = im_gray > 110;
    Mat img_dil;
    dilate(img_bw, img_dil, Mat(), Point(-1, -1), 2, 1, 1);
    imwrite("cropped.jpg", dst);
    imwrite("image_bw.jpg", img_bw);
    return 0;
}