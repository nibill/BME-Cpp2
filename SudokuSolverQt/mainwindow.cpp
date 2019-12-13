#include "Sudoku.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //trainig image
    const string trainImg = "train6.png";
    //sudoku img to be solved
    const string SudokuImg = "SudokuPaper.jpg";

    //set explicitly to true when you want to generate the training data for OCR
    bool blnGenOcr = false;

    //set explicitly to true when you want to Train the KNN algorithm
    //set this to true only when you have generated the data and copied it in the right folder
    bool blnTrainTest = false;
    OCR recognizeDigits;

    if (blnGenOcr == true)
    {
        //generate the OCR data
        recognizeDigits.GenerateOcrData(trainImg);
    }

    if (blnTrainTest == true)
    {
        //recognizeDigits.Train();
    }

    Sudoku sudoku;
    //get the sudoku and do some image processing stuff
    sudoku.getSudoku(SudokuImg);
    sudoku.processSudoku();
    sudoku.printInputSudoku();
    sudoku.sendDigitsToOCR();

    bool blnSolved = sudoku.SolveSudoku();

    if (blnSolved == true)
    {
        sudoku.PrintGrid();
        sudoku.overlayResult();
    }
    else
    {
        cout << "Sudoku can't be Solved!\n";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}





