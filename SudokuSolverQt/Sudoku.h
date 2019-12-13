#pragma once
#include "OCR.h"
//#include <string>

class Sudoku
{
public:
	//constructor
	Sudoku();

	//grab the sudoku image
	void getSudoku(string imgName);
    void processSudoku();
    void sendDigitsToOCR();
	void printInputSudoku();
	void overlayResult();
    void PrintGrid();

    bool SolveSudoku();
private:

	OCR _ocr;
	int _Digit;
	int _sudokuDigits[9][9];

	void _threshold(Mat& img, Mat& threshimg);
	void _findHoughLines(Mat img, vector <Vec2f>& Lines);
	void _mergeHoughLines(vector <Vec2f>* lines);
	void _drawLines(vector <Vec2f>& lines);
	void _allignSudoku(const vector <Vec2f>& lines);
	void _drawEdges(const Vec2f& edge, Scalar rgb);
	void _preProcessCell();
	void _extractSudoku(Mat img);

	string _sudokuImgName;

	Mat _threshROISudoku;
	Mat _Sudoku;
	Mat _cannySudoku;
	Mat _threshSudoku;
	Mat _graySudoku;
	Mat _blurrSudoku;
	Mat _ROISudoku;
	Mat _allignedSudoku;
	Mat _threshAllignedSudoku;
	Mat _cell;

    // backtracking algorithm used as solver
    // algorithm found at https://www.geeksforgeeks.org/sudoku-backtracking-7/
    bool IsSafe(int row, int col, int num);
    bool FindUnassignedLocation(int &row, int &col);
    bool UsedInRow(int row, int num);
    bool UsedInCol(int col, int num);
    bool UsedInBox(int boxStartRow, int boxStartCol, int num);



};

