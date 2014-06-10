/*
*  ImageProcessing.cpp
*/
#include <stdio.h>
#include <jni.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <sys/time.h>
#include <android/log.h>

#define APPNAME "Exposure jni"
#define LOGD(TAG) __android_log_print(ANDROID_LOG_DEBUG , APPNAME,TAG);

using namespace std;
using namespace cv;

Mat * mCanny = NULL;

extern "C"
{

jboolean Java_com_fenchtose_lex_CameraPreview_accumulate(
    JNIEnv* env, jobject thiz,
        jint width, jint height,
        jbyteArray NV21FrameData, jfloatArray outFloatPixels,
        jdouble alphaVal)
{
    jbyte * pNV21FrameData = env->GetByteArrayElements(NV21FrameData, 0);
    jfloat* poutFloatPixels = env->GetFloatArrayElements(outFloatPixels, 0);

    double alpha;
    alpha = (double) alphaVal;

    struct timeval start, end;
    //char str[20];
    //char tstr[];
    char times[10];

    Mat mNV(height + height/2, width, CV_8UC1, (unsigned char*)pNV21FrameData);
    Mat mBgr(height, width, CV_8UC3);
    Mat mAcc(height, width, CV_32FC3, (unsigned char*)poutFloatPixels);
    //Mat mAcc8(height, width, CV_8UC3);
    //Mat mResult(height, width, CV_8UC4, (unsigned char *)poutPixels);
    //gettimeofday(&start, NULL);
    cv::cvtColor(mNV, mBgr, CV_YUV2BGR_NV21);
    /*
    gettimeofday(&end, NULL);
    long seconds = end.tv_sec - start.tv_sec;
    long uSeconds = end.tv_usec - start.tv_usec;
    if (uSeconds < 0)
    {
        seconds -= 1;
    }
    double total_msec = double(seconds*1000.0) + double(abs(uSeconds/double(1000.0)));
    char tstr[] = "yuv2bgr";
    sprintf(times, "%.3lf", total_msec);
    strcat(tstr, times);
    LOGD(tstr);

    gettimeofday(&start, NULL);
    */
    cv::accumulateWeighted(mBgr, mAcc, alpha);
    /*
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    uSeconds = end.tv_usec - start.tv_usec;
    if (uSeconds < 0)
    {
        seconds -= 1;
    }
    total_msec = double(seconds*1000.0) + double(abs(uSeconds/double(1000.0)));
    char tstr1[] = "Acc";
    sprintf(times, "%.3lf", total_msec);
    strcat(tstr1, times);
    */
    //LOGD(tstr1);
    /*
    gettimeofday(&start, NULL);
    //convertScaleAbs(mAcc, mAcc8);
    //cv::convertScaleAbs(mAcc, mAcc8, 255);
    mAcc.convertTo(mAcc8, CV_8UC3, 255);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    uSeconds = end.tv_usec - start.tv_usec;
    if (uSeconds < 0)
    {
        seconds -= 1;
    }
    total_msec = double(seconds*1000.0) + double(abs(uSeconds/double(1000.0)));
    char tstr2[] = "conv";
    sprintf(times, "%.3lf", total_msec);
    strcat(tstr2, times);
    LOGD(tstr2);

    gettimeofday(&start, NULL);
    cv::cvtColor(mAcc8, mResult, CV_BGR2RGBA);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    uSeconds = end.tv_usec - start.tv_usec;
    if (uSeconds < 0)
    {
        seconds -= 1;
    }
    total_msec = double(seconds*1000.0) + double(abs(uSeconds/double(1000.0)));
    char tstr3[] = "bgr2rgba";
    sprintf(times, "%.3lf", total_msec);
    strcat(tstr3, times);
    LOGD(tstr3);
    */
    /*
    IplImage srcImg = mGray;
    IplImage CannyImg = *mCanny;
    IplImage ResultImg = mResult;

    cvCanny(&srcImg, &CannyImg, 80, 100, 3);
    cvCvtColor(&CannyImg, &ResultImg, CV_GRAY2BGRA);
    */
    env->ReleaseByteArrayElements(NV21FrameData, pNV21FrameData, 0);
    env->ReleaseFloatArrayElements(outFloatPixels, poutFloatPixels, 0);

    return true;
}

jboolean
Java_com_fenchtose_lex_CameraPreview_convertScale(
    JNIEnv* env, jobject thiz,
    jint width, jint height,
    jfloatArray outFloatPixels, jintArray outPixels)
{
    jint * poutPixels = env->GetIntArrayElements(outPixels, 0);
    jfloat* poutFloatPixels = env->GetFloatArrayElements(outFloatPixels, 0);

    Mat mAcc(height, width, CV_32FC3, (float*)poutFloatPixels);
    Mat mAcc8(height, width, CV_8UC3);
    Mat mResult(height, width, CV_8UC4, (unsigned char*)poutPixels);

    cv::convertScaleAbs(mAcc, mAcc8, 255);
    cv::cvtColor(mAcc8, mResult, CV_RGB2RGBA);

    env->ReleaseIntArrayElements(outPixels, poutPixels, 0);
    env->ReleaseFloatArrayElements(outFloatPixels, poutFloatPixels, 0);
    
    return true;
}

jboolean
Java_com_fenchtose_lex_CameraPreview_accumulatePreview(
        JNIEnv* env, jobject thiz,
        jint width, jint height,
        jbyteArray NV21FrameData, jintArray outPixels, jfloatArray outFloatPixels,
        jdouble alphaVal)
{
    jbyte * pNV21FrameData = env->GetByteArrayElements(NV21FrameData, 0);
    jint * poutPixels = env->GetIntArrayElements(outPixels, 0);
    jfloat* poutFloatPixels = env->GetFloatArrayElements(outFloatPixels, 0);

    double alpha;
    alpha = (double) alphaVal;

    /*
    if ( mCanny == NULL )
    {
        mCanny = new Mat(height, width, CV_8UC1);
    }*/
    /*
    Mat mRgba(height + height/2, width, CV_8UC1, (unsigned char *)pNV21FrameData);
    Mat bgrMat(height, width, CV_8UC3);

    Mat mResult(height, width, CV_8UC4, (unsigned char *)poutPixels);
    Mat mRGray(height, width, CV_8UC3);
    Mat mAcc(height, width, CV_32FC3, (unsigned char *)poutFloatPixels);

    cv::cvtColor(mRgba, bgrMat, CV_YUV2BGR_NV21);
    LOGD("YUV2BGR_NV21 conversion done");
    cv::accumulateWeighted(bgrMat, mAcc, 0.0001);
    LOGD("Accumulate done");
    cv::convertScaleAbs(mAcc, mRGray, 255);
    LOGD("convertScaleAbs done");
    cv::cvtColor(mRGray, mResult, CV_BGR2BGRA);
    */
    // Different approach
    /*
    Mat mNV(height + height/2, width, CV_8UC1, (unsigned char*)pNV21FrameData);
    //Mat mBgr(height, width, CV_8UC3);
    Mat mACCNV(height + height/2, width, CV_32FC1, (unsigned char*)poutFloatPixels);
    //Mat mAcc(height, width, CV_32FC3, (unsigned char*)poutFloatPixels);
    Mat mACCNV8(height, width, CV_8UC1);
    Mat mAcc8(height, width, CV_8UC3);
    char rowstr[10];
    sprintf(rowstr, "%d", width);
    LOGD(rowstr);
    Mat mResult(height, width, CV_8UC4, (unsigned char *)poutPixels);

    //cv::cvtColor(mNV, mBgr, CV_YUV2BGR_NV21);
    //cv::accumulate(mNV, mACCNV);
    cv::accumulateWeighted(mNV, mACCNV, 0.5);
    cv::convertScaleAbs(mACCNV, mACCNV8, 255);
    cv::cvtColor(mACCNV8, mResult, CV_YUV2RGBA_NV21);
    //cv::accumulateWeighted(mBgr, mAcc, 0.0003);
    //cv::convertScaleAbs(mAcc, mAcc8, 255);
    //cv::cvtColor(mAcc8, mResult, CV_BGR2RGBA);
    */
    struct timeval start, end;
    //char str[20];
    //char tstr[];
    char times[10];
    LOGD("init Mat");

    Mat mNV(height + height/2, width, CV_8UC1, (unsigned char*)pNV21FrameData);
    Mat mBgr(height, width, CV_8UC3);
    Mat mAcc(height, width, CV_32FC3, (float*)poutFloatPixels);
    Mat mAcc8(height, width, CV_8UC3);
    Mat mResult(height, width, CV_8UC4, (unsigned char*)poutPixels);

    LOGD("Mat init done");
    //IplImage ResultImg = mResult;
    /*
    gettimeofday(&start, NULL);
    */
    cv::cvtColor(mNV, mBgr, CV_YUV2BGR_NV21);
    LOGD("converted to BGR");
    /*
    gettimeofday(&end, NULL);
    long seconds = end.tv_sec - start.tv_sec;
    long uSeconds = end.tv_usec - start.tv_usec;
    if (uSeconds < 0)
    {
        seconds -= 1;
    }
    double total_msec = double(seconds*1000.0) + double(abs(uSeconds/double(1000.0)));
    char tstr[] = "yuv2bgr";
    sprintf(times, "%.3lf", total_msec);
    strcat(tstr, times);
    LOGD(tstr);
    
    gettimeofday(&start, NULL);
    */
    cv::accumulateWeighted(mBgr, mAcc, alpha);
    /*
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    uSeconds = end.tv_usec - start.tv_usec;
    if (uSeconds < 0)
    {
        seconds -= 1;
    }
    total_msec = double(seconds*1000.0) + double(abs(uSeconds/double(1000.0)));
    char tstr1[] = "Acc";
    sprintf(times, "%.3lf", total_msec);
    strcat(tstr1, times);
   //LOGD(tstr1);

    gettimeofday(&start, NULL);
    */
    //convertScaleAbs(mAcc, mAcc8);
    cv::convertScaleAbs(mAcc, mAcc8, 255);
    //mAcc.convertTo(mAcc8, CV_8UC3, 255);
    /*
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    uSeconds = end.tv_usec - start.tv_usec;
    if (uSeconds < 0)
    {
        seconds -= 1;
    }
    total_msec = double(seconds*1000.0) + double(abs(uSeconds/double(1000.0)));
    char tstr2[] = "conv";
    sprintf(times, "%.3lf", total_msec);
    strcat(tstr2, times);
    LOGD(tstr2);

    gettimeofday(&start, NULL);
    */
    cv::cvtColor(mAcc8, mResult, CV_RGB2RGBA);

    //uint8_t* buf;
    //buf = static_cast<uint8_t>(malloc(width * height * mResult.channels()));
    
    //jint* buf;
    //buf = new jint[width*height*4];
    /*
    for(int i=0; i<height; i++)
    {
        memcpy(&(poutPixels[i*width]), &(mResult.data[i*mResult.step]), width*mResult.channels());
    }*/
    /*
    char tsr4[] = "pixval";
    char pixvalstr[10];
    sprintf(pixvalstr, "%d", poutPixels[0]);
    strcat(tsr4, pixvalstr);
    LOGD(tsr4);

    char tsr5[] = "matval";
    sprintf(pixvalstr, "%d", mResult.at<Vec3b>(0,0)[0]);
    strcat(tsr5, pixvalstr);
    LOGD(tsr5);
    */
    /*
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    uSeconds = end.tv_usec - start.tv_usec;
    if (uSeconds < 0)
    {
        seconds -= 1;
    }
    total_msec = double(seconds*1000.0) + double(abs(uSeconds/double(1000.0)));
    char tstr3[] = "bgr2rgba";
    sprintf(times, "%.3lf", total_msec);
    strcat(tstr3, times);
    LOGD(tstr3);
    */
    /*
    IplImage srcImg = mGray;
    IplImage CannyImg = *mCanny;
    IplImage ResultImg = mResult;

    cvCanny(&srcImg, &CannyImg, 80, 100, 3);
    cvCvtColor(&CannyImg, &ResultImg, CV_GRAY2BGRA);
    */
    env->ReleaseByteArrayElements(NV21FrameData, pNV21FrameData, 0);
    env->ReleaseIntArrayElements(outPixels, poutPixels, 0);
    env->ReleaseFloatArrayElements(outFloatPixels, poutFloatPixels, 0);
    LOGD("Returning");
    return true;
}
}