
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>

#define XC1 300
#define XC2 400
#define XC3 250
#define XC4 350
#define XC5 450
#define XC6 300
#define XC7 400
#define YR1 100
#define YR2 250
#define YR3 400




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{


    QPainter painter(this);
    QPen pen;

    painter.setBrush(Qt::green);
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);

    //Background
    painter.drawRect(QRect(0,0,800,600));

    painter.setBrush(Qt::white);
    //Row 1
    painter.drawRect(QRect(XC1,YR1,80,130));
    painter.drawRect(QRect(XC2,YR1,80,130));
    //Row 2
    painter.drawRect(QRect(XC3,YR2,80,130));
    painter.drawRect(QRect(XC4,YR2,80,130));
    painter.drawRect(QRect(XC5,YR2,80,130));
    //Row 3
    painter.drawRect(QRect(XC6,YR3,80,130));
    painter.drawRect(QRect(XC7,YR3,80,130));

    QPainter myellip(this);
    myellip.setPen(pen);
    pen.setWidth(2);

    //All circles C1
    myellip.setBrush(Qt::red);
    myellip.drawEllipse(QRect(XC1+5, YR1+10, 30, 30));
    myellip.setBrush(QColorConstants::Svg::orange);
    myellip.drawEllipse(QRect(XC1+45, YR1+10, 30, 30));
    myellip.setBrush(Qt::yellow);
    myellip.drawEllipse(QRect(XC1+5, YR1+50, 30, 30));
    myellip.setBrush(Qt::green);
    myellip.drawEllipse(QRect(XC1+45, YR1+50, 30, 30));
    myellip.setBrush(Qt::cyan);
    myellip.drawEllipse(QRect(XC1+5, YR1+90, 30, 30));
    myellip.setBrush(QColorConstants::Svg::purple);
    myellip.drawEllipse(QRect(XC1+45, YR1+90, 30, 30));

    //All circles C2
    myellip.setBrush(Qt::red);
    myellip.drawEllipse(QRect(XC2+5, YR1+10, 30, 30));
    myellip.setBrush(QColorConstants::Svg::orange);
    myellip.drawEllipse(QRect(XC2+45, YR1+10, 30, 30));
    myellip.setBrush(Qt::yellow);
    myellip.drawEllipse(QRect(XC2+5, YR1+50, 30, 30));
    myellip.setBrush(Qt::green);
    myellip.drawEllipse(QRect(XC2+45, YR1+50, 30, 30));
    myellip.setBrush(Qt::cyan);
    myellip.drawEllipse(QRect(XC2+5, YR1+90, 30, 30));
    myellip.setBrush(QColorConstants::Svg::purple);
    myellip.drawEllipse(QRect(XC2+45, YR1+90, 30, 30));

    //All circles C3
    myellip.setBrush(Qt::red);
    myellip.drawEllipse(QRect(XC3+5, YR2+10, 30, 30));
    myellip.setBrush(QColorConstants::Svg::orange);
    myellip.drawEllipse(QRect(XC3+45, YR2+10, 30, 30));
    myellip.setBrush(Qt::yellow);
    myellip.drawEllipse(QRect(XC3+5, YR2+50, 30, 30));
    myellip.setBrush(Qt::green);
    myellip.drawEllipse(QRect(XC3+45, YR2+50, 30, 30));
    myellip.setBrush(Qt::cyan);
    myellip.drawEllipse(QRect(XC3+5, YR2+90, 30, 30));
    myellip.setBrush(QColorConstants::Svg::purple);
    myellip.drawEllipse(QRect(XC3+45, YR2+90, 30, 30));

    //All circles C4
    myellip.setBrush(Qt::red);
    myellip.drawEllipse(QRect(XC4+5, YR2+10, 30, 30));
    myellip.setBrush(QColorConstants::Svg::orange);
    myellip.drawEllipse(QRect(XC4+45, YR2+10, 30, 30));
    myellip.setBrush(Qt::yellow);
    myellip.drawEllipse(QRect(XC4+5, YR2+50, 30, 30));
    myellip.setBrush(Qt::green);
    myellip.drawEllipse(QRect(XC4+45, YR2+50, 30, 30));
    myellip.setBrush(Qt::cyan);
    myellip.drawEllipse(QRect(XC4+5, YR2+90, 30, 30));
    myellip.setBrush(QColorConstants::Svg::purple);
    myellip.drawEllipse(QRect(XC4+45, YR2+90, 30, 30));

}
