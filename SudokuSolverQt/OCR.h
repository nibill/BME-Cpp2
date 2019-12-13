#pragma once

//opencv header files
#include <opencv\cv.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\ml\ml.hpp>

#include <iostream>

using namespace cv;
using namespace std;

class OCR
{
public:

    OCR();
    void GenerateOcrData(string trainImg);
    int  Train(Mat img);
    void Recognize(Mat img);
    Mat classificationNumsTrain;
    Mat imageAsFlattenedFloatTrain;
    ~OCR();

private:

    KNearest knearest;

    Mat matFloatImage;
    Mat matTestImage;
    Mat matTrainingImage;
    Mat matGrayedImage;
    Mat matBlurredImage;
    Mat matThresholdImage;
    Mat matThresholdClone;
    Mat matClassNums;
};

