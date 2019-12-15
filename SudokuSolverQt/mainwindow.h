#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString sudokuPath;

private slots:

    void on_btnSelectSudoku_clicked();
    void on_btnSolveSudoku_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
