#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::plotData(QCustomPlot *widget,std::function<double(int)> &function){

    widget->setInteraction( QCP :: iRangeDrag , true );
    widget->setInteraction( QCP :: iRangeZoom , true );
    connect (widget , SIGNAL ( mouseDoubleClick ( QMouseEvent *)),
    widget , SLOT ( rescaleAxes ()) );
    // Add Graph and s e t some p r o p e r t i e s
    widget->addGraph();
    widget->xAxis->setLabel("X");
    widget->yAxis->setLabel("Y");
    widget->xAxis->grid () -> setSubGridVisible ( true );
    //Cr e a t e data : f ( x ) = x^2
    std :: vector < double > X (101) ;
    std :: iota (X. begin () ,X. end () , -50);
    std :: vector < double > Y (101) ;
    std :: transform (X. begin () ,X. end () ,
    Y.begin() ,function(x);
    // Pl o t data
    ui-> qcpwidget->graph(0)->setData( QVector < double >:: fromStdVector (X),
    QVector < double >:: fromStdVector(Y));
    //
    ui->qcpwidget->rescaleAxes ();
    ui->qcpwidget->replot ();
}
