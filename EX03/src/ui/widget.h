#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void plotData (QCustomPlot *widget,std::function<double(int)> &function);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
