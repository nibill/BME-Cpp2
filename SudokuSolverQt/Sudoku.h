#pragma once
#include "OCR.h"
#include "ImageProcessing.h"
//#include <string>

class Sudoku
{
public:
	//constructor
    //Sudoku();

    void sendDigitsToOCR(int grid[9][9]);
    void overlayResult(int grid[9][9]);
    void printGrid();
    bool solveSudoku(int grid[9][9]);
    ImageProcessing imgProcessing;

private:
    // backtracking algorithm used as solver
    // algorithm found at https://www.geeksforgeeks.org/sudoku-backtracking-7/
    bool m_isSafe(int grid[9][9], int row, int col, int num);
    bool m_findUnassignedLocation(int grid[9][9], int &row, int &col);
    bool m_usedInRow(int grid[9][9], int row, int num);
    bool m_usedInCol(int grid[9][9], int col, int num);
    bool m_usedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num);

    void m_preProcessCell();

    int m_digit;
    OCR m_ocr;
    Mat m_cell;
};

