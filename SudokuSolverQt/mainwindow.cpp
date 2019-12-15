#include "Sudoku.h"
#include "ImageProcessing.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("SudokuSolver v1.0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSelectSudoku_clicked()
{
    sudokuPath = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "Images (*.jpg)");

    if(QString::compare(sudokuPath, QString()) != 0)
    {
        QImage image;
        bool valid = image.load((sudokuPath));

        if(valid)
        {
            ui->lblSudoku->setPixmap(QPixmap::fromImage(image));

            ui->lblStatus->setStyleSheet("QLabel { color : black; }");
            ui->lblStatus->setText("Sudoku loaded");
        }
    }
}

void MainWindow::on_btnSolveSudoku_clicked()
{
    ui->lblStatus->setStyleSheet("QLabel { color : orange; }");
    ui->lblStatus->setText("Solving Sudoku");

    Sudoku sudoku;

    //trainig image
    const string TRAINIMG = "train6.png";

    //set explicitly to true when you want to generate the training data for OCR
    bool blnGenOcr = false;

    //set explicitly to true when you want to Train the KNN algorithm
    //set this to true only when you have generated the data and copied it in the right folder
    bool blnTrainTest = false;
    OCR recognizeDigits;

    if (blnGenOcr == true)
    {
        //generate the OCR data
        recognizeDigits.GenerateOcrData(TRAINIMG);
    }

    if (blnTrainTest == true)
    {
        //recognizeDigits.Train();
    }

    //get the sudoku and do some image processing stuff
    sudoku.imgProcessing.getSudoku(sudokuPath.toUtf8().constData());
    sudoku.imgProcessing.processSudoku();
    sudoku.sendDigitsToOCR(sudoku.imgProcessing.sudokuGrid);

    bool blnSolved = sudoku.solveSudoku(sudoku.imgProcessing.sudokuGrid);

    if (blnSolved == true)
    {
        ui->lblStatus->setStyleSheet("QLabel { color : green; }");
        ui->lblStatus->setText("Sudoku solved!");
        sudoku.overlayResult(sudoku.imgProcessing.sudokuGrid);

        QImage imgIn= QImage((uchar*) sudoku.imgProcessing.allignedImg.data, sudoku.imgProcessing.allignedImg.cols, sudoku.imgProcessing.allignedImg.rows, sudoku.imgProcessing.allignedImg.step, QImage::Format_RGB888);
        ui->lblSudoku->setPixmap(QPixmap::fromImage(imgIn));
    }
    else
    {
        ui->lblStatus->setStyleSheet("QLabel { color : red; }");
        ui->lblStatus->setText("Sudoku can't be solved!");
    }
}
