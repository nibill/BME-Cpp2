#include "ImageProcessing.h"

/////////////////////////////This is the image processing part////////////////////////////////////
//stores the minimum vote that a line must have to be considered as a line.
int minVote;
const string SUDOKUWINDOW = "Sudoku";
const string ALLIGNEDWINDOW= "allignedSudoku";

//get the sudoku image stored in the computer
void ImageProcessing::getSudoku(string imgName)
{
    //read the sudoku image
    sudokuImg = imread(imgName, CV_LOAD_IMAGE_UNCHANGED);

    //check if the image was loaded successfully
    if (sudokuImg.empty())
    {
        cout << "Sudoku could not be loaded!\n\n";
        cout << "Exiting the program now.......";

        exit(1);
    }
}

//perform various processings
void ImageProcessing::processSudoku()
{
    //vector to store the hough lines
    vector <Vec2f> houghLines;

    minVote = 220;

    //threshold the image so that we can find the contours and thereby extract the sudoku
    m_threshold(sudokuImg, m_thresholdImg);

    //extract the sudoku frome the image by assuming
    //that the largest contour in the iamge is of the sudoku grid
    m_extractSudoku(m_thresholdImg);

    //once again threshold the ROI(i.e sudoku box) so that we can find the
    //hough lines
    m_threshold(m_roiImg, m_thresholdRoiImg);

    //find the hough lines,merge and draw them
    m_getHoughLines(m_thresholdRoiImg, houghLines);
    m_mergeHoughLines(&houghLines);

    //detct the edges(left edge,top edge etc)
    m_allignSudoku(houghLines);

    m_threshold(allignedImg, thresholdAllignedImg);

    dilate(thresholdAllignedImg, thresholdAllignedImg, getStructuringElement(MORPH_RECT, Size(1, 1)), Point(-1, -1), 1);
}

void ImageProcessing::m_threshold(Mat& img, Mat& threshimg)
{
    Mat graySudoku;
    Mat blurrSudoku;

    //do opencv image processing
    cvtColor(img, graySudoku, CV_BGR2GRAY);
    GaussianBlur(graySudoku, blurrSudoku, Size(7, 7), 0);
    adaptiveThreshold(blurrSudoku, threshimg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 3, 2);
}

void ImageProcessing::m_getHoughLines(Mat img, vector <Vec2f>& Lines)
{
    HoughLines(img, Lines, 1, CV_PI / 180, minVote, 0, 0);
}

//we will try and merge the nearby lines so that they fuse together to a common lines
//this will reduce the number of unwanted lines.
void ImageProcessing::m_mergeHoughLines(vector <Vec2f>* lines)
{
    //iterartor to iterarte through the vector of lines
    vector <Vec2f>::iterator it1;

    for (it1 = lines->begin(); it1 != lines->end(); it1++)
    {
        //we will mark the lines which have been merged,by setting the rho and theta values to possibly the
        //impossible values,this is very necessary because we need to have a way to recognize the lines that
        //have been merged and no longer exist.
        if ((*it1)[0] == 0 || (*it1)[1] == -100)
        {
            continue;
        }

        float rho1 = (*it1)[0];
        float theta1 = (*it1)[1];

        Point point11, point12;

        if (((*it1)[1] > (CV_PI * 45 / 180)) && ((*it1)[1] < (CV_PI * 135 / 180)))
        {
            point11.x = 0;
            point11.y = (rho1 / sin(theta1));

            point12.x = m_roiImg.size().width;
            point12.y = (rho1 / sin(theta1)) - (m_roiImg.size().width / tan(theta1));
        }
        else
        {
            point11.y = 0;
            point11.x = (rho1 / cos(theta1));

            point12.y = m_roiImg.size().height;
            point12.x = (rho1 / cos(theta1)) - (m_roiImg.size().height * tan(theta1));
        }

        vector<Vec2f>::iterator it2;

        for (it2 = lines->begin(); it2 != lines->end(); it2++)
        {
            Point point21, point22;

            if ((*it1) == (*it2))
            {
                continue;
            }

            if ((fabs(((*it2)[0] - (*it1)[0])) < 20) && (fabs(((*it2)[1] - (*it1)[1])) < CV_PI * 20 / 180))
            {
                float rho2 = (*it2)[0];
                float theta2 = (*it2)[1];

                if (((*it2)[1] > (CV_PI * 45 / 180)) && ((*it2)[1] < (CV_PI * 135 / 180)))
                {
                    point21.x = 0;
                    point21.y = (rho2 / sin(theta2));

                    point22.x = m_roiImg.size().width;
                    point22.y = (rho2 / sin(theta2)) - (m_roiImg.size().width / tan(theta2));
                }
                else
                {
                    point21.y = 0;
                    point21.x = (rho2 / cos(theta2));

                    point22.y = m_roiImg.size().height;
                    point22.x = (rho2 / cos(theta2)) - (m_roiImg.size().height * tan(theta2));
                }

                if ((double)((point11.x - point21.x) * (point11.x - point21.x) + (point11.y - point21.y) * (point11.y - point21.y)) < 64 * 64 && (double)((point12.x - point22.x) * (point12.x - point22.x) + (point12.y - point22.y) * (point12.y - point22.y)) < 64 * 64)
                {
                    (*it1)[0] = ((*it1)[0] + (*it2)[0]) / 2.0;
                    (*it1)[1] = ((*it1)[1] + (*it2)[1]) / 2.0;

                    (*it2)[0] = 0;
                    (*it2)[1] = -100;
                }
            }
        }
    }
}

void ImageProcessing::m_allignSudoku(const vector <Vec2f>& lines)
{
    /*	We will first detect the edges of the sudoku to find the point of intersection (i.e the corners of the sudoku)*/

    //the edges
    Vec2f topEdge = Vec2f(1000, 1000);
    Vec2f bottomEdge = Vec2f(-1000, -1000);
    Vec2f leftEdge = Vec2f(1000, 1000);
    Vec2f rightEdge = Vec2f(-1000, -1000);
    double leftXintercept = 10000;
    double leftYintercept = 0;
    double rightXintercept = 0;
    double rightYintercept = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        Vec2f currentLine = lines[i];

        float rho = currentLine[0];
        float theta = currentLine[1];

        float xinter = currentLine[0] / cos(currentLine[1]);
        float yinter = currentLine[0] / sin(currentLine[1]);

        if (rho == 0 && theta == -100)
        {
            continue;
        }

        //check the horizontal lines
        if ((theta > CV_PI * 60 / 180) && (theta < CV_PI * 120 / 180))
        {
            if (rho < topEdge[0])
            {
                topEdge = currentLine;
            }

            if (rho > bottomEdge[0])
            {
                bottomEdge = currentLine;
            }
        }

        else if ((theta < CV_PI * 10 / 180) || (theta > CV_PI * 170 / 180))
        {
            if (xinter > rightXintercept)
            {
                rightEdge = currentLine;
                rightXintercept = xinter;
            }

            if (xinter <= leftXintercept)
            {
                leftEdge = currentLine;
                leftXintercept = xinter;
            }
        }
    }

    Point top1, top2, bottom1, bottom2, left1, left2, right1, right2;

    if (leftEdge[1] != 0)
    {
        left1.x = 0;
        left1.y = leftEdge[0] / sin(leftEdge[1]);

        left2.x = m_roiImg.size().width;
        left2.y = left1.y - (left2.x / tan(leftEdge[1]));
    }
    else
    {
        left1.y = 0;
        left1.x = leftEdge[0] / cos(leftEdge[1]);

        left2.y = m_roiImg.size().height;
        left2.x = left1.x - (left2.y * tan(leftEdge[1]));
    }

    if (rightEdge[1] != 0)
    {
        right1.x = 0;
        right1.y = rightEdge[0] / sin(rightEdge[1]);

        right2.x = m_roiImg.size().width;
        right2.y = right1.y - (right2.x / tan(rightEdge[1]));
    }
    else
    {
        right1.y = 0;
        right1.x = rightEdge[0] / cos(rightEdge[1]);

        right2.y = m_roiImg.size().height;
        right2.x = right1.x - (right2.y * tan(rightEdge[1]));
    }

    top1.x = 0;
    top1.y = topEdge[0] / sin(topEdge[1]);

    top2.x = m_roiImg.size().width;
    top2.y = top1.y - (top2.x / tan(topEdge[1]));

    bottom1.x = 0;
    bottom1.y = bottomEdge[0] / sin(bottomEdge[1]);

    bottom2.x = m_roiImg.size().width;
    bottom2.y = bottom1.y - (bottom2.x / tan(bottomEdge[1]));

    double leftA = left2.y - left1.y;
    double leftB = left1.x - left2.x;
    double leftC = leftB * left1.y + leftA * left1.x;

    double rightA = right2.y - right1.y;
    double rightB = right1.x - right2.x;
    double rightC = rightB * right1.y + rightA * right1.x;

    double topA = top2.y - top1.y;
    double topB = top1.x - top2.x;
    double topC = topB * top1.y + topA * top1.x;

    double bottomA = bottom2.y - bottom1.y;
    double bottomB = bottom1.x - bottom2.x;
    double bottomC = bottomB * bottom1.y + bottomA * bottom1.x;

    double topLeftDet = topA * leftB - topB * leftA;
    double topRightDet = topA * rightB - topB * rightA;
    double bottomLeftDet = bottomA * leftB - bottomB * leftA;
    double bottomRightDet = bottomA * rightB - bottomB * rightA;

    Point topLeft, topRight, bottomLeft, bottomRight;

    topLeft.x = (topC * leftB - topB * leftC) / topLeftDet;
    topLeft.y = (topA * leftC - topC * leftA) / topLeftDet;

    topRight.x = (topC * rightB - topB * rightC) / topRightDet;
    topRight.y = (topA * rightC - topC * rightA) / topRightDet;

    bottomRight.x = (bottomC * rightB - bottomB * rightC) / bottomRightDet;
    bottomRight.y = (bottomA * rightC - bottomC * rightA) / bottomRightDet;

    bottomLeft.x = (bottomC * leftB - bottomB * leftC) / bottomLeftDet;
    bottomLeft.y = (bottomA * leftC - bottomC * leftA) / bottomLeftDet;

    int maxLength = ((topRight.x - topLeft.x) * (topRight.x - topLeft.x)) + ((topRight.y - topLeft.y) * (topRight.y - topLeft.y));

    int length = ((topRight.x - bottomRight.x) * (topRight.x - bottomRight.x) + (topRight.y - bottomRight.y) * (topRight.y - bottomRight.y));
    if (length > maxLength)
    {
        maxLength = length;
    }

    length = ((bottomRight.x - bottomLeft.x) * (bottomRight.x - bottomLeft.x)) + ((bottomRight.y - bottomLeft.y) * (bottomRight.y - bottomLeft.y));
    if (length > maxLength)
    {
        maxLength = length;
    }

    length = ((bottomLeft.x - topLeft.x) * (bottomLeft.x - topLeft.x)) + ((bottomLeft.y - topLeft.y) * (bottomLeft.y - topLeft.y));
    if (length > maxLength)
    {
        maxLength = length;
    }

    maxLength = sqrt(maxLength);

    Point2f originalPoints[4], mappedPoints[4];

    originalPoints[0] = topLeft;
    mappedPoints[0] = Point(0, 0);
    originalPoints[1] = topRight;
    mappedPoints[1] = Point(maxLength - 1, 0);
    originalPoints[2] = bottomRight;
    mappedPoints[2] = Point(maxLength - 1, maxLength - 1);
    originalPoints[3] = bottomLeft;
    mappedPoints[3] = Point(0, maxLength - 1);

    allignedImg = Mat(Size(maxLength, maxLength), CV_8UC1);
    warpPerspective(m_roiImg, allignedImg, cv::getPerspectiveTransform(originalPoints, mappedPoints), Size(maxLength, maxLength));
}

void ImageProcessing::m_drawEdges(const Vec2f& edge, Scalar rgb)
{
    if (edge[1] != 0)
    {
        float m = -(1 / tan(edge[1]));
        float c = (edge[0] / sin(edge[1]));

        line(m_roiImg, Point(0, c), Point(m_roiImg.size().width, m * m_roiImg.size().width + c), rgb, 2, CV_AA);
    }
    else
    {
        line(m_roiImg, Point(edge[0], 0), Point(edge[0], m_roiImg.size().height), rgb, 2, CV_AA);
    }
}

void ImageProcessing::m_extractSudoku(Mat img)
{
    Mat copy = img.clone();

    vector < vector<Point> > contours;
    vector <Vec4i> hierarchy;

    int largestContourIndex;

    findContours(copy, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    double maxContourArea = contourArea(contours[0], false);

    for (int i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]);

        if (area >= maxContourArea)
        {
            maxContourArea = area;
            largestContourIndex = i;
        }
    }

    Rect BoundingRect = boundingRect(contours[largestContourIndex]);
    m_roiImg = this->sudokuImg(BoundingRect);
}

