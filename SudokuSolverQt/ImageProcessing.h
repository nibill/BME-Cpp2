#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#include "OCR.h"

class ImageProcessing
{
public:
    void processSudoku();
    void getSudoku(string imgName);

    Mat sudokuImg, allignedImg, thresholdAllignedImg;

    int sudokuGrid[9][9];

private:
    void m_threshold(Mat& img, Mat& threshimg);
    void m_getHoughLines(Mat img, vector <Vec2f>& Lines);
    void m_mergeHoughLines(vector <Vec2f>* lines);
    void m_allignSudoku(const vector <Vec2f>& lines);
    void m_drawEdges(const Vec2f& edge, Scalar rgb);
    void m_extractSudoku(Mat img);

    string m_sudokuPath;

    Mat m_thresholdRoiImg, m_sudokuImage, m_thresholdImg, m_grayedImg, m_blurredImg, m_roiImg;
};

#endif // IMAGEPROCESSING_H
