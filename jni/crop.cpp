#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>

using namespace std;
using namespace cv;

int main(){

    Mat im_rgb  = imread("imtest.jpg");
    Mat dst;
    int r = int(im_rgb.rows);
    int c = int(im_rgb.cols);
    cout<<r<<" "<<c;
    r=r/2;
    c=c/2;
    int i=r-r/30;
    int j = c-3*c/10;
    int x = j;
    int y = 3*c/10;
    Rect rect = Rect( j, i, x, y );
    cout<<i<<" "<<j<<" "<<x<<" "<<y;
    Mat im_gray;
    im_rgb(rect).copyTo(dst);
    cvtColor(dst,im_gray,CV_RGB2GRAY);

    Mat img_bw = im_gray > 100;
    imwrite("cropped.jpg", dst);
    imwrite("image_bw.jpg", img_bw);
    return 0;
}