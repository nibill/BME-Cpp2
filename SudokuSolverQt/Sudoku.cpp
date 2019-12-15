#include "Sudoku.h"
#include "ImageProcessing.h"

using namespace std;

// UNASSIGNED is used for empty cells in sudoku grid
#define UNASSIGNED 0

// N is used for the size of Sudoku grid.
// Size will be NxN
#define N 9

/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
bool Sudoku::solveSudoku(int grid[N][N])
{
    int row, col;

    // If there is no unassigned location,
    // we are done
    if (!m_findUnassignedLocation(grid, row, col))
    return true; // success!

    // consider digits 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        // if looks promising
        if (m_isSafe(grid, row, col, num))
        {
            // make tentative assignment
            grid[row][col] = num;

            // return, if success, yay!
            if (solveSudoku(grid))
                return true;

            // failure, unmake & try again
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; // this triggers backtracking
}

/* Searches the grid to find an entry that is
still unassigned. If found, the reference
parameters row, col will be set the location
that is unassigned, and true is returned.
If no unassigned entries remain, false is returned. */
bool Sudoku::m_findUnassignedLocation(int grid[N][N],
                            int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified row matches
the given number. */
bool Sudoku::m_usedInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified column
matches the given number. */
bool Sudoku::m_usedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether
an assigned entry within the specified 3x3 box
matches the given number. */
bool Sudoku::m_usedInBox(int grid[N][N], int boxStartRow,
               int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow]
                    [col + boxStartCol] == num)
                return true;
    return false;
}

/* Returns a boolean which indicates whether
it will be legal to assign num to the given
row, col location. */
bool Sudoku::m_isSafe(int grid[N][N], int row, int col, int num)
{
    /* Check if 'num' is not already placed in
    current row, current column and current 3x3 box */
    return !m_usedInRow(grid, row, num) &&
           !m_usedInCol(grid, col, num) &&
           !m_usedInBox(grid, row - row % 3 ,
                      col - col % 3, num) &&
            grid[row][col] == UNASSIGNED;
}

void Sudoku::m_preProcessCell()
{
    Mat newimg;
    Mat resizedNew;
    vector<vector<Point>>contours;
    vector<Vec4i>hierarchy;

    Mat cellClone = m_cell.clone();
    findContours(cellClone, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i++)
    {

        Rect rect = boundingRect(contours[i]);
        if (rect.x >= 2 && rect.x <= 22 && contourArea(contours[i]) >= 20/*&& rect.y >= 2 */)/*&& rect.y <= 18*/
        {
            newimg = m_cell(rect);
            resize(newimg, resizedNew, Size(20, 30));
            m_digit = m_ocr.Train(resizedNew);
        }
        else
        {
            resize(m_cell, resizedNew, Size(20, 30));
            imshow("problem", resizedNew);
        }
    }
}


void Sudoku::sendDigitsToOCR(int grid[N][N])
{
    int cellLength = floor(static_cast<float>(imgProcessing.allignedImg.size().width / 9));

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Rect rect = Rect((j * cellLength + 6), 6 + (i * cellLength), cellLength - 6, cellLength - 6);
            m_cell = Mat(imgProcessing.thresholdAllignedImg, rect);

            Moments moment = moments(m_cell, false);

            if (moment.m00 >= 1000) {
                m_preProcessCell();
                grid[i][j] = m_digit;
            }
            else
            {
                grid[i][j] = 0;
            }
        }
    }
}


void Sudoku::overlayResult(int grid[N][N])
{
	Mat Cell;

    int cellLength = floor((static_cast<float>(imgProcessing.allignedImg.size().width / 9)));

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
			Rect rect = Rect((j * cellLength + 6), 6 + (i * cellLength), cellLength - 6, cellLength - 6);
            Cell = Mat(imgProcessing.thresholdAllignedImg, rect);

			Moments moment = moments(Cell, false);
            if (moment.m00 >= 1000)
            {
				continue;
			}
            else
            {
				char digits[3];
                int overlayDigit = grid[i][j];

				sprintf(digits, "%d", overlayDigit);
                putText(imgProcessing.allignedImg, digits, Point(rect.x + 5, rect.y + 15), 1, 1.2, Scalar(255, 0, 0), 1, CV_AA);
			}
		}
	}
}
