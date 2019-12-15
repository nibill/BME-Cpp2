#pragma once

//opencv header files
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>


#include <iostream>

using namespace cv;
using namespace std;

class OCR
{
public:

    OCR();
    void GenerateOcrData(string trainImg);
    int  Train(Mat img);
    Mat classificationNumsTrain;
    Mat imageAsFlattenedFloatTrain;
    ~OCR();

private:

    KNearest m_knearest;

    Mat m_matFloatImage;
    Mat m_matTestImage;
    Mat m_matTrainingImage;
    Mat m_matGrayedImage;
    Mat m_matBlurredImage;
    Mat m_matThresholdImage;
    Mat m_matThresholdClone;
    Mat m_matClassNums;
};

